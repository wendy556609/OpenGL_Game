#include "../Header/Angel.h"
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
	Player* pPlayer;//���a
	Planet* pPlanet[3];//�P�y
	Enemy* pEnemy;

	bool isShoot = false;//���a�g��
	bool isProtect = false;//���@

	MainScene(mat4 g_mxModelView, mat4 g_mxProjection);
	~MainScene();

	void Update(float delta);
	void Draw();

	void SpecialInput(int key);//���k��
};