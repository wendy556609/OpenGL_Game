#include "Enemy.h"
Enemy::Enemy(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {

	_points[0] = point4(-1.0f, 10.0f, 0.0f, 1.0f);
	_points[1] = point4(1.0f, 10.0f, 0.0f, 1.0f);
	_points[2] = point4(1.0f, 9.0f, 0.0f, 1.0f);
	_points[3] = point4(-1.0f, 10.0f, 0.0f, 1.0f);
	_points[4] = point4(1.0f, 9.0f, 0.0f, 1.0f);
	_points[5] = point4(-1.0f, 9.0f, 0.0f, 1.0f);

	_colors[0] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[1] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[2] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[3] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[4] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[5] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	_collider = new Collider(1.0f, 0.5f, vec4(0.0f, 9.5f, 0.0f, 1.0f));
	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors);
}

Enemy::~Enemy() {
	if (_transform != NULL) delete _transform;
	if (_collider != NULL)delete  _collider;
}

void Enemy::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Enemy::SetColor(GLfloat vColor[4]) {
	_transform->SetColor(vColor);
}

void Enemy::Draw() {

	_transform->Draw();

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Enemy::Update(float delta) {
}