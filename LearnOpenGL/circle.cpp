#include <GL/glut.h>
#include <iostream>
using namespace std;
//窗口长宽
int width = 400, height = 400;
//鼠标点击位置
int hit_pos_x, hit_pos_y;
//鼠标拖动位置
int move_pos_x, move_pos_y;
//鼠标操作种类
int button_kind = -1;
//鼠标动作处理
bool move1 = false;

int subnum = 10;

void DrawLineFunc(float num)    //画线
{
	if (num == 0)return; int r = 80;
	float radio = 360.0f / num;
	for (int i = 1; i <= num; i++)
	{
		float spe = i * radio;
		glBegin(GL_LINE_STRIP);
		glVertex2i(hit_pos_x, hit_pos_y);
		glVertex2i(hit_pos_x+ cos(i* radio*3.14 / 180)*r, hit_pos_y+sin(i*radio*3.14 / 180)*r);
		//glVertex2i(-92 - i * 20, -75 + i * 10);
		glEnd();
	}
	float pi = 3.1415926536;
	int i = 0;
	int n = 50;
	glBegin(GL_POINTS);//圆1
	for (i = 0; i < n; i++)
	{
		glVertex2f(hit_pos_x+ 10 * cos(2 * pi * i / n), hit_pos_y+ 10 * sin(2 * pi * i / n));
	}
	glEnd();
	return;
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);			 //为了选择一个更小的绘图区域，在窗口中定义一个像素矩形，将图像映射到这个矩形中
	glMatrixMode(GL_PROJECTION);			  		 //指定哪一个矩阵是当前矩阵（GL_PROJECTION,对投影矩阵应用随后的矩阵操作）
	glLoadIdentity();							  	 //将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作  
	gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0 );	 //将当前的可视空间设置为正投影空间,这个函数描述了一个平行修剪空间,意味着离观察者较远的对象看上去不会变小  
}

void display()
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//重新设置OpenGL窗口：原点位置为左上角，x轴从左到右，y轴从上到下，坐标值与像素坐标值相同
	/*glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);*/
	if (move1)
	{
		DrawLineFunc(7);
		//move = false;
	}
	if (button_kind == 0)	//左键点击
	{
		//画一个蓝色的点
		glPointSize(20);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(hit_pos_x, hit_pos_y);
		glEnd();
	}
	else if (button_kind == 2)	//右键点击
	{
		//画一个绿色的点
		glPointSize(20);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(hit_pos_x, hit_pos_y);
		glEnd();
	}
	else if (button_kind == 3)	//鼠标拖动
	{
		//沿拖动轨迹画一条红色的线
		glLineWidth(5);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(hit_pos_x, hit_pos_y);
		glVertex2f(move_pos_x, move_pos_y);
		glEnd();
	}

	//双缓存交换缓存以显示图像
	glutSwapBuffers();
	//每次更新显示
	glutPostRedisplay();
}

void mouse_hit(int button, int state, int x, int y)       
{
	//鼠标操作种类赋值
	button_kind = button;
	//鼠标操作基本结构
	switch (button)
	{
	case GLUT_LEFT_BUTTON:	//左键操作，也可为数字0
		if (state == GLUT_DOWN)	//左键按下时
		{
			//记录按键位置                                        //按键位置
			hit_pos_x = x;	
			hit_pos_y = y;
			move1 = true;
		}
		break;
	case GLUT_RIGHT_BUTTON:	//右键操作，也可为数字1
		if (state == GLUT_DOWN)	//右键按下时
		{
			//记录按键位置
			hit_pos_x = x;
			hit_pos_y = y;
		}
		break;
	default:
		break;
	}
}

void mouse_move(int x, int y)
{
	//鼠标移动时操作种类设为3(0 1 2分别为左键、中键、右键)
	button_kind = 3;
	//记录拖动位置
	move_pos_x = x;
	move_pos_y = y;
}

void main(int argc, char** argv)
{
	//初始化GL
	glutInit(&argc, argv);
	//设置显示参数(双缓存，RGB格式)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//设置窗口尺寸：width*height
	glutInitWindowSize(width, height);
	//设置窗口位置：在屏幕左上角像素值(100,100)处
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	//设置窗口名称
	glutCreateWindow("OpenGL");
	//显示函数，display事件需要自行编写
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//鼠标点击函数，mouse_hit事件需要自行编写
	glutMouseFunc(mouse_hit);
	//鼠标拖动函数，mouse_move事件需要自行编写
	glutMotionFunc(mouse_move);

	//重复循环GLUT事件
	glutMainLoop();
}
