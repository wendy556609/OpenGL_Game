#include "Enemy.h"
#include "Smoke.h"
Bomb* bomb;
Smoke* smoke[3];
/////////////////////Enemy
void Enemy::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Enemy::SetColor(GLfloat vColor[4], bool hurt) {
	if (hurt)_transform->SetHurtColor(vColor);
	else _transform->SetColor(vColor);
}

GLboolean Enemy::CheckCollider(Collider one, Collider two) {
	bool collisionX = (one.leftButtom.x <= two.rightTop.x && one.leftButtom.x >= two.leftButtom.x) ||
		(one.rightTop.x <= two.rightTop.x && one.rightTop.x >= two.leftButtom.x) ||
		(two.leftButtom.x <= one.rightTop.x && two.leftButtom.x >= one.leftButtom.x) ||
		(two.rightTop.x <= one.rightTop.x && two.rightTop.x >= one.leftButtom.x);
	bool collisionY = (one.leftButtom.y <= two.rightTop.y && one.leftButtom.y >= two.leftButtom.y) ||
		(one.rightTop.y <= two.rightTop.y && one.rightTop.y >= two.leftButtom.y) ||
		(two.leftButtom.y <= one.rightTop.y && two.leftButtom.y >= one.leftButtom.y) ||
		(two.rightTop.y <= one.rightTop.y && two.rightTop.y >= one.leftButtom.y);
	return collisionX&&collisionY;

}

void Enemy::SetHurt(float delta) {
	if (_collider.isHurt) {
		if (hurtColorTime == 0.0f)SetColor(vec4(0.4f, 0.0f, 0.0f, 0.0f), true);

		hurtColorTime += delta;

		if (hurtColorTime >= 0.2f) {
			SetColor(vec4(-0.4f, 0.0f, 0.0f, 0.0f), true);
			hurtColorTime = 0.0f;
			_collider.isHurt = false;
		}
	}
}

void Enemy::EnemyMove(float delta, int speed) {
	mat4 mPLT;
	_pos.y -= speed * delta;

	mPLT = Translate(_pos.x, _pos.y, 0.0f);
	SetPosition(_pos);
}

void Enemy::SetPosition(vec4 position) {
	mat4 mT;
	_pos = position;
	mT = Translate(_pos);
	SetTRSMatrix(mT);
	_collider.SetCollider(_pos);
}

void Enemy::PlayerHurt() {
	int Count = 0;
	if (CheckCollider(_collider, *playerCollider))
	{
		if (Count <= 0) {
			playerCollider->hp -= 1;
			playerCollider->isHurt = true;
			Count++;
		}
	}
}

void Enemy::Init() {
	shootTime = 0.0f;
	hurtTime = 0.0f;
	_collider.hp = hp;
	_collider.isDestroy = false;
}


/////////////////////Enemy1
Enemy1::Enemy1(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	Num = 1;

	_pointNum = 47;
	_points = new point4[_pointNum];
	_colors = new color4[_pointNum];

	Create();

	_collider.Init(1.5f, 2.25f);
	_transform = new Transform(matModelView, matProjection, _pointNum, _points, _colors);
	SetEnemy();

	_bulletLink = new BulletLink(10, matModelView, matProjection);

	bomb = new Bomb(matModelView, matProjection);

	hp = 3;
	_collider.hp = hp;
}

Enemy1::~Enemy1() {
	if (_points != NULL)delete[] _points;
	if (_colors != NULL)delete[] _colors;
	if (_transform != NULL) delete _transform;
	if (_bulletLink != NULL) delete _bulletLink;
	if (bomb != NULL) delete bomb;
}

