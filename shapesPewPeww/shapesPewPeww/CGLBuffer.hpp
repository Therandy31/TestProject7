#pragma once
#include "main.hpp"
#include "CGLShader.hpp"

class CGLBuffer {
protected:
	CGLShader *shader;

	GLuint vbo;
	GLuint vao;
	GLuint ebo;

	GLenum drawMode;
	GLuint drawCount;
	GLuint drawOffset;

public:
	CGLBuffer();
	~CGLBuffer();

	bool setShader(CGLShader *shader);
	bool setVertexData(GLfloat *vertices, int count);
	bool setIndexData(GLuint *indices, int count);
	bool setAttribute(string attrib, int count, int stride, int offset);
	
	void setDrawMode(GLenum drawMode) { this->drawMode = drawMode; }
	void setDrawSize(GLenum drawCount) { this->drawCount = drawCount; }
	void setDrawOffset(GLenum drawOffset) { this->drawOffset = drawOffset; }

	GLenum getDrawMode() { return drawMode; }
	GLenum getDrawSize() { return drawCount; }
	GLenum getDrawOffset() { return drawOffset; }

	void drawElements();

	CGLShader *getGLShader() { return shader; }
	GLuint getVertexBufferObject() { return vbo; }
	GLuint getVertexArrayObject() { return vao; }
	GLuint getElementBufferObject() { return ebo; }
};