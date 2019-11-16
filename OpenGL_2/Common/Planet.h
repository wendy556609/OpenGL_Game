#include "../Header/Angel.h"
#include "Transform.h"
#define NUM 20 
#define NUM_1 20
#define NUM_2 20
#define NUM_3 20
#define Total_NUM NUM+NUM_1+NUM_2+NUM_3

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Planet {
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];

	int _planetNum;//�P�y�N��

	float vPLTx = 0.0f, vPLTy = 0.0f;//�P�y��m
	mat4 vPLS;//�P�y�Y��

	void PlanetMove(float delta);
	void SetPlanet();
public:
	Transform *_transform;

	Planet(int planetNum, mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Planet();

	void Update(float delta);
	void Draw();

	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]);
};