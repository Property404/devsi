#include "platform_config.h"
#include <iostream>
#include "devsi_mouse.h"
namespace Devsi{
/* Platform independent whatnots */
int Mouse::getX(){
	return this->getPosition().first;
}
int Mouse::getY(){
	return this->getPosition().second;
}
void Mouse::shift(int x, int y){
	std::pair<int, int> point = this->getPosition();
	this->setPosition(point.first+x,point.second+y);
}

void Mouse::validateButton(int button){
	if(button!=Mouse::LEFT_BUTTON &&  button!=Mouse::RIGHT_BUTTON && button != Mouse::MIDDLE_BUTTON){
		throw NoSuchMouseButtonException();
	}
}
void Mouse::clickUp(int button){
	this->clickPartial(false, button);
}
void Mouse::clickDown(int button){
	this->clickPartial(true, button);
}

/* Platform dependent whatnots */
#ifdef DEVSI_MACOS
Mouse::Mouse(){
}
void Mouse::setPosition(int x, int y){
	CGEventRef mouseEv = CGEventCreateMouseEvent(
		NULL, kCGEventMouseMoved,
		CGPointMake(x, y),
		kCGMouseButtonLeft);
	CGEventPost(kCGHIDEventTap, mouseEv);
	CFRelease(mouseEv);
}
std::pair<int,int> Mouse::getPosition(){
	CGEventRef event = CGEventCreate(NULL);
	CGPoint cursor = CGEventGetLocation(event);
	CFRelease(event);
	return std::pair<int,int>(int(cursor.x), int(cursor.y));
}
void Mouse::clickPartial(bool down, int button){
	// Arrays allow for this single generic function
	CGEventType ups[] = {kCGEventLeftMouseUp,kCGEventRightMouseUp,kCGEventOtherMouseUp};
	CGEventType downs[] = {kCGEventLeftMouseDown,kCGEventRightMouseDown,kCGEventOtherMouseDown};
	CGMouseButton buttons[] = {kCGMouseButtonLeft, kCGMouseButtonRight,kCGMouseButtonCenter};
	
	// Make sure the button is valid
	validateButton(button);

	//Alright, soldier, let's click
	std::pair<int,int> point = this->getPosition();
	CGEventRef mouseEv = CGEventCreateMouseEvent(
		NULL, (down?downs:ups)[button-1],CGPointMake(point.first,point.second), buttons[button-1]);
	CGEventPost(kCGHIDEventTap, mouseEv);
	CFRelease(mouseEv);
}
void Mouse::click(int button){
	// Arrays allow for this single generic function
	CGEventType ups[] = {kCGEventLeftMouseUp,kCGEventRightMouseUp,kCGEventOtherMouseUp};
	CGEventType downs[] = {kCGEventLeftMouseDown,kCGEventRightMouseDown,kCGEventOtherMouseDown};
	CGMouseButton buttons[] = {kCGMouseButtonLeft, kCGMouseButtonRight,kCGMouseButtonCenter};
	
	// Make sure the button is valid
	validateButton(button);

	//Alright, soldier, let's click
	std::pair<int,int> point = this->getPosition();
	CGEventRef mouseEv = CGEventCreateMouseEvent(
		NULL, downs[button-1],CGPointMake(point.first,point.second), buttons[button-1]);
	CGEventPost(kCGHIDEventTap, mouseEv);
	CGEventSetType(mouseEv, ups[button-1]);
	CGEventPost(kCGHIDEventTap, mouseEv);
	CFRelease(mouseEv);
}
#elif DEVSI_X11
Mouse::Mouse(){
	// X11 setup
	if((this->display = XOpenDisplay(NULL)) == NULL){
		throw  X11Exception();
	}

	root = DefaultRootWindow(display);
	Screen* pscr = DefaultScreenOfDisplay(displa);
	this->displayX = pscr->width;
	this->displayY = pscr->height;
}
void Mouse::setPosition(int x, int y){
	XWarpPointeR(display, None, root, 0,0,0,0,x,y);
	XFlush(display);
	
	XEvent event;
	memset(&event, 0, sizeof(event));
}
void Mouse::clickPartial(bool down, int button){
	XTestFakeButtonDisplay(display, button, down, CurrentTime);
	XFlush(display);
}
void Mouse::click(int button){
	this->mouseDown(button);
	usleep(100);

	this->mouseUp(button);
}
		
#endif
}
