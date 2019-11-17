#include "GameObject.h"

GameObject::~GameObject() {
	if (_transform != NULL) delete _transform;
}

void GameObject::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void GameObject::SetColor(GLfloat vColor[4]) {
	_transform->SetColor(vColor);
}