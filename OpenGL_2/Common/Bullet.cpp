#include "Bullet.h"
Bullet::Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	Create(matModelView, matProjection, shaderHandle);
}

void Bullet::Create(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	_points[0] = point4(-0.25f, 0.25f, 0.0f, 1.0f);
	_points[1] = point4(0.25f, 0.25f, 0.0f, 1.0f);
	_points[2] = point4(0.25f, -0.25f, 0.0f, 1.0f);
	_points[3] = point4(-0.25f, 0.25f, 0.0f, 1.0f);
	_points[4] = point4(0.25f, -0.25f, 0.0f, 1.0f);
	_points[5] = point4(-0.25f, -0.25f, 0.0f, 1.0f);

	_colors[0] = color4(1.0f, 0.0f, 0.0f, 1.0f);  // (r, g, b, a)
	_colors[1] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[2] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[3] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[4] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[5] = color4(1.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 6; i < Total_NUM; i++)
	{
		_points[i] = point4(0.025f*cosf(M_PI*(i - 6) / (Top_NUM - 1)), 0.025f* sinf(M_PI*(i - 6) / (Top_NUM - 1)) + 0.025, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	_collider.Init(0.25f, 0.5f);
	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors);
}

void Bullet::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
	glDrawArrays(GL_TRIANGLE_FAN, QUAD_NUM, Top_NUM);
}

void Bullet::Update(float delta) {
}

void Bullet::SetPlayerPos(vec4 playerpos) {
	pos = playerpos;
}
void Bullet::SetMove() {
	mat4 mT;

	pos.y += 1 * 0.005f;
	mT = Translate(pos);
	_collider.SetCollider(pos);
	SetTRSMatrix(mT);
}
void Bullet::EnemySetMove() {
	mat4 mT;

	pos.y -= 1 * 0.005f;
	mT = Translate(pos);
	_collider.SetCollider(pos);
	SetTRSMatrix(mT);
}


/////////////////////BulletLink
BulletLink::BulletLink(int total,mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	totalCount = total;
	_Head = _Get = _Tail = NULL;
	_Head = new Bullet(matModelView, matProjection);
	_Tail = _Head;
	for (int i = 0; i < totalCount; i++)
	{
		_Get = new Bullet(matModelView, matProjection);
		_Get->next = NULL;
		_Tail->next = _Get;
		_Tail = _Get;
	}	
}

//射擊
void BulletLink::Shoot(float delta,vec4 pos) {
	if (_ShootHead == NULL) {
		_ShootHead = _Head;
		_Head = _Head->next;
		_ShootTail = _ShootHead;
		_ShootGet = _ShootHead;
		_ShootGet->next = NULL;
		useCount++;
	}
	else {
		_ShootGet = _Head;
		_Head = _Head->next;
		_ShootGet->next = NULL;
		_ShootTail->next = _ShootGet;
		_ShootTail = _ShootGet;
		useCount++;
	}
	_ShootGet->SetPlayerPos(pos);
}

//檢查發射子彈
void BulletLink::DetectBullet() {
	_Link = NULL;
	_ShootGet = _ShootHead;
	while (_ShootGet != NULL) {
		_ShootGet->SetMove();
		if (_ShootGet->GetPos().y >= 12.0f) {
			RecycleBullet();
		}
		else {
			_Link = _ShootGet;
			_ShootGet = _ShootGet->next;
		}
	}
}

void BulletLink::DetectEnemyBullet() {
	_Link = NULL;
	_ShootGet = _ShootHead;
	while (_ShootGet != NULL) {
		_ShootGet->EnemySetMove();
		if (_ShootGet->GetPos().y <= -12.0f) {
			RecycleBullet();
		}
		else {
			_Link = _ShootGet;
			_ShootGet = _ShootGet->next;
		}
	}
}

//回收子彈
void BulletLink::RecycleBullet() {
	if (_Link == NULL) {
		_Get = _ShootGet;
		_ShootHead = _ShootGet->next;
		_ShootGet = _ShootGet->next;
		_Get->next = _Head;
		_Head = _Get;
		useCount--;
	}
	else {
		_Get = _ShootGet;
		_ShootGet = _Link;
		_ShootGet->next = _Get->next;
		_Get->next = _Head;
		_Head = _Get;
		useCount--;
	}
}

BulletLink::~BulletLink() {
	_Get = _Head;
	while (_Get != NULL) {
		_Head = _Get->next;
		delete _Get;
		_Get = _Head;
	}
	delete _Head;

	_ShootGet = _ShootHead;
	while (_ShootGet != NULL) {
		_ShootHead = _ShootGet->next;
		delete _ShootGet;
		_ShootGet = _ShootHead;
	}
	delete _ShootHead;
}

void BulletLink::Draw() {
	_ShootGet = _ShootHead;
	while (_ShootGet != NULL) {
		_ShootGet->Draw();
		_ShootGet = _ShootGet->next;
	}
}

void BulletLink::Update(float delta) {
}

GameObject* BulletLink::DetectCollider() {
	Bullet *colliderGet;
	colliderGet = _ShootHead;
	while (colliderGet != NULL) {
		return colliderGet;
		colliderGet = colliderGet->next;
	}
}