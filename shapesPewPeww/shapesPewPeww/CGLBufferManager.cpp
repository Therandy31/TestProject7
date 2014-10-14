#include "CGLBufferManager.hpp"

// CGLBufferManager manages GLBuffer objects, and makes them availiable to the rest of the program.
CGLBufferManager::CGLBufferManager() {
	clog << "[INFO] <CGLBufferManager>: Instance created." << endl;
}

// Gets a buffer from the list. If it does not exist, it attempts to load and return it.
CGLBuffer *CGLBufferManager::get(string name) {
	if (exist(name)) {
		return bufferList[name];
	}
	else {
		bool bCreateSuccess = load(name);
		if (bCreateSuccess) {
			return bufferList[name];
		}
	}
	return NULL;
}

// Checks to see if there is a buffer by the given name in the list.
bool CGLBufferManager::exist(string name) {
	if (bufferList.count(name)) {
		return true;
	}
	return false;
}

// Loads a buffer into the list from a Json file.
bool CGLBufferManager::load(string name) {
	string filename = "assets/buffers/";
	Json::Reader reader;
	Json::Value root;

	filename.append(name);
	filename.append(".json");

	ifstream fs(filename, ifstream::binary);

	if (fs.is_open()) {
		bool bParseSuccess = reader.parse(fs, root, false);
		fs.close();
		if (bParseSuccess) {
			if (root["type"].asString().compare("buffer") == 0) {
				bool bLoadSuccess = true;

				// Actually load the buffer and place it in the list.
				// If the shader fails to load, there is no point in continuing.
				// A buffer object will not be created on failure.
				CGLBuffer *buffer = loadShader(&root);
				if (buffer) {
					// If any one of these operations fail, 'bLoadSuccess' will be FALSE at the end.
					// If one of them fails, it will not crash when running the others.
					bLoadSuccess = loadVertices(buffer, &root) && bLoadSuccess;
					bLoadSuccess = loadIndices(buffer, &root) && bLoadSuccess;
					bLoadSuccess = loadAttributes(buffer, &root) && bLoadSuccess;
					bLoadSuccess = loadDrawParameters(buffer, &root) && bLoadSuccess;

					// Success? Add it to the list and return TRUE.
					if (bLoadSuccess) {
						string bufferName = root["name"].asString();
						bufferList[bufferName] = buffer;
						return true;
					}
					else {
						// Delete the buffer and exit.
						delete buffer;
					}
				}
			}
		}
	}

	// Should the file not open, just leave.
	return false;
}

// If it exist, removes the buffer from the list by the given name.
bool CGLBufferManager::remove(string name) {
	if (exist(name)) {
		bufferList.erase(name);
		return true;
	}
	return false;
}

// Add a manually created buffer object.
void CGLBufferManager::add(string name, CGLBuffer *buffer) {
	bufferList[name] = buffer;
}

// Singleton, only one instance of this class my exist.
// This is to reduce duplicate resources on the GFX card.
CGLBufferManager *CGLBufferManager::instance() {
	static CGLBufferManager *inst = NULL;
	if (!inst) {
		inst = new CGLBufferManager();
	}
	return inst;
}

// The following are private helper functions to reduce lengthy code in CGLBufferManager::load().
// Loads a CGLShader into the buffer (pointer). We will not need a CGLBuffer if this fails.
CGLBuffer *CGLBufferManager::loadShader(Json::Value *root) {
	string shaderName = (*root)["shader"].asString();

	CGLShader *shader = CGLShaderManager::instance()->get(shaderName);

	if (shader) {
		// The shader exist, lets make an new CGLBuffer object.
		CGLBuffer *buffer = new CGLBuffer();
		buffer->setShader(shader);
		return buffer;
	}
	else {
		// Shader does not exist, CGLBuffer loading ends here.
		return NULL;
	}
}

// Nothing special, just loads in the vertices.
bool CGLBufferManager::loadVertices(CGLBuffer *buffer, Json::Value *root) {
	Json::Value *verticesNode = &(*root)["vertices"];

	int arraySize = (*verticesNode).size();
	GLfloat *verticesArray = (GLfloat *)malloc(arraySize * sizeof(GLfloat *));
	Json::Value::iterator verticesIt = verticesNode->begin();
	for (int element = 0; verticesIt != verticesNode->end(); ++verticesIt) {
		verticesArray[element++] = (*verticesIt).asFloat();
	}
	bool bSetSuccess = buffer->setVertexData(verticesArray, arraySize);
	free(verticesArray);
	
	return bSetSuccess;
}

// Loads in all of the indices.
bool CGLBufferManager::loadIndices(CGLBuffer *buffer, Json::Value *root) {
	Json::Value *indicesNode = &(*root)["indices"];

	int arraySize = (*indicesNode).size();
	GLfloat *indicesArray = (GLfloat *)malloc(arraySize * sizeof(GLfloat *));
	Json::Value::iterator indicesIt = indicesNode->begin();
	for (int element = 0; indicesIt != indicesNode->end(); ++indicesIt) {
		indicesArray[element++] = (*indicesIt).asFloat();
	}
	bool bSetSuccess = buffer->setVertexData(indicesArray, arraySize);
	free(indicesArray);

	return bSetSuccess;
}

// Loads in all of the attributes specified in the Json file.
bool CGLBufferManager::loadAttributes(CGLBuffer *buffer, Json::Value *root) {
	Json::Value *attributeparametersNode = &(*root)["attributeparameters"];
	Json::Value *attributesNode = &(*attributeparametersNode)["attributes"];
	bool bSetSuccess = true;

	int stride = (*attributeparametersNode)["stride"].asUInt();
	
	Json::Value::iterator attributesIt = attributesNode->begin();
	for (; attributesIt != attributesNode->end(); ++attributesIt) {
		string attribName = (*attributesIt)["name"].asString();
		int count = (*attributesIt)["count"].asUInt();
		int offset = (*attributesIt)["offset"].asUInt();
		bSetSuccess = buffer->setAttribute(attribName, count, stride, offset) && bSetSuccess;
	}

	return bSetSuccess;
}

// Load in parameters to tell OpenGL how to draw the buffer.
bool CGLBufferManager::loadDrawParameters(CGLBuffer *buffer, Json::Value *root) {
	Json::Value *drawparametersNode = &(*root)["drawparameters"];

	int drawmode = (*drawparametersNode)["drawmode"].asUInt();
	int offset = (*drawparametersNode)["offset"].asUInt();

	return true;
}