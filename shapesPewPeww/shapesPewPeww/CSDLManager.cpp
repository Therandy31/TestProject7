#include "CSDLManager.hpp"

CSDLManager::CSDLManager() {
	SDL_Init(SDL_INIT_EVERYTHING);

	sdlWindow = 0;
	windowResize(800, 600);

	std::clog << "[INFO] <CSDLManager>: Instance created." << std::endl;
	CEventManager::instance()->subscribe(this);
}

CSDLManager::~CSDLManager() {
	if (sdlWindow) {
		SDL_DestroyWindow(sdlWindow);
		SDL_GL_DeleteContext(glContext);
	}
}

void CSDLManager::windowResize(int width, int height) {
	displayWidth = width < 320 ? 320 : width;
	displayHeight = height < 240 ? 240 : height;

	if (sdlWindow) {
		SDL_SetWindowSize(sdlWindow, displayWidth, displayHeight);
	}
	else {
		sdlWindow = SDL_CreateWindow("newProject", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, displayWidth, displayHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		glContext = SDL_GL_CreateContext(sdlWindow);
	}
}

void CSDLManager::swapBuffers()  {
	SDL_GL_SwapWindow(sdlWindow);
}

void CSDLManager::sdlEventHandle() {
	CEventManager *eventManager = CEventManager::instance();
	SDL_Event sdle;
	int key = 0;
	int width, height;
	int x, y, xrel, yrel;
	int button;

	while (SDL_PollEvent(&sdle)) {
		switch (sdle.type) {
		case SDL_QUIT:
			eventManager->post(&CSDLManagerEVENTQuit());
			break;
		case SDL_KEYDOWN:
			key = sdle.key.keysym.sym;
			eventManager->post(&CSDLManagerEVENTKeyDown(key));
			break;
		case SDL_KEYUP:
			key = sdle.key.keysym.sym;
			eventManager->post(&CSDLManagerEVENTKeyUp(key));
			break;
		case SDL_MOUSEMOTION:
			x = sdle.motion.x;
			y = sdle.motion.y;
			xrel = sdle.motion.xrel;
			yrel = sdle.motion.yrel;
			eventManager->post(&CSDLManagerEVENTMouseMotion(x, y, xrel, yrel));
			break;
		case SDL_MOUSEBUTTONDOWN:
			button = sdle.button.button;
			eventManager->post(&CSDLManagerEVENTMouseButtonDown(button));
			break;
		case SDL_MOUSEBUTTONUP:
			button = sdle.button.button;
			eventManager->post(&CSDLManagerEVENTMouseButtonUp(button));
			break;
		case SDL_WINDOWEVENT:
			switch (sdle.window.event) {
			case  SDL_WINDOWEVENT_RESIZED:
				displayWidth = sdle.window.data1;
				displayHeight = sdle.window.data2;
				displayWidth = displayWidth < 320 ? 320 : displayWidth;
				displayHeight = displayHeight < 240 ? 240 : displayHeight;
				windowResize(displayWidth, displayHeight);
				eventManager->post(&CSDLManagerEVENTWindowEventResize(displayWidth, displayHeight));
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void CSDLManager::notify(IEvent *e) {

}

CSDLManager *CSDLManager::instance() {
	static CSDLManager *inst = 0;
	if (!inst) {
		inst = new CSDLManager();
	}
	return inst;
}