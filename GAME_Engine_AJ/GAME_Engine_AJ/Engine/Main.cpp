#include "Core\ClassEngine.h"
#include "..\Game\Game.h"

int main(int arg, char* argv[]) {

	ClassEngine::GetInstance()->SetGameInterface(new Game());



	//VERSION 1 destructor or have shutdown in public
	/*if (!ClassEngine::GetInstance()->Initialize("GAME301 Engine", 800, 600)) {
		std::cout << "Engine Failed to Initialize " << std::endl;
		ClassEngine::GetInstance()->Shutdown();
		return 0;
	}*/

	//VERSION 2 shutdown stay in private
	ClassEngine::GetInstance()->Initialize("GAME301 Engine", 800, 600);
	
	ClassEngine::GetInstance()->Run();
	
	return 0;
}