#include "openglwidget.h"

/*
GLSL更多顶点属性
*/

// 矩形2（有EBO）
float vertices[] = {
    0.5f, 0.5f, 0.0f,1.0f, 0.0f, 0.0f,    // 右上角
    0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,   // 右下角
    -0.5f, -0.5f, 0.0f,0.0f, 0.0f, 1.0f,  // 左下角
    -0.5f, 0.5f, 0.0f,0.5f, 0.5f, 0.5f,    // 左上角
};

unsigned int indices[] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

// 创建VBO和VAO,EBO对象数组
unsigned int VAO,VBO,EBO;



OpenGlWidget::OpenGlWidget(QWidget *parent): QOpenGLWidget(parent)
{

}

OpenGlWidget::~OpenGlWidget()
{
    //if(!isValid())return; // 健壮一点
    // 释放资源
    makeCurrent(); // 调用当前状态
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);
    // 无需删除shaderprogram
    doneCurrent();
}

void OpenGlWidget::drawShape(OpenGlWidget::Shape shape)
{
    m_shape = shape;

    // 如果需要从OpenGlWidget::patinGL()以外的位置触发重新绘制行为，需要调用widget::update函数来安排更新
    // 触发paintGL()
    update();
}

void OpenGlWidget::setWireFrame(bool wireframe)
{
    makeCurrent();
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    // 如果需要从OpenGlWidget::patinGL()以外的位置触发重新绘制行为，需要调用widget::update函数来安排更新
    update();
    doneCurrent();
}

void OpenGlWidget::initializeGL()
{
    initializeOpenGLFunctions(); // GLAD

    // 为VAO，VBO分配索引
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    // 绑定VBO和VAO对象
    // 第一次绑定VAO是在初始化阶段,用于设置顶点属性指针,建立VAO和VBO之间的关联。
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);


    // 为当前绑定到target的缓冲区对象创建一个新的数据存储
    // 如果data不是NULL，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    // 告诉GPU如何解析缓冲里的属性值 从0开始，每个点有3+3个属性值，不需要标准化，步长为1个点的大小，偏移量：0:从0开始，1：从3开始
    // 0:aPos
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0); // 在顶点着色器声明layout时调用
    glEnableVertexAttribArray(0);
    // 1:aColor
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float))); // 在顶点着色器声明layout时调用
    glEnableVertexAttribArray(1);

    // 创建着色器程序并链接着色器
    bool success;
    shaderProgram.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":shaders/shapes.vert"); // 顶点着色器
    shaderProgram.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":shaders/shapes.frag"); // 片段着色器
    success = shaderProgram.link();
    if(!success)
    {
        qDebug()<<"ERR:"<<shaderProgram.log();
    }

    // 绑定EBO
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


    // 清空，VAO，VBO小助理下班
    // 将GL_ARRAY_BUFFER和顶点数组对象绑定为默认的 0,相当于解绑当前所绑定的 VBO 和 VAO。
    glBindBuffer(GL_ARRAY_BUFFER,0);
    // 注意VAO会存储EBO的解绑调用，但不是VBO，所以确保先解绑VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);


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
    shaderProgram.bind();

    //第二次绑定是在渲染循环中,用于激活渲染状态。
    glBindVertexArray(VAO);

    // 绘制
    switch(m_shape){
        // 第四个参数为0/NULL,表示使用默认的元素数组缓冲区(GL_ELEMENT_ARRAY_BUFFER)作为索引缓冲区,起始偏移量为0。VAO记录了EBO，所以还是用EBO
        // indices,表示使用 indices 作为索引缓冲区的起始地址指针,即自定义的索引缓冲区。所以当我们使用自定义的索引缓冲区时,需要传入indices参数。
        // 如果使用默认的元素数组缓冲区,则可以传入0或NULL。
    case Rect:glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        break;
    default:
        break;
    }
}

