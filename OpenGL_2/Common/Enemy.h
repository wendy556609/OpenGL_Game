#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Collider.h"
#include "Bullet.h"
#include "GameManager.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Enemy {
private:	
protected:
	Transform *_transform;
	
	int _pointNum;
	point4 *_points;
	color4 *_colors;

	vec4 _pos;
	
	int hp;

	float preX = 0.0f;
	float hurtColorTime = 0.0f;
	float hurtTime = 0.0f;
	float shootTime = 0.0f;

	virtual void Create() = 0;

	virtual void EnemyMove(float delta, int speed);

	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4], bool hurt = false);

	void SetHurt(float delta);
	void SetPosition(vec4 position);
	void PlayerHurt();

	GLboolean CheckCollider(Collider one, Collider two);
public:
	GameManager* gameManager;
	Collider _collider;
	Collider* playerCollider;

	Enemy *next;

	BulletLink *_bulletLink;
	
	int Num;
		
	virtual void Update(float delta) = 0;
	virtual void Draw() = 0;

	virtual void SetEnemy() = 0;
	virtual void Init();

	GLboolean GetDestroy() { return _collider.isDestroy; };
	vec4 GetPos() { return _pos; };
};

class Enemy1 :public Enemy {
private:
public:
	Enemy1(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Enemy1();

	void Create();
	void Update(float delta);
	void Draw();

	void SetEnemy();
};

class Enemy2 :public Enemy {
private:
public:
	float _fAngle = 0.0f;

	Enemy2(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Enemy2();

	void Create();
	void Update(float delta);
	void Draw();

	void SetEnemy();
};

class Enemy3 :public Enemy {
private:
	enum State
	{
		Animation,
		Level_1,
		Level_2,
		Level_3,
		Return
	};
	State _state;

	enum Broken {
		allhp,
		hp15,
		hp10,
		hp5
	};
	Broken _broken;

	int turn = 1;
	int level = 0;

	int speed = 5;
	float attackTime = 0.0f;
public:
	bool isMove = false;
	float _angle = 0.0f;

	Enemy3(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Enemy3();

	void Create();
	void Update(float delta);
	void Draw();

	void SetState();
	void SetEnemy();
	void EnemyMove(float delta, State state);
};