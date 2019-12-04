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
	Transform *_transform;

	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];

	vec4 _pos;

	vec4 direct = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	float sTime = 0.0f;
	float _fAngle = 0.0f;

	bool flag = false;//判斷Boss要發射

	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]);

	float Radius(float angle);
public:
	enum EnemyName
	{
		Enemy1 = 0,
		Enemy2,
		Enemy3
	};
	Bullet *next;
	
	Collider _collider;
	vec4 playerPos;	
	vec4 bossPos;
	
	int Num;
	int level = 0;	
	bool isUseItem = false;

	Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Bullet();

	void Create();
	void Update(float delta);
	void Draw();

	//子彈初始位置
	void SetPos(float angle, vec4 pos, int num);
	void SetPos(vec4 pos);

	//Player
	void SetMove(float delta);
	void SetFlyMove(float delta);
	//Enemy
	void EnemySetMove(float delta, EnemyName name); 

	void Init();
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
public:
	int totalCount;//子彈總數
	int useCount = 0;//發射子彈數量

	float ShootTime = 0.0f;

	bool enemyIsDestroy = false;
	bool useItem = false;
	
	EnemyLink* enemyLink = NULL;
	Collider* playerCollider = NULL;
	Collider* playerProtect = NULL;

	vec4 bossPos;

	BulletLink(int total,mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~BulletLink();

	void Draw();
	void Update(float delta);

	void Shoot(int level, vec4 pos, int tot);
	void Shoot(int num, vec4 pos);
	void Shoot(float angle, vec4 pos, int num, int level);
	void Shoot(bool useItem, vec4 pos);
	void Shoot(float delta, vec4 pos);

	void DetectEnemyBullet(float delta, int enemyName, bool isDestroy);
	void DetectBullet(float delta);
	void RecycleBullet();

	GLboolean CheckCollider(Collider one, Collider two);
	void EnemyCheck(Collider one);
};