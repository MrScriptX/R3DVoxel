#include "Application.h"

Application::Application()
{
}

void Application::Start()
{
	try
	{
		mp_engine = std::make_unique<Engine>(1920, 1080);
		Logger::init();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::shared_ptr<Material> world_mat = mp_engine->CreateMaterial(TSHADER::NO_TEXTURE);
	std::shared_ptr<GameObject> world = mp_engine->CreateGameObject();

	ChunkManager chunk_manager(world, world_mat);
	chunk_manager.InitWorld();

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	mp_engine->setScene(scene);
	scene->AddGameObject(world);

	std::function<void()> wireframemode = [this]() {
		mp_engine->SetWireframeMode();
	};
	mp_engine->BindKeyToFunc(GLFW_KEY_Q, wireframemode, ActionType::R3D_PRESS);

	std::function<void()> fillmode = [this]() {
		mp_engine->SetFillMode();
	};
	mp_engine->BindKeyToFunc(GLFW_KEY_E, fillmode, ActionType::R3D_PRESS);

	do
	{
		//chunk_manager.UpdateWorld(scene, mp_engine->GetMainCamera());

		mp_engine->update();
		mp_engine->draw();
	} while (!mp_engine->shouldClose());
}
