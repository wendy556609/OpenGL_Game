#pragma once

#include "../Header/Angel.h"

class Collider {
private:	
	float DistanceX;
	float DistanceY;
public:
	vec4 rightTop;
	vec4 leftButtom;

	Collider(float x,float y,vec4 position);
	~Collider();

	void SetCollider(vec4 position);
	void CheckCollider(vec4 left, vec4 right);
};