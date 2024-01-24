#include "openglwidget.h"
/*
你好，三角形
*/
//三角形顶点数据
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};


// 顶点着色源码
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

// 片段着色源码
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";


// 创建VBO和VAO对象
unsigned int VAO,VBO;

// 创建着色器程序
unsigned int shaderProgram;

OpenGlWidget::OpenGlWidget(QWidget *parent): QOpenGLWidget(parent)
{

}

void OpenGlWidget::initializeGL()
{
    initializeOpenGLFunctions(); // GLAD

    // 为VAO，VBO分配索引
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    // 绑定VBO和VAO对象
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // 第一次绑定VAO是在初始化阶段,用于设置顶点属性指针,建立VAO和VBO之间的关联。
    glBindVertexArray(VAO);

    // 为当前绑定到target的缓冲区对象创建一个新的数据存储
    // 如果data不是NULL，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    // 告诉GPU如何解析缓冲里的属性值 从0开始，每个点有3个属性值，不需要标准化，步长为一个点的大小，
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

    // 开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);



    // 创建顶点着色器和片段着色器
    unsigned int vertexShader,fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 为着色器分配索引，并绑定源码
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);

    // 编译顶点着色器
    glCompileShader(vertexShader);
        // 抛出顶点着色器编译异常
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }
    // 编译片段着色器
    glCompileShader(fragmentShader);
         // 抛出片段着色器编译异常
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }

    // 创建着色器程序并链接着色器
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    // 删除顶点着色器和片段着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 指定填充模式，两面都为线条，默认是GL_FILE
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


    // 清空，VAO，VBO小助理下班
    // 将GL_ARRAY_BUFFER和顶点数组对象绑定为默认的 0,相当于解绑当前所绑定的 VBO 和 VAO。
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

}

void OpenGlWidget::resizeGL(int , int )
{

}

void OpenGlWidget::paintGL()
{
    // 绘制背景
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用着色器程序
    glUseProgram(shaderProgram);

    //第二次绑定是在渲染循环中,用于激活渲染状态。
    glBindVertexArray(VAO);

    // 绘制三角形
    // 如果不设置顶点和片段着色器，会生成白色的三角形，从0开始找3个点
    glDrawArrays(GL_TRIANGLES,0,3);

}
