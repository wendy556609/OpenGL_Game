#include "../Header/Angel.h"
#include "Collider.h"
#include "Player.h"
#include "Planet.h"
#include "EnemyLink.h"
#include "GameManager.h"
class MainScene
{
private:
	// For Model View and Projection Matrix
	mat4 matModelView;
	mat4 matProjection;
public:
	Player* pPlayer;//���a
	Planet* pPlanet[3];//�P�y
	Collision collision;
	EnemyLink* enemyLink;
	GameManager* gameManager;

	bool isShoot = false;//���a�g��
	bool isProtect = false;//���@

	int enemyCount = 4;
	int bulletCount = 0;

	MainScene(mat4 g_mxModelView, mat4 g_mxProjection);
	~MainScene();

	void Update(float delta);
	void Draw();

	void SpecialInput(int key);//���k��
	void SetP();
};