#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <vector>
#include <QLabel>
#include <QPixmap>
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
    QPixmap wallpix;
    QPixmap player1pix;
    QPixmap monsterpix;
    QPixmap nothingpix;
    vector<vector<QLabel*>> tile;
    const int tileHeight = 30;
};

/* IGNORE this
 * ***********
 private slots:
    void on_pushButton_clicked();
*/

#endif // MAINWINDOW_H
