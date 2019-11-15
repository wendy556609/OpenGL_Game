// Model-View matrix and Projection matrix
// Orthogonal or Orthographic projection
// Windows Events - Keyboard & Mouse
// Rotate Rectangle
#include <time.h>
#include "header/Angel.h"
#include "Common/Main.h"
#include "Common/Protect.h"
#include "Common/Bullet.h"
#include "Common/Planet.h"

#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2) 
#define SPACE_KEY 32
#define VP_HALFWIDTH  12.0f

// 必須在 glewInit(); 執行完後,在執行物件實體的取得
Main *g_pQuad;	// 宣告 Quad 指標物件，結束時記得釋放
Protect *g_pPro;
//Bullet *g_pBullet;
//Bullet *g_pBullets[3];
//Bullet *g_pShootBullets[3];
Planet *g_pPlanet[3];

Bullet *g_pBulletHead = NULL;
Bullet *g_pBulletGet = NULL;
Bullet *g_pBulletTail = NULL;

Bullet *g_pBulletHead1 = NULL;
Bullet *g_pBulletGet1 = NULL;
Bullet *g_pBulletLink1 = NULL;
Bullet *g_pBulletTail1 = NULL;

				// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;
mat4 Main_Local;
mat4 mQT, mPT, mBT, mPLT[3];//位移
mat4 mPLS[3];//縮放
//vec4 ProColor;

//Main
float vQT[3];

//Protect
float vPT[3];

//Planet
float vIPLT[3][3] = {10.0f,15.0f,1.0f,
					-10.0f,20.0f,1.0f,
					1.0f,25.0f,1.0f};
float vPLT[3][3];
float vIPLS[3][3] = { 0.5f,0.5f,1.0f,
					1.0f,1.0f,1.0f,
					0.75f,0.75f,1.0f };
float vPLS[3][3];
float IPLcolor[3][4]= { 0.0f,0.75f,1.0f,0.5f,
						0.8f,0.5f,0.8f,0.5f,
						1.0f,0.8f,0.25f,0.5f };//0.0f,0.75f,1.0f,0.5f,
float PLcolor[3][4];
// For Rotation
float g_fAngle = 0;
float g_BTime = 0;
float ix = 0.0f, iy = 0.0f;

int bulletCount = 0;
int totalCount = 30;
bool isProtect = false;
bool isShoot = false;
bool isClear = false;
								 //----------------------------------------------------------------------------
								 // 函式的原型宣告
void IdleProcess();
void Create();
void ResetProtect();
void Shoot(float);
void DetectBullet();
void PlanetMove(float);

void init(void)
{
	g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);

	Create();	

	glClearColor(0.05, 0.05, 0.05, 1.0); // black background

	//透明顏色
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Create(void) {
	//Main
	g_pQuad = new Main;

	vQT[0] = vQT[1] = vQT[2] = 0.0f;
	mQT = Translate(vQT[0], vQT[1], vQT[2]);
	g_pQuad->SetColor(vec4(-1.0f, 1.0f, 1.0f, 1.0f));
	g_pQuad->SetShader(g_mxModelView, g_mxProjection);
	g_pQuad->SetTRSMatrix(mQT);

	//Protect
	g_pPro = new Protect;

	vPT[0] = vPT[1] = vPT[2] = 0.0f;
	mPT = Translate(vec4(vPT[0], vPT[1], vPT[2]));
	g_pPro->SetColor(vec4(1.0f,0.0f,0.0f,0.5f));
	g_pPro->SetShader(g_mxModelView, g_mxProjection);
	g_pPro->SetTRSMatrix(mQT*mPT);
	g_pPro->SetTurn(g_fAngle);

	//Planet
	for (int i = 0; i < 3; i++)
	{
		g_pPlanet[i] = new Planet;
		vPLT[i][0] = vIPLT[i][0]; vPLT[i][1] = vIPLT[i][1]; vPLT[i][2] = vIPLT[i][2];
		vPLS[i][0] = vIPLS[i][0]; vPLS[i][1] = vIPLS[i][1]; vPLS[i][2] = vIPLS[i][2];
		PLcolor[i][0] = IPLcolor[i][0]; PLcolor[i][1] = IPLcolor[i][1]; PLcolor[i][2] = IPLcolor[i][2]; PLcolor[i][3] = IPLcolor[i][3];
		mPLT[i] = Translate(vPLT[i][0], vPLT[i][1], vPLT[i][2]);
		mPLS[i] = Scale(vPLS[i][0], vPLS[i][1], vPLS[i][2]);
		g_pPlanet[i]->SetColor(vec4(PLcolor[i][0], PLcolor[i][1], PLcolor[i][2], PLcolor[i][3]));
		g_pPlanet[i]->SetShader(g_mxModelView, g_mxProjection);
		g_pPlanet[i]->SetMove(mPLT[i]*mPLS[i]);
	}
	
	//Bullet
	g_pBulletHead = g_pBulletGet = g_pBulletTail = NULL;
	g_pBulletHead = new Bullet;
	g_pBulletHead->SetShader(g_mxModelView, g_mxProjection);
	g_pBulletTail = g_pBulletHead;
	for (int i = 0; i < totalCount; i++)
	{
		g_pBulletGet = new Bullet;
		g_pBulletGet->SetShader(g_mxModelView, g_mxProjection);
		g_pBulletGet->next = NULL;		
		g_pBulletTail->next = g_pBulletGet;
		g_pBulletTail = g_pBulletGet;
	}
}

