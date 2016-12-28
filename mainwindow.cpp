#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <windows.h>
#include "room.h"
#include "agent.h"
#include "game.h"
#include "helpers.h"
using namespace std;

map<string, QPixmap> MainWindow::itemsPix;

// When the application loads
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	playerPix.resize(2);

	// Load images
	wallPix.load(":/files/imgs/wall.jpg");
	playerPix[0].load(":/files/imgs/player1.png");
	playerPix[1].load(":/files/imgs/player2.png");
	monsterPix.load(":/files/imgs/monster_1.png");
	nothingPix.load(":/files/imgs/nothing.png");

	vector<QPixmap> avatar(2);
	avatar[0].load(":/files/imgs/player1_avatar.png");
	avatar[1].load(":/files/imgs/player2_avatar.png");
	vector<QLabel*> avatarLabel(2);
	avatarLabel[0] = new QLabel(this);
	avatarLabel[1] = new QLabel(this);
	avatarLabel[0]->setGeometry(10, 10, 50, 50);
	avatarLabel[1]->setGeometry(Game::mapWidth * tileHeight / 2, 10, 50, 50);
	avatarLabel[0]->setPixmap(avatar[0].scaledToHeight(50));
	avatarLabel[1]->setPixmap(avatar[1].scaledToHeight(50));
	const int infoHeight = 70;

	statusLabel.resize(2);
	statusLabel[0] = new QLabel(this);
	statusLabel[1] = new QLabel(this);
	statusLabel[0]->setGeometry(70, 10, 200, 50);
	statusLabel[1]->setGeometry(Game::mapWidth * tileHeight / 2 + 60, 10, 200, 50);
	statusLabel[0]->setStyleSheet("color: white; font-family: Arial;font-style: normal;font-size: 9pt;font-weight: bold;");
	statusLabel[1]->setStyleSheet("color: white; font-family: Arial;font-style: normal;font-size: 9pt;font-weight: bold;");
	statusLabel[0]->setText(QString::fromStdString(Game::me[0]->status()));
	statusLabel[1]->setText(QString::fromStdString(Game::me[1]->status()));

	hitPix.resize(8);
	for	(int i = 1; i <= 8; i++)
		hitPix[i - 1].load(":/files/imgs/hit_" + QString::number(i) + ".png");

	itemsPix["Pandora's-Chest"].load(":/files/imgs/chest2.png");
	itemsPix["Neko'sTreasure"].load(":/files/imgs/chest.png");
	itemsPix["Chest-Key"].load(":/files/imgs/key1.png");
	itemsPix["Treasure-Key"].load(":/files/imgs/silverKey.png");
	itemsPix["Possessed-Sword"].load(":/files/imgs/1.png");
	itemsPix["Winterthorn-Sword"].load(":/files/imgs/2.png");
	itemsPix["Newbie-Sword"].load(":/files/imgs/3.png");

	this->setGeometry(100, 100, Game::mapWidth * tileHeight, infoHeight + Game::mapHeight * tileHeight);
	this->setStyleSheet("QMainWindow {background-color: black;}");

	tile.assign(Game::mapHeight, vector<QLabel*>(Game::mapWidth));
	hpTile.assign(Game::mapHeight, vector<QLabel*>(Game::mapWidth));
	hitTile.assign(Game::mapHeight, vector<QLabel*>(Game::mapWidth));

	for (int i = 0; i < Game::mapHeight; i++)
		for (int j = 0; j < Game::mapWidth; j++)
		{
			tile[i][j] = new QLabel(this);
			tile[i][j]->setGeometry(j * tileHeight, infoHeight + i * tileHeight, tileHeight, tileHeight);
			hpTile[i][j] = new QLabel(this);
			hpTile[i][j]->setGeometry(j * tileHeight, infoHeight + i * tileHeight, tileHeight, tileHeight);
			hitTile[i][j] = new QLabel(this);
			hitTile[i][j]->setGeometry(j * tileHeight, infoHeight + i * tileHeight, tileHeight, tileHeight);
			hpTile[i][j]->setAlignment(Qt::AlignCenter);
			hpTile[i][j]->setStyleSheet("color: white; font-size: 13pt;");
			if (Game::rooms[i][j].isWall())
				tile[i][j]->setPixmap(wallPix.scaledToHeight(tileHeight));
			else if (Game::rooms[i][j].occupants.size() > 0 &&
					 Game::rooms[i][j].occupants[0]->getType() == "player1")
				tile[i][j]->setPixmap(playerPix[0].scaledToHeight(tileHeight));
			else if (Game::rooms[i][j].occupants.size() > 0 &&
					 Game::rooms[i][j].occupants[0]->getType() == "player2")
				tile[i][j]->setPixmap(playerPix[1].scaledToHeight(tileHeight));
			else if (Game::rooms[i][j].occupants.size() > 0 &&
					 Game::rooms[i][j].occupants[0]->getType() == "monster")
				tile[i][j]->setPixmap(monsterPix.scaledToHeight(tileHeight));
			else if (Game::rooms[i][j].cur_objs.size() > 0)
				tile[i][j]->setPixmap(itemsPix[Game::rooms[i][j].cur_objs[0]->getName()]);
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
	string key = e->text().toLocal8Bit().constData();

	// If player 1 played
	if (key == "w" || key == "a" || key == "s" || key == "d" ||
		key == "e" || key == "q" || key == "f" || key == "r")
		nextStep = Game::me[0]->act(key);

	// If player 2 played
	else if (key == "u" || key == "h" || key == "j" || key == "k" ||
			 key == "i" || key == "y" || key == "l" || key == "o")
		nextStep = Game::me[1]->act(key);

	// If a wrong key pressed
	else
		return;

	moveMobs(Game::mobs);
	statusLabel[0]->setText(QString::fromStdString(Game::me[0]->status()));
	statusLabel[1]->setText(QString::fromStdString(Game::me[1]->status()));

	// Refresh GUI
	for (int i = 0; i < Game::mapHeight; i++)
		for (int j = 0; j < Game::mapWidth; j++)
			if (Game::rooms[i][j].isWall())
				continue;
			else if (Game::rooms[i][j].occupants.size() > 0 &&
					 Game::rooms[i][j].occupants[0]->getType() == "player1")
			{
				tile[i][j]->setPixmap(playerPix[0].scaledToHeight(tileHeight));
				hpTile[i][j]->setText(QString::number(Game::me[0]->getHealth()));
			}
			else if (Game::rooms[i][j].occupants.size() > 0 &&
					 Game::rooms[i][j].occupants[0]->getType() == "player2")
			{
				tile[i][j]->setPixmap(playerPix[1].scaledToHeight(tileHeight));
				hpTile[i][j]->setText(QString::number(Game::me[1]->getHealth()));
			}
			else if (Game::rooms[i][j].occupants.size() > 0 &&
					 Game::rooms[i][j].occupants[0]->getType() == "monster")
			{
				tile[i][j]->setPixmap(monsterPix.scaledToHeight(tileHeight));
				hpTile[i][j]->setText(QString::number(Game::rooms[i][j].occupants[0]->getHealth()));
			}
			else if (Game::rooms[i][j].cur_objs.size() > 0)
			{
				tile[i][j]->setPixmap(itemsPix[Game::rooms[i][j].cur_objs[0]->getName()]);
				hpTile[i][j]->setText("");
			}
			else
			{
				tile[i][j]->setPixmap(nothingPix.scaledToHeight(tileHeight));
				hpTile[i][j]->setText("");
			}

	/*
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
	*/
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
