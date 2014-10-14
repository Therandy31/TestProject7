#pragma once
#include "main.hpp"
using namespace std;

class CGLShader {
private:
	string vertexSource;
	string fragmentSource;

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;

public:
	CGLShader();
	~CGLShader();

	bool loadVertexSourceFromFile(string filename);
	bool loadFragmentSourceFromFile(string filename);

	bool buildShader();

	bool useProgram(bool bUse);

	GLuint getUniformLocation(string uniform);
	void setUniform1f(string uniform, float x);
	void setUniform2f(string uniform, float x, float y);
	void setUniform3f(string uniform, float x, float y, float z);
	void setUniform4f(string uniform, float x, float y, float z, float w);

	GLuint getAttribLocation(string attrib);

	void deleteShaderProgram();
	void deleteVertexShaderSource();
	void deleteFragmentShaderSource();

	GLuint getProgram() { return program; }
};