void Shoot(float delta) {	
	g_BTime += delta;
	if (g_BTime >= 0.2f) {
		if (g_pBulletHead1 == NULL) {
			g_pBulletHead1 = g_pBulletHead;
			g_pBulletHead = g_pBulletHead->next;
			g_pBulletTail1 = g_pBulletHead1;
			g_pBulletGet1 = g_pBulletHead1;
			g_pBulletGet1->next = NULL;
			bulletCount++;
		}
		else {
			g_pBulletGet1 = g_pBulletHead;
			g_pBulletHead = g_pBulletHead->next;
			g_pBulletGet1->next = NULL;
			g_pBulletTail1->next = g_pBulletGet1;
			g_pBulletTail1 = g_pBulletGet1;
			bulletCount++;
		}
		g_pBulletGet1->SetMainPos(vec4(vQT[0], vQT[1], vQT[2], 1.0f));
		g_BTime = 0;
	}
	
}

void DetectBullet() {
	g_pBulletLink1 = NULL;
	g_pBulletGet1 = g_pBulletHead1;
	while (g_pBulletGet1 != NULL)
	{
		g_pBulletGet1->SetMove();
		if (g_pBulletGet1->GetPos().y >= 12.0f) {
			if (g_pBulletLink1 == NULL) {
				g_pBulletGet = g_pBulletGet1;
				g_pBulletHead1 = g_pBulletGet1->next;
				g_pBulletGet1 = g_pBulletGet1->next;
				g_pBulletGet->next = g_pBulletHead;
				g_pBulletHead = g_pBulletGet;
				bulletCount--;
			}
			else {
				g_pBulletGet = g_pBulletGet1;
				g_pBulletGet1 = g_pBulletLink1;
				g_pBulletGet1->next = g_pBulletGet->next;
				g_pBulletGet->next = g_pBulletHead;
				g_pBulletHead = g_pBulletGet;
				bulletCount--;
			}
		}
		else {
			g_pBulletLink1 = g_pBulletGet1;
			g_pBulletGet1 = g_pBulletGet1->next;
		}	
	}
}

void PlanetMove(float delta) {
	for (int i = 0; i < 3; i++)
	{
		vPLT[i][1] -= 5*delta;

		mPLT[i] = Translate(vPLT[i][0], vPLT[i][1], vPLT[i][2]);
		g_pPlanet[i]->SetMove(mPLT[i] * mPLS[i]);

		if (vPLT[i][1]<=-15) {
			int b = rand() % 5;
			int R, G, B;
			R = rand() % 10;
			G = rand() % 10;
			B = rand() % 10;
			
			vPLT[i][0] = vIPLT[i][0]; vPLT[i][1] = vIPLT[i][1]; vPLT[i][2] = vIPLT[i][2];
			vPLS[i][0] = vPLS[i][1] = (b + 5)*0.1f;
			PLcolor[i][0] = (R + 1) * 0.1f; PLcolor[i][1] = (G + 1) * 0.1f; PLcolor[i][2] = (B + 1) * 0.1f; PLcolor[i][3] = 0.5f;
			mPLS[i] = Scale(vPLS[i][0], vPLS[i][1], vPLS[i][2]);
			g_pPlanet[i]->SetColor(vec4(PLcolor[i][0], PLcolor[i][1], PLcolor[i][2], PLcolor[i][3]));
		}
	}
}