void Enemy1::Create() {
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
		_points[i] = point4(0.1f*cosf(M_PI*2.0*(i - 6) / 20), 0.1f* sinf(M_PI*2.0*(i - 6) / 20), 0.0f, 0.1f);
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

	_colors[32] = color4(0.2f, 0.5f, 0.25f, 1.0f); //(0.75f, 0.25f, 0.25f, 1.0f)
	_colors[33] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[34] = color4(0.2f, 0.5f, 0.25f, 1.0f);

	//Top
	_points[35] = point4(-1.75f, 2.25f, 0.0f, 1.0f);
	_points[36] = point4(1.75f, 2.25f, 0.0f, 1.0f);
	_points[37] = point4(1.25f, 1.5f, 0.0f, 1.0f);
	_points[38] = point4(-1.75f, 2.25f, 0.0f, 1.0f);
	_points[39] = point4(1.25f, 1.5f, 0.0f, 1.0f);
	_points[40] = point4(-1.25f, 1.5f, 0.0f, 1.0f);

	_colors[35] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[36] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[37] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[38] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[39] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[40] = color4(0.2f, 0.5f, 0.25f, 1.0f);

	//Triangle
	_points[41] = point4(1.25f, 1.0f, 0.0f, 1.0f);
	_points[42] = point4(1.75f, 1.0f, 0.0f, 1.0f);
	_points[43] = point4(1.25f, -1.0f, 0.0f, 1.0f);
	_points[44] = point4(-1.25f, 1.0f, 0.0f, 1.0f);
	_points[45] = point4(-1.75f, 1.0f, 0.0f, 1.0f);
	_points[46] = point4(-1.25f, -1.0f, 0.0f, 1.0f);

	_colors[41] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[42] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[43] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[44] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[45] = color4(0.2f, 0.5f, 0.25f, 1.0f);
	_colors[46] = color4(0.2f, 0.5f, 0.25f, 1.0f);
}

