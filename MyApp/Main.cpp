#include "Engine.h" 
#include <iostream> 

#define POST_PROCESS 

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

	// Create Framebuffer Texture
	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(1024, 1024); //(64, 64) Pixel Effect/ (1024,1024) Color Effects/ Regular (512,512)
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);

	// Create Framebuffer
	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();


	// Load Scene 
	auto scene = neu::g_resources.Get<neu::Scene>("scenes/rtt.scn");

	glm::vec3 rot{ 0, 0, 0 };
	float interpolation = 0.5f;
	float refractiveIndex = 1.0f;
	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

		auto actor1 = scene->GetActorFromName <neu::Actor>("Ogre");
		auto actor2 = scene->GetActorFromName <neu::Actor>("RTT");

		if (actor1)
		{
			actor1->m_transform.rotation = Math::EulerToQuaternion(rot);
		}

		actor1 = scene->GetActorFromName("Light");
		if (actor1)
		{
			// move light using sin wave 
			//actor1->m_transform.position = os;
		}

// -----------------------------------------------------------------------------------------------------------
		
		// Wave Effect
		/*auto program1 = neu::g_resources.Get<neu::Program>("shaders/postprocess/postprocess.prog");
		if (program1)
		{
			program1->Use();
			program1->SetUniform("offset", neu::g_time.time);
		}*/

// -----------------------------------------------------------------------------------------------------------

		auto program = neu::g_resources.Get<neu::Program>("shaders/fx/reflection_refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("Interpolation", interpolation);
			program->SetUniform("RI", refractiveIndex);
		}


		ImGui::Begin("Transform");
		ImGui::Button("Press Me");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("RI", &refractiveIndex, 0.01f, 1, 3);
		ImGui::DragFloat("Interpolation", &interpolation, 0.01f, 0, 1);
		ImGui::End();

		scene->Update();

#ifdef POST_PROCESS 
		// don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (render scene to framebuffer) 
		neu::g_renderer.SetViewport(0, 0, framebuffer -> GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(neu::g_renderer);
			}
		}
#else 
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
#endif // POST_PROCESS 

		// Renderer Pass 1 (Render to framebuffer)
		//neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		//framebuffer->Bind();

		//neu::g_renderer.BeginFrame();

		//scene->PreRender(neu::g_renderer);
		//scene->Render(neu::g_renderer);
		//framebuffer->Unbind();

		//// Render Pass 2 (Render to screen)
		//neu::g_renderer.RestoreViewport();
		//neu::g_renderer.BeginFrame();

		//scene->PreRender(neu::g_renderer);
		//scene->Render(neu::g_renderer);
		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();

	}
	return 0;

	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
}