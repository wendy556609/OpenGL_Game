#include "Smoke.h"

float bombTime = 0.0f;
float color = 0;
bool isClear = false;

Bomb::Bomb(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	pointNum = 200;

	_points = new point4[pointNum];
	_colors = new color4[pointNum];

	//RED
	for (int i = 0; i < 20; i++)
	{
		_points[i] = point4(0.12f*cosf(M_PI*2.0f*i / 20) + 0.1f , 0.1f* sinf(M_PI*2.0f*i / 20), 0.0f, 0.1f);
		_colors[i] = color4(0.8f, 0.125f, 0.125f, 1.0f);
	}
	//Orange
	for (int i = 20; i < 40; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 20) / 20)+0.025f, 0.075f* sinf(M_PI*2.0f*(i - 20) / 20) - 0.1f , 0.0f, 0.1f);
		_colors[i] = color4(0.9f, 0.5f, 0.0f, 1.0f);
	}
	//RED
	for (int i = 40; i < 60; i++)
	{
		_points[i] = point4(0.1f*cosf(M_PI*2.0f*(i - 40) / 20)-0.2f + 0.1f, 0.1f* sinf(M_PI*2.0f*(i - 40) / 20)-0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.8f, 0.125f, 0.125f, 1.0f);
	}
	//RED
	for (int i = 60; i < 80; i++)
	{
		_points[i] = point4(0.1f*cosf(M_PI*2.0f*(i - 60) / 20)-0.13f+ 0.1f, 0.1f* sinf(M_PI*2.0f*(i - 60) / 20) +0.12f, 0.0f, 0.1f);
		_colors[i] = color4(0.8f, 0.125f, 0.125f, 1.0f);
	}
	//Orange
	for (int i = 80; i < 100; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 80) / 20)-0.05f, 0.075f* sinf(M_PI*2.0f*(i - 80) / 20), 0.0f, 0.1f);
		_colors[i] = color4(0.9f, 0.5f, 0.0f, 1.0f);
	}
	//Orange
	for (int i = 100; i < 120; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 100) / 20) +0.1f, 0.075f* sinf(M_PI*2.0f*(i - 100) / 20)+0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.9f, 0.5f, 0.0f, 1.0f);
	}
	//Yellow
	for (int i = 120; i < 140; i++)
	{
		_points[i] = point4(0.06f*cosf(M_PI*2.0f*(i - 120) / 20)+0.1f, 0.06f* sinf(M_PI*2.0f*(i - 120) / 20)-0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.9f, 0.9f, 0.0f, 1.0f);
	}
	//Yellow
	for (int i = 140; i < 160; i++)
	{
		_points[i] = point4(0.06f*cosf(M_PI*2.0f*(i - 140) / 20) - 0.04f, 0.06f* sinf(M_PI*2.0f*(i - 140) / 20) + 0.05f, 0.0f, 0.1f);
		_colors[i] = color4(0.9f, 0.9f, 0.0f, 1.0f);
	}
	//Yellow
	for (int i = 160; i < 180; i++)
	{
		_points[i] = point4(0.06f*cosf(M_PI*2.0f*(i - 160) / 20) + 0.05f, 0.06f* sinf(M_PI*2.0f*(i - 160) / 20) + 0.075f, 0.0f, 0.1f);
		_colors[i] = color4(0.9f, 0.9f, 0.0f, 1.0f);
	}
	//White
	for (int i = 180; i < 200; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*2.0f*(i - 180) / 20), 0.05f* sinf(M_PI*2.0f*(i - 180) / 20) + 0.09f, 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	_transform = new Transform(matModelView, matProjection, pointNum, _points, _colors, shaderHandle);
	SetColor(vec4(0.0f, 0.0f, 0.0f, -1.0f));
}

Bomb::~Bomb() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL)delete [] _points;
	if (_colors != NULL)delete [] _colors;
}

void Bomb::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 60, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 80, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 100, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 120, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 140, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 160, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 180, 20);
}

void Bomb::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Bomb::SetColor(GLfloat vColor[4]) {
	_transform->SetHurtColor(vColor);
}

