#pragma once
#include "main.hpp"
#include "CEventManager.hpp"

class CSDLManager : public IEventable {
private:
	int displayWidth;
	int displayHeight;
	bool displayFullscreen;

	SDL_Window *sdlWindow;
	SDL_GLContext glContext;
	CSDLManager();

public:
	~CSDLManager();

	void windowResize(int width, int height);
	void swapBuffers();
	void sdlEventHandle();

	int getDisplayWidth() { return displayWidth; }
	int getDisplayHeight() { return displayHeight; }
	bool getDisplayFullscreen() { return displayFullscreen; }

	void notify(IEvent *e);
	static CSDLManager *instance();
};

class CSDLManagerEVENTQuit : public IEvent {
public:
	CSDLManagerEVENTQuit() {
		type = "event_sdlmanager_quit";
	}
};

class CSDLManagerEVENTKeyDown : public IEvent {
private:
	int key;
public:
	CSDLManagerEVENTKeyDown(int key) {
		type = "event_sdlmanager_keydown";
		this->key = key;
	}
	int getKey() { return key; }
};

class CSDLManagerEVENTKeyUp : public IEvent {
private:
	int key;
public:
	CSDLManagerEVENTKeyUp(int key) {
		type = "event_sdlmanager_keyup";
		this->key = key;
	}
	int getKey() { return key; }
};

class CSDLManagerEVENTMouseMotion : public IEvent {
private:
	int x, y, xrel, yrel;
public:
	CSDLManagerEVENTMouseMotion(int x, int y, int xrel, int yrel) {
		type = "events_sdlmanager_mousemotion";
		this->x = x;
		this->y = y;
		this->xrel = xrel;
		this->yrel = yrel;
	}
	int getX() { return x; }
	int getY() { return y; }
	int getXRel() { return xrel; }
	int getYRel() { return yrel; }
};

class CSDLManagerEVENTMouseButtonDown : public IEvent {
private:
	int button;
public:
	CSDLManagerEVENTMouseButtonDown(int button) {
		type = "event_sdlmanager_mousebuttondown";
		this->button = button;
	}
	int getButton() { return button; }
};

class CSDLManagerEVENTMouseButtonUp : public IEvent {
private:
	int button;
public:
	CSDLManagerEVENTMouseButtonUp(int button) {
		type = "event_sdlmanager_mousebuttonup";
		this->button = button;
	}
	int getButton() { return button; }
};

class CSDLManagerEVENTWindowEventResize : public IEvent {
private:
	int width, height;
public:
	CSDLManagerEVENTWindowEventResize(int width, int height) {
		type = "event_sdlmanager_windoweventresize";
		this->width = width;
		this->height = height;
	}
	int getWidth() { return width; }
	int getHeight() { return height; }
};