#include<GL/glut.h>						//OpenGL实用工具包
#include <Windows.h>
#include <iostream>
using namespace std;
int num = 0;
void init(void) {
	//背景设定为白色
	glClearColor(1.0, 1.0, 1.0, 0.0);

	//正投影
	//glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-200.0, 200.0, -150.0, 150.0);
}
void DrawLineFunc(int num)    //画线
{
	if (num == 0)return; int r = 80;
	float radio = 360.0f / num;
	for (int i = 1; i <= num; i++)
	{
		float spe = i * radio;
		glBegin(GL_LINE_STRIP);
		glVertex2i(0, 0);
		glVertex2i(cos(i* radio*3.14 / 180)*r, sin(i*radio*3.14 / 180)*r);
		//glVertex2i(-92 - i * 20, -75 + i * 10);
		glEnd();
	}
	return;
}
void myDisplay(void)

{
	//显示窗口
	glClear(GL_COLOR_BUFFER_BIT);

	//设置颜色
	glColor3f(1.0, 0.7, 0.4);

	//设置线的粗细
	glLineWidth(2.0f);

#pragma region 折线
	//画折线
	DrawLineFunc(num);

#pragma endregion

#pragma region 同心圆
	//画同心圆
	float pi = 3.1415926536;
	int i = 0;
	int n = 800;
	glBegin(GL_POINTS);//圆1
	for (i = 0; i < n; i++)
	{
		glVertex2f(20 * cos(2 * pi * i / n), 20 * sin(2 * pi * i / n));
	}
	glEnd();

#pragma endregion

	//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	glFlush();

}


//带命令行参数的main函数
int main(int argc, char *argv[])

{
	cin >> num;
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowPosition(100, 100);

	glutInitWindowSize(400, 400);

	glutCreateWindow("OpenGL画一个棒棒糖程序");

	init();

	glutDisplayFunc(&myDisplay);

	glutMainLoop();

	return 0;

}