#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {

public:
	//reference ID of the Shader
	GLuint ID;
	//constructor for the shader class that builds the shader program
	//from two different shaders (vertex and fragment)
	Shader(const char* vertexFile, const char* fragmentFile);

	//activates shader program
	void Activate();
	//deletes shader program
	void Delete();

private:
	//used to check for errors
	void compileErrors(unsigned int shader, const char* type);

};

#endif // !SHADER_CLASS_H
