#include "CGLBuffer.hpp"

CGLBuffer::CGLBuffer() {
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);
	shader = NULL;

	drawMode = GL_TRIANGLES;
	drawCount = 0;
	drawOffset = 0;
}

CGLBuffer::~CGLBuffer() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}

bool CGLBuffer::setShader(CGLShader *shader) {
	if (shader) {
		this->shader = shader;
		return true;
	}
	return false;
}

bool CGLBuffer::setVertexData(GLfloat *vertices, int count) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	shader->useProgram(true);

	glBufferData(GL_ARRAY_BUFFER, count*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	return true;
}

bool CGLBuffer::setIndexData(GLuint *indices, int count) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	shader->useProgram(true);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLfloat), indices, GL_STATIC_DRAW);
	drawCount = count;

	return true;
}

bool CGLBuffer::setAttribute(string attrib, int count, int stride, int offset) {
	if (shader) {
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		shader->useProgram(true);

		GLuint attribLocation = glGetAttribLocation(shader->getProgram(), attrib.c_str());
		glVertexAttribPointer(attribLocation, count, GL_FLOAT, GL_FALSE, stride*sizeof(GLfloat), (GLvoid *)(offset*sizeof(GLfloat)));
		glEnableVertexAttribArray(attribLocation);
		return true;
	}
	return false;
}

void CGLBuffer::drawElements() {
	if (shader && drawCount>0) {
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		shader->useProgram(true);

		glDrawElements(drawMode, drawCount, GL_UNSIGNED_INT, (const GLvoid *)(drawOffset*sizeof(GLuint)));
	}
}