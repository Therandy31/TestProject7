#include "main.hpp"
#include "CEventManager.hpp"
#include "CSDLManager.hpp"
#include "CGLShaderManager.hpp"
#include "CGLBufferManager.hpp"
#include "CSession.hpp"

int main(int argc, char **argv) {
	CEventManager *eventManager = CEventManager::instance();
	CSDLManager *sdlManager = CSDLManager::instance();
	CGLShaderManager *glShaderManager = CGLShaderManager::instance();
	CGLBufferManager *glBufferManager = CGLBufferManager::instance();
	CSession *session = new CSession;

	session->run();

	return 0;
}