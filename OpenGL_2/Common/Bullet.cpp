#include "Bullet.h"
Bullet::Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	_points[0] = point4(-0.25f, 0.25f, 0.0f, 1.0f);
	_points[1] = point4(0.25f, 0.25f, 0.0f, 1.0f);
	_points[2] = point4(0.25f, -0.25f, 0.0f, 1.0f);
	_points[3] = point4(-0.25f, 0.25f, 0.0f, 1.0f);
	_points[4] = point4(0.25f, -0.25f, 0.0f, 1.0f);
	_points[5] = point4(-0.25f, -0.25f, 0.0f, 1.0f);

	_colors[0] = color4(1.0f, 0.0f, 0.0f, 1.0f);  // (r, g, b, a)
	_colors[1] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[2] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[3] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[4] = color4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[5] = color4(1.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 6; i < Total_NUM; i++)
	{
		_points[i] = vec4(0.025f*cosf(M_PI*(i-6) / (Top_NUM - 1)), 0.025f* sinf(M_PI*(i - 6) / (Top_NUM - 1))+0.025, 0.0f, 0.1f);
		_colors[i] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors);
}

Bullet::~Bullet() {
	if (_transform != NULL) delete _transform;
}

void Bullet::SetShader(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	_transform->SetShader(matModelView, matProjection, shaderHandle);
}

void Bullet::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Bullet::SetColor(GLfloat vColor[4]) {
	_transform->SetColor(vColor);
}

void Bullet::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
	glDrawArrays(GL_TRIANGLE_FAN, QUAD_NUM, Top_NUM);
}

void Bullet::Update(float delta) {
}

void Bullet::SetPlayerPos(vec4 playerpos) {
	pos = playerpos;
}
void Bullet::SetMove() {
	mat4 mT;

	pos.y += 1 * 0.005f;
	mT = Translate(pos);

	SetTRSMatrix(mT);
}

//BulletLink
BulletLink::BulletLink(int total,mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	totalCount = total;
	_Head = _Get = _Tail = NULL;
	_Head = new Bullet(matModelView, matProjection);
	_Tail = _Head;
	for (int i = 0; i < totalCount; i++)
	{
		_Get = new Bullet(matModelView, matProjection);
		_Get->next = NULL;
		_Tail->next = _Get;
		_Tail = _Get;
	}	
}

void BulletLink::Shoot(float delta,vec4 pos) {
	_BTime += delta;
	if (_BTime >= 0.2f) {
		if (_ShootHead == NULL) {
			_ShootHead = _Head;
			_Head = _Head->next;
			_ShootTail = _ShootHead;
			_ShootGet = _ShootHead;
			_ShootGet->next = NULL;
			useCount++;
		}
		else {
			_ShootGet = _Head;
			_Head = _Head->next;
			_ShootGet->next = NULL;
			_ShootTail->next = _ShootGet;
			_ShootTail = _ShootGet;
			useCount++;
		}
		_ShootGet->SetPlayerPos(pos);
		_BTime = 0;
	}
}

void BulletLink::DetectBullet() {
	_Link = NULL;
	_ShootGet = _ShootHead;
	while (_ShootGet != NULL) {
		_ShootGet->SetMove();
		if (_ShootGet->GetPos().y >= 12.0f) {
			RecycleBullet();
		}
		else {
			_Link = _ShootGet;
			_ShootGet = _ShootGet->next;
		}
	}
}
void BulletLink::RecycleBullet() {
	if (_Link == NULL) {
		_Get = _ShootGet;
		_ShootHead = _ShootGet->next;
		_ShootGet = _ShootGet->next;
		_Get->next = _Head;
		_Head = _Get;
		useCount--;
	}
	else {
		_Get = _ShootGet;
		_ShootGet = _Link;
		_ShootGet->next = _Get->next;
		_Get->next = _Head;
		_Head = _Get;
		useCount--;
	}
}

BulletLink::~BulletLink() {
	_Get = _Head;
	while (_Get != NULL) {
		_Head = _Get->next;
		delete _Get;
		_Get = _Head;
	}
	delete _Head;

	_ShootGet = _ShootHead;
	while (_ShootGet != NULL) {
		_ShootHead = _ShootGet->next;
		delete _ShootGet;
		_ShootGet = _ShootHead;
	}
	delete _ShootHead;
}

void BulletLink::Draw() {
	_ShootGet = _ShootHead;
	while (_ShootGet != NULL) {
		_ShootGet->Draw();
		_ShootGet = _ShootGet->next;
	}
}

