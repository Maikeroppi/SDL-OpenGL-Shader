/////////////////////////////////
// GLSL_ShaderManager.cpp
//
// Implementation of simple static methods to assist in dealing with GLSL shaders
//

#include "GLSL_ShaderManager.h"

char * GLSL_ShaderManager::errorStr = NULL;

GLSL_ShaderManager::GLSL_ShaderManager() 
{
	errorStr = NULL;
}

GLuint GLSL_ShaderManager::LoadVertexShader(string filename)
{
	return LoadShader(filename, GL_VERTEX_SHADER);
}

GLuint GLSL_ShaderManager::LoadFragmentShader(string filename)
{
	return LoadShader(filename, GL_FRAGMENT_SHADER);
}


GLuint GLSL_ShaderManager::LoadShader(string filename, GLenum shaderType)
{
	GLuint shaderID;
	const char *buffer;
	int shaderCompiled = 0;
	int maxLength = 0;

	buffer = filename.c_str();

	char *shaderSource = ReadFileToBuffer(buffer);
	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, (const GLchar **)&shaderSource, 0);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID,	GL_COMPILE_STATUS,	&shaderCompiled);

	if(shaderCompiled != TRUE) {		
		// Retrieve error status, store in error string
		 glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
 
		/* The maxLength includes the NULL character */
		if(errorStr != NULL) delete[] errorStr;
		errorStr = new char[maxLength];
 		glGetShaderInfoLog(shaderID, maxLength, &maxLength, errorStr);

		// Set shader ID to 0 to indicate failure
		shaderID = 0;
	}

	return shaderID;
}

char * GLSL_ShaderManager::ReadFileToBuffer(const char *filename)
{
	ifstream fin;
	string buffer;

	char line[256];
	char *ret_val = NULL;

	fin.open(filename, ios::in);

	if(fin.is_open()) {
		while(fin.good()) {
			fin.getline(line,256);
			buffer.append(line);
			buffer.append("\n");
		}

		ret_val = new char[buffer.length() + 1];
		strncpy(ret_val, buffer.c_str(), buffer.length()+1);
	}

	return ret_val;
}

const char *GLSL_ShaderManager::getError()
{
	return (const char *)errorStr;
}