void Enemy1::Draw() {
	bomb->Draw();
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

void Enemy1::Update(float delta) {
		shootTime += delta;
		if (shootTime >= 1.5f && (_bulletLink->useCount < _bulletLink->totalCount)) {			
			_bulletLink->Shoot(delta, vec4(_pos.x, _pos.y - 2.25f, 0.0f, 1.0f));
			shootTime = 0.0f;
		}
		hurtTime += delta;
		if (hurtTime >= 1.0f) {
			PlayerHurt();
			hurtTime = 0.0f;
		}

		EnemyMove(delta, 7);

		SetHurt(delta);

	_bulletLink->DetectEnemyBullet(delta, 1, _collider.isDestroy);

	bomb->SetBomb(delta);
}

void Enemy1::SetEnemy() {
	if (_collider.isDestroy) {
		bomb->SetPos(_pos);
		bomb->finish = false;
	}
	Init();
	int b = rand() % 10;
	while (b == preX) {
		b = rand() % 10;
	}
	preX = b;
	_pos.x = (b - 5)*2.0f;
	_pos.y = 18.0f;
	SetPosition(_pos);	
}

/////////////////////Enemy2
Enemy2::Enemy2(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	Num = 2;

	_pointNum = 70;
	_points = new point4[_pointNum];
	_colors = new color4[_pointNum];

	Create();
	_collider.Init(1.5f, 2.25f);
	_transform = new Transform(matModelView, matProjection, _pointNum, _points, _colors);
	SetEnemy();

	_bulletLink = new BulletLink(10, matModelView, matProjection);

	bomb = new Bomb(matModelView, matProjection);

	hp = 5;
	_collider.hp = hp;
}

Enemy2::~Enemy2() {
	if (_points != NULL)delete[] _points;
	if (_colors != NULL)delete[] _colors;
	if (_transform != NULL) delete _transform;
	if (_bulletLink != NULL) delete _bulletLink;
	if (bomb != NULL) delete bomb;
}

void Enemy2::Create() {
	//Body
	_points[0] = point4(-1.5f, 1.5f, 0.0f, 1.0f);
	_points[1] = point4(1.5f, 1.5f, 0.0f, 1.0f);
	_points[2] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[3] = point4(-1.5f, 1.5f, 0.0f, 1.0f);
	_points[4] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[5] = point4(-1.25f, -1.5f, 0.0f, 1.0f);

	_colors[0] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[1] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[2] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[3] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[4] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[5] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//Top
	_points[6] = point4(-1.0f, 2.25f, 0.0f, 1.0f);
	_points[7] = point4(1.0f, 2.25f, 0.0f, 1.0f);
	_points[8] = point4(1.5f, 1.5f, 0.0f, 1.0f);
	_points[9] = point4(-1.0f, 2.25f, 0.0f, 1.0f);
	_points[10] = point4(1.5f, 1.5f, 0.0f, 1.0f);
	_points[11] = point4(-1.5f, 1.5f, 0.0f, 1.0f);

	_colors[6] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[7] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[8] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[9] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[10] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[11] = color4(0.2f, 0.5f, 0.55f, 1.0f);

	//Head
	for (int i = 12; i < 32; i++)
	{
		_points[i] = point4(0.1f*cosf(M_PI*2.0*(i - 6) / 20), 0.1f* sinf(M_PI*2.0*(i - 6) / 20), 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.5f, 0.25f, 1.0f);
	}

	//Eyes
	_points[32] = point4(0.25f, 0.0f, 0.0f, 1.0f);
	_points[33] = point4(0.75f, 0.25f, 0.0f, 1.0f);
	_points[34] = point4(0.5f, -0.25f, 0.0f, 1.0f);
	_points[35] = point4(-0.25f, 0.0f, 0.0f, 1.0f);
	_points[36] = point4(-0.75f, 0.25f, 0.0f, 1.0f);
	_points[37] = point4(-0.5f, -0.25f, 0.0f, 1.0f);

	_colors[32] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[33] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[34] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[35] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[36] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[37] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//LeftRight
	_points[38] = point4(-2.0f, 1.0f, 0.0f, 1.0f);
	_points[39] = point4(-1.35f, 0.7f, 0.0f, 1.0f);
	_points[40] = point4(-1.25f, -0.7f, 0.0f, 1.0f);
	_points[41] = point4(-2.0f, 1.0f, 0.0f, 1.0f);
	_points[42] = point4(-1.25f, -0.7f, 0.0f, 1.0f);
	_points[43] = point4(-1.75f, -0.5f, 0.0f, 1.0f);
	_points[44] = point4(2.0f, 1.0f, 0.0f, 1.0f);
	_points[45] = point4(1.35f, 0.7f, 0.0f, 1.0f);
	_points[46] = point4(1.25f, -0.7f, 0.0f, 1.0f);
	_points[47] = point4(2.0f, 1.0f, 0.0f, 1.0f);
	_points[48] = point4(1.25f, -0.7f, 0.0f, 1.0f);
	_points[49] = point4(1.75f, -0.5f, 0.0f, 1.0f);

	_colors[38] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[39] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[40] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[41] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[42] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[43] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[44] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[45] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[46] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[47] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[48] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	_colors[49] = color4(0.2f, 0.5f, 0.55f, 1.0f);

	for (int i = 50; i < 70; i++)
	{
		_points[i] = point4(0.125f*cosf(M_PI*(i - 50) / 19), -(0.1f* sinf(M_PI*(i - 50) / 19)) - 0.15f, 0.0f, 0.1f);
		_colors[i] = color4(0.2f, 0.5f, 0.55f, 1.0f);
	}
}

void Enemy2::Draw() {
	bomb->Draw();
	_bulletLink->Draw();
	_transform->Draw();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_TRIANGLES, 6, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 20);
	glDrawArrays(GL_TRIANGLES, 32, 3);
	glDrawArrays(GL_TRIANGLES, 35, 3);
	glDrawArrays(GL_TRIANGLES, 38, 6);
	glDrawArrays(GL_TRIANGLES, 44, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 50, 20);
}

