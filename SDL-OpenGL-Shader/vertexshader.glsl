/////////////////////////////////
// vertextshader.glsl
//
// GLSL vertex shader source for our cube example.  Handles roation, scaling, transformation, etc.
// for each individual vertex. Not particularly efficient as it recalculates all these matrices for each vertice.
//

#version 130
// Version 1.30 would require OpenGL 3.0.
// However, Intel HD drivers complain that the "in/out" keywords were not available in 1.20.
// The spec says they are, but oh well.

// Define default precision
// (required for some ATI drivers)
precision highp float;

// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
in  vec4 in_Position;
in  vec3 in_Color;

// We output the ex_Color variable to the next shader in the chain
out vec3 ex_Color;

uniform mat4 MasterMatrix;


void main(void) {
 
	// Apply master matrix from main program
    gl_Position = MasterMatrix * in_Position;
 
    // We're simply passing the color through unmodified
    ex_Color = in_Color;
}