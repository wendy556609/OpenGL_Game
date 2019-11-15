#version 130
in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 vT;

void main()
{
	mat4 mxT=mat4(
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1);


    gl_Position = Projection * ModelView * vT * vPosition;
	color = vColor;
}