#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QPixmap>

// When the application loads
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load image
    QPixmap pixmap(":/new/prefix1/wall.jpg");

    // Generate 10 walls
    QLabel *wall[10];
    for (int i = 0; i < 10; i++)
    {
        wall[i] = new QLabel(this);
        wall[i]->setPixmap(pixmap.scaledToHeight(50));
        wall[i]->setGeometry(i * 60, i * 60, 50, 50);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// On pressing anykey
void MainWindow::keyPressEvent(QKeyEvent* e)
{
    // Get original location
    int
        x = ui->label->x(),
        y = ui->label->y(),
        height = ui->label->height(),
        width = ui->label->width();
    int step = 30;

    // Change position
    if (e->text() == "d")
        x += step;
    else if (e->text() == "a")
        x -= step;
    else if (e->text() == "w")
        y -= step;
    else if (e->text() == "s")
        y += step;

    // Update position
    ui->label->setGeometry(x, y, height, width);
};

/* IGNORE this
 * ***********
 ui->pushButton->setVisible(false);
 void MainWindow::on_pushButton_clicked()
 {
     ui->label->setText("ok");
     this->setStyleSheet("background-color: red;");
 }
*/
