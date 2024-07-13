#include "widget.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QVector>
#include <QMouseEvent>


//Widget::Widget(QWidget *parent)
//    : QOpenGLWidget(parent)
//{
//    setWindowTitle("alala");
//    setGeometry(400, 200, 800, 600);
//    makeCurrent();
//    delete geometries;
//    doneCurrent();
//}

Widget::~Widget()
{
    makeCurrent();
    delete geometries;
    doneCurrent();
}





void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    initShaders();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    geometries = new GeometryEngine;
//    timer.start(120, this);
}

void Widget::initShaders()
{
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":vshader.glsl"))
        close();


    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":fshader.glsl"))
        close();

    if(!program.link())
        close();

    if(!program.bind())
        close();
}

void Widget::initColors() {
    glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(), 0);

    int vertexLocation = program.attributeLocation("vertex");
    int colorLocation = program.uniformLocation("color");

    program.enableAttributeArray(vertexLocation);
    program.setUniformValue(colorLocation, *color);
    program.disableAttributeArray(vertexLocation);
}

void Widget::initColorsVer() {
//    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(), 0);

//    color_ver->setRgb(0,0,0);

    int vertexLocation = program.attributeLocation("vertex");
    int colorLocation = program.uniformLocation("color");

    program.enableAttributeArray(vertexLocation);
    program.setUniformValue(colorLocation, *color_ver);
    program.disableAttributeArray(vertexLocation);
}

void Widget::updating()
{
    update();
}

void Widget::resizeGL(int w, int h)
{
    float aspect = qreal(w) / qreal(h ? h : 1);
    projection.setToIdentity();

    projection.perspective(45.0, aspect, 0.5, 7.8);

}

void Widget::paintGL()
{
    glLineWidth(1);

    initColors();

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    program.setUniformValue("mvp_matrix", projection * matrix);

    geometries->drawprocess(&program);


//    program.setUniformValue("texture", 0);
    initColorsVer();
//    geometries->drawdot(&program);
    update();
}


