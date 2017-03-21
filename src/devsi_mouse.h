#pragma once
#include <utility>
#include <exception>
#include "devsi_device.h"
namespace Devsi {
	class Mouse : Device{
	/* Make sure button is an actual button - else throw error */
	void validateButton(int button);

	/* Private primer for clickUp and clickDown */
	void clickPartial(int down, int button);
	/*Platform specifics */
	#ifdef DEVSI_X11
	Display *display;
	Window root;
	XEvent event;
	size_t displayX;
	size_t displayY;
	#endif
	public:
	Mouse();
	// get and set absolute position of mouse
	void setPosition(int x, int y);
	std::pair<int,int> getPosition();
	int getX();
	int getY();

	// Change relative position
	void shift(int x, int y);

	// Clicksand partial clicks - argument takes LEFT, RIGHT, MIDDLE, etc
	// throw error upon invalid argument
	void click(int);
	void doubleClick(int);
	void clickUp(int);
	void clickDown(int);

	// Scrolling (mouse wheel)
	void scrollX(int);
	void scrollY(int);

	// Static shit
	static const int LEFT_BUTTON = 1;
	static const int RIGHT_BUTTON = 2;
	static const int MIDDLE_BUTTON = 3;
	};

	// Mouse specific exceptions
	class NoSuchMouseButtonException: public std::exception{
		virtual const char* what() const throw(){
			return "Error - no such mouse button";
		}
	};
}
