/////////////////////////////////
// fragmentshader.glsl
//
// GLSL fragment shader source for the cube example. Basically just passes our
// fragment color through unmodified.

#version 130
 
 // Define default precision
 // (required for some ATI drivers)
precision highp float;

in  vec3 ex_Color;
out vec4 ex_FragColor;
 
void main(void) {
    // Pass through our original color with full opacity.
    ex_FragColor = vec4(ex_Color,1.0f);
}