void Bomb::SetBomb(float delta) {
	int Count = 0;
	mat4 mT;
	SetTRSMatrix(Translate(_pos));
	if (!finish) {
		
		
		if (color < 1.0f && !isClear) {
			bombTime += delta;
			if (bombTime >= 0.1f&&Count < 1) {
				color += 0.1f;
				SetColor(vec4(0.0f, 0.0f, 0.0f, 0.1));
				Count++;
				
				if (color >= 1.0) {
					color = 0;
					isClear = true;
				}
				bombTime = 0;
			}
		}
		else if (color > -1.0f&&isClear) {
			bombTime += delta;
			if (bombTime >= 0.1f&&Count < 1) {
				color -= 0.1f;
				SetColor(vec4(0.0f, 0.0f, 0.0f, -0.1));
				Count++;
				if (color <= -1.0f) {
					color = 0;
					isClear = false;
					
					finish = true;
				}
				bombTime = 0;
			}
		}
	}		
		
}


///////////////////////////////////////

Smoke::Smoke(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	pointNum = 160;

	_points = new point4[pointNum];
	_colors = new color4[pointNum];

	///
	//Gray
	for (int i = 0; i < 20; i++)
	{
		_points[i] = point4(0.05f*cosf(M_PI*2.0f*i / 20)-0.05f, 0.05f* sinf(M_PI*2.0f*i / 20) + 0.05f, 0.0f, 0.1f);//(0,1)
		_colors[i] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	}
	//Gray2
	for (int i = 20; i < 40; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 20) / 20) + 0.025f - 0.05f, 0.075f* sinf(M_PI*2.0f*(i - 20) / 20) + 0.15f, 0.0f, 0.1f);
		_colors[i] = color4(0.35f, 0.35f, 0.35f, 1.0f);
	}
	///
	//Gray3
	for (int i = 40; i < 60; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 40) / 20) - 0.075f - 0.05f, 0.075f* sinf(M_PI*2.0f*(i - 40) / 20) +0.125f, 0.0f, 0.1f);
		_colors[i] = color4(0.425f, 0.425f, 0.425f, 1.0f);
	}
	//Gray3
	for (int i = 60; i < 80; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 60) / 20) + 0.0175f - 0.05f, 0.075f* sinf(M_PI*2.0f*(i - 60) / 20) + 0.25f, 0.0f, 0.1f);
		_colors[i] = color4(0.425f, 0.425f, 0.425f, 1.0f);
	}
	///
	//Gray4
	for (int i = 80; i < 100; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 80) / 20) - 0.12f - 0.05f, 0.075f* sinf(M_PI*2.0f*(i - 80) / 20)+0.325f, 0.0f, 0.1f);
		_colors[i] = color4(0.325f, 0.325f, 0.325f, 1.0f);
	}
	//Gray3
	for (int i = 100; i < 120; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 100) / 20) - 0.09f - 0.05f, 0.075f* sinf(M_PI*2.0f*(i - 100) / 20) + 0.225f, 0.0f, 0.1f);
		_colors[i] = color4(0.425f, 0.425f, 0.425f, 1.0f);
	}
	///
	//Gray4
	for (int i = 120; i < 140; i++)
	{
		_points[i] = point4(0.075f*cosf(M_PI*2.0f*(i - 120) / 20) -0.175f - 0.05f, 0.075f* sinf(M_PI*2.0f*(i - 120) / 20) + 0.21f, 0.0f, 0.1f);
		_colors[i] = color4(0.325f, 0.325f, 0.325f, 1.0f);
	}
	//Gray
	for (int i = 140; i < 160; i++)
	{
		_points[i] = point4(0.06f*cosf(M_PI*2.0f*(i - 140) / 20) - 0.04f - 0.05f, 0.06f* sinf(M_PI*2.0f*(i - 140) / 20) + 0.2f, 0.0f, 0.1f);
		_colors[i] = color4(0.475f, 0.475f, 0.475f, 1.0f);
	}

	_transform = new Transform(matModelView, matProjection, pointNum, _points, _colors, shaderHandle);
	SetColor(0, pointNum,vec4(0.0f, 0.0f, 0.0f, -1.0f));
}

Smoke::~Smoke() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL)delete[] _points;
	if (_colors != NULL)delete[] _colors;
}

void Smoke::Draw() {
	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 60, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 80, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 100, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 120, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 140, 20);
}

