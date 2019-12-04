#include "Player.h"
Player::Player(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	
	Create();
	
	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors);
	_collider.Init(2.25f, 1.25f, vec4(0.0f, 0.0f, 0.0f, 1.0f));
	
	_protect = new Protect(matModelView, matProjection);
	SetPosition(vec4(0.0f, -10.0f, 0.0f, 1.0f));
	_bulletLink = new BulletLink(10, matModelView, matProjection);

	playerItem[0] = new PlayerItem(matModelView, matProjection);
	playerItem[1] = new PlayerItem(matModelView, matProjection);
	playerItem[2] = new PlayerItem(matModelView, matProjection);

	_collider.hp = hp;
}

Player::~Player() {
	if (_transform != NULL) delete _transform;
	if (_bulletLink != NULL) delete _bulletLink;
	if (_protect != NULL)delete _protect;

	if (playerItem[0] != NULL)delete playerItem[0];
	if (playerItem[1] != NULL)delete playerItem[1];
	if (playerItem[2] != NULL)delete playerItem[2];
}

void Player::Create() {
	//UpQuad
	_points[0] = point4(-1.0f, 0.0f, 0.0f, 1.0f);
	_points[1] = point4(1.0f, 0.0f, 0.0f, 1.0f);
	_points[2] = point4(1.5f, -0.5f, 0.0f, 1.0f);
	_points[3] = point4(-1.0f, 0.0f, 0.0f, 1.0f);
	_points[4] = point4(1.5f, -0.5f, 0.0f, 1.0f);
	_points[5] = point4(-1.5f, -0.5f, 0.0f, 1.0f);

	_colors[0] = color4(0.25f, 0.25f, 0.25f, 1.0f);  // (r, g, b, a)
	_colors[1] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[2] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[3] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[4] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[5] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//Head
	for (int i = 6; i < 26; i++)
	{
		_points[i] = point4(0.1f*cosf(M_PI*(i-6) / (Head_NUM-1)), 0.1f* sinf(M_PI*(i - 6) / (Head_NUM-1)), 0.0f, 0.1f);
		_colors[i] = color4(0.25f, 1.0f, 0.5f, 1.0f);
	}

	//Eyes
	for (int i = 26; i < 46; i++)
	{
		_points[i] = point4(0.025f*cosf(M_PI*2.0f*(i - 26) / 20)+0.05f, 0.025f* sinf(M_PI*2.0f*(i - 26) / 20) + 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	for (int i = 46; i < 66; i++)
	{
		_points[i] = point4(0.025f*cosf(M_PI*2.0f*(i - 46) / 20) - 0.05f, 0.025f* sinf(M_PI*2.0f*(i - 46) / 20) + 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//ButtomQuad
	_points[66] = point4(-2.0f, -0.5f, 0.0f, 1.0f);
	_points[67] = point4(2.0f, -0.5f, 0.0f, 1.0f);
	_points[68] = point4(2.5f, -1.25f, 0.0f, 1.0f);
	_points[69] = point4(-2.0f, -0.5f, 0.0f, 1.0f);
	_points[70] = point4(2.5f, -1.25f, 0.0f, 1.0f);
	_points[71] = point4(-2.5f, -1.25f, 0.0f, 1.0f);

	_colors[66] = color4(0.25f, 0.25f, 0.25f, 1.0f);  // (r, g, b, a)
	_colors[67] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[68] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[69] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[70] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[71] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//ButtomCircle
	for (int i = 72; i < 92; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*(i - 72) / 19) - 0.175f, 0.05f* (-sinf(M_PI*(i - 72) / 19)) - 0.125f, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.75f, 0.2f, 1.0f);
	}
	for (int i = 92; i < 112; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*(i - 92) / 19) , 0.05f* (-sinf(M_PI*(i - 92) / 19)) - 0.125f, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.75f, 0.2f, 1.0f);
	}
	for (int i = 112; i < 132; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*(i - 112) / 19) + 0.175f, 0.05f* (-sinf(M_PI*(i - 112) / 19)) - 0.125f, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.75f, 0.2f, 1.0f);
	}

	//UpCircle
	for (int i = 132; i < 152; i++)
	{
		_points[i] = point4(0.2f*cosf(M_PI*(i - 132) / 19), 0.2f* sinf(M_PI*(i - 132) / 19) - 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 1.0f, 1.0f, 0.25f);
	}

}

