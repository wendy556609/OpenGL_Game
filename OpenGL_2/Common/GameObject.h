#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Collider.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class GameObject {
private:
protected:
	vec4 _pos;
public:
	Transform *_transform;
	Collider _collider;
	int hp;

	Collider* playerCollider;

	~GameObject();

	//virtual void test() { Print("EnemyManager"); };
	virtual void Create(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {};
	virtual void Update(float delta) {};
	virtual void Draw() {};

	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]);

	GLboolean CheckCollider(Collider one, Collider two);
};