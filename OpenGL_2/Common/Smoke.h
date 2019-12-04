
#include "../Header/Angel.h"
#include "Transform.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Bomb {
private:
	int pointNum;
	point4* _points;
	color4* _colors;
public:
	Transform *_transform;

	vec4 _pos;
	bool finish = true;

	Bomb(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Bomb();

	void Draw();

	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]);

	void SetPos(vec4 pos) {
		_pos = pos;
	};
	void SetBomb(float delta);
};

class Smoke {
private:
	int pointNum;
	point4* _points;
	color4* _colors;

	float time1 = 0.0f, time2 = 0.0f, time3 = 0.0f, time4 = 0.0f;

	float _color1 = 0.0f, _color2 = 0.0f, _color3 = 0.0f, _color4 = 0.0f;

	bool clear1 = false, clear2 = false, clear3 = false, clear4 = false;
public:
	Transform *_transform;

	vec4 _pos;
	float _angle = 0.0f;
	bool start = false;

	Smoke(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Smoke();
	
	void Draw();

	void SetTRSMatrix(mat4 &mat);
	void SetColor(int start, int end, GLfloat vColor[4]);
	void SetPosition(int start, int end, GLfloat vPosition[4]);

	void SetPos(vec4 pos, float angle = 0.0f) {
		_pos = pos;
		_angle = angle;
	};
	void SetSmoke(float delta);
};