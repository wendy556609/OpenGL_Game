#include "../Header/Angel.h"
#include "Transform.h"
#include "Collider.h"
#include "Bullet.h"
#include "Protect.h"
class PlayerItem;
#define UpCircle_NUM 20
#define Eyes_NUM 40
#define Head_NUM 20
#define UpQuad_NUM 6
#define ButtomQuad_NUM 6
#define ButtomCircle_NUM 60
#define Total_NUM UpQuad_NUM+Head_NUM+Eyes_NUM+ButtomQuad_NUM+ButtomCircle_NUM+UpCircle_NUM

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Player {
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];

	vec4 _pos;
	
	float twoBulletTime = 0.0f;
	int FlyBulletCount = 0;
	int clearCount = 0;
	int deadCount = 0;

	bool isDead = false;
	bool isShoot = false;

	bool isProtect = false;
	bool isTwoBullet = false;
	bool isFlyBullet = false;
	bool isProClear = false;
public:
	Protect *_protect;
	Transform *_transform;
	Collider _collider;
	BulletLink *_bulletLink;
	PlayerItem* playerItem[3];

	Collider* _Item_Pro;
	Collider* _Item_Bullet;
	Collider* _Item_FlyBullet;

	vec4 bossPos;

	int hp = 20;

	float shootTime = 0.0f;
	float protectTime = 0.0f;

	bool isUseItem = false;

	Player(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Player();

	void Create();
	void Update(float delta);
	void Draw();
	
	void SetPosition(vec4 position);
	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4], bool hurt = false);
	void SetHurt(float delta);

	void SetShoot(bool shoot) { isShoot = shoot; }
	void CheckItem();

	void Init();
	GLboolean Dead() { return isDead; };

	GLboolean CheckCollider(Collider one, Collider two);
};

class PlayerItem {
private:
	int pointNum;
	point4 *_points;
	color4 *_colors;

	vec4 _pos;
	vec4 _playerPos;

	float _angle = 0.0f;
public:
	Transform *_transform;
	float size = 0.0f;

	bool isClear = true;

	PlayerItem(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~PlayerItem();

	void Create();
	void Update(float delta);
	void Draw();

	void SetPosition(vec4 pos, float Size);
	void SetPlayer(vec4 playerPos);
	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]);

	void Init();

	float Radius(float angle);
};