#include "Scene.h"
#include "Framework/Factory.h"
#include "Engine.h"
#include <algorithm>
#include <iostream>

namespace neu
{
	void Scene::Initialize()
	{
		for (auto& actor : m_actors) { actor->Initialize(); }
	}
	void neu::Scene::Update()
	{
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(*iter)->Update();
			if ((*iter)->m_destroy)
			{
				iter = m_actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		// get camera / set renderer view/projection 
		auto camera = GetActorFromName("Camera");
		if (camera)
		{
			g_renderer.SetView(camera->GetComponent<CameraComponent>() -> GetView());
			g_renderer.SetProjection(camera->GetComponent<CameraComponent>() -> GetProjection());
		}

		// draw actors 
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		for (auto& actor : m_actors) { actor->SetDestroy(); }

		m_actors.clear();
	}

	bool Scene::Create(const std::string name, ...)
	{
		rapidjson::Document document;
		bool success = neu::json::Load("scenes/basic.scn", document);
		if (!success)
		{
			LOG("error loading scene file %s.", "scenes/basic.scn");
		}
		else
		{
			Read(document);
			Initialize();
		}
		return true;
	}

	bool Scene::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Scene::Read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") || !value["actors"].IsArray()) return false;

		// Read Actors
		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor)
			{
				// Read Actor
				actor->Read(actorValue);
				bool prefab = false;
				READ_DATA(actorValue, prefab);
				if (prefab)
				{
					std::string name = actor->GetName();
					Factory::Instance().RegisterPreFab(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));

				}
			}
		}

		return true;
	}

}
