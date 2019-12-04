#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Collider.h"
class Item
{
private:	
protected:
	Transform *_transform;

	int _pointNum;
	point4 *_points;
	color4 *_colors;

	vec4 _pos;

	virtual void Create() = 0;
	void SetTRSMatrix(mat4 &mat);
public:
	Collider _collider;
	bool start = false;

	virtual void Init() = 0;

	virtual void Update(float delta) = 0;
	virtual void Draw() = 0;

	vec4 GetPos() { return _pos; };
};

class Item_Pro :public Item
{
private:
protected:
	void Create();
public:
	Collider _collider;

	Item_Pro(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Item_Pro();

	void Update(float delta);
	void Draw();

	void Init();
};

class Item_Bullet :public Item
{
private:
protected:
	void Create();
public:
	Collider _collider;

	Item_Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Item_Bullet();

	void Update(float delta);
	void Draw();

	void Init();
};

class Item_FlyBullet :public Item
{
private:
protected:
	void Create();
public:
	Collider _collider;

	Item_FlyBullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Item_FlyBullet();

	void Update(float delta);
	void Draw();

	void Init();
};