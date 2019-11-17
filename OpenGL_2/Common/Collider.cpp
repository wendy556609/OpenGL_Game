#include "Collider.h"

void Collider::Init(float x, float y, vec4 position) {
	DistanceX = x;
	DistanceY = y;
	SetCollider(position);
}

void Collider::SetCollider(vec4 position) {
	rightTop = vec4(position.x + DistanceX, position.y + DistanceY, 0.0f, 1.0f);
	leftButtom = vec4(position.x - DistanceX, position.y - DistanceY, 0.0f, 1.0f);
}