void ResetProtect() {
	g_fAngle = 0;
	g_pPro->SetTurn(g_fAngle);
}
//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window	
	
	g_pPlanet[0]->Draw();
	g_pPlanet[1]->Draw();
	g_pPlanet[2]->Draw();

	g_pBulletGet1 = g_pBulletHead1;
	while (g_pBulletGet1 != NULL)
	{
		g_pBulletGet1->Draw();
		g_pBulletGet1 = g_pBulletGet1->next;
	}

	g_pQuad->Draw();

	if (isProtect) {
		g_pPro->Draw();
	}	

	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	if (isShoot && bulletCount <= totalCount) {
		Shoot(delta);
	}	
	DetectBullet();
	PlanetMove(delta);
	if (!isProtect) ResetProtect();
	GL_Display();
}

//----------------------------------------------------------------------------

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case  SPACE_KEY:
		isProtect = !isProtect;
		break;
	case 033:
		delete g_pPro;
		delete g_pQuad;	
		for (int i = 0; i < 3; i++)
		{
			delete g_pPlanet[i];
		}
		g_pBulletGet = g_pBulletHead;
		while (g_pBulletGet!=NULL)
		{
			g_pBulletHead = g_pBulletGet->next;
			delete g_pBulletGet;
			g_pBulletGet = g_pBulletHead;
		}
		delete g_pBulletHead;
		g_pBulletGet1 = g_pBulletHead1;
		while (g_pBulletGet1 != NULL)
		{
			g_pBulletHead1 = g_pBulletGet1->next;
			delete g_pBulletGet1;
			g_pBulletGet1 = g_pBulletHead1;
		}
		delete g_pBulletHead1;
		exit(EXIT_SUCCESS);
		break;
	}
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN) {
			isShoot = true;
		}
		if (state == GLUT_UP) {
			isShoot = false;
		}
		break;
	case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 ，換成 Y 軸
		break;
	case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	if (isProtect) {
		switch (key) {
		case GLUT_KEY_LEFT:		// 目前按下的是向左方向鍵
			g_fAngle += 2.0f;
			break;
		case GLUT_KEY_RIGHT:	// 目前按下的是向右方向鍵
			g_fAngle -= 2.0f;
			break;
		default:
			break;
		}
		if (g_fAngle >= 45)g_fAngle = 45;
		else if ((g_fAngle <= -45))g_fAngle = -45;
		g_pPro->SetTurn(g_fAngle);
	}
		glutPostRedisplay();
}
//----------------------------------------------------------------------------
void Win_MouseMotion(int x, int y) {
	ix = 12.0f*(x - HALF_SIZE) / (HALF_SIZE);
	iy = -12.0f*(y - HALF_SIZE) / (HALF_SIZE);
	vQT[0] = ix;
	vQT[1] = iy;
	mPT = Translate(vPT[0], vPT[1], vPT[2]);
	mQT = Translate(vQT[0], vQT[1], vQT[2]);
	g_pPro->SetTRSMatrix(mQT*mPT);
	g_pQuad->SetTRSMatrix(mQT);
	//glutPostRedisplay();     // 目前的視窗需要被重畫
}
//----------------------------------------------------------------------------
void Win_PassiveMotion(int x, int y) { //滑鼠單純移動
	ix = 12.0f*(x - HALF_SIZE) / (HALF_SIZE);
	iy = -12.0f*(y - HALF_SIZE) / (HALF_SIZE);
	vQT[0] = ix;
	vQT[1] = iy;
	mPT = Translate(vPT[0], vPT[1], vPT[2]);
	mQT = Translate(vQT[0], vQT[1], vQT[2]);
	g_pPro->SetTRSMatrix(mQT*mPT);
	g_pQuad->SetTRSMatrix(mQT);
	//glutPostRedisplay();     // 目前的視窗需要被重畫
}
//----------------------------------------------------------------------------；
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}

//----------------------------------------------------------------------------

int main(int argc, char **argv)
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Draw two triangles");

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutPassiveMotionFunc(Win_PassiveMotion);
	glutMotionFunc(Win_MouseMotion);
	glutMouseFunc(Win_Mouse);
	glutKeyboardFunc(Win_Keyboard);	// 處理 ASCI 按鍵如 A、a、ESC 鍵...等等
	glutSpecialFunc(Win_SpecialKeyboard);	// 處理 NON-ASCI 按鍵如 F1、Home、方向鍵...等等
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}
