#include<GL/glut.h>						//OpenGL实用工具包
#include <Windows.h>

/*所遇问题：
1、系统API函数Sleep()不听话，睡眠时快时慢（可能跟我计算机当前运行程序有关吧）
解决方案：重写Sleep()函数，实质为空循环。仅用于Debug下，Release会将其优化
2、动态画直线，朝某些方向画线时出现块状
解决方案：认认真真把直线方程推导一遍，斜率存在或不存在分别讨论，将数学思想转换为编程思想
*/

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);		//指定清除颜色（黑色），即背景颜色
	glShadeModel(GL_FLAT);				//设置着色模式，采用恒定着色
}

void Sleep(int ms)			//覆盖系统API函数
{
	for (int i = 0; i < ms*ms*ms * 10; i++)		//数值大小根据实际情况调试
	{
		;
	}
}

//特别注意：1、斜率不存在。2、直线斜率一定要保持一致，将直线两点式方程转化为斜率式方程y=kx+c
//k=(y2-y1)/(x2-x1);	
//c=(x2*y1-x1*y2)/(x2-x1);
void DrawDynamicLine(GLfloat x1, GLfloat y1,		//起点坐标
	GLfloat x2, GLfloat y2,							//终点坐标
	GLfloat red, GLfloat green, GLfloat blue,			//线段颜色
	int speed,										//绘制速度，0-100，值越大速度越大
	int type										//虚线类型，16位2进制表示，1为实点，0为虚点，0xFFFF为实线
)
{
	glEnable(GL_LINE_STIPPLE);						//点画线模式
	glColor3f(red, green, blue);						//设置线段绘制颜色
	glLineStipple(1, type);							//dashed（虚线）,type为16位2进制数，0表示实点，1表示虚点

	if (x1 != x2)										//如果斜率存在
	{
		GLfloat k = (y2 - y1) / (x2 - x1);					//直线斜率 y=kx+c
		GLfloat c = (x2*y1 - x1 * y2) / (x2 - x1);			//直线常数
		//假定以A为原点建立二维坐标系，则下边4个if分别对应于：第一象限，第二象限，第三象限，第四象限
		if (x1 < x2&&y1 <= y2)							//从A(x1,y1)到B(x2,y2)画线，B点在A点的右上方
		{
			for (int i = 0; i <= x2 - x1; i++)				//注意循环条件
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1 + i, k*(x1 + i) + c);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//立刻开始处理保存在缓冲区中的OpenGL函数调用
			}
		}
		else if (x1 > x2&&y1 <= y2)						//从A(x1,y1)到B(x2,y2)画线，B点在A点的左下方
		{
			for (int i = 0; i >= x2 - x1; i--)				//特别注意循环条件，既要避免死循环又要避免少循环
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1 + i, k*(x1 + i) + c);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//立刻开始处理保存在缓冲区中的OpenGL函数调用
			}
		}
		else if (x1 > x2&&y1 >= y2)						//从A(x1,y1)到B(x2,y2)画线，B点在A点的左上方
		{
			for (int i = 0; i >= x2 - x1; i--)				//特别注意循环条件，既要避免死循环又要避免少循环
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1 + i, k*(x1 + i) + c);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//立刻开始处理保存在缓冲区中的OpenGL函数调用
			}
		}
		else if (x1 < x2&&y1 >= y2)						//从A(x1,y1)到B(x2,y2)画线，B点在A点的左上方
		{
			for (int i = 0; i <= x2 - x1; i++)				//特别注意循环条件，既要避免死循环又要避免少循环
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1 + i, k*(x1 + i) + c);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//立刻开始处理保存在缓冲区中的OpenGL函数调用
			}
		}
	}
	else
	{
		if (y1 < y2)									//沿y轴正方向画线
		{
			for (int i = 0; i <= y2 - y1; i++)				//特别注意循环条件，既要避免死循环又要避免少循环
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1, y1 + i);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//立刻开始处理保存在缓冲区中的OpenGL函数调用
			}
		}
		else										//沿y轴负方向画线
		{
			for (int i = 0; i >= y2 - y1; i--)				//特别注意循环条件，既要避免死循环又要避免少循环
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1, y1 + i);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//立刻开始处理保存在缓冲区中的OpenGL函数调用
			}
		}
	}

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//清除所有的像素
	//正方形ABCD
	DrawDynamicLine(100, 500, 500, 500, 1, 1, 0, 60, 0xFFFF);			//AB
	DrawDynamicLine(500, 500, 500, 100, 1, 0, 1, 70, 0xFFFF);			//BC
	DrawDynamicLine(500, 100, 100, 100, 1, 1, 1, 80, 0xFFFF);			//CD
	DrawDynamicLine(100, 100, 100, 500, 0, 1, 1, 90, 0xFFFF);			//DA


	//沿顺时针方向测试动态画线：第一象限，第四象限，第三象限，第二象限
	DrawDynamicLine(300, 300, 300, 500, 1, 0, 0, 90, 0xFFFF);			//1
	DrawDynamicLine(300, 300, 400, 500, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 500, 500, 1, 0, 0, 90, 0xFFFF);
	DrawDynamicLine(300, 300, 500, 400, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 500, 300, 1, 0, 0, 90, 0xFFFF);

	DrawDynamicLine(300, 300, 500, 300, 1, 0, 0, 90, 0xFFFF);			//2
	DrawDynamicLine(300, 300, 500, 200, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 500, 100, 1, 0, 0, 90, 0xFFFF);
	DrawDynamicLine(300, 300, 400, 200, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 400, 100, 1, 0, 0, 90, 0x00FF);

	DrawDynamicLine(300, 300, 300, 100, 1, 0, 0, 90, 0xFFFF);			//3
	DrawDynamicLine(300, 300, 200, 100, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 100, 100, 1, 0, 0, 90, 0xFFFF);
	DrawDynamicLine(300, 300, 100, 200, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 100, 300, 1, 0, 0, 90, 0xFFFF);

	DrawDynamicLine(300, 300, 100, 300, 1, 0, 0, 90, 0xFFFF);			//4
	DrawDynamicLine(300, 300, 100, 400, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 100, 500, 1, 0, 0, 90, 0xFFFF);
	DrawDynamicLine(300, 300, 200, 500, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 300, 500, 1, 0, 0, 90, 0xFFFF);

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);			 //为了选择一个更小的绘图区域，在窗口中定义一个像素矩形，将图像映射到这个矩形中
	glMatrixMode(GL_PROJECTION);			  		 //指定哪一个矩阵是当前矩阵（GL_PROJECTION,对投影矩阵应用随后的矩阵操作）
	glLoadIdentity();							  	 //将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作  
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);	 //将当前的可视空间设置为正投影空间,这个函数描述了一个平行修剪空间,意味着离观察者较远的对象看上去不会变小  
}

int main(int argc, char** argv)						//注意参数
{
	glutInit(&argc, argv);							//初始化GLUT并处理命令行参数
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);		//指定模式：单缓存OR双缓存；RGBA模式OR颜色索引模式
	glutInitWindowSize(600, 600);					//指定窗口大小（像素）
	glutInitWindowPosition(300, 50);					//指定窗口左上角在屏幕上的位置
	glutCreateWindow(argv[0]);						//使用OpenGL场景创建一个窗口，参数为窗口名称
	init();											//调用初始化函数
	glutDisplayFunc(display);						//注册用于显示图形的回调函数，每当GLUT认为需要重绘窗口时，都会执行该函数，故应将重绘场景所需调用的函数都放到显示回调函数中。
	glutReshapeFunc(reshape);						//重绘回调函数
	glutMainLoop();									//进入主循环并处理事件，此时创建的所有窗口都会显示出来，被渲染到这些窗口中的内容也将显示出来，程序开始处理事件，注册的显示回调函数被触发
	return 0;										//ANSI C要求函数main()返回一个int值
}