void Smoke::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Smoke::SetColor(int start,int end,GLfloat vColor[4]) {
	_transform->SetSmokeColor(start, end, vColor);
}

void Smoke::SetPosition(int start, int end, GLfloat vPosition[4]) {
	_transform->SetPosition(start, end, vPosition);
}

void Smoke::SetSmoke(float delta) {
	int Count1 = 0, Count2 = 0, Count3 = 0, Count4 = 0;

	if (start) {
		time1 += delta; time2 += delta; time3 += delta; time4 += delta;

		SetTRSMatrix(RotateZ(_angle)*Translate(_pos));

		if (_color1 < 1.0f && !clear1) {
			if (time1 >= 0.1f&&Count1 < 1) {
				_color1 += 0.1f;
				if (_color1 <= 0.9f)SetColor(0, 40, vec4(0.0f, 0.0f, 0.0f, 0.1f));
				Count1++;

				if (_color1 >= 0.9f) {
					_color1 = 0.0f;
					clear1 = true;
				}
				time1 = 0.0f;
			}
		}
		else if (_color1 > -1.0f&&clear1) {
			if (time1 >= 0.1f&&Count1 < 1) {
				_color1 -= 0.1f;
				if (_color1 >= -0.9f)SetColor(0, 40, vec4(0.0f, 0.0f, 0.0f, -0.1f));
				Count1++;
				if (_color1 <= -0.9f) {
						_color1 = 0.0f;
						clear1 = false;
				}
				time1 = 0.0f;
			}
		}

		if (_color2 < 1.0f && !clear2) {
			if (time2 >= 0.125f&&Count2 < 1) {
				_color2 += 0.1f;
				if (_color2 <= 0.9f)SetColor(40, 80, vec4(0.0f, 0.0f, 0.0f, 0.1f));
				Count2++;

				if (_color2 >= 0.9f) {
						_color2 = 0.0f;
						clear2 = true;
				}
				time2 = 0.0f;
			}
		}
		else if (_color2 > -1.0f&&clear2) {
			if (time2 >= 0.125f&&Count2 < 1) {
				_color2 -= 0.1f;
				if (_color2 >= -0.9f)SetColor(40, 80, vec4(0.0f, 0.0f, 0.0f, -0.1f));
				Count2++;
				if (_color2 <= -0.9f) {
						_color2 = 0.0f;
						clear2 = false;
				}
				time2 = 0.0f;
			}
		}

		if (_color3 < 1.0f && !clear3) {
			if (time3 >= 0.15f&&Count3 < 1) {
				_color3 += 0.1f;
				if (_color3 <= 0.9f)SetColor(80, 120, vec4(0.0f, 0.0f, 0.0f, 0.1f));
				Count3++;

				if (_color3 >= 0.9f) {
						_color3 = 0.0f;
						clear3 = true;
				}
				time3 = 0.0f;
			}
		}
		else if (_color3 > -1.0f&&clear3) {
			if (time3 >= 0.15f&&Count3 < 1) {
				_color3 -= 0.1f;
				if (_color3 >= -0.9f)SetColor(80, 120, vec4(0.0f, 0.0f, 0.0f, -0.1f));
				Count3++;
				if (_color3 <= -0.9f) {
						_color3 = 0.0f;
						clear3 = false;
				}
				time3 = 0.0f;
			}
		}

		if (_color4 < 1.0f && !clear4) {
			if (time4 >= 0.175f&&Count4 < 1) {
				_color4 += 0.1f;
				if (_color4 <= 0.9f)SetColor(120, 160, vec4(0.0f, 0.0f, 0.0f, 0.1f));
				Count4++;

				if (_color4 >= 0.9f) {
						_color4 = 0.0f;
						clear4 = true;
				}
				time4 = 0.0f;
			}
		}
		else if (_color4 > -1.0f&&clear4) {
			if (time4 >= 0.175f&&Count4 < 1) {
				_color4 -= 0.1f;
				if(_color4>=-0.9f)SetColor(120, 160, vec4(0.0f, 0.0f, 0.0f, -0.1f));				
				Count4++;
				if (_color4 <= -0.9f) {
						_color4 = 0.0f;
						clear4 = false;
				}
				time4 = 0.0f;
			}
		}
	}
	

}