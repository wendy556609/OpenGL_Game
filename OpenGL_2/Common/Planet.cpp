#include "Planet.h"
Planet::Planet(GameManager* gameManager, int planetNum,mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	for (int i = 0; i < NUM; i++)
	{
		_points[i] = point4(0.5f*cosf(M_PI*2.0f*i / (NUM)), 0.5f* sinf(M_PI*2.0f*i / (NUM)), 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	for (int i = 20; i < 40; i++)
	{
		_points[i] = point4(0.15f*cosf(M_PI*2.0f*(i- 20) / (NUM_1))-0.2f, 0.15f* sinf(M_PI*2.0f*(i - 20) / (NUM_1))+0.2f, 0.0f, 0.1f);
		_colors[i] = color4(0.0f, 0.0f, 0.0f, 0.5f);
	}
	for (int i = 40; i < 60; i++)
	{
		_points[i] = point4(0.2f*cosf(M_PI*2.0f*(i - 40) / (NUM_2))+0.25f, 0.2f* sinf(M_PI*2.0f*(i - 40) / (NUM_2)), 0.0f, 0.1f);
		_colors[i] = color4(0.0f, 0.0f, 0.0f, 0.5f);
	}
	for (int i = 60; i < 80; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*2.0f*(i - 60) / (NUM_3))-0.2f, 0.05f* sinf(M_PI*2.0f*(i - 60) / (NUM_3)) - 0.25f, 0.0f, 0.1f);
		_colors[i] = color4(0.0f, 0.0f, 0.0f, 0.5f);
	}

	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors, shaderHandle);
	_planetNum = planetNum;
	SetPlanet();//設定星球初始數值
	_gameManager = gameManager;
}

Planet::~Planet() {
	if (_transform != NULL) delete _transform;
}

void Planet::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 60, 20);
}

void Planet::SetTRSMatrix(mat4 &mat)
{
	_transform->ShaderTRS(mat);
}

void Planet::SetColor(GLfloat vColor[4]) {
	_transform->SetColor(0,NUM,vColor);
}

void Planet::PlanetMove(float delta) {
	mat4 mPLT;
	int speed;

	switch (_gameManager->Level)
	{
	case 1:
		speed = 5;
		break;
	case 2:
		speed = 8;
		break;
	case 3:
		speed = 12;
		break;
	default:
		break;
	}
	vPLTy -= speed * delta;

	mPLT = Translate(vPLTx, vPLTy, 0.0f);

	SetTRSMatrix(mPLT*vPLS);

	if (vPLTy <= -15.0f) {
		SetPlanet();
	}
}

void Planet::SetPlanet() {
	int b = rand() % 5;
	int R, G, B;
	R = rand() % 10;
	G = rand() % 10;
	B = rand() % 10;
	SetColor(vec4((R + 1) * 0.1f, (G + 1) * 0.1f, (B + 1) * 0.1f, 0.5f));
	vPLS = Scale((b + 5)*0.1f, (b + 5)*0.1f,0.0f);
	switch (_planetNum)
	{
	case 0:
		vPLTx = 10.0f;
		vPLTy = 15.0f;
		break;
	case 1:
		vPLTx = -10.0f;
		vPLTy = 20.0f;
		break;
	case 2:
		vPLTx = 1.0f;
		vPLTy = 25.0f;
		break;
	default:
		break;
	}
}

void Planet::Update(float delta) {
	PlanetMove(delta);
}