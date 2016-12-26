#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>
#include <vector>
#include <string>
#include <iostream>
#include "room.h"
#include "agent.h"
#include "game.h"
#include "helpers.h"
using namespace std;

// When the application loads
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load images
    wallpix.load(":/files/imgs/wall.jpg");
    player1pix.load(":/files/imgs/player1.png");
    monsterpix.load(":/files/imgs/monster_1.png");
    nothingpix.load(":/files/imgs/nothing.png");

    this->setGeometry(200, 200, Game::mapWidth * tileHeight, Game::mapHeight * tileHeight);
    this->setStyleSheet("background-color: black;");

    tile.assign(Game::mapHeight, vector<QLabel*>(Game::mapWidth));

    for (int i = 0; i < Game::mapHeight; i++)
        for (int j = 0; j < Game::mapWidth; j++)
        {
            tile[i][j] = new QLabel(this);
            tile[i][j]->setGeometry(j * tileHeight, i * tileHeight, tileHeight, tileHeight);
            if (Game::rooms[i][j].isWall())
                tile[i][j]->setPixmap(wallpix.scaledToHeight(tileHeight));
            else if (Game::rooms[i][j].occupants.size() > 0 &&
                     Game::rooms[i][j].occupants[0]->getType() == "player")
                tile[i][j]->setPixmap(player1pix.scaledToHeight(tileHeight));
            else if (Game::rooms[i][j].occupants.size() > 0 &&
                     Game::rooms[i][j].occupants[0]->getType() == "monster")
                tile[i][j]->setPixmap(monsterpix.scaledToHeight(tileHeight));
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// On pressing anykey
void MainWindow::keyPressEvent(QKeyEvent* e)
{
    int nextStep;
    nextStep = Game::me[0]->act(e->text().toLocal8Bit().constData());
    moveMobs(Game::mobs);

    // Refresh GUI
    for (int i = 0; i < Game::mapHeight; i++)
        for (int j = 0; j < Game::mapWidth; j++)
            if (Game::rooms[i][j].isWall())
                tile[i][j]->setPixmap(wallpix.scaledToHeight(tileHeight));
            else if (Game::rooms[i][j].occupants.size() > 0 &&
                     Game::rooms[i][j].occupants[0]->getType() == "player")
                tile[i][j]->setPixmap(player1pix.scaledToHeight(tileHeight));
            else if (Game::rooms[i][j].occupants.size() > 0 &&
                     Game::rooms[i][j].occupants[0]->getType() == "monster")
                tile[i][j]->setPixmap(monsterpix.scaledToHeight(tileHeight));
            else
                tile[i][j]->setPixmap(nothingpix.scaledToHeight(tileHeight));

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