void Enemy2::Update(float delta) {
		shootTime += delta;
		if (shootTime >= 2.0f && (_bulletLink->useCount < _bulletLink->totalCount - 2)) {
			_bulletLink->Shoot(0, _pos);
			_bulletLink->Shoot(1, _pos);
			shootTime = 0;
		}

		hurtTime += delta;
		if (hurtTime >= 1.0f) {
			PlayerHurt();
			hurtTime = 0.0f;
		}

		EnemyMove(delta, 5);

		SetHurt(delta);

	_bulletLink->DetectEnemyBullet(delta, 2, _collider.isDestroy);

	bomb->SetBomb(delta);
}



void Enemy2::SetEnemy() {
	if (_collider.isDestroy) {
		bomb->SetPos(_pos);
		bomb->finish = false;
	}
	Init();
	int b = rand() % 10;
	while (b == preX) {
		b = rand() % 10;
	}
	preX = b;
	_pos.x = (b - 5)*2.0f;
	_pos.y = 18.0f;
	SetPosition(_pos);	
}

Enemy3::Enemy3(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	Num = 3;

	_pointNum = 117;
	_points = new point4[_pointNum];
	_colors = new color4[_pointNum];

	Create();
	_collider.Init(4.0f, 4.0f);
	_transform = new Transform(matModelView, matProjection, _pointNum, _points, _colors);
	SetEnemy();
	_state = Animation;

	_bulletLink = new BulletLink(40, matModelView, matProjection);

	_broken = allhp;
	
	for (int i = 0; i < 3; i++)
	{
		smoke[i] = new Smoke(matModelView, matProjection);
	}
	smoke[0]->SetPosition(0, 160, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	smoke[1]->SetPosition(0, 160, vec4(-1.0f, 1.0f, 1.0f, 1.0f));
	smoke[2]->SetPosition(0, 160, vec4(1.0f, 1.0f, 1.0f, 1.0f));

	bomb = new Bomb(matModelView, matProjection);

	hp = 20;
	_collider.hp = hp;
}

Enemy3::~Enemy3() {
	if (_points != NULL)delete[] _points;
	if (_colors != NULL)delete[] _colors;
	if (_transform != NULL) delete _transform;
	if (_bulletLink != NULL) delete _bulletLink;
	if (smoke[0] != NULL) delete smoke[0];
	if (smoke[1] != NULL) delete smoke[1];
	if (smoke[2] != NULL) delete smoke[2];
	if (bomb != NULL) delete bomb;
}

void Enemy3::Create() {
	//Body
	_points[0] = point4(-2.0f, 3.0f, 0.0f, 1.0f);
	_points[1] = point4(2.0f, 3.0f, 0.0f, 1.0f);
	_points[2] = point4(2.0f, -2.5f, 0.0f, 1.0f);
	_points[3] = point4(-2.0f, 3.0f, 0.0f, 1.0f);
	_points[4] = point4(2.0f, -2.5f, 0.0f, 1.0f);
	_points[5] = point4(-2.0f, -2.5f, 0.0f, 1.0f);

	_colors[0] = color4(0.3f, 0.3f, 0.3f, 1.0f);
	_colors[1] = color4(0.3f, 0.3f, 0.3f, 1.0f);
	_colors[2] = color4(0.3f, 0.3f, 0.3f, 1.0f);
	_colors[3] = color4(0.3f, 0.3f, 0.3f, 1.0f);
	_colors[4] = color4(0.3f, 0.3f, 0.3f, 1.0f);
	_colors[5] = color4(0.3f, 0.3f, 0.3f, 1.0f);

	//Buttom
	_points[6] = point4(-2.0f, -2.5f, 0.0f, 1.0f);
	_points[7] = point4(2.0f, -2.5f, 0.0f, 1.0f);
	_points[8] = point4(0.0f, -4.0f, 0.0f, 1.0f);

	_colors[6] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[7] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[8] = color4(0.5f, 0.0f, 0.0f, 1.0f);

	//QuadButtom
	_points[9] = point4(2.0f, 3.0f, 0.0f, 1.0f);
	_points[10] = point4(3.0f, 3.0f, 0.0f, 1.0f);
	_points[11] = point4(3.0f, -1.75f, 0.0f, 1.0f);
	_points[12] = point4(2.0f, 3.0f, 0.0f, 1.0f);
	_points[13] = point4(3.0f, -1.75f, 0.0f, 1.0f);
	_points[14] = point4(2.0f, -1.75f, 0.0f, 1.0f);

	_points[15] = point4(-2.0f, 3.0f, 0.0f, 1.0f);
	_points[16] = point4(-3.0f, 3.0f, 0.0f, 1.0f);
	_points[17] = point4(-3.0f, -1.75f, 0.0f, 1.0f);
	_points[18] = point4(-2.0f, 3.0f, 0.0f, 1.0f);
	_points[19] = point4(-3.0f, -1.75f, 0.0f, 1.0f);
	_points[20] = point4(-2.0f, -1.75f, 0.0f, 1.0f);

	_colors[9] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[10] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[11] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[12] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[13] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[14] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	_colors[15] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[16] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[17] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[18] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[19] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[20] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//QuadBullet
	_points[21] = point4(2.5f, 3.0f, 0.0f, 1.0f);
	_points[22] = point4(3.5f, 3.0f, 0.0f, 1.0f);
	_points[23] = point4(3.5f, -1.75f, 0.0f, 1.0f);
	_points[24] = point4(2.5f, 3.0f, 0.0f, 1.0f);
	_points[25] = point4(3.5f, -1.75f, 0.0f, 1.0f);
	_points[26] = point4(2.5f, -1.75f, 0.0f, 1.0f);

	_points[27] = point4(-2.5f, 3.0f, 0.0f, 1.0f);
	_points[28] = point4(-3.5f, 3.0f, 0.0f, 1.0f);
	_points[29] = point4(-3.5f, -1.75f, 0.0f, 1.0f);
	_points[30] = point4(-2.5f, 3.0f, 0.0f, 1.0f);
	_points[31] = point4(-3.5f, -1.75f, 0.0f, 1.0f);
	_points[32] = point4(-2.5f, -1.75f, 0.0f, 1.0f);

	_colors[21] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[22] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[23] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[24] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[25] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[26] = color4(0.4f, 0.4f, 0.4f, 1.0f);

	_colors[27] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[28] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[29] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[30] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[31] = color4(0.4f, 0.4f, 0.4f, 1.0f);
	_colors[32] = color4(0.4f, 0.4f, 0.4f, 1.0f);

	//CircleBullet
	for (int i = 33; i <53; i++)
	{
		_points[i] = point4(-0.05f*cosf(M_PI*(i - 33) / 19)+0.3, -0.075f* sinf(M_PI*(i - 33) / 19) - 0.175, 0.0f, 0.1f);
		_colors[i] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	}

	for (int i = 53; i <73; i++)
	{
		_points[i] = point4(-0.05f*cosf(M_PI*(i - 53) / 19) - 0.3, -0.075f* sinf(M_PI*(i - 53) / 19) - 0.175, 0.0f, 0.1f);
		_colors[i] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	}

	//LeftRight
	_points[73] = point4(2.0f, 3.0f, 0.0f, 1.0f);
	_points[74] = point4(4.0f, 3.0f, 0.0f, 1.0f);
	_points[75] = point4(4.0f, 2.0f, 0.0f, 1.0f);
	_points[76] = point4(2.0f, 3.0f, 0.0f, 1.0f);
	_points[77] = point4(4.0f, 2.0f, 0.0f, 1.0f);
	_points[78] = point4(2.0f, 0.0f, 0.0f, 1.0f);

	_points[79] = point4(-4.0f, 3.0f, 0.0f, 1.0f);
	_points[80] = point4(-2.0f, 3.0f, 0.0f, 1.0f); 
	_points[81] = point4(-2.0f, 0.0f, 0.0f, 1.0f);
	_points[82] = point4(-4.0f, 3.0f, 0.0f, 1.0f);
	_points[83] = point4(-2.0f, 0.0f, 0.0f, 1.0f);
	_points[84] = point4(-4.0f, 2.0f, 0.0f, 1.0f); 

	_colors[73] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[74] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[75] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[76] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[77] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[78] = color4(0.5f, 0.0f, 0.0f, 1.0f);

	_colors[79] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[80] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[81] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[82] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[83] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[84] = color4(0.5f, 0.0f, 0.0f, 1.0f);

	//Top
	_points[85] = point4(-3.5f, 4.0f, 0.0f, 1.0f);
	_points[86] = point4(3.5f, 4.0f, 0.0f, 1.0f);
	_points[87] = point4(2.0f, 3.0f, 0.0f, 1.0f);
	_points[88] = point4(-3.5f, 4.0f, 0.0f, 1.0f);
	_points[89] = point4(2.0f, 3.0f, 0.0f, 1.0f);
	_points[90] = point4(-2.0f, 3.0f, 0.0f, 1.0f);

	_colors[85] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[86] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[87] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[88] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[89] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[90] = color4(0.5f, 0.0f, 0.0f, 1.0f);

	//Head
	for (int i = 91; i < 111; i++)
	{
		_points[i] = point4(0.175f*cosf(M_PI*2.0*(i - 91) / 20), 0.175f* sinf(M_PI*2.0*(i - 91) / 20), 0.0f, 0.1f);
		_colors[i] = color4(0.75f, 0.5f, 0.25f, 1.0f);
	}

	//Eyes
	_points[111] = point4(0.25f, 0.0f, 0.0f, 1.0f);
	_points[112] = point4(1.5f, 0.8f, 0.0f, 1.0f);
	_points[113] = point4(1.0f, -0.5f, 0.0f, 1.0f);
	_points[114] = point4(-0.25f, 0.0f, 0.0f, 1.0f);
	_points[115] = point4(-1.5f, 0.8f, 0.0f, 1.0f);
	_points[116] = point4(-1.0f, -0.5f, 0.0f, 1.0f);

	_colors[111] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[112] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[113] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[114] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[115] = color4(0.5f, 0.0f, 0.0f, 1.0f);
	_colors[116] = color4(0.5f, 0.0f, 0.0f, 1.0f);
}

void Enemy3::Draw() {
	bomb->Draw();
	_bulletLink->Draw();
	smoke[0]->Draw();
	smoke[1]->Draw();
	smoke[2]->Draw();
	_transform->Draw();
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_TRIANGLES, 6, 3);	
	glDrawArrays(GL_TRIANGLES, 9, 6);
	glDrawArrays(GL_TRIANGLES, 15, 6);
	glDrawArrays(GL_TRIANGLES, 21, 6);
	glDrawArrays(GL_TRIANGLES, 27, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 33, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 53, 20);
	glDrawArrays(GL_TRIANGLES, 73, 6);
	glDrawArrays(GL_TRIANGLES, 79, 6);
	glDrawArrays(GL_TRIANGLES, 85, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 91, 20);
	glDrawArrays(GL_TRIANGLES, 111, 3);
	glDrawArrays(GL_TRIANGLES, 114, 3);
}
void Enemy3::Update(float delta) {
	shootTime += delta;

	

	hurtTime += delta;
	if (hurtTime >= 1.0f) {
		PlayerHurt();
		hurtTime = 0.0f;
	}

	EnemyMove(delta, _state);

	SetState();
	switch (_broken)
	{
	case hp15:
		if(_state==Level_2)smoke[0]->SetPos(_pos + vec4(-3.0f, -1.5f, 0.0f, 1.0f),_angle);
		else smoke[0]->SetPos(_pos + vec4(-3.0f, -1.5f, 0.0f, 1.0f));		
		break;
	case hp10:
		if (_state == Level_2) {
			smoke[0]->SetPos(_pos + vec4(-3.0f, -1.5f, 0.0f, 1.0f), _angle);
			smoke[1]->SetPos(_pos + vec4(3.0f, 0.0f, 0.0f, 1.0f), _angle);
		}
		else {
			smoke[0]->SetPos(_pos + vec4(-3.0f, -1.5f, 0.0f, 1.0f));
			smoke[1]->SetPos(_pos + vec4(3.0f, 0.0f, 0.0f, 1.0f));
		}		
		break;
	case hp5:
		if (_state == Level_2) {
			smoke[0]->SetPos(_pos + vec4(-3.0f, -1.5f, 0.0f, 1.0f), _angle);
			smoke[1]->SetPos(_pos + vec4(3.0f, 0.0f, 0.0f, 1.0f), _angle);
			smoke[2]->SetPos(_pos + vec4(1.5f, 3.5f, 0.0f, 1.0f), _angle);
		}
		else {
			smoke[0]->SetPos(_pos + vec4(-3.0f, -1.5f, 0.0f, 1.0f));
			smoke[1]->SetPos(_pos + vec4(3.0f, 0.0f, 0.0f, 1.0f));
			smoke[2]->SetPos(_pos + vec4(1.5f, 3.5f, 0.0f, 1.0f));
		}		
		break;
	}
	smoke[0]->SetSmoke(delta);
	smoke[1]->SetSmoke(delta);
	smoke[2]->SetSmoke(delta);

	SetHurt(delta);

	_bulletLink->DetectEnemyBullet(delta, 3, _collider.isDestroy);

	bomb->SetBomb(delta);
}

