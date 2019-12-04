#include "Protect.h"
Protect::Protect(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	for (int i = 0; i < 20; i++)
	{
		_points[i]=point4(0.25f*cosf(M_PI*i/19), 0.1f* sinf(M_PI*i /19), 0.0f, 0.1f);
		_colors[i] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	}
	for (int i = 20; i < 40; i++)
	{
		_points[i] = point4(0.2f*cosf(M_PI*(i-20) / 19), 0.05f* sinf(M_PI*(i - 20) / 19) + 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.5f, 0.3f, 0.1f, 1.0f);
	}
	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors, shaderHandle);
	mxIdle = Translate(vec4(0.0f, 2.0f, 0.0f, 1.0f));
	_collider.Init(2.5f, 1.0f);
}

Protect::~Protect() {
	if (_transform != NULL) delete _transform;
}

void Protect::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 40);
}

void Protect::SetParent(vec4 &vecParent) {	
	mxIdle = Translate(vec4(0.0f, 2.0f, 0.0f, 1.0f));
	_collider.SetCollider(vec4(vecParent.x, vecParent.y + 2.0f, 0.0f, 1.0f));
	SetTRSMatrix(Translate(vecParent)*mxIdle);
}

void Protect::SetTRSMatrix(mat4 &mat)
{	
	_transform->SetTRSMatrix(mat);
}

void Protect::SetColor(GLfloat vColor[4]) {
	_transform->SetHurtColor(vColor);
}

void Protect::Update(float delta) {
}