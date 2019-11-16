#include <time.h>
#include "header/Angel.h"
#include "Common/MainScene.h"

#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2) 
#define SPACE_KEY 32
#define VP_HALFWIDTH  12.0f

// 必須在 glewInit(); 執行完後,在執行物件實體的取得
MainScene *g_MainScene;

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

//----------------------------------------------------------------------------
// 函式的原型宣告
void IdleProcess();

//----------------------------------------------------------------------------
void init(void)
{
	g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);

	//MainScene
	g_MainScene = new MainScene(g_mxModelView, g_mxProjection);

	glClearColor(0.05, 0.05, 0.05, 1.0); // black background

	//透明顏色
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window	

	g_MainScene->Draw();

	glutSwapBuffers();	// 交換 Frame Buffer
}

//----------------------------------------------------------------------------

void onFrameMove(float delta)
{
	g_MainScene->Update(delta);

	GL_Display();
}

//----------------------------------------------------------------------------

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case  SPACE_KEY:
		g_MainScene->isProtect = !g_MainScene->isProtect;
		break;
	case 033:
		delete g_MainScene;	
		exit(EXIT_SUCCESS);
		break;
	}
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN) {
			g_MainScene->isShoot = true;
		}
		if (state == GLUT_UP) {
			g_MainScene->isShoot = false;
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

	g_MainScene->SpecialInput(key);

		switch (key) {
		case GLUT_KEY_LEFT:		// 目前按下的是向左方向鍵
			break;
		case GLUT_KEY_RIGHT:	// 目前按下的是向右方向鍵
			break;
		default:
			break;
		}
}
//----------------------------------------------------------------------------
void Win_MouseMotion(int x, int y) {
	float ix = 12.0f*(x - HALF_SIZE) / (HALF_SIZE);
	float iy = -12.0f*(y - HALF_SIZE) / (HALF_SIZE);

	g_MainScene->pPlayer->SetPosition(vec4(ix, iy, 0.0f, 1.0f));
}
//----------------------------------------------------------------------------
void Win_PassiveMotion(int x, int y) { //滑鼠單純移動
	float ix = 12.0f*(x - HALF_SIZE) / (HALF_SIZE);
	float iy = -12.0f*(y - HALF_SIZE) / (HALF_SIZE);

	g_MainScene->pPlayer->SetPosition(vec4(ix, iy, 0.0f, 1.0f));
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

	glutCreateWindow("2D ShootingGame");

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
