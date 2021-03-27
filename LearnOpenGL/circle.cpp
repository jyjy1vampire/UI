#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//窗口长宽
int width = 1500, height = 1000;
//鼠标点击位置
int hit_pos_x = width / 2, hit_pos_y = height / 2;
//鼠标拖动位置
int move_pos_x, move_pos_y;
//鼠标操作种类
int button_kind = -1;
//鼠标动作处理

//int subnum = 10;
int select_point = -1;

//存放选中物体的缓冲的尺寸
#define SIZE 500

//选中区域的尺寸
#define N 50
vector<string> names = { "朝代","地点","人物","年号","书画","服饰","榜单","8","9","10","11","12","13" ,"14","15","16","17","18","19" };
bool set = false;
int SelectCount = 0;//名称栈内容
void* bitmap_fonts[7] = {
		GLUT_BITMAP_9_BY_15,
		GLUT_BITMAP_8_BY_13,
		GLUT_BITMAP_TIMES_ROMAN_10,
		GLUT_BITMAP_TIMES_ROMAN_24,
		GLUT_BITMAP_HELVETICA_10,
		GLUT_BITMAP_HELVETICA_12,
		GLUT_BITMAP_HELVETICA_18
};
void print_bitmap_string(void* font, const char* s)
{
	if (s && strlen(s)) {
		while (*s) {
			glutBitmapCharacter(font, *s);
			s++;
		}
	}
}
int TextOut(float x, float y, const char* cstr)
{
	glRasterPos2f(x, y);
	print_bitmap_string(bitmap_fonts[6], cstr);
	return 1;
}

void DrawLineFunc(float num, int x, int y)    //画线
{
	if (num == 0)return; int r = 80;
	float radio = 360.0f / num;
	for (int i = 1; i <= num; i++)
	{
		float spe = i * radio;
		glBegin(GL_LINE_STRIP);
		glVertex2i(x, y);
		glVertex2i(x + cos(i* radio*3.14 / 180)*r, y + sin(i*radio*3.14 / 180)*r);
		//glVertex2i(-92 - i * 20, -75 + i * 10);
		glEnd();
	}
	return;
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);			 //为了选择一个更小的绘图区域，在窗口中定义一个像素矩形，将图像映射到这个矩形中
	glMatrixMode(GL_PROJECTION);			  		 //指定哪一个矩阵是当前矩阵（GL_PROJECTION,对投影矩阵应用随后的矩阵操作）
	glLoadIdentity();							  	 //将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作  
	gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);	 //将当前的可视空间设置为正投影空间,这个函数描述了一个平行修剪空间,意味着离观察者较远的对象看上去不会变小  
}
void DrawLineCircle(int src_x, int src_y, int des_x, int des_y)
{
	int count;
	int sections = 200;
	int x = src_x;
	int y = src_y;
	/*x = x==des_x?des_x:src_x+(des_x-src_x)*0.1;
	y = y==des_y?des_y:src_y+(des_y-src_y)*0.1;*/
	GLfloat TWOPI = 2.0f * 3.14159f;
	glBegin(GL_TRIANGLE_FAN);    //GL_LINE_STRIP空心
	glVertex2f(x, y);
	for (count = 0; count <= sections; count++)
	{
		glVertex2f(x + 20 * cos(count*TWOPI / sections), y + 20 * sin(count*TWOPI / sections));
	}
	glEnd();
}

void draw(GLenum mode)
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	const static GLfloat color_selected[] = { 1.0f,1.0f,0.0f };
	const static GLfloat color_unselected[] = { 0.0f,0.0f,1.0f };
	glPointSize(20);
	for (int i = 0; i < 7; i++)
	{
		if (mode == GL_SELECT)
		{
			glLoadName(i);
			SelectCount = i;
		}
		//DrawLineFunc(7, 200+i * 200, 800);
		glColor3fv((select_point == i) ? color_selected : color_unselected);
		if (select_point == i)
		{
			set = true;
			DrawLineCircle(100 + i * 200, 800, width / 2, height / 2);
			glColor3f(1.0, 1.0, 1.0);
		}
		else
		{
			//glLoadIdentity();
			DrawLineCircle(100 + i * 200, 800, 100 + i * 200, 800);
		}
		TextOut(100 + i * 200, 850, "Hello");
		/*glBegin(GL_POINTS);
		glVertex2f(i * 100, 700);
		glEnd();*/
	}
	if (set)
	{
		glColor3f(1.0, 1.0, 1.0);
		DrawLineFunc(9, width / 2, height / 2);
		if (mode == GL_SELECT)
		{
			glLoadName(++SelectCount);
		}
		DrawLineCircle(width / 2, height / 2, width / 2, height / 2);
		for (int i = 0; i < 9; i++)                                        //画子集线条和圆
		{
			glPushMatrix();
			glTranslatef(cos(i* (360 / 9)*3.14 / 180) * 80, sin(i*(360 / 9)*3.14 / 180) * 80, 0.0);
			//glRotatef(1, 0, 0, 1);
			glLoadName(++SelectCount);
			DrawLineCircle(width / 2, height / 2, width / 2, height / 2);
			glPopMatrix();
		}

	}

	//双缓存交换缓存以显示图像
	glutSwapBuffers();
	//每次更新显示
	glutPostRedisplay();
}

void processHits(GLint hits, GLuint buffer[])
{
	unsigned int i;
	GLuint name;

	//ptr = (GLuint*)buffer;
	for (i = 0; i < hits; i++)
	{
		name = buffer[3 + i * 4];
		select_point = name;//每个选中物体有占用名字栈中4个单位，第4个是物体名字的值
		cout << names[name] << endl;
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw(GL_RENDER);
	glFlush();
}


void mouse_hit(int button, int state, int x, int y)
{
	//鼠标操作种类赋值
	button_kind = button;
	//鼠标操作基本结构
	GLuint selectBuffer[SIZE];//存放物体名称的栈
	GLint hits;//存放被选中对象个数
	GLint viewport[4];//存放可视区参数
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)//当鼠标左键按下时
	{
		cout << "down" << endl;
		glGetIntegerv(GL_VIEWPORT, viewport);//获取当前视口坐标参数
		glSelectBuffer(SIZE, selectBuffer);//选择名称栈存放被选中的名称
		glRenderMode(GL_SELECT);//设置当前为 选择模式

		//初始化名称栈
		glInitNames();
		glPushName(0);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		gluPickMatrix(x, viewport[3] - y, N, N, viewport);//创建用于选择的投影矩阵栈
		gluOrtho2D(0, width, height, 0);//设置投影方式
		draw(GL_SELECT);//绘制场景
		glPopMatrix();
		glFlush();
		hits = glRenderMode(GL_RENDER);
		glMatrixMode(GL_MODELVIEW);
		if (hits > 0) processHits(hits, selectBuffer);

		glutPostRedisplay();
	}
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) //当鼠标左键抬起时
	{
		select_point = -1;
		glRenderMode(GL_RENDER);
		draw(GL_RENDER);
		glutPostRedisplay();
	}
	if (GLUT_RIGHT_BUTTON&&state == GLUT_DOWN) //右键操作，也可为数字1,右键按下时
	{
		hit_pos_x = x;
		hit_pos_y = y;
	}
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
	glutInitWindowSize(width, height);
	//设置窗口名称
	glutCreateWindow("OpenGL");
	//显示函数，display事件需要自行编写
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//鼠标点击函数，mouse_hit事件需要自行编写
	glutMouseFunc(mouse_hit);
	//重复循环GLUT事件
	glutMainLoop();
}