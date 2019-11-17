#include "../Header/Angel.h"
#include "Collider.h"
#include "Player.h"
#include "Planet.h"
#include "Enemy.h"
class MainScene
{
private:
	// For Model View and Projection Matrix
	mat4 matModelView;
	mat4 matProjection;
public:
	Player* pPlayer;//ª±®a
	Planet* pPlanet[3];//¬P²y
	Enemy* pEnemy;
	Collision collision;

	bool isShoot = false;//ª±®a®gÀ»
	bool isProtect = false;//¨¾Å@

	int bulletCount = 0;
	float hurtTime = 0;

	MainScene(mat4 g_mxModelView, mat4 g_mxProjection);
	~MainScene();

	void Update(float delta);
	void Draw();

	void SpecialInput(int key);//¥ª¥kÁä
	void DoCollision(float delta);
};