void Player::Draw() {
	_bulletLink->Draw();

	if(isProtect)_protect->Draw();

	playerItem[0]->Draw();
	playerItem[1]->Draw();
	playerItem[2]->Draw();

	_transform->Draw();	
	
	glDrawArrays(GL_TRIANGLES, 0, 6); 
	glDrawArrays(GL_TRIANGLE_FAN, 6, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 26, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 46, 20);
	glDrawArrays(GL_TRIANGLES, 66, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 72, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 92, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 112, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 132, 20);
}

void Player::SetPosition(vec4 position) {
	mat4 mT;
	_pos = position;
	mT = Translate(_pos);
	SetTRSMatrix(mT);
	_collider.SetCollider(_pos);
}

void Player::Update(float delta) {
	if (!isDead) {
		if (isShoot && (_bulletLink->useCount< _bulletLink->totalCount) && _pos.y<15.0f&&_pos.y>-15.0f&&_pos.x<15.0f&&_pos.x>-15.0f) {
			shootTime += delta;
			if (shootTime >= 0.3f) {
				if (isTwoBullet) {
					_bulletLink->Shoot(delta, vec4(_pos.x - 0.3f, _pos.y + 1.25f, 0.0f, 1.0f));
					_bulletLink->Shoot(delta, vec4(_pos.x + 0.3f, _pos.y + 1.25f, 0.0f, 1.0f));
				}
				else _bulletLink->Shoot(delta, vec4(_pos.x, _pos.y + 1.25f, 0.0f, 1.0f));				
				shootTime = 0;
			}
		}

		if (isFlyBullet) {
			_bulletLink->bossPos = bossPos;
			if (isUseItem) {
				_bulletLink->Shoot(true, vec4(_pos.x, _pos.y + 1.25f, 0.0f, 1.0f));
				FlyBulletCount++;
				isUseItem = false;
			}
		}		
		else _bulletLink->bossPos = bossPos;

		_bulletLink->DetectBullet(delta);

		SetHurt(delta);		

		if (!playerItem[0]->isClear) {
			playerItem[0]->Update(delta);
			playerItem[0]->SetPlayer(_pos);
			
		}
		else {
			playerItem[0]->Init();
		}

		if (!playerItem[1]->isClear) {
			playerItem[1]->Update(delta);
			playerItem[1]->SetPlayer(_pos);
			
		}
		else {
			playerItem[1]->Init();
		}

		if (!playerItem[2]->isClear) {
			playerItem[2]->Update(delta);
			playerItem[2]->SetPlayer(_pos);

		}
		else {
			playerItem[2]->Init();
		}

		if (isProtect) {		
			protectTime += delta;
			_protect->SetParent(_pos);
			if (protectTime >= 8.0f) {
				Print("a");
				isProtect = false;
			}
			else if (protectTime >= 6.0f&&clearCount < 2)isProClear = true;
			else if (protectTime >= 3.0f&&clearCount < 1)isProClear = true;

			if (isProClear) {
				_protect->SetColor(vec4(0.0f, 0.0f, 0.0f, -0.3f));
				clearCount++;
				isProClear = false;
			}
		}
		else {

			_protect->SetParent(vec4(50.0f, 50.0f, 0.0f, 1.0f));
		}

		if (isTwoBullet) {
			twoBulletTime += delta;
			if (twoBulletTime >= 10.0f)isTwoBullet = false;
		}

		if (FlyBulletCount == 1) {
			playerItem[0]->isClear = true;
			playerItem[0]->SetColor(vec4(0.0f, 0.0f, 0.0f, -1.0f));
		}
		if (FlyBulletCount == 2) {
			playerItem[1]->isClear = true;
			playerItem[1]->SetColor(vec4(0.0f, 0.0f, 0.0f, -1.0f));
		}
		if (FlyBulletCount == 3) {
			playerItem[2]->isClear = true;
			playerItem[2]->SetColor(vec4(0.0f, 0.0f, 0.0f, -1.0f));
		}
		if (FlyBulletCount >= 3) {
			isFlyBullet = false;
		}

		CheckItem();
	}	

	if (_collider.isDestroy)isDead = true;
	else isDead = false;
}

