/////////////////////////////////
// CubeWithShaders.cpp
//
// Implementation of the CubeWithShaders class.

#include "CubeWithShaders.h"

const GLfloat CubeWithShaders::CubeVertexData[] = {	
	  1.0,  1.0, -1.0, 1.0,		// Top Quad
     -1.0,  1.0, -1.0, 1.0,
     -1.0,  1.0,  1.0, 1.0, 
      1.0,  1.0,  1.0, 1.0,

      
      1.0, -1.0,  1.0, 1.0,		// Bottom Quad
     -1.0, -1.0,  1.0, 1.0,
     -1.0, -1.0, -1.0, 1.0,
      1.0, -1.0, -1.0, 1.0,
	  
      1.0,  1.0,  1.0, 1.0,		// Front Quad
     -1.0,  1.0,  1.0, 1.0,
     -1.0, -1.0,  1.0, 1.0,
      1.0, -1.0,  1.0, 1.0,

      
      1.0, -1.0, -1.0, 1.0,		// Back Quad
     -1.0, -1.0, -1.0, 1.0,
     -1.0,  1.0, -1.0, 1.0,
      1.0,  1.0, -1.0, 1.0,

      
     -1.0,  1.0,  1.0, 1.0,		// Left Quad
     -1.0,  1.0, -1.0, 1.0,
     -1.0, -1.0, -1.0, 1.0,
     -1.0, -1.0,  1.0, 1.0,

      1.0,  1.0, -1.0, 1.0,		// Right Quad
      1.0,  1.0,  1.0, 1.0,
      1.0, -1.0,  1.0, 1.0,
      1.0, -1.0, -1.0, 1.0,
	};

const GLushort CubeWithShaders::CubeElementData[] = {
	0,1,2,3,				// Top Quad
	4, 5, 6, 7,				// Bottom Quad
	8, 9, 10, 11,			// Front Quad
	12,13,14,15,			// Back Quad
	16, 17, 18, 19,			// Left Quad
	20, 21, 22, 23			// Right Quad
};

const GLfloat CubeWithShaders::CubeColors[] = {
	// Top colors - Blue
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,

   // Bottom colors - Red
   1.0, 0.0, 0.0,
   1.0, 0.0, 0.0,
   1.0, 0.0, 0.0,
   1.0, 0.0, 0.0,

   // Front colors - Orange
   1.0, 0.65f, 0.0,
   1.0, 0.65f, 0.0,
   1.0, 0.65f, 0.0,
   1.0, 0.65f, 0.0,

   // Back colors - Green
   0.0, 1.0, 0.0,
   0.0, 1.0, 0.0,
   0.0, 1.0, 0.0,
   0.0, 1.0, 0.0,

   // Left colors - Purple
   0.5, 0.0, 0.5,
   0.5, 0.0, 0.5,
   0.5, 0.0, 0.5,
   0.5, 0.0, 0.5,
   
   // Right colors - Yellow
   1.0, 1.0, 0.0,
   1.0, 1.0, 0.0,
   1.0, 1.0, 0.0,
   1.0, 1.0, 0.0,

  };

CubeWithShaders::CubeWithShaders()
{
	CubeWithShaders(1280, 720, 32);
}

CubeWithShaders::CubeWithShaders(GLuint ScreenWidth, GLuint ScreenHeight, GLuint ScreenBpp)
	: ScreenWidth(ScreenWidth), ScreenHeight(ScreenHeight)
	, ScreenBpp(ScreenBpp)
	, vertBuffID(0)
	, vertElemID(0)
	, vertColorID(0)
	, programID(0)
	, vertexShaderID(0)
	, fragmentShaderID(0)
	, MasterMatrixID(0)
	, running(true)
	, CurRotateDeg(0.0)
	, frameTime(0.0f)
	, frameStartTick(0)
	, fpsCapped(true)
	, maxFPS(60.0f)
	, maxFPSTime(1000.0f / maxFPS)
	, WindowMessage()
	, fpsString()
{
	// Initialize arrays as we can't put them in the initialization list.
	RotationValues[0] = RotationValues[1] = RotationValues[2] = 0.0f;
}

