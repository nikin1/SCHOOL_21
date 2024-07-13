#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <qmath.h>
#include <QColor>

#ifdef __cplusplus
extern "C" {
    #endif
    #include "s21_3Dviewer.h"
    #ifdef __cplusplus
}
#endif

class GeometryEngine : public QOpenGLFunctions {
    struct VertexData {
      QVector3D position;
    };

 public:

  QString filepath;
  int flag_draw = 0;

  GeometryEngine();
  virtual ~GeometryEngine();

  void drawprocess(QOpenGLShaderProgram *program);
  void drawdot(QOpenGLShaderProgram *program);
  void drawcube(QOpenGLShaderProgram *program);
  void parsing();
  void binding();

  void scaling(double value);
  void rotate(double value, char c);
  void move(double value, char c);

  double tmp_scale = 1;
  double tmp_rotate_x = 0;
  double tmp_rotate_y = 0;
  double tmp_rotate_z = 0;

  double tmp_move_x = 0;
  double tmp_move_y = 0;
  double tmp_move_z = 0;



  vertex_t figure;


 private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;

  GLsizei lines;
};


#endif // GEOMETRY_H
