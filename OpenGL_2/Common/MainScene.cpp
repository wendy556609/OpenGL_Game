#include "MainScene.h"

void MainScene::Update(float delta) {
	pPlayer->SetShoot(isShoot);
	pPlayer->Update(delta);
	for (int i = 0; i < 3; i++)
	{
		pPlanet[i]->Update(delta);
	}
}

void MainScene::Draw() {
	pPlanet[0]->Draw();
	pPlanet[1]->Draw();
	pPlanet[2]->Draw();
	pPlayer->Draw();
}

MainScene::MainScene(mat4 g_mxModelView, mat4 g_mxProjection) {
	//  產生 projection 矩陣，此處為產生正投影矩陣
	matProjection = g_mxProjection;
	matModelView = g_mxModelView;
	//產生玩家
	pPlayer = new Player(matModelView, matProjection);
	pPlanet[0] = new Planet(0,matModelView, matProjection);
	pPlanet[1] = new Planet(1,matModelView, matProjection);
	pPlanet[2] = new Planet(2,matModelView, matProjection);
	//pPlayer->SetShader(matModelView, matProjection);
}

MainScene::~MainScene() {
	if (pPlayer != NULL) delete pPlayer;
	if (pPlanet[0] != NULL) delete pPlanet[0];
	if (pPlanet[1] != NULL) delete pPlanet[1];
	if (pPlanet[2] != NULL) delete pPlanet[2];
}