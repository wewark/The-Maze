#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <QFile>
#include "room.h"
using namespace std;

// When the application loads
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load image
    QPixmap pixmap(":/files/imgs/wall.jpg");

    // Load map file and read it
    QFile mapFile(":/files/txts/map.txt");
    mapFile.open(QIODevice::ReadOnly | QIODevice::Text);
    string temp;
    vector<string> map;
    while (!mapFile.atEnd())
    {
        temp = mapFile.readLine();
        temp = temp.substr(0, temp.length() - 1);
        map.push_back(temp);
    }

    Room::initializeRooms(map);
    this->setGeometry(200, 200, Room::mapWidth * 50, Room::mapHeight * 50);
    this->setStyleSheet("background-color: black;");

    // Generate blocks
    QLabel *block[100];
    int currentBlock = 0;
    for (int i = 0; i < Room::mapHeight; i++)
        for (int j = 0; j < Room::mapWidth; j++)
            if (Room::room[i][j].isBlock())
            {
                block[currentBlock] = new QLabel(this);
                block[currentBlock]->setPixmap(pixmap.scaledToHeight(50));
                block[currentBlock]->setGeometry(j * 50, i * 50, 50, 50);
                currentBlock++;
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
    int step = 50;

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
