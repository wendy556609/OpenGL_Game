#include "Bullet.h"
#include "EnemyLink.h"

Bullet::Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	Create();

	_collider.Init(0.25f, 0.55f);
	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors);
}

void Bullet::Create() {
	_points[0] = point4(-0.25f, 0.25f, 0.0f, 1.0f);
	_points[1] = point4(0.25f, 0.25f, 0.0f, 1.0f);
	_points[2] = point4(0.25f, -0.25f, 0.0f, 1.0f);
	_points[3] = point4(-0.25f, 0.25f, 0.0f, 1.0f);
	_points[4] = point4(0.25f, -0.25f, 0.0f, 1.0f);
	_points[5] = point4(-0.25f, -0.25f, 0.0f, 1.0f);

	_colors[0] = color4(0.8f, 0.0f, 0.0f, 1.0f);  // (r, g, b, a)
	_colors[1] = color4(0.8f, 0.0f, 0.0f, 1.0f);
	_colors[2] = color4(0.8f, 0.0f, 0.0f, 1.0f);
	_colors[3] = color4(0.8f, 0.0f, 0.0f, 1.0f);
	_colors[4] = color4(0.8f, 0.0f, 0.0f, 1.0f);
	_colors[5] = color4(0.8f, 0.0f, 0.0f, 1.0f);

	for (int i = 6; i < Total_NUM; i++)
	{
		_points[i] = point4(0.025f*cosf(M_PI*(i - 6) / (Top_NUM - 1)), 0.025f* sinf(M_PI*(i - 6) / (Top_NUM - 1)) + 0.02, 0.0f, 0.1f);
		_colors[i] = color4(0.8f, 0.0f, 0.0f, 1.0f);
	}
}

void Bullet::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
	glDrawArrays(GL_TRIANGLE_FAN, QUAD_NUM, Top_NUM);
}

Bullet::~Bullet() {
	if (_transform != NULL) delete _transform;
}

void Bullet::Update(float delta) {
}

void Bullet::SetPos(float angle, vec4 pos, int num) {
	Num = num;
	_fAngle = angle;
	_pos = pos;
	_collider.SetCollider(_pos);
}

void Bullet::SetPos(vec4 pos) {
	_pos = pos;
	_collider.SetCollider(_pos);
}

//Player
void Bullet::SetMove(float delta) {
	mat4 mT;

	_pos.y += 1 * delta *10.0f;
	mT = Translate(_pos);
	_collider.SetCollider(_pos);
	SetTRSMatrix(mT);
}

void Bullet::SetFlyMove(float delta) {
	mat4 mT;

	direct.x = bossPos.x - _pos.x;
	direct.y = bossPos.y - _pos.y;
	direct = direct / pow(direct.x*direct.x + direct.y*direct.y, 0.5);

	_pos.x += direct.x* delta *10.0f;
	_pos.y += direct.y* delta *10.0f;
	mT = Translate(_pos);
	_collider.SetCollider(_pos);
	SetTRSMatrix(mT);
}

