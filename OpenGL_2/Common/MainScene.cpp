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
	
	enemyLink = new EnemyLink(30, matModelView, matProjection);
}

MainScene::~MainScene() {
	if (pPlanet[0] != NULL) delete pPlanet[0];
	if (pPlanet[1] != NULL) delete pPlanet[1];
	if (pPlanet[2] != NULL) delete pPlanet[2];

	if (pPlayer != NULL) delete pPlayer;

	if (enemyLink != NULL)delete enemyLink;
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

	enemyTime += delta;
	
	if (enemyTime >= 2.0f) {
		if (enemyLink->useCount <= enemyLink->totalCount) {
			enemyLink->Shoot();
			enemyTime = 0;
		}
	}
	enemyLink->DetectBullet(delta);

	for (int i = 0; i < 3; i++)
	{
		pPlanet[i]->Update(delta);
	}

	DoCollision(delta);
	//test(pEnemy);
}

void MainScene::DoCollision(float delta) {
	TouchTime += delta;
	hurtTime += delta;
	AttackTime += delta;
	/*if (collision.CheckCollider(pPlayer, enemyLink->DetectEnemyCollider())) {
		if (TouchTime >= 1.0f) {
			Print("Touch");
			TouchTime = 0;
		}
		
	};*/
	/*if (collision.CheckCollider(pPlayer->_bulletLink->DetectCollider(), enemyLink->DetectEnemyCollider())) {
		if (AttackTime >= 0.2f) {
			Print("Attack");
			AttackTime = 0;
		}
	};*/
	/*if (collision.CheckCollider(enemyLink->DetectBulletCollider(), pPlayer)) {
		if (hurtTime >= 0.2f) {
			Print("Hurt");
			hurtTime = 0;
		}
	};*/
}