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



///////////////Collision
GLboolean Collision::CheckCollider(Collider one, Collider two) {
	bool collisionX = (one.leftButtom.x <= two.rightTop.x && one.leftButtom.x >= two.leftButtom.x) || (one.rightTop.x <= two.rightTop.x && one.rightTop.x >= two.leftButtom.x) ||
		(two.leftButtom.x <= one.rightTop.x && two.leftButtom.x >= one.leftButtom.x) || (two.rightTop.x <= one.rightTop.x && two.rightTop.x >= one.leftButtom.x);
	bool collisionY = (one.leftButtom.y <= two.rightTop.y && one.leftButtom.y >= two.leftButtom.y) || (one.rightTop.y <= two.rightTop.y && one.rightTop.y >= two.leftButtom.y) ||
		(two.leftButtom.y <= one.rightTop.y && two.leftButtom.y >= one.leftButtom.y) || (two.rightTop.y <= one.rightTop.y && two.rightTop.y >= one.leftButtom.y);
	return collisionX&&collisionY;
}

