#ifndef GAME_H
#define GAME_H


#include "../Engine/Core/ClassEngine.h"
#include <glm/gtx/string_cast.hpp>


//You want your game to inherit from Gameinterface.h
class Game : public GameInterface 
{


public:
	Game();
	virtual ~Game();

	virtual bool Initialize();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:
	

};

#endif //! GAME_H