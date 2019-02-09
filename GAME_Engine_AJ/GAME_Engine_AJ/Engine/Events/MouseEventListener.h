#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

#include <SDL.h>
#include <glm/glm.hpp>

class ClassEngine; //Tells the compiler theres a class called ClassEngine and that it exist.



class MouseEventListener
{
public:

	MouseEventListener() = delete;
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator = (const MouseEventListener&) = delete;
	MouseEventListener& operator = (MouseEventListener&&) = delete;
	~MouseEventListener();

	//click on thingy then Ctrl .
	static void RegisterEngineObject(ClassEngine* engine_);
	static void Update(SDL_Event e_);

	static void NotifyOfMousePressed(int buttonType_);  //Takes in what button was pressed.
	static void NotifyOfMouseReleased(int buttonType_); // Takes in what button was released.
	static void NotifyOfMouseMove();					//Dont need a buttontype for movement.
	static void NotifyOfMouseScroll(int y_);			//In what direction we scroll.

	static glm::vec2 GetPreviousMousePosition(); 
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetMouseOffset();

private:

	static ClassEngine* engineInstance; 
	static int mouseX, mouseY, prevMouseX, prevMouseY;
	static bool firstUpdate;
	static void UpdateMousePosition(); 

};


#endif // !MOUSEEVENTLISTENER_H
