#include "Item.h"

void Item::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}


Item_Pro::Item_Pro(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	mat4 mT;

	_pointNum = 80;

	_points = new point4[_pointNum];
	_colors = new color4[_pointNum];

	Create();

	_transform = new Transform(matModelView, matProjection, _pointNum, _points, _colors);

	_collider.isDestroy = false;
	_collider.Init(0.75f, 0.75f);

	Init();
}
void Item_Pro::Create() {
	//Buttom
	for (int i = 0; i < 20; i++)
	{
		_points[i] = point4(0.15f*cosf(M_PI*2.0f*i / 20), 0.15f* sinf(M_PI*2.0f*i / 20), 0.0f, 0.1f);
		_colors[i] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	}
	//Wood
	for (int i = 20; i < 40; i++)
	{
		_points[i] = point4(0.125f*cosf(M_PI*2.0f*(i - 20) / 20), 0.125f* sinf(M_PI*2.0f*(i - 20) / 20), 0.0f, 0.1f);
		_colors[i] = color4(0.5f, 0.3f, 0.1f, 1.0f);
	}
	//Middle
	for (int i = 40; i < 60; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*2.0f*(i - 40) / 20), 0.05f* sinf(M_PI*2.0f*(i - 40) / 20), 0.0f, 0.1f);
		_colors[i] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	}
	//BlackMiddle
	for (int i = 60; i < 80; i++)
	{
		_points[i] = point4(0.025f*cosf(M_PI*2.0f*(i - 60) / 20), 0.025f* sinf(M_PI*2.0f*(i - 60) / 20), 0.0f, 0.1f);
		_colors[i] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	}
}

Item_Pro::~Item_Pro() {
	if (_points != NULL) delete[] _points;
	if (_colors != NULL) delete[] _colors;
	if (_transform != NULL) delete _transform;
}

void Item_Pro::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 60, 20);
}

void Item_Pro::Init() {
	mat4 mT;
	if (!_collider.isDestroy) {
		int b = rand() % 10;
		_pos.x = (b - 5)*2.0f;
		_pos.y = 20.0f;
	}
	else {
		_pos.x = 50.0f;
		_pos.y = 50.0f;
	}

	mT = Translate(_pos);
	_collider.SetCollider(_pos);
	SetTRSMatrix(mT);
}

void Item_Pro::Update(float delta) {
	mat4 mT;
	if (!_collider.isDestroy) {
		_pos.y -= 3 * delta;

		mT = Translate(_pos);
		_collider.SetCollider(_pos);
		SetTRSMatrix(mT);

		if (_pos.y <= -15.0f)Init();
	}
	else Init();
}


