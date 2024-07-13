#include "geometry.h"

#include <QVector2D>
#include <QVector3D>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QVector>

struct VertexData
{
    QVector3D position;
};


GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    arrayBuf.create();
    indexBuf.create();


    filepath = "";
    parsing();
}

GeometryEngine::~GeometryEngine()
{

    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::parsing()
{
    if (filepath == "") {
        return;
    }

    if (flag_draw == 1) {
//        printf("START\n");
        QByteArray ba = filepath.toLocal8Bit();
        char *str = ba.data();

//        char str[] = "/Users/olegsapoval/Desktop/cube.obj";
//        char str[] = "/home/santonet/C8_3DViewer_v1.0-0/src/qt/cube.obj";

//        printf("str: %s\n", str);

        FILE *fp = fopen(str, "r");


        int error = 0;

        figure = Parsing(fp, &error);

        if (fp != NULL && error == 0) {

            binding();
            QVector<GLuint> indices;
            for (int i = 0; i < figure.col_connect; i++) {
                indices.push_back(figure.connect_array[i]);
    //                printf("%d ", (int)figure.connect_array[i]);
            }
//qDebug()<< indices;



            lines = indices.length();

            indexBuf.bind();
            indexBuf.allocate(indices.data(), sizeof(GLuint)*indices.length());
        }

        fclose(fp);


    }





}

void GeometryEngine::binding()
{
    QVector<VertexData> vertices;

    for (int i = 0; i < figure.col; i+=3) {
        VertexData tmp_vert = {QVector3D(figure.coord_array[i], figure.coord_array[i+1], figure.coord_array[i+2])};
//        printf("%f %f %f, ", figure.coord_array[i], figure.coord_array[i+1], figure.coord_array[i+2]);

        vertices.push_back(tmp_vert);
    }

    arrayBuf.bind();
    arrayBuf.allocate(vertices.data(), sizeof(VertexData) * vertices.length());
}




void GeometryEngine::scaling(double value) {
    if (value != 0.0) {
//        printf("scaling...\n");
        figure = Scale(figure, value / tmp_scale);
        tmp_scale = value;
    }
}


void GeometryEngine::rotate(double value, char c) {
    if (value != 0) {

        if (c == 'x') {
            figure = TurnAround(figure, value - tmp_rotate_x, c);
            tmp_rotate_x = value;
        } else if (c == 'y') {
            figure = TurnAround(figure, value - tmp_rotate_y, c);
            tmp_rotate_y = value;
        } else if (c == 'z') {
            figure = TurnAround(figure, value - tmp_rotate_z, c);
            tmp_rotate_z = value;
        }
    }
}


void GeometryEngine::move(double value, char c) {
    if (value != 0) {

        if (c == 'x') {
//            printf("---___---\n");
            figure = Shift(figure, value - tmp_move_x, c);
            tmp_move_x = value;
        } else if (c == 'y') {
            figure = Shift(figure, value - tmp_move_y, c);
            tmp_move_y = value;
        } else if (c == 'z') {
            figure = Shift(figure, value - tmp_move_z, c);
            tmp_move_z = value;
        }
    }
}


void GeometryEngine::drawprocess(QOpenGLShaderProgram *program)
{

    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_POINT_SIZE);

    glPointSize(2);
    if (flag_draw == 1) {
        binding();
    }
    arrayBuf.bind();
    indexBuf.bind();
//    arrayBuf.bind();
    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));   

    if (flag_draw == 1) {
        glDrawElements(GL_LINES, lines, GL_UNSIGNED_INT, nullptr);
//        glDrawElements(GL_POINTS, lines, GL_UNSIGNED_INT, nullptr);

    }
}

void GeometryEngine::drawdot(QOpenGLShaderProgram *program)
{

//        glDisable(GL_POINT_SMOOTH);
//        glEnable(GL_POINT_SIZE);

//        glPointSize(2);

//        binding();
//        arrayBuf.bind();
//        indexBuf.bind();
////        arrayBuf.bind();
//        quintptr offset = 0;

//        int vertexLocation = program->attributeLocation("a_position");
//        program->enableAttributeArray(vertexLocation);
//        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

//        offset += sizeof(QVector3D);

//        // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//        int texcoordLocation = program->attributeLocation("a_texcoord");
//        program->enableAttributeArray(texcoordLocation);
//        program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
//        if (flag_draw == 1) {
//            glDrawElements(GL_POINTS, lines, GL_UNSIGNED_INT, nullptr);
//        }
}