void Enemy3::SetEnemy() {
	if (_collider.isDestroy) {
		bomb->SetPos(_pos);
		bomb->finish = false;
	}
	_pos.x = 0.0f;
	_pos.y = 20.0f;
	SetPosition(_pos);
}

void Enemy3::SetState() {
	if (_collider.hp <= 5) {
		attackTime = 0.05f;
		_broken = hp5;			
		smoke[2]->start = true;
		smoke[1]->start = true;
		smoke[0]->start = true;
	}
	else if (_collider.hp <= 10) {
		speed = 8;
		_broken = hp10;
		smoke[1]->start = true;
		smoke[0]->start = true;
	}
	else if (_collider.hp <= 15) {
		_broken = hp15;
		smoke[0]->start = true;
	}
}

float rest = 0.0f;
int circle = 2;
void Enemy3::EnemyMove(float delta, State state) {
	mat4 mET, mER;	
	switch (state)
	{
	case Animation:
		_pos.y -= speed * delta;
		if (_pos.y <= 10.0f) {
			rest += delta;
			_pos.y = 10.0f;
			if (rest >= 1.0f) {
				_state = Level_1;
				isMove = true;
				rest = 0.0f;
			}			
		}
		mET = Translate(_pos);
		SetPosition(_pos);
		SetTRSMatrix(mET);
		break;
	case Level_1://繞無限發射導彈
		level = 1;
		rest += delta;
		switch (turn)
		{
		case 1:
		if (rest > 2.0f) {
			isMove = true;			
		}
		else if (rest <= 2.0f) {
			isMove = false;
		}
		if (isMove) {
			_pos.x -= speed *delta;
			if (_pos.x <= -10.0f) {
				_pos.x = -10.0f;
				rest = 0.0f;
				turn = 2;
			}
			_pos.y = 10.0f + (-3.0f / 25.0f)*(_pos.x + 5.0f)*(_pos.x + 5.0f) + 3.0f;
		}		
		else {
			if (shootTime >= (0.5f-attackTime) && (_bulletLink->useCount < _bulletLink->totalCount - 1)) {
				_bulletLink->Shoot(level, _pos);
				shootTime = 0.0f;
			}
		}
		break;
		case 2:
		if (rest > 2.0f) {
			isMove = true;
		}
		else if (rest <= 2.0f) {
			isMove = false;
		}
		if (isMove) {
			_pos.x += speed*delta;
			 if (_pos.x >= 0.0f) {
				 _pos.x = 0.0f;
				 rest = 0;
				turn = 3;
			}
			_pos.y = 10.0f + (3.0f / 25.0f)*(_pos.x + 5.0f)*(_pos.x + 5.0f) - 3.0f;
		}
		else {
			if (shootTime >= (0.5f - attackTime) && (_bulletLink->useCount < _bulletLink->totalCount - 1)) {
				_bulletLink->Shoot(level, _pos);
				shootTime = 0.0f;
			}
		}
		break;
		case 3:
			if (rest > 2.0f) {
				isMove = true;
			}
			else if (rest <= 2.0f) {
				isMove = false;
			}
			if (isMove) {
				_pos.x += speed*delta;
				if (_pos.x >= 10.0f) {
					_pos.x = 10.0f;
					rest = 0;
					turn = 4;
				}
				_pos.y = 10.0f + (-3.0f / 25.0f)*(_pos.x - 5.0f)*(_pos.x - 5.0f) + 3.0f;
			}
			else {
				if (shootTime >= (0.5f - attackTime) && (_bulletLink->useCount < _bulletLink->totalCount - 1)) {
					_bulletLink->Shoot(level, _pos);
					shootTime = 0.0f;
				}
			}
		break;
		case 4:
			if (rest > 2.0f) {
				isMove = true;
			}
			else if (rest <= 2.0f) {
				isMove = false;
			}
			if (isMove) {
				_pos.x -= speed*delta;
				if (_pos.x <= 0.0f) {
					_pos.x = 0.0f;
					turn = 1;
					rest = 0;
					_state = Level_2;
				}
				_pos.y = 10.0f + (3.0f / 25.0f)*(_pos.x - 5.0f)*(_pos.x - 5.0f) - 3.0f;
			}
			else {
				if (shootTime >= (0.5f - attackTime) && (_bulletLink->useCount < _bulletLink->totalCount - 1)) {
					_bulletLink->Shoot(level, _pos);
					shootTime = 0.0f;
				}
			}
		break;
		}
		mET = Translate(_pos);
		SetPosition(_pos);
		SetTRSMatrix(mET);
		
		break;
	case Level_2://旋轉發射子彈
		level = 2;
		if (isMove) {
			_pos.y -= speed * delta;
			if (_pos.y <= 0.0f) {
				_pos.y = 0.0f;
				isMove = false;
			}
		}
		else {
			_angle += 90.0f*delta;
			if (_angle >= 360.0*circle) {
				_angle = 0.0*circle;
				_state = Level_3;
				isMove = true;
			}
			if (shootTime >= (0.25f - attackTime) && (_bulletLink->useCount < _bulletLink->totalCount - 4)) {
				_bulletLink->Shoot(_angle, _pos, 0, level);
				_bulletLink->Shoot(_angle, _pos, 1, level);
				_bulletLink->Shoot(_angle, _pos, 2, level);
				_bulletLink->Shoot(_angle, _pos, 3, level);
				shootTime = 0.0f;
			}
		}
		mET = Translate(_pos);
		mER = RotateZ(_angle);
		SetPosition(_pos);
		SetTRSMatrix(mET*mER);
		break;
	case Level_3://上方發射多枚子彈下降	
		level = 3;
		if (isMove) {
			_pos.y += speed * delta;
			if (_pos.y >= 10.0f) {
				_pos.y = 10.0f;
				isMove = false;
			}
			mET = Translate(_pos);
			SetPosition(_pos);
			SetTRSMatrix(mET);
		}
		else {
			rest += delta;
			if (shootTime >= (0.75f - attackTime) && (_bulletLink->useCount < _bulletLink->totalCount - 20)) {
				_bulletLink->Shoot(3, _pos, 20);
				shootTime = 0.0f;		
			}
			if (rest >= 5.0f) {
				_state = Return;
				isMove = false;
				rest = 0.0f;
			}
		}				
		break;
	case Return:
		level = 0;
		rest += delta;
		if (rest >= 2.0f) {
			_state = Level_1;
			isMove = false;
			rest = 0.0f;
		}
		break;
	default:
		break;
	}	
}