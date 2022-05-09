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
		return;
	}

	// init world
	std::shared_ptr<Material> world_mat = mp_engine->CreateMaterial(TSHADER::NO_TEXTURE);
	std::shared_ptr<GameObject> world = mp_engine->CreateGameObject();

	ChunkManager chunk_manager(world, world_mat, mp_engine->GetMainCamera());
	chunk_manager.CreateWorld();

	glm::vec3 lposition = { 50.0f, 10.0f, 0.0f };

	// create global lighting
	std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>();
	light->ambient_strength = 0.2f;
	light->diffuse_strength = 0.7f;
	light->specular_strength = 0.2f;
	light->color = glm::vec3(1.0f, 1.0f, 1.0f);
	light->position = lposition;
	light->direction = glm::normalize(light->position - glm::vec3(.0f, .0f, .0f));

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	mp_engine->setScene(scene);
	scene->AddGameObject(world);
	scene->AddLight(light);

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
		chunk_manager.UpdateWorld(scene, mp_engine->GetMainCamera());

		mp_engine->update();
		mp_engine->draw();
	} while (!mp_engine->shouldClose());
}
