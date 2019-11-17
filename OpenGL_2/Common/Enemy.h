#include "../Header/Angel.h"
#include "GameObject.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define Quad_NUM 20
#define Total_NUM Quad_NUM

class Enemy :public GameObject {
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];
public:

	Enemy(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	
	//void test() { Print("Enemy"); };
	void Create(mat4& matModelView, mat4& matProjection, GLuint shaderHandle);
	void Update(float delta);
	void Draw();
};
//#include "../Header/Angel.h"
//#include "Transform.h"
//#include "Collider.h"
//#define Quad_NUM 20
//#define Total_NUM Quad_NUM
//
//typedef Angel::vec4  color4;
//typedef Angel::vec4  point4;
//
//class Enemy {
//private:
//	point4 _points[Total_NUM];
//	color4 _colors[Total_NUM];
//
//	int enemyNum;
//public:
//	Transform *_transform;
//	Collider _collider;
//
//	Enemy(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
//	~Enemy();
//
//	void Create();
//	void Update(float delta);
//	void Draw();
//
//	void SetTRSMatrix(mat4 &mat);
//	void SetColor(GLfloat vColor[4]);
//};