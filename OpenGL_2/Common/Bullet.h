#pragma once
#include "../Header/Angel.h"
#include "GameObject.h"
#define QUAD_NUM 6 
#define Top_NUM 20
#define Total_NUM QUAD_NUM+Top_NUM

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Bullet :public GameObject{
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];

public:
	Bullet *next;

	Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);

	void Create(mat4& matModelView, mat4& matProjection, GLuint shaderHandle);
	void Update(float delta);
	void Draw();

	void SetPlayerPos(vec4 pos);
	void SetMove();
	void EnemySetMove();

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

	BulletLink(int total,mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~BulletLink();

	void Draw();
	void Update(float delta);

	void Shoot(float delta,vec4 pos);	
	void DetectEnemyBullet();
	void DetectBullet();	
	void RecycleBullet();	
	GameObject* DetectCollider();
};