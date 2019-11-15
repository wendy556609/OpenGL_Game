#include "../Header/Angel.h"
#include "Transform.h"
#include "Bullet.h"
#define QUAD_NUM 6  // 2 faces, 2 triangles/face 
#define Top_NUM 3
#define Total_NUM QUAD_NUM+Top_NUM

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Player {
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];
	vec4 _pos;

	bool isShoot=false;
public:
	//only the pointer for outer input class
	BulletLink *_bulletLink;
	Transform *_transform;
	Player(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Player();
	void SetShader(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	void Draw();
	void SetTRSMatrix(mat4 &mat);
	void SetPosition(vec4 position);
	void SetColor(GLfloat vColor[4]);
	void Update(float delta);
	void SetShoot(bool shoot) { isShoot = shoot; }
};