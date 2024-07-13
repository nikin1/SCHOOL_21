#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"
#include "geometry.h"
#include <QFileDialog>
#include <QTimer>
#include <fstream>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OPEN_FILE_clicked();

    void on_scale_slider_valueChanged(int value);

    void on_rotate_z_slider_valueChanged(int value);

    void on_rotate_y_slider_valueChanged(int value);

    void on_rotate_x_slider_valueChanged(int value);

    void on_move_x_slider_valueChanged(int value);

    void on_move_y_slider_valueChanged(int value);

    void on_move_z_silder_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QColor *LineColor = new QColor(255, 249, 0, 0);
    QColor *ColorBack = new QColor(182, 0, 255, 255);
    QColor *VerColor = new QColor();

};

#endif // MAINWINDOW_H
