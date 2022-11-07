#include "Engine.h"

namespace neu
{
	Renderer g_renderer;
	InputSystem g_inputSystem;
	Time g_time;
	AudioSystem g_audioSystem;
	ResourceManager g_resources;
	PhysicsSystem g_physicsSystem;
	EventManager g_eventManager;


	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(TextComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(RBPhysicsComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(SpriteAnimComponent);
		REGISTER_CLASS(TilemapComponent);
		REGISTER_CLASS(CameraComponent);
		REGISTER_CLASS(CameraController);
		REGISTER_CLASS(LightComponent);
	}

	void Engine::Initialize()
	{
		g_renderer.Initialized();
		g_inputSystem.Initialized();
		g_audioSystem.Initialize();
		g_resources.Initialize();
		g_physicsSystem.Initialize();
		g_eventManager.Initialize();
	}

	void Engine::Update()
	{
		g_time.Tick();
		g_eventManager.Update();
		g_physicsSystem.Update();
		g_inputSystem.Update();
		g_audioSystem.Update();
	}

	void Engine::Shutdown()
	{
		Factory::Instance().Shutdown();

		g_eventManager.Shutdown();
		g_physicsSystem.Shutdown();
		g_resources.Shutdown();
		g_inputSystem.Shutdown();
		g_audioSystem.Shutdown();
		g_renderer.Shutdown();
	}
}