#include "CGLShader.hpp"

CGLShader::CGLShader() {
	vertexShader = 0;
	fragmentShader = 0;
	program = 0;
}

CGLShader::~CGLShader() {
	deleteShaderProgram();
}

bool CGLShader::loadVertexSourceFromFile(string filename) {
	ifstream fs(filename);
	string line;

	if (fs.is_open()) {
		while (!fs.eof()) {
			getline(fs, line);
			vertexSource.append(line);
			vertexSource.append("\n");
			line.clear();
		}
		fs.close();
		return true;
	}
	return false;
}

bool CGLShader::loadFragmentSourceFromFile(string filename) {
	ifstream fs(filename);
	string line;

	if (fs.is_open()) {
		while (!fs.eof()) {
			getline(fs, line);
			fragmentSource.append(line);
			fragmentSource.append("\n");
			line.clear();
		}
		fs.close();
		return true;
	}
	return false;
}

bool CGLShader::buildShader() {
	GLchar *source;
	
	source = (GLchar *)vertexSource.c_str();
	glShaderSource(vertexShader, 1, (const GLchar **)&source, NULL);

	source = (GLchar *)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, (const GLchar **)&source, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	if (program) {
		return true;
	}
	else {
		return false;
	}
}

bool CGLShader::useProgram(bool bUse) {
	if (program) {
		if (bUse) {
			glUseProgram(program);
		}
		else {
			glUseProgram(0);
		}
		return true;
	}
	else {
		return false;
	}
}

GLuint CGLShader::getUniformLocation(string uniform) {
	if (program) {
		glUseProgram(true);
		return glGetUniformLocation(program, uniform.c_str());
	}
	return 0;
}

void CGLShader::setUniform1f(string uniform, float x) {
	GLuint uniformLocation = getUniformLocation(uniform);

	if (uniformLocation) {
		glUniform1f(uniformLocation, x);
	}
}

void CGLShader::setUniform2f(string uniform, float x, float y) {
	GLuint uniformLocation = getUniformLocation(uniform);

	if (uniformLocation) {
		glUniform2f(uniformLocation, x, y);
	}
}

void CGLShader::setUniform3f(string uniform, float x, float y, float z) {
	GLuint uniformLocation = getUniformLocation(uniform);

	if (uniformLocation) {
		glUniform3f(uniformLocation, x, y, z);
	}
}

void CGLShader::setUniform4f(string uniform, float x, float y, float z, float w) {
	GLuint uniformLocation = getUniformLocation(uniform);

	if (uniformLocation) {
		glUniform4f(uniformLocation, x, y, z, w);
	}
}

GLuint CGLShader::getAttribLocation(string attrib) {
	if (program) {
		glUseProgram(true);
		return glGetAttribLocation(program, attrib.c_str());
	}
	return 0;
}

void CGLShader::deleteShaderProgram() {
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);
	
	vertexShader = 0;
	fragmentShader = 0;
	program = 0;
}

void CGLShader::deleteVertexShaderSource() {
	vertexSource.clear();
}

void CGLShader::deleteFragmentShaderSource() {
	fragmentSource.clear();
}