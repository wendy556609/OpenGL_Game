#include "../Header/Angel.h"
#include "Collider.h"
#include "Player.h"
#include "Planet.h"
#include "EnemyLink.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Item.h"
class MainScene
{
private:
	// For Model View and Projection Matrix
	mat4 matModelView;
	mat4 matProjection;
public:
	GameManager* gameManager;

	Player* pPlayer;//ª±®a	
	EnemyLink* enemyLink;	
	Planet* _Planet[3];

	Item_Pro* _item_Pro;
	Item_Bullet* _item_Bullet;
	Item_FlyBullet* _item_FlyBullet;

	bool isShoot = false;//ª±®a®gÀ»

	MainScene(mat4 g_mxModelView, mat4 g_mxProjection);
	~MainScene();

	void Update(float delta);
	void Draw();

	void Win_Keyboard(unsigned char key, int x, int y);
	void SpecialInput(int key);//¥ª¥kÁä
	void SetP();
};