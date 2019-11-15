#version 130
in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform float fAngle;

void main()
{
	mat4 mxRot=mat4(
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1);

	float a=radians(fAngle);
	float x=cos(a);
	float y=sin(a);

	mxRot[0][0]=x;mxRot[0][1]=y;
	mxRot[1][0]=-y;mxRot[1][1]=x;

    gl_Position = Projection * ModelView *mxRot * vPosition;
	color = vColor;
}
