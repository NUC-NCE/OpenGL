/*
 * 顶点数组对象  Vertex Array Object, VAO
 * 顶点缓冲对象  Vertex Buffer Object, VBO
 * 索引缓冲对象  Element Buffer Object, EBO
 *              Index Buffer Object, IBO
 */

/*
 * 在OpenGL中，任何事物都在3D空间中，而屏幕和窗口都是2D像素数组，
 * 这导致OpenGL的大部分工作都是关于把3D坐标转化为适应屏幕的2D像素。
 * 3D坐标转化为2D坐标的处理过程是由OpenGL的图形渲染管线(Graphic Pipeline)管理的。
 * 图形渲染管线可以被划分为两个主要部分：第一部分把你的3D坐标转化为2D坐标，
 * 第二部分把2D坐标转变为实际的有颜色的像素。
 */

/*
 * 2D坐标和像素也是不同的，2D坐标精确表示一个点在2D空间中的位置，
 * 而2D像素是这个点的近似值，2D像素受到你屏幕/窗口分辨率的限制。
 */

/*
 * 首先我们以数组的形式传递3个3D坐标作为图形渲染管的输入，
 * 用来表示一个三角形，这个数组叫做顶点数据(Vertex Data)；
 * 顶点数据是一系列顶点的集合。一个顶点是一个3D坐标数据的集合。
 * 定点数据是用顶点属性(Vertex Attribute)表示的，它可以包含任何我们想用的数据
 */

/*
 * 为了让OpenGL知道我们的坐标和颜色值构成的内容是什么，OpenGL需要你去指定这些数据所表示的渲染类型。
 * 做出的这些提示叫做图元(Primitive)，任何一个绘制指令的调用都将把图元传递给OpenGL
 * 比如GL_POINTS、GL_TRIANGLES、GL_LINE_STRIP.
 */

/*
 * 图形渲染管线的第一个部分是顶点着色器(Vertex Shader)，它把一个单独的顶点作为输入。
 * 顶点着色器的主要目的是把3D坐标转化为另一种3D坐标，同时允许我们的对顶点属性进行一些基本的处理。
 */

/*
 * 图元装配(Primitive Assembly)阶段将顶点着色器输出的所有顶点作为输入，
 * 如果是GL_POINTS，那么就是一个顶点，下面程序中例子是一个三角形。
 * 图元装配阶段的输出会传递给几何着色器(Geometry Shader)。
 * 几何着色器把图元形式的一系列顶点的集合作为输入，
 * 它可以通过产生新顶点构造出新的（或是其它的）图元来生成其他形状。
 */

/*
 * 几何着色器的输出会被传入光栅化阶段(Rasterization Stage)，
 * 这里它会把图元映射为最终屏幕上相应的像素，
 * 生成供片段着色器(Fragment Shader)使用的片段(Fragment)。
 * 在片段着色器运行之前会执行裁切(Clipping)。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。
 */

//OpenGL中的一个片段是OpenGL渲染一个像素所需的所有数据。

/*
 * 片段着色器的主要目的是计算一个像素的最终颜色，这也是所有OpenGL高级效果产生的地方。
 * 片段着色器包含3D场景的数据（比如光照、阴影、光的颜色等等），这些数据可以被用来计算最终像素的颜色。
 * 在所有对应颜色值确定以后，最终的对象将会被传到最后一个阶段，我们叫做Alpha测试和混合(Blending)阶段。
 * 这个阶段检测片段的对应的深度（和模板(Stencil)）值（后面会讲），用它们来判断这个像素是其它物体的前面还是后面，决定是否应该丢弃。
 * 这个阶段也会检查alpha值（alpha值定义了一个物体的透明度）并对物体进行混合(Blend)。
 * 即使在片段着色器中计算出来了一个像素输出的颜色，在渲染多个三角形的时候最后的像素颜色也可能完全不同。
 */

/*
 * 在现代OpenGL中，我们必须定义至少一个顶点着色器和一个片段着色器，
 */

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
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}