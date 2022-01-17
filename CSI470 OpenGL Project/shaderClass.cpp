#include "shaderClass.h"

//Reads a text file and outouts a string with everything in said text file
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


Shader::Shader(const char* vertexFile, const char* fragmentFile) 
{
	//Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compile vertex shader into machine code
	glCompileShader(vertexShader);
	//checking for compilation errors
	compileErrors(vertexShader, "VERTEX");

	//create fragment shader object and get its reference 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//attach fragment shader souce to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//compile fragment shader into machine code
	glCompileShader(fragmentShader);
	//checking for compilation errors
	compileErrors(fragmentShader, "FRAGMENT");

	//create shader program and get its reference
	ID = glCreateProgram();
	//attach the vertex and fragment shaders to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	//link all shaders to the shader program
	glLinkProgram(ID);
	//checking for compilation errors
	compileErrors(ID, "PROGRAM");
	//delete shaders after they are linked to program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

//Activates the Shader Program
void Shader::Activate() {
	//activate program
	glUseProgram(ID);
}

//Deletes the Shader Program
void Shader::Delete() {
	//delete program
	glDeleteProgram(ID);
}


void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}