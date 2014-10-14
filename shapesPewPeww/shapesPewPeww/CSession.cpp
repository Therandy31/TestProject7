#include "CSession.hpp"

CSession::CSession() {
	eventManager = CEventManager::instance();
	sdlManager = CSDLManager::instance();

	iFrameDelay = 16;
	bRunning = true;

	eventManager->subscribe(this);
}

void CSession::run() {
	while (bRunning) {
		iFrameStart = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sdlManager->sdlEventHandle();

		// Do stuff here.

		sdlManager->swapBuffers();
		iFrameEnd = SDL_GetTicks();
		if (iFrameDelay - (iFrameEnd - iFrameStart) > 0) {
			SDL_Delay(iFrameDelay - (iFrameEnd - iFrameStart));
		}
		iFrameDelay = iFrameEnd - iFrameStart;
		iFrameDelay = iFrameDelay < 16 ? 16 : iFrameDelay;
	}
}

void CSession::drawScene() {
	// Do nothing for now.
}

void CSession::notify(IEvent *e) {
	if (e->compareType("event_sdlmanager_quit")) {
		bRunning = false;
	}
}