#include "MainScene.h"
#define SPACE_KEY 32

MainScene::MainScene(mat4 g_mxModelView, mat4 g_mxProjection) {
	vec4 pos;
	//  產生 projection 矩陣，此處為產生正投影矩陣
	matProjection = g_mxProjection;
	matModelView = g_mxModelView;
	gameManager = new GameManager;
	//產生玩家
	pPlayer = new Player(matModelView, matProjection);

	for (int i = 0; i < 3; i++)
	{
		_Planet[i] = new Planet(gameManager, i, matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	}
	
	enemyLink = new EnemyLink(matModelView, matProjection);	

	_item_Pro = new Item_Pro(matModelView, matProjection);
	_item_Bullet = new Item_Bullet(matModelView, matProjection);
	_item_FlyBullet = new Item_FlyBullet(matModelView, matProjection);
	//設立指標
	SetP();
}

void MainScene::SetP() {
	enemyLink->gameManager = gameManager;
	enemyLink->playerCollider = &pPlayer->_collider;
	enemyLink->playerProtect = &pPlayer->_protect->_collider;
	pPlayer->_bulletLink->enemyLink = enemyLink;

	pPlayer->_Item_Pro = &_item_Pro->_collider;
	pPlayer->_Item_Bullet = &_item_Bullet->_collider;
	pPlayer->_Item_FlyBullet = &_item_FlyBullet->_collider;
}

MainScene::~MainScene() {
	for (int i = 0; i < 3; i++)
	{
		if (_Planet[i] != NULL) delete _Planet[i];
	}

	if (pPlayer != NULL) delete pPlayer;

	if (enemyLink != NULL) delete enemyLink;

	if (gameManager != NULL) delete gameManager;

	if (_item_Pro != NULL) delete _item_Pro;
	if (_item_Bullet != NULL) delete _item_Bullet;
	if (_item_FlyBullet != NULL) delete _item_FlyBullet;
}

void MainScene::Draw() {
	for (int i = 0; i < 3; i++)
	{
		_Planet[i]->Draw();
	}

	if (!pPlayer->Dead()) {
		pPlayer->Draw();
	}

	enemyLink->Draw();
	
	_item_Pro->Draw();
	_item_Bullet->Draw();
	_item_FlyBullet->Draw();
}

void MainScene::Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'Z':
	case 'z':
		pPlayer->_collider.isDestroy = false;
		pPlayer->Init();
		break;
	case  SPACE_KEY:
		break;
	}
}

void MainScene::SpecialInput(int key) {
	switch (key) {
	case GLUT_KEY_LEFT://Left
		break;
	case GLUT_KEY_RIGHT://Right
		break;
	}
}

void MainScene::Update(float delta) {
	if (!pPlayer->Dead()) {
		pPlayer->SetShoot(isShoot);//射擊
	}
	pPlayer->Update(delta);
	
	enemyLink->Update(delta);

	for (int i = 0; i < 3; i++)
	{
		_Planet[i]->Update(delta);
	}

	if (gameManager->_enemyCount_1 >= 0) {
		_item_Pro->Update(delta);
	}
	if (gameManager->Level >= 2) {
		_item_Bullet->Update(delta);
	}
	if (gameManager->Level >= 3) {
		pPlayer->bossPos = enemyLink->bossPos;
		_item_FlyBullet->Update(delta);
	}

	gameManager->SetLevel();//改變Level
}