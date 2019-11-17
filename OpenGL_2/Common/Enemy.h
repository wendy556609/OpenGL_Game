#include "../Header/Angel.h"
#include "GameObject.h"
#include "Bullet.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
#define Head_NUM 20
#define Eyes_NUM 6
#define Body_NUM 6
#define Buttom_NUM 3
#define Top_NUM 6
#define Triangle_NUM 6
#define Total_NUM Body_NUM+Head_NUM+Eyes_NUM+Buttom_NUM+Top_NUM+Triangle_NUM

class Enemy :public GameObject {
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];
public:
	float shootTime = 0.0;
	BulletLink *_bulletLink;
	Enemy *next;

	Enemy(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Enemy();

	void Create(mat4& matModelView, mat4& matProjection, GLuint shaderHandle);
	void Update(float delta);
	void Draw();

	void SetPosition(vec4 position);
	void EnemyMove(float delta);
	void SetEnemy();
	vec4 GetPos() { return _pos; };
};

class EnemyLink {
private:
	Enemy *_Head = NULL;
	Enemy *_Get = NULL;
	Enemy *_Tail = NULL;

	Enemy *_ShootHead = NULL;
	Enemy *_ShootGet = NULL;
	Enemy *_ShootTail = NULL;

	Enemy *_Link = NULL;

	float _BTime = 0;//發射子彈間隔

public:
	int totalCount;//子彈總數
	int useCount = 0;//發射子彈數量

	EnemyLink(int total, mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~EnemyLink();

	void Draw();
	void Update(float delta);

	void Shoot();
	void DetectBullet(float delta);
	void RecycleBullet();
	Enemy* DetectEnemyCollider();
	GameObject* DetectBulletCollider();
};