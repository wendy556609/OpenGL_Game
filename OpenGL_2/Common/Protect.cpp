#include "Protect.h"
Protect::Protect(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	for (int i = 0; i < Total_NUM; i++)
	{
		_points[i]=point4(0.2f*cosf(M_PI*i/(Total_NUM-1)), 0.05f* sinf(M_PI*i /(Total_NUM -1))+0.2f, 0.0f, 0.1f);
		_colors[i] =color4(1.0f, 0.0f, 0.0f, 0.5f);
	}
	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors, shaderHandle);
	mxIdle = Translate(vec4(0.0f, 0.0f, 0.0f));
}

Protect::~Protect() {
	if (_transform != NULL) delete _transform;
}

void Protect::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_FAN, 0, Total_NUM);
}

void Protect::ResetProtect() {
	_angle = 0;
	SetTurn();
}

void Protect::SetParent(mat4 &mxParent) {
	parent = mxParent;
}

void Protect::SetTurn() {	
	SetTRSMatrix(RotateZ(_angle));
}

void Protect::SetTRSMatrix(mat4 &mat)
{
	_transform->ShaderTRS(parent*mat*mxIdle);
}

void Protect::SetColor(GLfloat vColor[4]) {
	_transform->SetColor(vColor);
}

void Protect::Update(float delta) {
	if (_angle >= 45)_angle = 45;
	else if ((_angle <= -45))_angle = -45;
	SetTurn();
}