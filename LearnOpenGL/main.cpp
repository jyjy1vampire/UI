#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor=aColor;\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"	FragColor = vec4(ourColor,1.0);\n"
"}\0";
const char *fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
const char *fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

//处理输入
void processInput(GLFWwindow* window) {
	//glfwGetKey(参数1，参数2)
	//参数1：响应窗口对象
	//参数2：按下的键
	//返回值：int
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//按下ESC键
	{
		//glfwSetWindowShouldClose(参数1，参数2)
		//参数1：响应窗口对象
		//参数2：bool值，用来设置是否关闭窗口
		glfwSetWindowShouldClose(window, true);//关闭窗口
	}
}
int main() {
	//初始化GLFW
	glfwInit();

	//配置GLFW====================
	//glfwWindowHint(参数1，参数2)
	//参数1：选项的名称。可以从很多以GLFW_开头的枚举值中选择
	//参数2：接受一个整型，用来设置这个选项的值
	//设置版本号为3.3版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主板本号为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置副版本号为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//模式：核心模式(Core-profile)

	//如果你使用的是Mac OS X系统，你还需要解除下面这行代码的注释
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//创建窗口对象=================
	//glfwCreateWindow(参数1，参数2，参数3，参数4，参数5)
	//参数1：窗口宽
	//参数2：窗口高
	//参数3：窗口标题（名字）
	//参数4，参数5暂时忽略
	//返回值类型：GLFWwindow*
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//创建窗口对象失败
	if (window == NULL)
	{
		//打印错误信息
		std::cout << "Failed to create GLFW window" << std::endl;//需要引用iostream头文件
		//终止GLFW
		glfwTerminate();
		return -1;
	}
	//将窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);

	//GLAD========================
    //加载系统相关的OpenGL函数指针地址的函数，它根据我们编译的系统定义了正确的函数。
	//gladLoadGLLoader(参数1)
	//参数1：GLADloadproc类型的函数指针地址。这里我们通过GLFW中的glfwGetProcAddress属性获取了函数指针的的地址
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//加载函数地址失败
		//打印错误信息
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//设置视口（渲染窗口）的尺寸大小============
	//glViewport(参数1，参数2，参数3，参数4)
	//参数1，参数2：渲染窗口左下角的位置
	//参数3，参数4：渲染窗口的宽度和高度（单位：像素）
	glViewport(0, 0, 800, 600);
	//渲染循环================================
	//glfwWindowShouldClose(参数1)
	//此函数每次循环的开始前检查一次GLFW是否被要求退出，
	//如果是的话该函数返回true，渲染循环结束，之后关闭应用程序。
	//参数1：检测对象

	

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	//unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	//unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	//unsigned int shaderProgramOrange = glCreateProgram();
	//unsigned int shaderProgramYellow = glCreateProgram();
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
	//glCompileShader(fragmentShaderOrange);
	//glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
	//glCompileShader(fragmentShaderYellow);

	//glAttachShader(shaderProgramOrange, vertexShader);
	//glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	//glLinkProgram(shaderProgramOrange);
	//glAttachShader(shaderProgramYellow, vertexShader);
	//glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	//glLinkProgram(shaderProgramYellow);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	//float vertices[] = {    //VAO绘制两个三角形
	//-0.5f, 0.0f, 0.0f,
	// 0.0f, 0.5f, 0.0f,
	//0.5f, 0.0f, 0.0f,
	//0.5f, 0.0f, 0.0f,
	//0.0f,-0.5f,0.0f,
	//-0.5f,0.0f,0.0f,
	//};
	
	float vertices[] = {
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};

	unsigned int VBO;    //生成一个VBO对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//把用户定义的数据复制到当前绑定缓冲
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glUseProgram(shaderProgram);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);   //告诉OpenGL该如何解析顶点数据
	//glEnableVertexAttribArray(0);  //顶点属性0现在会链接到它的顶点数据
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//float vertices[] = {            //绘制矩形
	//0.5f, 0.5f, 0.0f,   // 右上角
	//0.5f, -0.5f, 0.0f,  // 右下角
	//-0.5f, -0.5f, 0.0f, // 左下角
	//-0.5f, 0.5f, 0.0f   // 左上角
	//};
	//unsigned int indices[] = { // 注意索引从0开始! 
	//	0, 2, 3, // 第一个三角形
	//	0, 1, 2,  // 第二个三角形
	//};

	

	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);*/

	//float firstTriangle[] = {
	//	-0.9f, -0.5f, 0.0f,  // left 
	//	-0.0f, -0.5f, 0.0f,  // right
	//	-0.45f, 0.5f, 0.0f,  // top 
	//};
	//float secondTriangle[] = {
	//	0.0f, -0.5f, 0.0f,  // left
	//	0.9f, -0.5f, 0.0f,  // right
	//	0.45f, 0.5f, 0.0f   // top 
	//};

	//unsigned int VBOs[2], VAOs[2];
	//glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
	//glGenBuffers(2, VBOs);
	//// first triangle setup
	//// --------------------
	//glBindVertexArray(VAOs[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	//glEnableVertexAttribArray(0);
	//// glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
	//// second triangle setup
	//// ---------------------
	//glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	//glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），
		//它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
		//检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，
		//并调用对应的回调函数（可以通过回调方法手动设置）。

		//设置清屏颜色（参数1：R，参数2：G，参数3：B，参数4：A）
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//设置要清除的缓冲位 (参数1：缓冲位（Buffer Bit）)
		//缓冲位（如：GL_COLOR_BUFFER_BIT（颜色缓存），GL_DEPTH_BUFFER_BIT（深度缓存）和GL_STENCIL_BUFFER_BIT（模板缓存））
		//这里我们只关心颜色值，所以只清空颜色缓冲即可
		glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);  //绘制三角形

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //绘制矩形
		//glBindVertexArray(0);

		//glUseProgram(shaderProgramOrange);
		//glBindVertexArray(VAOs[0]);       //绘制两个三角形用不同VAO
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		// then we draw the second triangle using the data from the second VAO
		//glUseProgram(shaderProgramYellow);
		//glBindVertexArray(VAOs[1]);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		/*float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
		glfwSwapBuffers(window);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glfwPollEvents();
	}
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);*/
	/*glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);*/

	//glDeleteProgram(shaderProgram);
	//glDeleteShader(shaderProgramOrange);
	//glDeleteShader(shaderProgramYellow);
	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}
