#pragma once

#include "../Header/Angel.h"
#include <vector>
typedef std::vector<vec4> vPoint4;
typedef std::vector<vec4> vColor4;
typedef Angel::vec4 color4;
typedef Angel::vec4 point4;

class Transform {
private:
	int _pointNum;
	vec4 *_points, *_colors;

	GLuint _uiVao;
	GLuint _uiBuffer;
	GLuint _uiProgram;
	GLuint _uiModelView, _uiProjection;	
	GLuint _uiTRS;//傳入Shader用

	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal;

	bool  _bUpdateMV;
	bool  _bUpdateProj;

	void CreateBufferObject();
	
	GLuint GetShaderHandle() { return _uiProgram; }
public:
	mat4  _mxTRS;
	mat4 _mxShaderTRS;//傳入Shader用

	Transform(mat4 &mxView, mat4 &mxProjection, int pointNum, vec4 *points, vec4 *colors, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	~Transform();

	void Draw();

	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle);
	void SetTRSMatrix(mat4 &mat);
	void ShaderTRS(mat4 &mat);//傳入Shader用
	void SetColor(GLfloat vColor[4]);
	void SetColor(int start, int pointNum, GLfloat vColor[4]);
};