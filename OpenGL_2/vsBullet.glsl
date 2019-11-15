#version 130
in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 mxT;
void main()
{
    gl_Position = Projection * ModelView * mxT * vPosition;
	color = vColor;
}
