#pragma once
#include "GameObject.h"
class Collision {
private:
public:
	GLboolean CheckCollider(GameObject *one, GameObject *two);

	void Update(float delta);
};