//Enemy
bool turn = false;
void Bullet::EnemySetMove(float delta, EnemyName enemyName) {
	mat4 mT, mR;
	float radius = 0.0f;
	switch (enemyName)
	{
	case Bullet::Enemy1://直線下降	
		mR = RotateZ(180.0f);
		_pos.y -= 10.0 * delta;
		mT = Translate(_pos);
		_collider.SetCollider(_pos);
		SetTRSMatrix(mT*mR);
		break;
	case Bullet::Enemy2://曲線下降
		_fAngle += 5.0f*delta;
		if (Num == 0) {
			_pos.x += sin(_fAngle)*0.005f;
		}
		if (Num == 1) {
			_pos.x -= sin(_fAngle)*0.005f;
		}
		_pos.y -= 8.0f * delta;
		mT = Translate(_pos);
		_collider.SetCollider(_pos);
		SetTRSMatrix(mT*mR*RotateZ(180.0f));
		break;
	case Bullet::Enemy3:
		switch (level)
		{
		case 1://導彈
			sTime += delta;
			if (!flag) {
				direct.x = playerPos.x - _pos.x;
				direct.y = playerPos.y - _pos.y;
				direct = direct / pow(direct.x*direct.x + direct.y*direct.y, 0.5);
			}
			if (sTime >= 2.0f) {
				flag = true;
				sTime = 0.0f;
			}
			_pos.x += direct.x* delta *10.0f;
			_pos.y += direct.y* delta *10.0f;
			mT = Translate(_pos);
			_collider.SetCollider(_pos);
			SetTRSMatrix(mT*RotateZ(180.0f));
			break;
		case 2://旋轉發射
			switch (Num)
			{
			case 0:
				radius = Radius(_fAngle);
				mR = RotateZ(_fAngle);
				break;
			case 1:
				radius = Radius(_fAngle + 90.0);
				mR = RotateZ(_fAngle + 90.0);
				break;
			case 2:
				radius = Radius(_fAngle + 180.0);
				mR = RotateZ(_fAngle + 180.0);
				break;
			case 3:
				radius = Radius(_fAngle + 270.0);
				mR = RotateZ(_fAngle + 270.0);
				break;
			}
			_pos.x += sin(radius)* delta * 10.0f;
			_pos.y -= cos(radius)* delta * 10.0f;
			mT = Translate(_pos);
			_collider.SetCollider(_pos);
			SetTRSMatrix(mT*mR*RotateZ(180.0f));
			break;
		case 3://上方一排掉落
			sTime += delta;
			if (sTime >= 2.0f) {
				flag = true;
			}
			if (flag) {
				switch (Num)
				{
				case 0:
					if (turn) {
						radius = Radius(45.0);
						mR = RotateZ(45.0);
					}
					else {
						radius = Radius(-45.0);
						mR = RotateZ(-45.0);
					}
					break;
				case 1:
					if (turn) {
						radius = Radius(-45.0);
						mR = RotateZ(-45.0);
					}
					else {
						radius = Radius(45.0);
						mR = RotateZ(45.0);
					}
					break;
				}
				_pos.x += sin(radius)* delta * 10.0f;
				_pos.y -= cos(radius)* delta * 10.0f;
				if (sTime >= 1.0f) {
					turn = !turn;
					sTime = 0.0;
				}
			}
			else {
				mR = RotateZ(0.0);
			}
			mT = Translate(_pos);
			_collider.SetCollider(_pos);
			SetTRSMatrix(mT*mR*RotateZ(180.0f));
			break;
		}
		break;
	}
}

void Bullet::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Bullet::SetColor(GLfloat vColor[4]) {
	_transform->SetColor(vColor);
}

float Bullet::Radius(float angle) {
	return (angle*3.14f * 1 / 180.0);
}

void Bullet::Init() {
	isUseItem = false;
	flag = false;
	sTime = 0.0f;
}


/////////////////////BulletLink
BulletLink::BulletLink(int total,mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	totalCount = total;
	_Head = _Get = _Tail = NULL;
	_Head = new Bullet(matModelView, matProjection);
	_Tail = _Head;
	for (int i = 1; i < totalCount; i++)
	{
		_Get = new Bullet(matModelView, matProjection);
		_Get->next = NULL;
		_Tail->next = _Get;
		_Tail = _Get;
	}	
	
}

//射擊
void BulletLink::Shoot(int num, vec4 pos) {
	Bullet *shootGet;

	if (_ShootHead == NULL) {
		shootGet = _Head;
		_Head = _Head->next;
		shootGet->next = NULL;
		_ShootTail = _ShootHead = shootGet;
		useCount++;
		shootGet->SetPos(pos);
		shootGet->Init();
		shootGet->level = num;
		shootGet->Num = num;
	}
	else {
		shootGet = _Head;
		if (_Head != NULL)_Head = _Head->next;
		else _Tail = _Head;
		if (shootGet != NULL) {
			shootGet->next = NULL;
			_ShootTail->next = shootGet;
			_ShootTail = shootGet;
			useCount++;
			shootGet->SetPos(pos);
			shootGet->Init();
			shootGet->level = num;
			shootGet->Num = num;
		}
	}
	
}

