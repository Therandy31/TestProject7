#pragma once
#include "main.hpp"
#include "CEventManager.hpp"
#include "CSDLManager.hpp"

class CSession : public IEventable {
private:
	CEventManager *eventManager;
	CSDLManager *sdlManager;
	
	int iFrameStart;
	int iFrameEnd;
	int iFrameDelay;

	bool bRunning;

public:
	CSession();

	void run();
	void drawScene();

	void notify(IEvent *e);
};