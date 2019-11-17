#include "Collision.h"

GLboolean Collision::CheckCollider(GameObject *one, GameObject *two) {
	bool collisionX = (one->_collider.leftButtom.x <= two->_collider.rightTop.x && one->_collider.leftButtom.x >= two->_collider.leftButtom.x) ||
		(one->_collider.rightTop.x <= two->_collider.rightTop.x && one->_collider.rightTop.x >= two->_collider.leftButtom.x) ||
		(two->_collider.leftButtom.x <= one->_collider.rightTop.x && two->_collider.leftButtom.x >= one->_collider.leftButtom.x) ||
		(two->_collider.rightTop.x <= one->_collider.rightTop.x && two->_collider.rightTop.x >= one->_collider.leftButtom.x);
	bool collisionY = (one->_collider.leftButtom.y <= two->_collider.rightTop.y && one->_collider.leftButtom.y >= two->_collider.leftButtom.y) ||
		(one->_collider.rightTop.y <= two->_collider.rightTop.y && one->_collider.rightTop.y >= two->_collider.leftButtom.y) ||
		(two->_collider.leftButtom.y <= one->_collider.rightTop.y && two->_collider.leftButtom.y >= one->_collider.leftButtom.y) ||
		(two->_collider.rightTop.y <= one->_collider.rightTop.y && two->_collider.rightTop.y >= one->_collider.leftButtom.y);
	return collisionX&&collisionY;
}