#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include<QtOpenGLWidgets/QOpenGLWidget>
#include<QtOpenGL/QOpenGLFunctions_4_5_Core>
#include<QDebug>
class OpenGlWidget : public QOpenGLWidget,QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGlWidget(QWidget *parent = nullptr);

protected:
    virtual void initializeGL();  //
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

signals:
};

#endif // OPENGLWIDGET_H
