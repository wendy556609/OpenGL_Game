#include "../Header/Angel.h"
#include "Transform.h"
#define Total_NUM 20

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Protect {
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];

	mat4 mxIdle;//初始位置
	mat4 parent;//玩家位置
public:
	Transform *_transform;

	float _angle = 0.0f;

	Protect(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Protect();

	void Update(float delta);
	void Draw();

	void SetTRSMatrix(mat4 &mat = mat4(GLfloat(1.0)));
	void SetColor(GLfloat vColor[4]);
	void SetTurn();
	void SetParent(mat4 &mxParent);
	void ResetProtect();

};