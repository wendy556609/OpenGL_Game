#include "Planet.h"

Planet::Planet()
{
	for (int i = 0; i < NUM; i++)
	{
		m_Points[i] = vec4(0.5f*cosf(M_PI*2.0f*i / (NUM)), 0.5f* sinf(M_PI*2.0f*i / (NUM)), 0.0f, 0.1f);
		m_Colors[i] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	for (int i = 20; i < 40; i++)
	{
		m_Points[i] = vec4(0.15f*cosf(M_PI*2.0f*(i- 20) / (NUM_1))-0.2f, 0.15f* sinf(M_PI*2.0f*(i - 20) / (NUM_1))+0.2f, 0.0f, 0.1f);
		m_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	for (int i = 40; i < 60; i++)
	{
		m_Points[i] = vec4(0.2f*cosf(M_PI*2.0f*(i - 40) / (NUM_2))+0.25f, 0.2f* sinf(M_PI*2.0f*(i - 40) / (NUM_2)), 0.0f, 0.1f);
		m_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	for (int i = 60; i < 80; i++)
	{
		m_Points[i] = vec4(0.05f*cosf(M_PI*2.0f*(i - 60) / (NUM_3))-0.2f, 0.05f* sinf(M_PI*2.0f*(i - 60) / (NUM_3)) - 0.25f, 0.0f, 0.1f);
		m_Colors[i] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	// Create and initialize a buffer object 
	CreateBufferObject();
	m_bUpdateProj = false;
}


void Planet::CreateBufferObject()
{
	glGenVertexArrays(1, &m_uiVao);
	glBindVertexArray(m_uiVao);

	// Create and initialize a buffer object

	glGenBuffers(1, &m_uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Points) + sizeof(m_Colors), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_Points), m_Points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_Points), sizeof(m_Colors), m_Colors);
}

void Planet::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) m_uiProgram = InitShader("vsPlanet.glsl", "fsVtxColor.glsl");
	else m_uiProgram = uiShaderHandle;

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(m_uiProgram, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(m_uiProgram, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(m_Points)));

	m_uiModelView = glGetUniformLocation(m_uiProgram, "ModelView");
	m_mxView = mxView;
	glUniformMatrix4fv(m_uiModelView, 1, GL_TRUE, m_mxView);

	m_uiProjection = glGetUniformLocation(m_uiProgram, "Projection");
	m_mxProjection = mxProjection;
	glUniformMatrix4fv(m_uiProjection, 1, GL_TRUE, m_mxProjection);

	m_uiMove = glGetUniformLocation(m_uiProgram, "vT");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Planet::SetMove(mat4 &mat)
{
	glUseProgram(m_uiProgram);
	glUniformMatrix4fv(m_uiMove, 1, GL_TRUE, mat);
}

void Planet::SetViewMatrix(mat4 &mat)
{
	m_mxView = mat;
	m_bUpdateMV = true;
}

void Planet::SetProjectionMatrix(mat4 &mat)
{
	m_mxProjection = mat;
	m_bUpdateProj = true;
}

void Planet::SetTRSMatrix(mat4 &mat)
{
	m_mxTRS = mat;
	m_bUpdateMV = true;
}

void Planet::SetColor(GLfloat vColor[4])
{
	for (int i = 0; i < NUM; i++) {
		m_Colors[i].x = vColor[0];
		m_Colors[i].y = vColor[1];
		m_Colors[i].z = vColor[2];
		m_Colors[i].w = vColor[3];
	}
	for (int i = 20; i < Total_NUM; i++)
	{
		m_Colors[i].w = vColor[3];
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_uiBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_Points), sizeof(m_Colors), m_Colors);
}

void Planet::Draw()
{
	glUseProgram(m_uiProgram);
	glBindVertexArray(m_uiVao);
	if (m_bUpdateMV) {
		m_mxMVFinal = m_mxView*m_mxTRS;
		m_bUpdateMV = false;
	}
	glUniformMatrix4fv(m_uiModelView, 1, GL_TRUE, m_mxMVFinal);

	if (m_bUpdateProj) {
		glUniformMatrix4fv(m_uiProjection, 1, GL_TRUE, m_mxProjection);
		m_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 60, 20);
}