void Player::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Player::SetColor(GLfloat vColor[4], bool hurt) {
	if (hurt)_transform->SetHurtColor(vColor);
	else _transform->SetColor(vColor);
}

float hurtTime = 0.0f;
void Player::SetHurt(float delta) {	
	if (_collider.isHurt) {		
		if(hurtTime == 0.0f)SetColor(vec4(0.6f, 0.0f, 0.0f, 0.0f), true);
		
		hurtTime += delta;
		
		if (hurtTime >= 0.2f) {
			SetColor(vec4(-0.6f, 0.0f, 0.0f, 0.0f), true);
			hurtTime = 0.0f;
			_collider.isHurt = false;
		}
	}	
}

void Player::Init() {
	hp = 20;
	_collider.hp = hp;
	shootTime = 0.0f;
	isShoot = false;
}

void Player::CheckItem() {

	//Protect
	if (CheckCollider(_collider, *_Item_Pro)) {
		playerItem[0]->SetPlayer(_pos);
		_Item_Pro->isDestroy = true;
		isProtect = true;
	}	
	//TwoBullet
	if (CheckCollider(_collider, *_Item_Bullet)) {
		_Item_Bullet->isDestroy = true;
		isTwoBullet = true;
	}
	//FlyBullet
	if (CheckCollider(_collider, *_Item_FlyBullet)) {
		playerItem[0]->isClear = false;
		playerItem[1]->isClear = false;
		playerItem[2]->isClear = false;
		playerItem[2]->SetPosition(vec4(-3.0f, -0.5f, 0.0f, 1.0f), 0.0f);
		playerItem[2]->SetColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));
		playerItem[2]->SetPlayer(_pos);
		playerItem[1]->SetPosition(vec4(-3.0f - 1.5f, -0.48f, 0.0f, 1.0f), 5.0f);
		playerItem[1]->SetColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));
		playerItem[1]->SetPlayer(_pos);
		playerItem[0]->SetPosition(vec4(-3.0f - 3.0f, -0.48f, 0.0f, 1.0f), 10.0f);
		playerItem[0]->SetColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));
		_Item_FlyBullet->isDestroy = true;
		isFlyBullet = true;
	}
	
}

GLboolean Player::CheckCollider(Collider one, Collider two) {
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


///////////////////////
PlayerItem::PlayerItem(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	pointNum = 20;

	_points = new point4[pointNum];
	_colors = new color4[pointNum];
	Create();

	_transform = new Transform(matModelView, matProjection, pointNum, _points, _colors);
	Init();
}

PlayerItem::~PlayerItem() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL) delete[] _points;
	if (_colors != NULL) delete[] _colors;
}

void PlayerItem::Create() {
	//RED
	for (int i = 0; i < 20; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*2.0f*i / 20), 0.05f* sinf(M_PI*2.0f*i / 20), 0.0f, 0.1f);
		_colors[i] = color4(0.8f, 0.8f, 0.8f, 1.0f);
	}
}

void PlayerItem::Update(float delta) {
	mat4 mR;
	float radius;
		_angle += 180.0f*delta;

		radius = Radius(_angle);
		if (_angle >= 360.0f)_angle -= 360.0f;

		_pos.x += sinf(radius) *delta *(10.0f + size);
		_pos.y += cosf(radius) *delta *(10.0f + size);

		SetTRSMatrix(Translate(_playerPos)*Translate(_pos));
}

void PlayerItem::Draw() {
	_transform->Draw();	
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20); 
}

void PlayerItem::SetPlayer(vec4 playerPos) {
	_playerPos = playerPos;
}

void PlayerItem::SetPosition(vec4 pos,float Size) {
	_pos = pos;
	size = Size;
}

void PlayerItem::SetTRSMatrix(mat4 &mat) {
	_transform->SetTRSMatrix(mat);
}

float PlayerItem::Radius(float angle) {
	return (angle*3.14f * 1 / 180.0f);
}

void PlayerItem::SetColor(GLfloat vColor[4]) {
	_transform->SetHurtColor(vColor);
}

void PlayerItem::Init() {
	_pos = vec4(20.0f, 20.0f, 0.0f, 1.0f);
	_angle = 0.0f;
	size = 0.0f;

	SetTRSMatrix(Translate(_pos));
}