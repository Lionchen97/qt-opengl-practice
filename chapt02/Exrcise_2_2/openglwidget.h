#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include<QtOpenGLWidgets/QOpenGLWidget>
#include<QtOpenGL/QOpenGLFunctions_4_5_Core>
#include<QDebug>
#include<QOpenGLShaderProgram>
#include<QTimer>
#include<QTime>
class OpenGlWidget : public QOpenGLWidget,QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    enum Shape{None,Rect,Circle,Triangle};
    explicit OpenGlWidget(QWidget *parent = nullptr);
    ~OpenGlWidget();

    // 绘制接口
    void drawShape(Shape shape);
    // 管线渲染接口
    void setWireFrame(bool wireframe);
protected:
    virtual void initializeGL();  //
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

signals:
public slots:

private:
    Shape m_shape;
    QOpenGLShaderProgram shaderProgram;

};

#endif // OPENGLWIDGET_H
