#include "MainScene.h"

MainScene::MainScene(mat4 g_mxModelView, mat4 g_mxProjection) {
	//  產生 projection 矩陣，此處為產生正投影矩陣
	matProjection = g_mxProjection;
	matModelView = g_mxModelView;
	//產生玩家
	pPlayer = new Player(matModelView, matProjection);

	//Planet
	pPlanet[0] = new Planet(0,matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	pPlanet[1] = new Planet(1,matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	pPlanet[2] = new Planet(2,matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	
	pEnemy[0] = new Enemy(matModelView, matProjection);
	pEnemy[1] = new Enemy(matModelView, matProjection);
	pEnemy[2] = new Enemy(matModelView, matProjection);
	pEnemy[3] = new Enemy(matModelView, matProjection);
}

MainScene::~MainScene() {
	if (pPlanet[0] != NULL) delete pPlanet[0];
	if (pPlanet[1] != NULL) delete pPlanet[1];
	if (pPlanet[2] != NULL) delete pPlanet[2];

	if (pPlayer != NULL) delete pPlayer;

	if (pEnemy[0] != NULL) delete pEnemy[0];
	if (pEnemy[1] != NULL) delete pEnemy[1];
	if (pEnemy[2] != NULL) delete pEnemy[2];
	if (pEnemy[3] != NULL) delete pEnemy[3];
}

void MainScene::Draw() {
	pPlanet[0]->Draw();
	pPlanet[1]->Draw();
	pPlanet[2]->Draw();

	pPlayer->Draw();

	pEnemy[0]->Draw();
	pEnemy[1]->Draw();
	pEnemy[2]->Draw();
	pEnemy[3]->Draw();
}

void MainScene::SpecialInput(int key) {
	switch (key) {
	case GLUT_KEY_LEFT://Left
		//pPlayer->_protect->_angle += 2.0;
		break;
	case GLUT_KEY_RIGHT://Right
		//pPlayer->_protect->_angle -= 2.0;
		break;
	}
}

void MainScene::Update(float delta) {
	DoCollision(delta);
	//pPlayer->SetProtect(isProtect);//防護
	pPlayer->SetShoot(isShoot);//射擊
	
	pPlayer->Update(delta);
	
	pEnemy[0]->Update(delta);
	pEnemy[1]->Update(delta);
	pEnemy[2]->Update(delta);
	pEnemy[3]->Update(delta);

	for (int i = 0; i < 3; i++)
	{
		pPlanet[i]->Update(delta);
	}
	
}

void MainScene::DoCollision(float delta) {

	for (int i = 0; i < 4; i++)
	{
		pPlayer->enemyCollider[i] = &pEnemy[i]->_collider;
		pPlayer->_bulletLink->enemyCollider[i] = &pEnemy[i]->_collider;
		pEnemy[i]->_bulletLink->playerCollider = &pPlayer->_collider;
		pEnemy[i]->playerCollider = &pPlayer->_collider;
	}
}