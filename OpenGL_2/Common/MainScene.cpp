#include "MainScene.h"

MainScene::MainScene(mat4 g_mxModelView, mat4 g_mxProjection) {
	//  產生 projection 矩陣，此處為產生正投影矩陣
	matProjection = g_mxProjection;
	matModelView = g_mxModelView;
	gameManager = new GameManager;
	//產生玩家
	pPlayer = new Player(matModelView, matProjection);

	//Planet
	pPlanet[0] = new Planet(gameManager, 0, matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	pPlanet[1] = new Planet(gameManager, 1, matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	pPlanet[2] = new Planet(gameManager, 2, matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	
	enemyLink = new EnemyLink(matModelView, matProjection);	

	//設立指標
	SetP();
}

void MainScene::SetP() {
	enemyLink->gameManager = gameManager;
	enemyLink->playerCollider = &pPlayer->_collider;
	//enemyLink->playerProtect = &pPlayer->_protect->_collider;
	pPlayer->_bulletLink->enemyLink = enemyLink;
}

MainScene::~MainScene() {
	if (pPlanet[0] != NULL) delete pPlanet[0];
	if (pPlanet[1] != NULL) delete pPlanet[1];
	if (pPlanet[2] != NULL) delete pPlanet[2];

	if (pPlayer != NULL) delete pPlayer;

	if (enemyLink != NULL) delete enemyLink;

	if (gameManager != NULL) delete gameManager;
}

void MainScene::Draw() {
	pPlanet[0]->Draw();
	pPlanet[1]->Draw();
	pPlanet[2]->Draw();

	pPlayer->Draw();
	enemyLink->Draw();
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
	//pPlayer->SetProtect(isProtect);//防護
	pPlayer->SetShoot(isShoot);//射擊
	
	pPlayer->Update(delta);
	
	enemyLink->Update(delta);

	for (int i = 0; i < 3; i++)
	{
		pPlanet[i]->Update(delta);
	}
	gameManager->SetLevel();//改變Level
}