#ifndef Planet_H
#define Planet_H
#include "../header/Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define NUM 20  // 2 faces, 2 triangles/face 
#define NUM_1 20
#define NUM_2 20
#define NUM_3 20
#define Total_NUM NUM+NUM_1+NUM_2+NUM_3

class Planet
{
private:
	vec4 m_Points[Total_NUM];
	vec4 m_Colors[Total_NUM];
	// VAO
	GLuint m_uiVao;
	// VBO
	GLuint m_uiBuffer;
	//  for Shader
	GLuint m_uiProgram;
	// Vertex Position Attribute
	GLuint m_uiModelView, m_uiProjection;
	GLuint m_uiMove;
	// Matrix 
	mat4 m_mxView, m_mxProjection;
	mat4 m_mxMVFinal, m_mxTRS;
	mat4  m_mxTra, m_mxRot, m_mxSca;

	// 紀錄是否有矩陣的更新
	bool  m_bUpdateMV;
	bool  m_bUpdateProj;

	void CreateBufferObject();
public:
	Planet();


	void SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return m_uiProgram; }
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetMove(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]); // Single color

	void Draw();
};




#endif