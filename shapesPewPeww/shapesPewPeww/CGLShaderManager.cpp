#include "CGLShaderManager.hpp"

CGLShaderManager::CGLShaderManager() {
	clog << "[INFO] <CGLShaderManager>: Instance created." << endl;
}

CGLShader *CGLShaderManager::get(string name) {
	if (exist(name)) {
		return shaderList[name];
	}
	else {
		bool bCreateSuccess = load(name);
		if (bCreateSuccess) {
			return shaderList[name];
		}
	}
	return NULL;
}

bool CGLShaderManager::exist(string name) {
	if (shaderList.count(name)) {
		return true;
	}
	return false;
}

bool CGLShaderManager::load(string name) {
	string vertexFile = "assets/shaders/";
	string fragmentFile = "assets/shaders/";

	vertexFile.append(name);
	vertexFile.append("_vs.glsl");
	fragmentFile.append(name);
	fragmentFile.append("_fs.glsl");

	CGLShader *shader = new CGLShader();
	shader->loadVertexSourceFromFile(vertexFile);
	shader->loadFragmentSourceFromFile(fragmentFile);
	
	bool bCreateSuccess = shader->buildShader();
	if (bCreateSuccess) {
		shaderList[name] = shader;
		return true;
	}
	else {
		delete shader;
		return false;
	}
}

bool CGLShaderManager::remove(string name) {
	if (exist(name)) {
		shaderList.erase(name);
		return true;
	}
	return false;
}

void CGLShaderManager::add(string name, CGLShader *shader) {
	shaderList[name] = shader;
}

CGLShaderManager *CGLShaderManager::instance() {
	static CGLShaderManager *inst = NULL;
	if (!inst) {
		inst = new CGLShaderManager();
	}
	return inst;
}