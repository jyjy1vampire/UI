#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

//确定多边形绕法的方向
bool bWinding = true;

void SetupRC(void) {
	//设置窗口背景颜色为黑色
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ChangeSize(GLint w, GLint h) {
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-100.0f, 100.0f * h / w, -100.0f, 100.0f * h / w, -100.0f, 100.0f);
	}
	else {
		glOrtho(-100.0f * w / h, 100.0f * w / h, -100.0f, 100.0f, -100.0f, 100.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//在窗口中绘制图形
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//旋转图形
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	//设置点的大小以及线宽
	glPointSize(5.0f);
	glLineWidth(5.0f);

	//设置多边形绕法的方向是顺时针还是逆时针

	if (bWinding) {
		glFrontFace(GL_CW);
	}
	else {
		glFrontFace(GL_CCW);
	}

	//绘制三角形
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 60.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-60.0f, -60.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(60.0f, -60.0f, 0.0f);

	glEnd();
	glPopMatrix();
	glutSwapBuffers();

}

void SpecialKeys(GLint key, GLint x, GLint y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		xRot -= 5.0f;
		break;
	case GLUT_KEY_DOWN:
		xRot += 5.0f;
		break;
	case GLUT_KEY_LEFT:
		yRot -= 5.0f;
		break;
	case GLUT_KEY_RIGHT:
		yRot += 5.0f;
		break;
	default:
		//assert(0);
		break;

	}


	if (xRot > 356.0f) xRot = 0.0f;

	if (xRot < -1.0f)  xRot = 355.0f;

	if (yRot > 356.0f) yRot = 0.0f;

	if (yRot < -1.0f)  yRot = 355.0f;

	glutPostRedisplay();//重回窗口
}

void ProcessMenu(GLint value) {
	switch (value)
	{
	case 1:
		//修改多边形正面为填充模式
		glPolygonMode(GL_FRONT, GL_FILL);
		break;
	case 2:
		glPolygonMode(GL_FRONT, GL_LINE);
		break;
	case 3:
		glPolygonMode(GL_FRONT, GL_POINT);
		break;
	case 4:
		glPolygonMode(GL_FRONT, GL_FILL);
		break;
	case 5:
		glPolygonMode(GL_FRONT, GL_LINE);
		break;
	case 6:
		glPolygonMode(GL_FRONT, GL_POINT);
		break;
	case 7:
		glShadeModel(GL_FLAT);
		break;
	case 8:
		glShadeModel(GL_SMOOTH);
		break;
	case 9:
		bWinding = !bWinding;
		break;
	case 10:
		//以线条的框架显示图
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	default:
		break;
	}

}

int main(int argc, char *argv[]) {
	GLint nModeMenu = 0;
	GLint nMainMenu = 0;
	GLint nColorMenu = 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("多边形演示");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);

	//创建一个子菜单
	nModeMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("正面多边形填充模式", 1);
	glutAddMenuEntry("正面线框模型", 2);
	glutAddMenuEntry("正面点模式", 3);


	glutAddMenuEntry("反面多边形填充模式", 1);
	glutAddMenuEntry("反面线框模型", 2);
	glutAddMenuEntry("反面点模式", 3);
	glutAddMenuEntry("线条框架", 10);

	//增加一个子菜单
	nColorMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("平面明暗模式", 7);
	glutAddMenuEntry("光滑明暗模式", 8);

	//创建主菜单
	nMainMenu = glutCreateMenu(ProcessMenu);
	glutAddSubMenu("多边形模式", nModeMenu);
	glutAddSubMenu("颜色模式", nColorMenu);
	glutAddMenuEntry("改变绕法", 9);

	//将创建菜单与右键关联，即把菜单设置为右键弹出式菜单
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	SetupRC();
	glutMainLoop();
}