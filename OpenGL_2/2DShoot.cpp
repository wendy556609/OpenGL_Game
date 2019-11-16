#include <time.h>
#include "header/Angel.h"
#include "Common/MainScene.h"

#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2) 
#define SPACE_KEY 32
#define VP_HALFWIDTH  12.0f

// �����b glewInit(); ���槹��,�b���檫����骺���o
MainScene *g_MainScene;

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

//----------------------------------------------------------------------------
// �禡���쫬�ŧi
void IdleProcess();

//----------------------------------------------------------------------------
void init(void)
{
	g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);

	//MainScene
	g_MainScene = new MainScene(g_mxModelView, g_mxProjection);

	glClearColor(0.05, 0.05, 0.05, 1.0); // black background

	//�z���C��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window	

	g_MainScene->Draw();

	glutSwapBuffers();	// �洫 Frame Buffer
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
	case GLUT_LEFT_BUTTON:   // �ثe���U���O�ƹ�����
		if (state == GLUT_DOWN) {
			g_MainScene->isShoot = true;
		}
		if (state == GLUT_UP) {
			g_MainScene->isShoot = false;
		}
		break;
	case GLUT_MIDDLE_BUTTON:  // �ثe���U���O�ƹ����� �A���� Y �b
		break;
	case GLUT_RIGHT_BUTTON:   // �ثe���U���O�ƹ��k��
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {

	g_MainScene->SpecialInput(key);

		switch (key) {
		case GLUT_KEY_LEFT:		// �ثe���U���O�V����V��
			break;
		case GLUT_KEY_RIGHT:	// �ثe���U���O�V�k��V��
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
void Win_PassiveMotion(int x, int y) { //�ƹ���²���
	float ix = 12.0f*(x - HALF_SIZE) / (HALF_SIZE);
	float iy = -12.0f*(y - HALF_SIZE) / (HALF_SIZE);

	g_MainScene->pPlayer->SetPosition(vec4(ix, iy, 0.0f, 1.0f));
}
//----------------------------------------------------------------------------�F
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
	glutKeyboardFunc(Win_Keyboard);	// �B�z ASCI ����p A�Ba�BESC ��...����
	glutSpecialFunc(Win_SpecialKeyboard);	// �B�z NON-ASCI ����p F1�BHome�B��V��...����
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}
