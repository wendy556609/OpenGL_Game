#include "../Header/Angel.h"
#include "Transform.h"
#include "Bullet.h"
#include "Protect.h"
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
	vec4 _pos;//ª±®a¦ì¸m

	bool isShoot=false;
	bool isProtect = false;
public:
	Protect *_protect;
	BulletLink *_bulletLink;

	Transform *_transform;

	Player(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Player();

	void Create();
	void Update(float delta);
	void Draw();

	void SetTRSMatrix(mat4 &mat);
	void SetPosition(vec4 position);
	void SetColor(GLfloat vColor[4]);

	void SetShoot(bool shoot) { isShoot = shoot; }
	void SetProtect(bool protect) { isProtect = protect; }
};