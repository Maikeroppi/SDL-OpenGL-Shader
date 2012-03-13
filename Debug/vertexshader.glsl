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

uniform vec3 rot;

mat4 view_frustum(
    float angle_of_view,
    float aspect_ratio,
    float z_near,
    float z_far
) {
    return mat4(
        vec4(1.0/tan(angle_of_view),           0.0, 0.0, 0.0),
        vec4(0.0, aspect_ratio/tan(angle_of_view),  0.0, 0.0),
        vec4(0.0, 0.0,    (z_far+z_near)/(z_far-z_near), 1.0),
        vec4(0.0, 0.0, -2.0*z_far*z_near/(z_far-z_near), 0.0)
    );
}

// These could be combined into a single matrix, but I find it
// easier to thing about them in terms of separate rotations
mat4 RotX = mat4(
	vec4(1.0,	0.0,		0.0,			0.0),
	vec4(0.0,	cos(radians(rot.x)),	-sin(radians(rot.x)),	0.0),
	vec4(0.0,	sin(radians(rot.x)),	cos(radians(rot.x)),		0.0),
	vec4(0.0,	0.0,		0.0,			1.0)
	);

mat4 RotY = mat4(
	vec4(cos(radians(rot.y)),	0.0,		-sin(radians(rot.y)),		0.0),
	vec4(0.0,					1.0,		0.0,						0.0),
	vec4(sin(radians(rot.y)),	0.0,		cos(radians(rot.y)),		0.0),
	vec4(0.0,					0.0,		0.0,						1.0)
	);

mat4 RotZ = mat4(
	vec4(1.0,		0.0,						0.0,					0.0),
	vec4(0.0,		cos(radians(rot.z)),		-sin(radians(rot.z)),	0.0),
	vec4(0.0,		sin(radians(rot.z)),		cos(radians(rot.z)),	0.0),
	vec4(0.0,		0.0,						0.0,					1.0)
	);

mat4 Scale = mat4(
	vec4(4.0/3.0,	0.0, 0.0, 0.0),
	vec4(0.0,		1.0, 0.0, 0.0),
	vec4(0.0,		0.0, 1.0, 0.0),
	vec4(0.0,		0.0, 0.0, 1.0)
	);

mat4 Translate = mat4(
	vec4(1.0, 0.0, 0.0, 0.0),
	vec4(0.0, 1.0, 0.0, 0.0),
	vec4(0.0, 0.0, 1.0, 0.0),
	vec4(0.0, 0.0, 4.0, 1.0)
	);
 

void main(void) {
 
	// Apply our matrices to the current point
    gl_Position = view_frustum(radians(45.0), 16.0/9.0, 0.5, 10.0)
	    * Translate
		* RotX  
		* RotY
		* RotZ		 
		* Scale
		* in_Position;
 
    // We're simply passing the color through unmodified
    ex_Color = in_Color;
}