#include "Enemy.h"
Enemy::Enemy(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {

	Create(matModelView, matProjection, shaderHandle);
	_pos = vec4(0.0f, 9.5f, 0.0f, 1.0f);
	_bulletLink = new BulletLink(30, matModelView, matProjection);
	SetPosition(_pos);
}

Enemy::~Enemy() {
	if (_bulletLink != NULL) delete _bulletLink;
}

void Enemy::Create(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	//Body
	_points[0] = point4(-1.25f, 1.5f, 0.0f, 1.0f);
	_points[1] = point4(1.25f, 1.5f, 0.0f, 1.0f);
	_points[2] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[3] = point4(-1.25f, 1.5f, 0.0f, 1.0f);
	_points[4] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[5] = point4(-1.25f, -1.5f, 0.0f, 1.0f);

	_colors[0] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[1] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[2] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[3] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[4] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[5] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//Head
	for (int i = 6; i < 26; i++)
	{
		_points[i] = point4(0.1f*cosf(M_PI*2.0*(i - 6) / (Head_NUM)), 0.1f* sinf(M_PI*2.0*(i - 6) / (Head_NUM)), 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.5f, 0.25f, 1.0f);
	}

	//Eyes
	_points[26] = point4(0.25f, 0.0f, 0.0f, 1.0f);
	_points[27] = point4(0.75f, 0.25f, 0.0f, 1.0f);
	_points[28] = point4(0.5f, -0.25f, 0.0f, 1.0f);
	_points[29] = point4(-0.25f, 0.0f, 0.0f, 1.0f);
	_points[30] = point4(-0.75f, 0.25f, 0.0f, 1.0f);
	_points[31] = point4(-0.5f, -0.25f, 0.0f, 1.0f);

	_colors[26] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[27] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[28] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[29] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[30] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[31] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//Buttom
	_points[32] = point4(-1.25f, -1.5f, 0.0f, 1.0f);
	_points[33] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[34] = point4(0.0f, -2.25f, 0.0f, 1.0f);

	_colors[32] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[33] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[34] = color4(0.75f, 0.25f, 0.25f, 1.0f);

	//Top
	_points[35] = point4(-1.75f, 2.25f, 0.0f, 1.0f);
	_points[36] = point4(1.75f, 2.25f, 0.0f, 1.0f);
	_points[37] = point4(1.25f, 1.5f, 0.0f, 1.0f);
	_points[38] = point4(-1.75f, 2.25f, 0.0f, 1.0f);
	_points[39] = point4(1.25f, 1.5f, 0.0f, 1.0f);
	_points[40] = point4(-1.25f, 1.5f, 0.0f, 1.0f);

	_colors[35] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[36] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[37] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[38] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[39] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[40] = color4(0.75f, 0.25f, 0.25f, 1.0f);

	//Triangle
	_points[41] = point4(1.25f, 1.0f, 0.0f, 1.0f);
	_points[42] = point4(1.75f, 1.0f, 0.0f, 1.0f);
	_points[43] = point4(1.25f, -1.0f, 0.0f, 1.0f);
	_points[44] = point4(-1.25f, 1.0f, 0.0f, 1.0f);
	_points[45] = point4(-1.75f, 1.0f, 0.0f, 1.0f);
	_points[46] = point4(-1.25f, -1.0f, 0.0f, 1.0f);

	_colors[41] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[42] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[43] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[44] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[45] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[46] = color4(0.75f, 0.25f, 0.25f, 1.0f);

	_collider.Init(1.75f, 2.25f, vec4(0.0f, 0.0f, 0.0f, 1.0f));

	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors);
}

void Enemy::Draw() {
	_bulletLink->Draw();
	_transform->Draw();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 20);
	glDrawArrays(GL_TRIANGLES, 26, 3);
	glDrawArrays(GL_TRIANGLES, 29, 3);
	glDrawArrays(GL_TRIANGLES, 32, 3);
	glDrawArrays(GL_TRIANGLES, 35, 6);
	glDrawArrays(GL_TRIANGLES, 41, 3);
	glDrawArrays(GL_TRIANGLES, 44, 3);
}

void Enemy::Update(float delta) {
	shootTime += delta;
	if (shootTime >= 0.5f&&_bulletLink->useCount <= _bulletLink->totalCount) {
		_bulletLink->Shoot(delta, _pos);
		shootTime = 0;
	}
	_bulletLink->DetectEnemyBullet();
}

void Enemy::SetPosition(vec4 position) {
	mat4 mT;
	_pos = position;
	mT = Translate(_pos);
	SetTRSMatrix(mT);
	_collider.SetCollider(_pos);
}