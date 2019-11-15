#pragma once
#include "../Header/Angel.h"
#include "Player.h"
#include "Planet.h"
class MainScene
{
public:
	Player* pPlayer;
	Planet* pPlanet[3];

	bool isShoot = false;

	void Update(float delta);
	void Draw();
	MainScene(mat4 g_mxModelView, mat4 g_mxProjection);
	~MainScene();
private:
	// For Model View and Projection Matrix
	

	mat4 matModelView;
	mat4 matProjection;
};