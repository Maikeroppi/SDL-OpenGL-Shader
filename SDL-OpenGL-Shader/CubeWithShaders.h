/////////////////////////////////
// CubeWithShaders.h
//
// Class to produce a Cube with pixel shaders
//

// This define is required to prevent SDL from initializing with default GL extension parameters.
// We want to control the detection / loading of extensions with GLEW.
#define NO_SDL_GLEXT
#include "GL/glew.h"
#include "SDL_opengl.h"
#include "SDL.h"
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

#include "GLSL_ShaderManager.h"

#ifndef __CUBEWITHSHADERS_H
#define __CUBEWITHSHADERS_H



class CubeWithShaders
{
public:
	// Initialization.  By default, CubeWithShaders will assume a default screen size of 
	// 1280x720 with 32bpp.
	CubeWithShaders();
	CubeWithShaders(GLuint ScreenWidth, GLuint ScreenHeight, GLuint ScreenBpp);

	// Init to actually intialize object. If any memory allocation needs to be done, it will happen here.
	bool Init();

	// Update the cube for the next frame.
	void Update();

	// Perform actual rendering.
	void Render();

	// Free up any memory, if it's used.
	void DeInit();

	// Report whether the demo is still running.
	bool IsRunning();

private:
	// Read in GLSL source, compile it, and link it if there are no errors
	bool BuildShaders();

	// Member variables
	GLuint			ScreenWidth, ScreenHeight, ScreenBpp;
	GLfloat			RotationValues[3];
	GLfloat			CurRotateDeg;
	SDL_Event		sdevent;
	bool			running, fpsCapped;
	int				frameStartTick;
	float			frameTime, maxFPS, maxFPSTime;
	string			WindowMessage;
	stringstream	fpsString;

	// GL IDs for various parts of our program that require them
	GLuint			vertBuffID, vertElemID, vertColorID;
	GLuint			programID, vertexShaderID, fragmentShaderID;
	GLuint			MasterMatrixID;

	// Define variables for cube data
	static const GLfloat CubeVertexData[];
	static const GLushort CubeElementData[];
	static const GLfloat CubeColors[];

	// Define GLM variables for calculating our View/Scale/Rotation Matrix
	// Before sending it to the GPU
	glm::mat4		Rotation;
	glm::mat4		Scale;
	glm::mat4		Translate;
	glm::mat4		View;
	glm::mat4		StaticMatrix;
	glm::mat4		MasterMatrix;
};
#endif