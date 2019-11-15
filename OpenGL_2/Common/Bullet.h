#ifndef Bullet_H
#define Bullet_H
#include "../header/Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 6  // 2 faces, 2 triangles/face 
#define Top_NUM 20
#define Total_NUM QUAD_NUM+Top_NUM

class Bullet
{
private:
	vec4 m_Points[Total_NUM];
	vec4 m_Colors[Total_NUM];
	vec4 pos;
	// VAO
	GLuint m_uiVao;
	// VBO
	GLuint m_uiBuffer;
	//  for Shader
	GLuint m_uiProgram;
	// Vertex Position Attribute
	GLuint m_uiModelView, m_uiProjection;
	GLuint  m_uiLoc;
	GLuint m_Move;
	// Matrix 
	mat4 m_mxView, m_mxProjection;
	mat4 m_mxMVFinal, m_mxTRS;
	mat4 mT = (
		1, 0, 0, 0,
		0, 1, 0, 1,
		0, 0, 1, 0,
		0, 0, 0, 1
		);

	// 紀錄是否有矩陣的更新
	bool  m_bUpdateMV;
	bool  m_bUpdateProj;

	void CreateBufferObject();
public:
	Bullet();
	Bullet* next;
	
	void SetMainPos(vec4 mainPos);
	void SetMove();
	void SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return m_uiProgram; }
	vec4 GetPos() { return pos; }
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]); // Single color

	void Draw();
	void DrawW();
};




#endif