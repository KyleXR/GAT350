#pragma once
#include "Actor.h"
#include "Resource/Resource.h"
#include <list>
#include <memory>

namespace neu
{
	// Forward Declaration
	class Actor;
	class Renderer;
	class Game;

	class Scene : public GameObject, public ISerializable, public Resource
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game{ game } {}
		Scene(const Scene& other) {}
		~Scene() = default;


		CLASS_DECLARATION(Scene)

		void Initialize() override;
		void Update() override; 

		void PreRender(Renderer& renderer);
		void Render(Renderer& renderer);

		virtual bool Create(const std::string name, ...) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* GetActorFromName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsFromTag(const std::string& tag);

		Game* GetGame() { return m_game; }

	private:
		Game* m_game;
		std::list<std::unique_ptr<Actor>> m_actors;

		

		// Inherited via Resource

	};
	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;

		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorFromName(const std::string& name)
	{
		for( auto& m_actor : m_actors)
		{
			if (name == m_actor->GetName())
				{
				 return dynamic_cast<T*>(m_actor.get()); 
				}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsFromTag(const std::string& tag)
	{
		std::vector<T*> result;

		for (auto& m_actor : m_actors)
		{
			if (m_actor->GetName() == m_actors->GetName())
			{
				 T * tagActor = dynamic_cast<T*>(m_actor.get()); 
				 if (tagActor) result.push_back(tagActor);					 
			}
		}

		return result;
	}
}