void BulletLink::Update(float delta) {
}
//#include "Bullet.h"
//
//Bullet::Bullet()
//{
//	m_Points[0] = vec4(-0.25f, 0.25f, 0.0f, 1.0f);
//	m_Points[1] = vec4(0.25f, 0.25f, 0.0f, 1.0f);
//	m_Points[2] = vec4(0.25f, -0.25f, 0.0f, 1.0f);
//	m_Points[3] = vec4(-0.25f, 0.25f, 0.0f, 1.0f);
//	m_Points[4] = vec4(0.25f, -0.25f, 0.0f, 1.0f);
//	m_Points[5] = vec4(-0.25f, -0.25f, 0.0f, 1.0f);
//
//	m_Colors[0] = vec4(1.0f, 0.0f, 0.0f, 1.0f);  // (r, g, b, a)
//	m_Colors[1] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_Colors[2] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_Colors[3] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_Colors[4] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_Colors[5] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//
//	for (int i = 6; i < Total_NUM; i++)
//	{
//		m_Points[i] = vec4(0.025f*cosf(M_PI*(i-6) / (Top_NUM - 1)), 0.025f* sinf(M_PI*(i - 6) / (Top_NUM - 1))+0.025, 0.0f, 0.1f);
//		m_Colors[i] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	}
//	// Create and initialize a buffer object 
//	CreateBufferObject();
//	m_bUpdateProj = false;
//}
//
//
//void Bullet::CreateBufferObject()
//{
//	glGenVertexArrays(1, &m_uiVao);
//	glBindVertexArray(m_uiVao);
//
//	// Create and initialize a buffer object
//
//	glGenBuffers(1, &m_uiBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, m_uiBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Points) + sizeof(m_Colors), NULL, GL_STATIC_DRAW);
//
//	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_Points), m_Points);
//	glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_Points), sizeof(m_Colors), m_Colors);
//}
//
//void Bullet::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle)
//{
//	// Load shaders and use the resulting shader program
//	if (uiShaderHandle == MAX_UNSIGNED_INT) m_uiProgram = InitShader("vsBullet.glsl", "fsVtxColor.glsl");
//	else m_uiProgram = uiShaderHandle;
//
//	// set up vertex arrays
//	GLuint vPosition = glGetAttribLocation(m_uiProgram, "vPosition");
//	glEnableVertexAttribArray(vPosition);
//	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//
//	GLuint vColor = glGetAttribLocation(m_uiProgram, "vColor");
//	glEnableVertexAttribArray(vColor);
//	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(m_Points)));
//
//	m_uiModelView = glGetUniformLocation(m_uiProgram, "ModelView");
//	m_mxView = mxView;
//	glUniformMatrix4fv(m_uiModelView, 1, GL_TRUE, m_mxView);
//
//	m_uiProjection = glGetUniformLocation(m_uiProgram, "Projection");
//	m_mxProjection = mxProjection;
//	glUniformMatrix4fv(m_uiProjection, 1, GL_TRUE, m_mxProjection);
//
//	m_Move = glGetUniformLocation(m_uiProgram, "mxT");
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void Bullet::SetMainPos(vec4 mainPos) {
//	pos = mainPos;
//}
//
//void Bullet::SetMove() {
//	glUseProgram(m_uiProgram);
//	pos.y += 1 * 0.005f;
//	mT = Translate(pos);
//	glUniformMatrix4fv(m_Move, 1, GL_TRUE, mT);
//}
//
//void Bullet::SetViewMatrix(mat4 &mat)
//{
//	m_mxView = mat;
//	m_bUpdateMV = true;
//}
//
//void Bullet::SetProjectionMatrix(mat4 &mat)
//{
//	m_mxProjection = mat;
//	m_bUpdateProj = true;
//}
//
//void Bullet::SetTRSMatrix(mat4 &mat)
//{
//	m_mxTRS = mat;
//	m_bUpdateMV = true;
//}
//
//void Bullet::SetColor(GLfloat vColor[4])
//{
//	for (int i = 0; i < Total_NUM; i++) {
//		m_Colors[i].x = vColor[0];
//		m_Colors[i].y = vColor[1];
//		m_Colors[i].z = vColor[2];
//		m_Colors[i].w = vColor[3];
//	}
//	glBindBuffer(GL_ARRAY_BUFFER, m_uiBuffer);
//	glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_Points), sizeof(m_Colors), m_Colors);
//}
//
//
//void Bullet::Draw()
//{
//	glUseProgram(m_uiProgram);
//	glBindVertexArray(m_uiVao);
//	if (m_bUpdateMV) {
//		m_mxMVFinal = m_mxView*m_mxTRS;
//		m_bUpdateMV = false;
//	}
//	glUniformMatrix4fv(m_uiModelView, 1, GL_TRUE, m_mxMVFinal);
//
//	if (m_bUpdateProj) {
//		glUniformMatrix4fv(m_uiProjection, 1, GL_TRUE, m_mxProjection);
//		m_bUpdateProj = false;
//	}
//	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
//	glDrawArrays(GL_TRIANGLE_FAN, QUAD_NUM, Top_NUM);
//}
//
//void Bullet::DrawW()
//{
//	glBindVertexArray(m_uiVao);
//
//	if (m_bUpdateMV) {
//		m_mxMVFinal = m_mxView*m_mxTRS;
//		m_bUpdateMV = false;
//	}
//
//	glUniformMatrix4fv(m_uiModelView, 1, GL_TRUE, m_mxMVFinal);
//	if (m_bUpdateProj) {
//		glUniformMatrix4fv(m_uiProjection, 1, GL_TRUE, m_mxProjection);
//		m_bUpdateProj = false;
//	}
//	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
//	glDrawArrays(GL_TRIANGLE_FAN, QUAD_NUM, Top_NUM);
//}