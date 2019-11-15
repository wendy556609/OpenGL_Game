#include "../Header/Angel.h"
#include "Transform.h"
#define QUAD_NUM 6 
#define Top_NUM 20
#define Total_NUM QUAD_NUM+Top_NUM

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Bullet {
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];

	vec4 pos;
public:
	//only the pointer for outer input class
	Bullet *next;
	Transform *_transform;
	Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Bullet();
	void SetShader(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	void Draw();
	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]);
	void Update(float delta);
	void SetPlayerPos(vec4 pos);
	void SetMove();
	vec4 GetPos() { return pos; }
};

class BulletLink {
private:
	Bullet *_Head = NULL;
	Bullet *_Get = NULL;
	Bullet *_Tail = NULL;

	Bullet *_ShootHead = NULL;
	Bullet *_ShootGet = NULL;
	Bullet *_ShootTail = NULL;

	Bullet *_Link = NULL;

	float _BTime = 0;

	
public:
	int totalCount;
	int useCount = 0;
	//only the pointer for outer input class
	BulletLink(int total,mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~BulletLink();
	void Shoot(float delta,vec4 pos);	
	void DetectBullet();
	void RecycleBullet();
	void SetShader(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	void Draw();
	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]);
	void Update(float delta);
};

//#ifndef Bullet_H
//#define Bullet_H
//#include "../header/Angel.h"
//
//typedef Angel::vec4  color4;
//typedef Angel::vec4  point4;
//
//#define QUAD_NUM 6  // 2 faces, 2 triangles/face 
//#define Top_NUM 20
//#define Total_NUM QUAD_NUM+Top_NUM
//
//class Bullet
//{
//private:
//	vec4 m_Points[Total_NUM];
//	vec4 m_Colors[Total_NUM];
//	vec4 pos;
//	// VAO
//	GLuint m_uiVao;
//	// VBO
//	GLuint m_uiBuffer;
//	//  for Shader
//	GLuint m_uiProgram;
//	// Vertex Position Attribute
//	GLuint m_uiModelView, m_uiProjection;
//	GLuint  m_uiLoc;
//	GLuint m_Move;
//	// Matrix 
//	mat4 m_mxView, m_mxProjection;
//	mat4 m_mxMVFinal, m_mxTRS;
//	mat4 mT = (
//		1, 0, 0, 0,
//		0, 1, 0, 1,
//		0, 0, 1, 0,
//		0, 0, 0, 1
//		);
//
//	// 紀錄是否有矩陣的更新
//	bool  m_bUpdateMV;
//	bool  m_bUpdateProj;
//
//	void CreateBufferObject();
//public:
//	Bullet();
//	Bullet* next;
//	
//	void SetMainPos(vec4 mainPos);
//	void SetMove();
//	void SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
//	GLuint GetShaderHandle() { return m_uiProgram; }
//	vec4 GetPos() { return pos; }
//	void SetViewMatrix(mat4 &mat);
//	void SetProjectionMatrix(mat4 &mat);
//	void SetTRSMatrix(mat4 &mat);
//	void SetColor(GLfloat vColor[4]); // Single color
//
//	void Draw();
//	void DrawW();
//};
//
//
//
//
//#endif