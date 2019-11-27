#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Collider.h"
#include "Enemy.h"
#include "GameManager.h"
class EnemyLink {
private:
	Enemy *_Head_1 , *_Tail_1;
	Enemy *_Head_2, *_Tail_2;
	Enemy *_Head_3;
	Enemy *_Get = NULL;

	Enemy *_Link = NULL;

public:
	Enemy *_UseHead, *_UseTail;
	Enemy *_UseGet = NULL;

	int _totalCount_1,_totalCount_2, _totalCount_3;
	int useCount_1 = 0;
	int useCount_2 = 0;
	int useCount_3 = 0;
	float ShootTime_1 = 0.0f;
	float ShootTime_2 = 0.0f;

	GameManager *gameManager;
	Collider* playerProtect;
	Collider* playerCollider;

	bool enemyIsDestroy = false;

	EnemyLink(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT, int totalCount_1 = 4, int totalCount_2 = 2, int totalCount_3 = 1);
	~EnemyLink();

	void Draw();
	void Update(float delta);
	void DetectEnemy(float delta);
	void RecycleEnemy(int num);

	void UseEnemy(float delta);
};