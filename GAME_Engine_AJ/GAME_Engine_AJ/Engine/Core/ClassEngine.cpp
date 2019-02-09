#include "ClassEngine.h"

std::unique_ptr<ClassEngine> ClassEngine::engineInstance = nullptr;


ClassEngine::ClassEngine() : window(nullptr), isRunning(false), fps(120)
{
	
}


ClassEngine::~ClassEngine()
{
	Shutdown();
}

ClassEngine* ClassEngine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new ClassEngine);
	}
	return engineInstance.get();
}


bool ClassEngine::Initialize(std::string name_, int width_, int height_) {
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();

	if (!window->Initialize(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", __FILE__, __LINE__);
		std::cout << "Window Failed to initialize" << std::endl;
		//Shutdown();
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), 
		window->GetWidth() / 2, 
		window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl",
		"Engine/Shaders/ColourFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("baseShader", 
		"Engine/Shaders/VertexShader.glsl", 
		"Engine/Shaders/FragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->Initialize()) {
			Debug::FatalError("Failed to initialize game interface", __FILE__, __LINE__);
			return isRunning = false;
		}
	}
	Debug::Info("Everything Good", __FILE__, __LINE__);
		

	timer.Start();

	return isRunning = true;
}

void ClassEngine::Run() {
	while (isRunning) {
		EventListener::Update();
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime()); //60 fps
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	if (!isRunning) {
		Shutdown();
	}
}

bool ClassEngine::GetIsRunning() {
	return isRunning; 

}

void ClassEngine::Update(const float deltaTime_) {
	//std::cout << "Delta Time: " << deltaTime_ << std::endl;
	if (gameInterface) {
		gameInterface->Update(deltaTime_);

	}
}

void ClassEngine::Render() {

	//This is where you change the color.
	// 0 0 0 1 is TriHard
	// 1 1 1 1 is white
	glClearColor(0.0f, 3.0f, 5.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInterface) {
		gameInterface->Render();
	}

	//CALL GAME RENDER

	SDL_GL_SwapWindow(window->GetWindow());
}

void ClassEngine::Shutdown() {
	//window->Shutdown();

	delete window;
	window = nullptr;

	delete gameInterface;
	gameInterface = nullptr;

	SDL_Quit();
	exit(0);
}

void ClassEngine::SetGameInterface(GameInterface* gameInterface_) {
	
	gameInterface = gameInterface_;

}

glm::vec2 ClassEngine::GetScreenSize() const {
	return glm::vec2(window->GetWidth(),
		window->GetHeight());
}

void ClassEngine::NotifyOfMousePressed(int x_, int y_){

}

void ClassEngine::NotifyOfMouseReleased(int x_, int y_, int buttonType_){

}

void ClassEngine::NotifyOfMouseMove(int x_, int y_){
	Camera::GetInstance()->ProcessMouseMovement(
		MouseEventListener::GetMouseOffset().x,
		MouseEventListener::GetMouseOffset().y
	);
}

void ClassEngine::NotifyOfMouseScroll(int y_){
	Camera::GetInstance()->ProcessMouseZoom(y_);
}

void ClassEngine::ExitGame(){
	isRunning = false;
}
