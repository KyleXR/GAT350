#include "Engine.h" 
#include <iostream> 


int main(int argc, char** argv)
{
	LOG("Application Started...");
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Inialized...");

	neu::g_renderer.CreateWindow("Neumont", 800, 600, false);
	LOG("Window Initialized...");

	// Load Scene 
	auto scene = neu::g_resources.Get<neu::Scene>("scenes/texture.scn");


	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

		auto actor = scene->GetActorFromName <neu::Actor>("Ogre");

		if (actor)
		{
			actor->m_transform.rotation.y += neu::g_time.deltaTime * 90.0f;
		}

		auto material = neu::g_resources.Get<neu::Material>("Materials/multi.mtrl");
		if (material)
		{
			material->uv_offset.x += neu::g_time.deltaTime;
		}

		scene->Update();

		neu::g_renderer.BeginFrame();


		scene->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();

	}
	return 0;

	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
}