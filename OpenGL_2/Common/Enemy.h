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
	vec4 _pos;
	vec4 _rot;
public:
	GameManager* gameManager;
	Transform *_transform;
	Collider _collider;
	Enemy *next;
	int Num;
	int hp;
	BulletLink *_bulletLink;
	Collider* playerCollider;
	float preX = 0.0f;
	float hurtColorTime = 0.0f;
	float hurtTime = 0.0f;

	~Enemy();

	virtual void Create() {};
	virtual void Update(float delta) {};
	virtual void Draw() {};

	virtual void SetEnemy() {};
	virtual void PlayerHurt() {};

	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4], bool hurt = false);
	void SetHurt(float delta);

	vec4 GetPos() { return _pos; };

	GLboolean CheckCollider(Collider one, Collider two);
};

class Enemy1 :public Enemy {
private:
	point4 _points[47];
	color4 _colors[47];
public:
	
	float shootTime = 0.0f;

	Enemy1(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Enemy1();

	void Create();
	void Update(float delta);
	void Draw();

	void SetPosition(vec4 position);
	void EnemyMove(float delta);
	void SetEnemy();
	void PlayerHurt();
};

class Enemy2 :public Enemy {
private:
	point4 _points[9];
	color4 _colors[9];
public:
	float shootTime = 0.0f;

	float _fAngle = 0.0f;

	Enemy2(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Enemy2();

	void Create();
	void Update(float delta);
	void Draw();

	void SetPosition(vec4 position);
	void EnemyMove(float delta);
	void SetEnemy();
	void PlayerHurt();
};