#include "../Header/Angel.h"
#include "Collider.h"
#include "Player.h"
#include "Planet.h"
#include "Enemy.h"
#include "Collision.h"
class MainScene
{
private:
	// For Model View and Projection Matrix
	mat4 matModelView;
	mat4 matProjection;
public:
	Player* pPlayer;//玩家
	Planet* pPlanet[3];//星球
	Enemy* pEnemy;
	Collision collision;

	bool isShoot = false;//玩家射擊
	bool isProtect = false;//防護

	int bulletCount = 0;
	float hurtTime = 0;

	MainScene(mat4 g_mxModelView, mat4 g_mxProjection);
	~MainScene();

	void Update(float delta);
	void Draw();

	//void test(EnemyManager *a) { a->test(); };
	void SpecialInput(int key);//左右鍵
	void DoCollision(float delta);
};