#include "MainScene.h"

MainScene::MainScene(mat4 g_mxModelView, mat4 g_mxProjection) {
	//  ���� projection �x�}�A���B�����ͥ���v�x�}
	matProjection = g_mxProjection;
	matModelView = g_mxModelView;
	//���ͪ��a
	pPlayer = new Player(matModelView, matProjection);

	//Planet
	pPlanet[0] = new Planet(0,matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	pPlanet[1] = new Planet(1,matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	pPlanet[2] = new Planet(2,matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	//pPlayer->SetShader(matModelView, matProjection);
}

MainScene::~MainScene() {
	if (pPlanet[0] != NULL) delete pPlanet[0];
	if (pPlanet[1] != NULL) delete pPlanet[1];
	if (pPlanet[2] != NULL) delete pPlanet[2];

	if (pPlayer != NULL) delete pPlayer;	
}

void MainScene::Draw() {
	pPlanet[0]->Draw();
	pPlanet[1]->Draw();
	pPlanet[2]->Draw();

	pPlayer->Draw();
}

void MainScene::SpecialInput(int key) {
	switch (key) {
	case GLUT_KEY_LEFT://Left
		pPlayer->_protect->_angle += 2.0;
		break;
	case GLUT_KEY_RIGHT://Right
		pPlayer->_protect->_angle -= 2.0;
		break;
	}
}

void MainScene::Update(float delta) {
	pPlayer->SetProtect(isProtect);//���@
	pPlayer->SetShoot(isShoot);//�g��

	pPlayer->Update(delta);

	for (int i = 0; i < 3; i++)
	{
		pPlanet[i]->Update(delta);
	}
}