// Performs any actual initialization of the object (i.e., dynamic memory allocation) and
// intiailizes SDL systems and OpenGL
bool CubeWithShaders::Init()
{
	// Start SDL 
	SDL_Init( SDL_INIT_EVERYTHING ); 

	//Create Window 
	if( SDL_SetVideoMode( ScreenWidth, ScreenHeight, ScreenBpp, SDL_OPENGL ) == NULL ) { return false; }
	SDL_WM_SetCaption("SDL OpenGL Shader Tester",NULL);
	
	// Initialize window message for reporting frame rate.
	WindowMessage = "SDL OpenGL Shader Tester - OpenGL2.1 available, FPS: ";

	// Start GLEW
	glewInit();

	// Check for OpenGL 2.1
	if(!GLEW_VERSION_2_1) {
		std::cout << "Error: OpenGL 2.1 not available" << std::endl;
		return false;
	}

	SDL_WM_SetCaption("SDL OpenGL Shader Tester - OpenGL2.1 available",NULL);

	// Set clear color to black
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    // Depth buffer set to 1.0f when cleared
    glClearDepth( 1.0f );

    // Enable depth test 
    glEnable( GL_DEPTH_TEST );

    // Set depth fuction 
    glDepthFunc( GL_LEQUAL );

    
	// Generate buffers and set attributes for pixel shaders
	// Vertex data
	glGenBuffers(1, &vertBuffID);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertexData), CubeVertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// Color data
	glGenBuffers(1, &vertColorID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertColorID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeColors), CubeColors, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index array of vertex / color data 
	glGenBuffers(1, &vertElemID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertElemID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeElementData), CubeElementData, GL_STATIC_DRAW);


	glViewport(0,0,ScreenWidth,ScreenHeight);
	
	// Load our shaders
	if(BuildShaders() == false) {
		SDL_WM_SetCaption("Error in creating shaders",NULL);
		SDL_Delay(1000);
		return false;
	}	

	// Initialize our static matrices
	View		= glm::perspective(60.0f, (16.0f / 9.0f), 0.1f, 10.0f);
	Translate	= glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -4.0));
	Scale		= glm::scale(glm::mat4(1.0), glm::vec3(4.0/3.0));
	View = View * Scale * Translate;

	return true;
}

bool CubeWithShaders::BuildShaders()
{
	// Load up our vertex and fragment shader's source
	bool ret_val = true;
	int program_linked;
	int string_is_null_terminated = -1;

	int maxLength = 256;
	char errorbuf[256];
   
	// Load and compile the shaders
	vertexShaderID = GLSL_ShaderManager::LoadVertexShader("vertexshader.glsl");
	if(vertexShaderID == 0) {
		cout << "Error loading vertex shader: " << GLSL_ShaderManager::getError() << endl;
		return false;
	}

	fragmentShaderID = GLSL_ShaderManager::LoadFragmentShader("fragmentshader.glsl");
	if(fragmentShaderID == 0) {
		cout << "Error loading fragment shader: " << GLSL_ShaderManager::getError() << endl;
		return false;
	}

	// Things compiled okay, so create program and attach shaders
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	// Bind the attributes that our shaders will use
	glBindAttribLocation(programID, 0, "in_Position");
	glBindAttribLocation(programID, 1, "in_Color"); 

	// Link our program and check if there's any issues
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &program_linked);
	if(program_linked == FALSE) {
		glGetProgramInfoLog(programID, maxLength, 0, errorbuf);
		cout << "Error linking program: " << errorbuf << endl;
		ret_val = false;
	} else {
		glUseProgram(programID);		 
	 
		// Get the locations of our uniform attributes
		MasterMatrixID = glGetUniformLocation(programID, "MasterMatrix");
		ret_val = true;
	}
	
	return ret_val;
}

void CubeWithShaders::Render()
{
	// Get the current tick before starting frame
	frameStartTick = SDL_GetTicks();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	// Send master matrix to GPU
	glUniformMatrix4fv(
		MasterMatrixID,					// GL ID
		1,								// size (1 4x4 matrix)
		false,							// transposed?
		glm::value_ptr(MasterMatrix)	// data element
	);

	// Bind vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffID);
	glVertexAttribPointer(
		0,							      /* attribute */
        4,                                /* size */
        GL_FLOAT,                         /* type */
        GL_FALSE,                         /* normalized? */
        0,								  /* stride */
        (void*)0                          /* array buffer offset */
    );
    glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, vertColorID);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertElemID);
    glDrawElements(
        GL_QUADS,				// Mode
        24,						// Count
        GL_UNSIGNED_SHORT,		// Data type
        (void*)0				// Offset
    );

	// Update window
	SDL_GL_SwapBuffers();

	// Perform simple FPS capping:
	// --Determine how long frame took
	// --Sleep max FPS frame time minus actual frame time
	if(fpsCapped) {
		frameTime = float(SDL_GetTicks() - frameStartTick);

		if( frameTime < maxFPSTime )
			SDL_Delay( int(maxFPSTime - frameTime) );
	}

	fpsString.str("");
	fpsString << WindowMessage << ( 1000 / ( SDL_GetTicks() - frameStartTick));
	
	SDL_WM_SetCaption(fpsString.str().c_str(),NULL);

	return;
}

void CubeWithShaders::Update()
{
	if(SDL_PollEvent(&sdevent)) {
		switch(sdevent.type)
		{
		case SDL_QUIT: running = false; break;

		case SDL_KEYDOWN:
		{
			switch(sdevent.key.keysym.sym)
			{
			// Signal to quit if q is pressed
			case SDLK_q: running = false; break;

			default:
				break;
			}
		} break;
		// Do nothing if its some other event
		default:
			break;
		}
	}

	// Update the rotation array for the vertex shader
	CurRotateDeg+=0.5;
	RotationValues[0] = RotationValues[1] = RotationValues[2] = CurRotateDeg;

	// Update rotation and master matrices
	Rotation = glm::rotate(glm::mat4(1.0), CurRotateDeg, glm::vec3(1.0));
	MasterMatrix = View * Rotation;// * RotY * RotZ;
}

bool CubeWithShaders::IsRunning()
{
	return running;
}

void CubeWithShaders::DeInit()
{
	// Shut down SDL
	SDL_Quit();
}