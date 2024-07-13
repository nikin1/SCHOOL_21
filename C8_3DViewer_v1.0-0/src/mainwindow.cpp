#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_OPEN_FILE_clicked()
{
    QString str = QFileDialog::getOpenFileName(this, "open file", "/", "*.obj");

//      QString str = "/Users/olegsapoval/Desktop/cube.obj";
        if (str.length()) {

            ui->openGLWidget->geometries->flag_draw = 1;
//             ui->openGLWidget->geometries->filepath = "/Users/olegsapoval/Desktop/cube.obj";

            QByteArray barr = str.toLatin1();
            QString alala = (char *) barr.data();


           ui->openGLWidget->geometries->filepath = alala;


           ui->openGLWidget->geometries->parsing();
           ui->openGLWidget->geometries->drawprocess(&ui->openGLWidget->program);
        }
}





void MainWindow::on_scale_slider_valueChanged(int value)
{
    float new_value = (float) value / 10;

    ui->scale_value->setValue(new_value);

    ui->openGLWidget->geometries->scaling(new_value);

//    ui->openGLWidget->updating();
    ui->openGLWidget->geometries->drawprocess(&ui->openGLWidget->program);



}


void MainWindow::on_rotate_z_slider_valueChanged(int value)
{
    float new_value = (float) value / 10;

    ui->rotate_z_value->setValue(new_value);

    ui->openGLWidget->geometries->rotate(new_value, 'z');
    ui->openGLWidget->geometries->drawprocess(&ui->openGLWidget->program);
//    ui->openGLWidget->updating();
//    update();
}


void MainWindow::on_rotate_y_slider_valueChanged(int value)
{
    float new_value = (float) value / 10;

    ui->rotate_y_value->setValue(new_value);

//    ui->openGLWidget->geometries->scaling(new_value);
//    ui->openGLWidget->updating();

    ui->openGLWidget->geometries->rotate(new_value, 'y');
    ui->openGLWidget->geometries->drawprocess(&ui->openGLWidget->program);
}


void MainWindow::on_rotate_x_slider_valueChanged(int value)
{
    float new_value = (float) value / 10;

    ui->rotate_x_value->setValue(new_value);

//    ui->openGLWidget->geometries->scaling(new_value);
//    ui->openGLWidget->updating();

    ui->openGLWidget->geometries->rotate(new_value, 'x');
    ui->openGLWidget->geometries->drawprocess(&ui->openGLWidget->program);
}


void MainWindow::on_move_x_slider_valueChanged(int value)
{
    float new_value = (float) value / 10;

//    printf("\n\nVALUE: %f\n\n", new_value);



//    printf("");
    ui->move_x_value->setValue(new_value);

//    printf("OLD\n\n");
//    for (int i = 0; i <  ui->openGLWidget->geometries->figure.col; i++) {
//        printf("%lf, ",  ui->openGLWidget->geometries->figure.coord_array[i]);
//    }
//    printf("\n\n");
    ui->openGLWidget->geometries->move(new_value, 'x');

//    printf("NEW\n\n");
//    for (int i = 0; i <  ui->openGLWidget->geometries->figure.col; i++) {
//        printf("%lf, ",  ui->openGLWidget->geometries->figure.coord_array[i]);
//    }

    ui->openGLWidget->geometries->drawprocess(&ui->openGLWidget->program);
//    ui->openGLWidget->geometries->scaling(new_value);
//    ui->openGLWidget->updating();
}


void MainWindow::on_move_y_slider_valueChanged(int value)
{
    float new_value = (float) value / 100;

    ui->move_y_value->setValue(new_value);

    ui->openGLWidget->geometries->move(new_value, 'y');
    ui->openGLWidget->geometries->drawprocess(&ui->openGLWidget->program);
//    ui->openGLWidget->geometries->scaling(new_value);
//    ui->openGLWidget->updating();

}


void MainWindow::on_move_z_silder_valueChanged(int value)
{
    float new_value = (float) value / 10;

    ui->move_z_value->setValue(new_value);

    ui->openGLWidget->geometries->move(new_value, 'z');
    ui->openGLWidget->geometries->drawprocess(&ui->openGLWidget->program);
//    ui->openGLWidget->geometries->scaling(new_value);
//    ui->openGLWidget->updating();
}
