#include "Protect.h"
Protect::Protect(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	for (int i = 0; i < Total_NUM; i++)
	{
		_points[i]=point4(0.2f*cosf(M_PI*i/(Total_NUM-1)), 0.05f* sinf(M_PI*i /(Total_NUM -1)), 0.0f, 0.1f);
		_colors[i] =color4(1.0f, 0.0f, 0.0f, 0.5f);
	}
	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors, shaderHandle);
	mxIdle = Translate(vec4(0.0f, 2.0f, 0.0f, 1.0f));
	_collider.Init(2, 1, vec4(parent.x, parent.y + 2.0f, 0.0f, 1.0f));
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

void Protect::SetParent(vec4 &vecParent) {
	parent = vecParent;
}

void Protect::SetTurn() {	
	SetTRSMatrix(RotateZ(_angle));
}

void Protect::SetTRSMatrix(mat4 &mat)
{
	mat4 mT;
	vec4 vT;
	mT = Translate(parent)*mat*mxIdle;
	vT.x = mat[0][0] * parent.x - mat[0][1] * (parent.y + 2.0f);
	vT.y = mat[1][0] * parent.x + mat[1][1] * (parent.y + 2.0f);
	//Print(vT);
	_collider.SetCollider(vT);
	_transform->ShaderTRS(mT);
}

void Protect::SetColor(GLfloat vColor[4]) {
	_transform->SetColor(vColor);
}

void Protect::Update(float delta) {
	if (_angle >= 45)_angle = 45;
	else if ((_angle <= -45))_angle = -45;
	SetTurn();
}