void BulletLink::Shoot(float angle, vec4 pos, int num, int level) {
	Bullet *shootGet;

	if (_ShootHead == NULL) {
		shootGet = _Head;
		_Head = _Head->next;
		shootGet->next = NULL;
		_ShootTail = _ShootHead = shootGet;
		useCount++;
		shootGet->SetPos(angle, pos, num);
		shootGet->Init();
		shootGet->level = level;
	}
	else {
		shootGet = _Head;
		if (_Head != NULL)_Head = _Head->next;
		else _Tail = _Head;
		if (shootGet != NULL) {
			shootGet->next = NULL;
			_ShootTail->next = shootGet;
			_ShootTail = shootGet;
			useCount++;
			shootGet->SetPos(angle, pos, num);
			shootGet->Init();
			shootGet->level = level;
		}
	}
	
}

void BulletLink::Shoot(bool useItem,vec4 pos) {
	Bullet *shootGet;
		
		if (_ShootHead == NULL) {
			shootGet = _Head;
			_Head = _Head->next;
			shootGet->next = NULL;
			_ShootTail = _ShootHead = shootGet;
			useCount++;
			shootGet->SetPos(pos);
			shootGet->Init();
			shootGet->isUseItem = true;
		}
		else {
			shootGet = _Head;
			if (_Head != NULL)_Head = _Head->next;
			else _Tail = _Head;
			if (shootGet != NULL) {
			shootGet->next = NULL;
			_ShootTail->next = shootGet;
			_ShootTail = shootGet;
			useCount++;
			shootGet->SetPos(pos);
			shootGet->Init();
			shootGet->isUseItem = true;
			}
		}	
		
}

void BulletLink::Shoot(float delta,vec4 pos) {
	Bullet *shootGet;

	if (_ShootHead == NULL) {
		shootGet = _Head;
		_Head = _Head->next;
		shootGet->next = NULL;
		_ShootTail = _ShootHead = shootGet;
		useCount++;
		shootGet->SetPos(pos);
	}
	else {
		shootGet = _Head;
		if (_Head != NULL)_Head = _Head->next;
		else _Tail = _Head;
		if (shootGet != NULL) {
			shootGet->next = NULL;
			_ShootTail->next = shootGet;
			_ShootTail = shootGet;
			useCount++;
			shootGet->SetPos(pos);
		}
	}
	shootGet->Init();
}

void BulletLink::Shoot(int level, vec4 pos, int tot) {
	Bullet *shootGet;

	for (int i = 0; i < tot; i++)
	{
		if (_ShootHead == NULL) {
			shootGet = _Head;
			_Head = _Head->next;
			shootGet->next = NULL;
			_ShootTail = _ShootHead = shootGet;
			useCount++;
			shootGet->SetPos(vec4(pos.x - (10.0f - i), pos.y, pos.z, pos.w));
			
		}
		else {
		
			shootGet = _Head;
			if (_Head != NULL)_Head = _Head->next;
			else _Tail = _Head;
			if (shootGet != NULL) {
				shootGet->next = NULL;
				_ShootTail->next = shootGet;
				_ShootTail = shootGet;
				useCount++;
				shootGet->SetPos(vec4(pos.x - (10.0f - i), pos.y, pos.z, pos.w));
			}
		}	
		shootGet->Init();
		shootGet->Num = i % 2;
		shootGet->level = level;		
	}
}

