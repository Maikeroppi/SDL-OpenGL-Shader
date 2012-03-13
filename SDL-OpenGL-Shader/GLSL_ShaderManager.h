/////////////////////////////////
// GLSL_ShaderManager.h
//
// Header file for the ShaderManager class.  The ShaderManager is a class that assists in loading / unloading GLSL shaders
//

#ifndef __GLSL_SHADERMANAGER_H
#define __GLSL_SHADERMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#define NO_SDL_GLEXT
#include "GL/glew.h"
#include "SDL_opengl.h"

using namespace std;

class GLSL_ShaderManager
{
public:
	// Loads a vertex shader
	static GLuint LoadVertexShader(string filename);
	static GLuint LoadFragmentShader(string filename);
	static const char *getError();

private:
	GLSL_ShaderManager();
	static GLuint LoadShader(string filename, GLenum shaderType);
	static char *ReadFileToBuffer(const char *filename);
	static char *errorStr;
};

#endif