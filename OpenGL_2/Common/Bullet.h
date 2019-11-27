#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Collider.h"

class EnemyLink;
#define QUAD_NUM 6 
#define Top_NUM 20
#define Total_NUM QUAD_NUM+Top_NUM

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Bullet {
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];

	vec4 _pos;
	float _fAngle = 0.0f;
public:
	
	Bullet *next;
	Transform *_transform;
	Collider _collider;
	bool isTouch = false;
	int Num;

	Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Bullet();

	void Create();
	void Update(float delta);
	void Draw();

	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]);

	void SetPlayerPos(vec4 pos, float angle = 0.0f);
	void SetMove();
	void EnemySetMove();
	void Enemy2SetMove(float delta, int num);
	//void GetCollider(Collider other);
	

	vec4 GetPos() { return _pos; }
};


//子彈鏈結串列
class BulletLink {
private:
	Bullet *_Head = NULL;
	Bullet *_Get = NULL;
	Bullet *_Tail = NULL;

	Bullet *_ShootHead = NULL;
	Bullet *_ShootGet = NULL;
	Bullet *_ShootTail = NULL;

	Bullet *_Link = NULL;

	float _BTime = 0;//發射子彈間隔
	
public:
	int totalCount;//子彈總數
	int useCount = 0;//發射子彈數量
	float ShootTime = 0.0f;

	bool enemyIsDestroy = false;
	bool enter = false;
	
	EnemyLink* enemyLink = NULL;
	Collider* playerCollider = NULL;
	//Collider* playerProtect = NULL;

	BulletLink(int total,mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~BulletLink();

	void Draw();
	void Update(float delta);

	void Shoot(int num,float delta, vec4 pos);
	void Shoot(float delta, vec4 pos, float angle = 0.0f);
	void DetectEnemy2Bullet(float delta);
	void DetectEnemyBullet();
	void DetectBullet();
	void RecycleBullet();
	//void GetPlayerCollider(Collider other);
	GLboolean CheckCollider(Collider one, Collider two);
	void EnemyCheck(Collider one);
};