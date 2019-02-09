#include "Game.h"



Game::Game()
{
}


Game::~Game()
{

}


bool Game::Initialize() {

	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 2.0f, 6.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(
		glm::vec3(0.0f, 0.0f, 2.0f),
		0.1f, 0.5f,
		glm::vec3(1.0f, 1.0f, 1.0f)
	));
	Model* apple = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));
	SceneGraph::GetInstance()->AddModel(apple);

	Model* dice = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));
	SceneGraph::GetInstance()->AddModel(dice);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(apple), "apple1");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(dice, glm::vec3(3.0f, 0.0f, 0.0f)));


	SceneGraph::GetInstance()->GetGameObject("apple1")->SetScale(glm::vec3(0.5f));
	std::cout << "object's bounding box: " << std::endl;
	std::cout << "Min Vert: " << glm::to_string(SceneGraph::GetInstance()->GetGameObject("apple1")->GetBoundingBox().minVert) << std::endl;
	std::cout << "Max Vert: " << glm::to_string(SceneGraph::GetInstance()->GetGameObject("apple1")->GetBoundingBox().maxVert) << std::endl;

	return true;
}

void Game::Update(const float deltaTime_) {
	//std::cout << "Game's Update" << std::endl;
	//object1->SetAngle(object1->GetAngle() + 0.050f);
	SceneGraph::GetInstance()->Update(deltaTime_);
	
}

void Game::Render() {

	SceneGraph::GetInstance()->Render(Camera::GetInstance());
}