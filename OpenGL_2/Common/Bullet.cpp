#include "Bullet.h"
Bullet::Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	Create();

	_collider.Init(0.2f, 0.5f);
	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors);
}

void Bullet::Create() {
	_points[0] = point4(-0.2f, 0.2f, 0.0f, 1.0f);
	_points[1] = point4(0.2f, 0.2f, 0.0f, 1.0f);
	_points[2] = point4(0.2f, -0.2f, 0.0f, 1.0f);
	_points[3] = point4(-0.2f, 0.2f, 0.0f, 1.0f);
	_points[4] = point4(0.2f, -0.2f, 0.0f, 1.0f);
	_points[5] = point4(-0.2f, -0.2f, 0.0f, 1.0f);

	_colors[0] = color4(1.0f, 0.0f, 0.0f, 1.0f);  // (r, g, b, a)
	_colors[1] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[2] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[3] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[4] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[5] = color4(1.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 6; i < Total_NUM; i++)
	{
		_points[i] = point4(0.02f*cosf(M_PI*(i - 6) / (Top_NUM - 1)), 0.02f* sinf(M_PI*(i - 6) / (Top_NUM - 1)) + 0.02, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.0f, 0.0f, 1.0f);
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

void Bullet::SetPlayerPos(vec4 playerpos) {
	_pos = playerpos;
	_collider.SetCollider(_pos);
}
void Bullet::SetMove() {
	mat4 mT;

	_pos.y += 1 * 0.005f;
	mT = Translate(_pos);
	_collider.SetCollider(_pos);
	SetTRSMatrix(mT);
}
void Bullet::EnemySetMove() {
	mat4 mT,mR;
	mR = RotateZ(180.0f);
	_pos.y -= 1 * 0.005f;
	mT = Translate(_pos);
	_collider.SetCollider(_pos);
	SetTRSMatrix(mT*mR);
}

void Bullet::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Bullet::SetColor(GLfloat vColor[4]) {
	_transform->SetColor(vColor);
}
//
//void Bullet::GetCollider(Collider other) {
//	if (CheckCollider(this->_collider, other)) {
//		Print("Touch");
//	}
//}




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
void BulletLink::Shoot(float delta,vec4 pos) {
	Bullet *shootGet;
		
		if (_ShootHead == NULL) {
			shootGet = _Head;
			_Head = _Head->next;
			shootGet->next = NULL;
			_ShootTail = _ShootHead = shootGet;
			useCount++;
			shootGet->SetPlayerPos(pos);
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
			shootGet->SetPlayerPos(pos);
			}
		}	
}

//檢查發射子彈
void BulletLink::DetectBullet() {
	_Link = NULL;
	_ShootGet = _ShootHead;

	while (_ShootGet != NULL) {
		_ShootGet->SetMove();
		EnemyCheck(_ShootGet->_collider);
		if (_ShootGet->GetPos().y >= 15.0f) {
			RecycleBullet();
		}
		
		else if (enemyIsDestroy) {
			RecycleBullet();
			enemyIsDestroy = false;
		}
		else {
			//printf("%d",useCount);
			_Link = _ShootGet;
			_ShootGet = _ShootGet->next;
		}		
	}
}

void BulletLink::DetectEnemyBullet() {
	int Count = 0;
	_Link = NULL;
	_ShootGet = _ShootHead;
	while (_ShootGet != NULL) {
		_ShootGet->EnemySetMove();
		if (CheckCollider(_ShootGet->_collider, *playerCollider)) {
			RecycleBullet();
			if (Count <= 0) {
				playerCollider->hp -= 1;
				Count++;
			}
			if (playerCollider->hp <= 0) {
				playerCollider->hp = 0;
				//Print("Dead");

			}
		}
		else if (_ShootGet->GetPos().y <= -15.0f) {
			RecycleBullet();
		}
		else {
			_Link = _ShootGet;
			_ShootGet = _ShootGet->next;
		}
	}
}

void BulletLink::EnemyCheck(Collider one) {
	int Count = 0;
	
	if (CheckCollider(one, *enemyCollider[0])) {
		enemyIsDestroy = true;
		if (Count <= 0) {
			enemyCollider[0]->hp -= 1;
			Count++;
		}		
		if (enemyCollider[0]->hp <= 0) {
			
			enemyCollider[0]->isDestroy = true;
			
		}		
		
	}
	else if (CheckCollider(one, *enemyCollider[1])) {
		enemyIsDestroy = true;
		if (Count <= 0) {
		enemyCollider[1]->hp -= 1;
		Count++;
		}
		if (enemyCollider[1]->hp <= 0) {
			
			enemyCollider[1]->isDestroy = true;
		}

	}
	else if (CheckCollider(one, *enemyCollider[2])) {
		enemyIsDestroy = true;
		if (Count <= 0) {
		enemyCollider[2]->hp -= 1;
		Count++;
		}
		if (enemyCollider[2]->hp <= 0) {
			
			enemyCollider[2]->isDestroy = true;
		}		
	}
	else if (CheckCollider(one, *enemyCollider[3])) {
		enemyIsDestroy = true;
		if (Count <= 0) {
		enemyCollider[3]->hp -= 1;
		Count++;
		}
		if (enemyCollider[3]->hp <= 0) {
			
			enemyCollider[3]->isDestroy = true;
		}		
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
		//Print(useCosunt);
	}
	Print(useCount);
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
		//Print(_ShootGet);
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