#include "Collider.h"

Collider::Collider(float x,float y,vec4 position) {
	DistanceX = x;
	DistanceY = y;
	SetCollider(position);
}

Collider::~Collider() {
}

void Collider::SetCollider(vec4 position) {
	rightTop = vec4(position.x + DistanceX, position.y + DistanceY, 0.0f, 1.0f);
	leftButtom = vec4(position.x - DistanceX, position.y - DistanceY, 0.0f, 1.0f);
}

void Collider::CheckCollider(vec4 left, vec4 right) {
	bool collisionX = (leftButtom.x <= right.x && leftButtom.x >= left.x) || (rightTop.x <= right.x && rightTop.x >= left.x)||
		(left.x <= rightTop.x && left.x >= leftButtom.x)|| (right.x <= rightTop.x && right.x >= leftButtom.x);
	bool collisionY = (leftButtom.y <= right.y && leftButtom.y >= left.y) || (rightTop.y <= right.y && rightTop.y >= left.y) ||
		(left.y <= rightTop.y && left.y >= leftButtom.y) || (right.y <= rightTop.y && right.y >= leftButtom.y);
	Print(collisionX&&collisionY);
}