////////////////////////////////
Item_Bullet::Item_Bullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	mat4 mT;

	_pointNum = 116;

	_points = new point4[_pointNum];
	_colors = new color4[_pointNum];

	Create();

	_transform = new Transform(matModelView, matProjection, _pointNum, _points, _colors);

	_collider.isDestroy = false;
	_collider.Init(1.25f, 1.125f);

	Init();
}
void Item_Bullet::Create() {
	//Handle
	for (int i = 0; i < 20; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*2.0f*i / 20) + 0.1f-0.05f , 0.05f* sinf(M_PI*2.0f*i / 20)+0.025f+0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	}

	for (int i = 20; i < 40; i++)
	{
		_points[i] = point4(0.03f*cosf(M_PI*2.0f*(i - 20) / 20) + 0.1f - 0.05f, 0.03f* sinf(M_PI*2.0f*(i - 20) / 20) + 0.025f+0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.05, 0.05, 0.05, 1.0);
	}

	//GunBody
	_points[40] = point4(-0.5f - 0.5f, 1.0f+0.5f, 0.0f, 1.0f);
	_points[41] = point4(2.0f - 0.5f, 1.0f + 0.5f, 0.0f, 1.0f);
	_points[42] = point4(2.0f - 0.5f, 0.25f + 0.5f, 0.0f, 1.0f);
	_points[43] = point4(-0.5f - 0.5f, 1.0f + 0.5f, 0.0f, 1.0f);
	_points[44] = point4(2.0f - 0.5f, 0.25f + 0.5f, 0.0f, 1.0f);
	_points[45] = point4(-0.5f - 0.5f, 0.25f + 0.5f, 0.0f, 1.0f);

	_colors[40] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[41] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[42] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[43] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[44] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[45] = color4(0.35f, 0.35f, 0.35f, 1.0f);

	//GunHandle
	_points[46] = point4(1.0f - 0.5f, 1.0f + 0.5f, 0.0f, 1.0f);
	_points[47] = point4(2.0f - 0.5f, 1.0f + 0.5f, 0.0f, 1.0f);
	_points[48] = point4(2.0f - 0.5f, -1.0f + 0.5f, 0.0f, 1.0f);
	_points[49] = point4(1.0f - 0.5f, 1.0f + 0.5f, 0.0f, 1.0f);
	_points[50] = point4(2.0f - 0.5f, -1.0f + 0.5f, 0.0f, 1.0f);
	_points[51] = point4(1.0f - 0.5f, -1.0f + 0.5f, 0.0f, 1.0f);

	_colors[46] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[47] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[48] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[49] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[50] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[51] = color4(0.35f, 0.35f, 0.35f, 1.0f);

	//GunHead
	_points[52] = point4(-0.6f - 0.5f, 0.85f + 0.5f, 0.0f, 1.0f);
	_points[53] = point4(-0.5f - 0.5f, 0.85f + 0.5f, 0.0f, 1.0f);
	_points[54] = point4(-0.5f - 0.5f, 0.65f + 0.5f, 0.0f, 1.0f);
	_points[55] = point4(-0.6f - 0.5f, 0.85f + 0.5f, 0.0f, 1.0f);
	_points[56] = point4(-0.5f - 0.5f, 0.65f + 0.5f, 0.0f, 1.0f);
	_points[57] = point4(-0.6f - 0.5f, 0.65f + 0.5f, 0.0f, 1.0f);

	_colors[52] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[53] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[54] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[55] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[56] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[57] = color4(0.35f, 0.35f, 0.35f, 1.0f);


	/////Gun2
	//Handle
	for (int i = 58; i < 78; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*2.0f*(i - 58) / 20) - 0.1f+0.05f, 0.05f* sinf(M_PI*2.0f*(i - 58) / 20) - 0.025f - 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	}

	for (int i = 78; i < 98; i++)
	{
		_points[i] = point4(0.03f*cosf(M_PI*2.0f*(i - 78) / 20) - 0.1f+0.05, 0.03f* sinf(M_PI*2.0f*(i - 78) / 20) - 0.025f - 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.05, 0.05, 0.05, 1.0);
	}

	//GunBody
	_points[98] = point4(0.5f + 0.5f, -1.0f - 0.5f, 0.0f, 1.0f);
	_points[99] = point4(-2.0f + 0.5f, -1.0f - 0.5f, 0.0f, 1.0f);
	_points[100] = point4(-2.0f + 0.5f, -0.25f - 0.5f, 0.0f, 1.0f);
	_points[101] = point4(0.5f + 0.5f, -1.0f - 0.5f, 0.0f, 1.0f);
	_points[102] = point4(-2.0f + 0.5f, -0.25f - 0.5f, 0.0f, 1.0f);
	_points[103] = point4(0.5f + 0.5f, -0.25f - 0.5f, 0.0f, 1.0f);

	_colors[98] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[99] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[100] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[101] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[102] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[103] = color4(0.35f, 0.35f, 0.35f, 1.0f);

	//GunHandle
	_points[104] = point4(-1.0f + 0.5f, -1.0f - 0.5f, 0.0f, 1.0f);
	_points[105] = point4(-2.0f + 0.5f, -1.0f - 0.5f, 0.0f, 1.0f);
	_points[106] = point4(-2.0f + 0.5f, 1.0f - 0.5f, 0.0f, 1.0f);
	_points[107] = point4(-1.0f + 0.5f, -1.0f - 0.5f, 0.0f, 1.0f);
	_points[108] = point4(-2.0f + 0.5f, 1.0f - 0.5f, 0.0f, 1.0f);
	_points[109] = point4(-1.0f + 0.5f, 1.0f - 0.5f, 0.0f, 1.0f);

	_colors[104] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[105] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[106] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[107] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[108] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[109] = color4(0.35f, 0.35f, 0.35f, 1.0f);

	//GunHead
	_points[110] = point4(0.6f + 0.5f, -0.85f - 0.5f, 0.0f, 1.0f);
	_points[111] = point4(0.5f + 0.5f, -0.85f - 0.5f, 0.0f, 1.0f);
	_points[112] = point4(0.5f + 0.5f, -0.65f - 0.5f, 0.0f, 1.0f);
	_points[113] = point4(0.6f + 0.5f, -0.85f - 0.5f, 0.0f, 1.0f);
	_points[114] = point4(0.5f + 0.5f, -0.65f - 0.5f, 0.0f, 1.0f);
	_points[115] = point4(0.6f + 0.5f, -0.65f - 0.5f, 0.0f, 1.0f);

	_colors[110] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[111] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[112] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[113] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[114] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	_colors[115] = color4(0.35f, 0.35f, 0.35f, 1.0f);
}

