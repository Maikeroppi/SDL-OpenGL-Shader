/////////////////////////////////
// main.cpp
//
// Main program file for a simple rotating cube done in OpenGL with shaders.
//

#include "CubeWithShaders.h"

using namespace std;

int main( int argc, char* args[] ) 
{ 
	// Allocate cube demo to run at 1280x720 with 32 bit pixels
	CubeWithShaders cubeDemo(1280, 720, 32);	
	
	// Initialize demo
	if(!cubeDemo.Init()) {
		cout << "Error initializing Cube Demo. Returning..." << endl;
		return -1;
	}

	// Simple update loop
	while(cubeDemo.IsRunning()) {
		cubeDemo.Render();
		cubeDemo.Update();		
	}

	cubeDemo.DeInit();
 
	return 0; 
}

