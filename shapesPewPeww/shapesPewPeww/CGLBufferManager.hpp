#pragma once
#include "main.hpp"
#include "CGLShaderManager.hpp"
#include "CGLBuffer.hpp"
using namespace std;

class CGLBufferManager {
private:
	map<string, CGLBuffer *> bufferList;

	CGLBufferManager();

	CGLBuffer *loadShader(Json::Value *root);
	bool loadVertices(CGLBuffer *buffer, Json::Value *root);
	bool loadIndices(CGLBuffer *buffer, Json::Value *root);
	bool loadAttributes(CGLBuffer *buffer, Json::Value *root);
	bool loadDrawParameters(CGLBuffer *buffer, Json::Value *root);

public:
	~CGLBufferManager();

	CGLBuffer *get(string name);
	bool exist(string name);
	bool load(string name);
	bool remove(string name);
	void add(string name, CGLBuffer *buffer);

	static CGLBufferManager *instance();
};