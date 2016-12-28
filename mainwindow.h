#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <vector>
#include <map>
#include <string>
#include "room.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* e);

private:
    Ui::MainWindow *ui;
	QPixmap wallPix;
	vector<QPixmap> playerPix;
	vector<QPixmap> hitPix;
	QPixmap monsterPix;
	QPixmap nothingPix;
	vector<vector<QLabel*>> tile;
	vector<vector<QLabel*>> hpTile;
	vector<vector<QLabel*>> hitTile;
	vector<QLabel*> statusLabel;
	static map<string, QPixmap> itemsPix;
	const int tileHeight = 40;
};

/* IGNORE this
 * ***********
 private slots:
    void on_pushButton_clicked();
*/

#endif // MAINWINDOW_H
