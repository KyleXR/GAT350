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

	neu::g_gui.Initialize(neu::g_renderer);

	// Load Scene 
	auto scene = neu::g_resources.Get<neu::Scene>("scenes/texture.scn");

	glm::vec3 pos{ 0, 0, 0 };

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

		auto actor1 = scene->GetActorFromName <neu::Actor>("Ogre");
		auto actor2 = scene->GetActorFromName <neu::Actor>("Rock");

		/*if (actor1)
		{
			actor1->m_transform.rotation.y += neu::g_time.deltaTime * 90.0f;
		}*/

		actor1 = scene->GetActorFromName("Light");
		if (actor1)
		{
			// move light using sin wave 
			actor1->m_transform.position = pos;
		}

		ImGui::Begin("Hello");
		ImGui::Button("Press Me");
		ImGui::SliderFloat3("Position", &pos[0], -5.0f, 5.0f);
		ImGui::End();

		scene->Update();

		neu::g_renderer.BeginFrame();


		scene->Draw(neu::g_renderer);
		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();

	}
	return 0;

	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
}