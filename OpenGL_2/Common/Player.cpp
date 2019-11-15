#include "Player.h"
Player::Player(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	_points[0] = point4(-0.5f, 0.5f, 0.0f, 1.0f);
	_points[1] = point4(0.5f, 0.5f, 0.0f, 1.0f);
	_points[2] = point4(0.5f, -0.5f, 0.0f, 1.0f);
	_points[3] = point4(-0.5f, 0.5f, 0.0f, 1.0f);
	_points[4] = point4(0.5f, -0.5f, 0.0f, 1.0f);
	_points[5] = point4(-0.5f, -0.5f, 0.0f, 1.0f);

	_points[6] = point4(-0.5f, 0.5f, 0.0f, 1.0f);
	_points[7] = point4(0.5f, 0.5f, 0.0f, 1.0f);
	_points[8] = point4(0.0f, 1.0f, 0.0f, 1.0f);

	_colors[0] = color4(-1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	_colors[1] = color4(-1.0f, 1.0f, 1.0f, 1.0f);
	_colors[2] = color4(-1.0f, 1.0f, 1.0f, 1.0f);
	_colors[3] = color4(-1.0f, 1.0f, 1.0f, 1.0f);
	_colors[4] = color4(-1.0f, 1.0f, 1.0f, 1.0f);
	_colors[5] = color4(-1.0f, 1.0f, 1.0f, 1.0f);

	_colors[6] = color4(-1.0f, 1.0f, 1.0f, 1.0f);
	_colors[7] = color4(-1.0f, 1.0f, 1.0f, 1.0f);
	_colors[8] = color4(-1.0f, 1.0f, 1.0f, 1.0f);
	
	_bulletLink = new BulletLink(30, matModelView, matProjection);
	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors);
}

Player::~Player() {
	if (_transform != NULL) delete _transform;
	if (_bulletLink != NULL) delete _bulletLink;
}

void Player::SetShader(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	_transform->SetShader(matModelView, matProjection, shaderHandle);
}

void Player::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Player::SetColor(GLfloat vColor[4]) {
	_transform->SetColor(vColor);
}

void Player::Draw() {
	_bulletLink->Draw();

	_transform->Draw();
	
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
	glDrawArrays(GL_TRIANGLES, QUAD_NUM, Top_NUM);
}

void Player::SetPosition(vec4 position) {
	mat4 mT;
	_pos = position;
	mT = Translate(_pos);
	SetTRSMatrix(mT);
}

void Player::Update(float delta) {
	if (isShoot && _bulletLink->useCount<= _bulletLink->totalCount) {
		_bulletLink->Shoot(delta,_pos);
	}
	_bulletLink->DetectBullet();
}