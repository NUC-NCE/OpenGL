#include <bits/stdc++.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;
/* 回调函数，当改变窗口大小的时候，视口也应该被调整
 * 对窗口注册一个回调函数(Callback Function)
 * 这个帧缓冲大小函数需要一个GLFWwindow作为它的第一个参数，以及两个整数表示窗口的新维度。
 * 每当窗口改变大小，GLFW会调用这个函数并填充相应的参数供你处理。
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);//重新设置窗口维度
    //glViewport函数来设置窗口的维度(Dimension),前两个参数控制窗口左下角的位置。
    // 第三个和第四个参数控制渲染窗口的宽度和高度（像素）
}
/*
 * 检查用户是否按下了返回键(Esc)
 * 如果没有按下，glfwGetKey将会返回GLFW_RELEASE。
 * 如果用户的确按下了返回键，我们将通过glfwSetwindowShouldClose使用把WindowShouldClose属性设置为 true的方法关闭GLFW
 */
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main()
{
    glfwInit();//初始化GLFW
    /*
     * glfwWindowHint配置GLFW
     * glfwWindowHint的第一个参数代表选项的名称，第二个参数接受一个整形，用来设置这个选项的值
     * 该函数所有对应的值都可以在 GLFW
     * 基于opengl 3.3以上版本
     *
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//主版本号设置为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);//次版本号设置为3
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);//GLFW使用的模式为核心模式 Core-profile
                                                                 //这意味着我们只能使用OpenGL功能的一个子集

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE); //MAC OS中需要加入这一行初始化代码前面的配置才能有效
    /*
     * 创建窗口以及上下文
     */
    GLFWwindow* window = glfwCreateWindow(800,600,/*glfwCreateWindow创建窗口时需要的前两个参数是窗口的宽和高*/
                                           "LearnOpenGL",/*第三个参数为标题*/NULL,NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();//退出程序
        return -1;
    }

    glfwMakeContextCurrent(window);//设置当前OpenGL上下文

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册函数，该函数还可以注册其他相关硬件的回调函数

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))/*如果你使用Extension loader library来加载OpenGL，那么这是初始化它的时候，
                                                             Loader需要一个当前的上下文来加载它，比如glad库*/
    {
        cout<< "Failed to initialize GLAD" <<endl;
        return -1;
    }
    while(!glfwWindowShouldClose(window))//glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了。
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);//glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
        glfwPollEvents();//glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。

    }
    glfwTerminate();//退出程序
    return 0;
}