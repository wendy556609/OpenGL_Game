#include "Player.h"
Player::Player(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	
	Create(matModelView, matProjection, shaderHandle);
	
	//_protect = new Protect(matModelView, matProjection, InitShader("vsMove.glsl", "fsVtxColor.glsl"));
	_bulletLink = new BulletLink(30, matModelView, matProjection);
}

Player::~Player() {
	if (_bulletLink != NULL) delete _bulletLink;
	//if (_protect != NULL)delete _protect;
}

void Player::Create(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	//UpQuad
	_points[0] = point4(-1.0f, 0.0f, 0.0f, 1.0f);
	_points[1] = point4(1.0f, 0.0f, 0.0f, 1.0f);
	_points[2] = point4(1.5f, -0.5f, 0.0f, 1.0f);
	_points[3] = point4(-1.0f, 0.0f, 0.0f, 1.0f);
	_points[4] = point4(1.5f, -0.5f, 0.0f, 1.0f);
	_points[5] = point4(-1.5f, -0.5f, 0.0f, 1.0f);

	_colors[0] = color4(0.25f, 0.25f, 0.25f, 1.0f);  // (r, g, b, a)
	_colors[1] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[2] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[3] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[4] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[5] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//Head
	for (int i = 6; i < 26; i++)
	{
		_points[i] = point4(0.1f*cosf(M_PI*(i-6) / (Head_NUM-1)), 0.1f* sinf(M_PI*(i - 6) / (Head_NUM-1)), 0.0f, 0.1f);
		_colors[i] = color4(0.25f, 1.0f, 0.5f, 1.0f);
	}

	//Eyes
	for (int i = 26; i < 46; i++)
	{
		_points[i] = point4(0.025f*cosf(M_PI*2.0f*(i - 26) / 20)+0.05f, 0.025f* sinf(M_PI*2.0f*(i - 26) / 20) + 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	for (int i = 46; i < 66; i++)
	{
		_points[i] = point4(0.025f*cosf(M_PI*2.0f*(i - 46) / 20) - 0.05f, 0.025f* sinf(M_PI*2.0f*(i - 46) / 20) + 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//ButtomQuad
	_points[66] = point4(-2.0f, -0.5f, 0.0f, 1.0f);
	_points[67] = point4(2.0f, -0.5f, 0.0f, 1.0f);
	_points[68] = point4(2.5f, -1.25f, 0.0f, 1.0f);
	_points[69] = point4(-2.0f, -0.5f, 0.0f, 1.0f);
	_points[70] = point4(2.5f, -1.25f, 0.0f, 1.0f);
	_points[71] = point4(-2.5f, -1.25f, 0.0f, 1.0f);

	_colors[66] = color4(0.25f, 0.25f, 0.25f, 1.0f);  // (r, g, b, a)
	_colors[67] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[68] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[69] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[70] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[71] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//ButtomCircle
	for (int i = 72; i < 92; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*(i - 72) / 19) - 0.175f, 0.05f* (-sinf(M_PI*(i - 72) / 19)) - 0.125f, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.75f, 0.2f, 1.0f);
	}
	for (int i = 92; i < 112; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*(i - 92) / 19) , 0.05f* (-sinf(M_PI*(i - 92) / 19)) - 0.125f, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.75f, 0.2f, 1.0f);
	}
	for (int i = 112; i < 132; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*(i - 112) / 19) + 0.175f, 0.05f* (-sinf(M_PI*(i - 112) / 19)) - 0.125f, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.75f, 0.2f, 1.0f);
	}

	//UpCircle
	for (int i = 132; i < 152; i++)
	{
		_points[i] = point4(0.2f*cosf(M_PI*(i - 132) / 19), 0.2f* sinf(M_PI*(i - 132) / 19) - 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 1.0f, 1.0f, 0.25f);
	}

	_transform = new Transform(matModelView, matProjection, Total_NUM, _points, _colors);
	_collider.Init(2.5f, 1.5f, vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

void Player::Draw() {
	_bulletLink->Draw();

	//if(isProtect)_protect->Draw();

	_transform->Draw();
	
	glDrawArrays(GL_TRIANGLES, 0, 6); 
	glDrawArrays(GL_TRIANGLE_FAN, 6, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 26, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 46, 20);
	glDrawArrays(GL_TRIANGLES, 66, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 72, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 92, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 112, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 132, 20);
}

void Player::SetPosition(vec4 position) {
	mat4 mT;
	_pos = position;
	mT = Translate(_pos);
	//_protect->SetParent(mT);
	SetTRSMatrix(mT);
	_collider.SetCollider(_pos);
}

void Player::Update(float delta) {
	if (isShoot && _bulletLink->useCount<= _bulletLink->totalCount) {
		shootTime += delta;
		if (shootTime >= 0.2f) {
			_bulletLink->Shoot(delta, _pos);
			shootTime = 0;
		}		
	}
	_bulletLink->DetectBullet();

	//if (!isProtect)_protect->ResetProtect();
	//else _protect->Update(delta);
}