Item_Bullet::~Item_Bullet() {
	if (_points != NULL) delete[] _points;
	if (_colors != NULL) delete[] _colors;
	if (_transform != NULL) delete _transform;
}

void Item_Bullet::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 20);
	glDrawArrays(GL_TRIANGLES, 40, 6);
	glDrawArrays(GL_TRIANGLES, 46, 6);
	glDrawArrays(GL_TRIANGLES, 52, 6);

	glDrawArrays(GL_TRIANGLE_FAN, 58, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 78, 20);
	glDrawArrays(GL_TRIANGLES, 98, 6);
	glDrawArrays(GL_TRIANGLES, 104, 6);
	glDrawArrays(GL_TRIANGLES, 110, 6);
}

void Item_Bullet::Init() {
	mat4 mT;
	if (!_collider.isDestroy) {
		int b = rand() % 10;
		_pos.x = (b - 5)*2.0f;
		_pos.y = 20.0f;
	}
	else {
		_pos.x = 50.0f;
		_pos.y = 50.0f;
	}

	mT = Translate(_pos);
	_collider.SetCollider(_pos);
	SetTRSMatrix(mT);
}

void Item_Bullet::Update(float delta) {
	mat4 mT;
	if (!_collider.isDestroy) {
		_pos.y -= 3 * delta;

		mT = Translate(_pos);
		_collider.SetCollider(_pos);
		SetTRSMatrix(mT);

		if (_pos.y <= -15.0f)Init();
	}
	else Init();
}

////////////////////////////////
Item_FlyBullet::Item_FlyBullet(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	mat4 mT;

	_pointNum = 66;

	_points = new point4[_pointNum];
	_colors = new color4[_pointNum];

	Create();

	_transform = new Transform(matModelView, matProjection, _pointNum, _points, _colors);

	_collider.isDestroy = false;
	_collider.Init(1.25f, 1.125f);

	Init();
}
void Item_FlyBullet::Create() {
	//Body
	_points[0] = point4(-1.5f, 1.0f, 0.0f, 1.0f);
	_points[1] = point4(1.5f, 1.0f, 0.0f, 1.0f);
	_points[2] = point4(1.5f, -1.0f, 0.0f, 1.0f);
	_points[3] = point4(-1.5f, 1.0f, 0.0f, 1.0f);
	_points[4] = point4(1.5f, -1.0f, 0.0f, 1.0f);
	_points[5] = point4(-1.5f, -1.0f, 0.0f, 1.0f);

	_colors[0] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	_colors[1] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	_colors[2] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	_colors[3] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	_colors[4] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	_colors[5] = color4(0.475f, 0.475f, 0.475f, 1.0f);

	//Wood
	for (int i = 6; i < 26; i++)
	{
		_points[i] = point4(0.1f*cosf(M_PI*2.0f*(i - 6) / 20) - 0.05f, 0.1f* sinf(M_PI*2.0f*(i - 6) / 20) - 0.1f , 0.0f, 0.1f);
		_colors[i] = color4(0.5f, 0.3f, 0.1f, 1.0f);
	}

	//Black
	for (int i = 26; i < 46; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 26) / 20) - 0.05f, 0.075f* sinf(M_PI*2.0f*(i - 26) / 20) - 0.1f, 0.0f, 0.1f);
		_colors[i] = color4(0.05, 0.05, 0.05, 1.0);
	}

	//Middle
	for (int i = 46; i < 66; i++)
	{
		_points[i] = point4(0.025f*cosf(M_PI*2.0f*(i - 46) / 20) - 0.05f, 0.025f* sinf(M_PI*2.0f*(i - 46) / 20) - 0.1f, 0.0f, 0.1f);
		_colors[i] = color4(0.5f, 0.3f, 0.1f, 1.0f);
	}
}

Item_FlyBullet::~Item_FlyBullet() {
	if (_points != NULL) delete[] _points;
	if (_colors != NULL) delete[] _colors;
	if (_transform != NULL) delete _transform;
}

void Item_FlyBullet::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 26, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 46, 20);
}

void Item_FlyBullet::Init() {
	mat4 mT;
	if (!_collider.isDestroy) {
		int b = rand() % 10;
		_pos.x = (b - 5)*2.0f;
		_pos.y = 20.0f;
	}
	else {
		_pos.x = 50.0f;
		_pos.y = 50.0f;
	}

	mT = Translate(_pos);
	_collider.SetCollider(_pos);
	SetTRSMatrix(mT);
}

void Item_FlyBullet::Update(float delta) {
	mat4 mT;
	if (!_collider.isDestroy) {
		_pos.y -= 3 * delta;

		mT = Translate(_pos);
		_collider.SetCollider(_pos);
		SetTRSMatrix(mT);

		if (_pos.y <= -15.0f)Init();
	}
	else Init();
}