//Player檢查發射子彈
void BulletLink::DetectBullet(float delta) {
	_Link = NULL;
	_ShootGet = _ShootHead;

	while (_ShootGet != NULL) {
		if (_ShootGet->isUseItem) {
			_ShootGet->bossPos = bossPos;
			_ShootGet->SetFlyMove(delta);
		}
		else _ShootGet->SetMove(delta);		
		EnemyCheck(_ShootGet->_collider);
		if (_ShootGet->GetPos().y >= 15.0f) {
			RecycleBullet();
		}
		
		else if (enemyIsDestroy) {
			RecycleBullet();
			enemyIsDestroy = false;
		}
		else {
			_Link = _ShootGet;
			_ShootGet = _ShootGet->next;
		}		
	}
}

//敵人檢查已發射子彈
void BulletLink::DetectEnemyBullet(float delta, int enemyName, bool isDestroy) {
	int Count = 0;
	_Link = NULL;
	_ShootGet = _ShootHead;
	while (_ShootGet != NULL) {
		switch (enemyName)
		{
		case 1:
			_ShootGet->EnemySetMove(delta, _ShootGet->Enemy1);
			break;
		case 2:
			_ShootGet->EnemySetMove(delta, _ShootGet->Enemy2);
			break;
		case 3:
			_ShootGet->playerPos = playerCollider->GetPlayerPos();
			_ShootGet->EnemySetMove(delta, _ShootGet->Enemy3);
			break;
		}
		if (CheckCollider(_ShootGet->_collider, *playerCollider)) {
			RecycleBullet();
			if (Count <= 0) {
				playerCollider->hp -= 1;
				playerCollider->isHurt = true;
				Count++;
			}
			if (playerCollider->hp <= 0) {
				playerCollider->hp = 0;
				playerCollider->isDestroy = true;
			}
		}
		else if (CheckCollider(_ShootGet->_collider, *playerProtect)) {
			RecycleBullet();
		}
		else if (isDestroy) {
			RecycleBullet();
		}
		else if (_ShootGet->GetPos().y <= -15.0f || _ShootGet->GetPos().y >= 15.0f || _ShootGet->GetPos().x <= -15.0f || _ShootGet->GetPos().x >= 15.0f) {
			RecycleBullet();
		}
		else {
			_Link = _ShootGet;
			_ShootGet = _ShootGet->next;
		}
	}
	
}

//Player子彈檢查Enemy Collider
void BulletLink::EnemyCheck(Collider one) {
	Enemy* checkGet;
	int Count = 0;
	checkGet = enemyLink->_UseHead;
	while (checkGet != NULL&&!enemyIsDestroy) {
		if (CheckCollider(one, checkGet->_collider)) {
			enemyIsDestroy = true;
			if (Count <= 0) {
				checkGet->_collider.hp -= 1;
				checkGet->_collider.isHurt = true;
				Count++;
			}
			if (checkGet->_collider.hp <= 0) {

				checkGet->_collider.isDestroy = true;
			}
		}
		checkGet = checkGet->next;
	}
}

//回收子彈
void BulletLink::RecycleBullet() {
	Bullet* recycleGet;
	if (_Head == NULL) {
		recycleGet = _ShootGet;
		_ShootGet = _ShootGet->next;
		if (_ShootGet == NULL)_ShootTail = _Link;
		if (_Link != NULL)_Link->next = _ShootGet;
		else _ShootHead = _ShootGet;
		recycleGet->next = NULL;
		_Tail = _Head = recycleGet;
		useCount--;
		
	}
	else {
		recycleGet = _ShootGet;
		_ShootGet = _ShootGet->next;
		if (_ShootGet == NULL)_ShootTail = _Link;
		if (_Link != NULL)_Link->next = _ShootGet;
		else _ShootHead = _ShootGet;
		recycleGet->next = NULL;
		_Tail->next = recycleGet;
		_Tail = recycleGet;
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
	Bullet* drawGet;
	drawGet = _ShootHead;
	while (drawGet != NULL) {
		drawGet->Draw();
		drawGet = drawGet->next;
	}
}

void BulletLink::Update(float delta) {
}

GLboolean BulletLink::CheckCollider(Collider one, Collider two) {
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