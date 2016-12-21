#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QKeyEvent>

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
};

/* IGNORE this
 * ***********
 private slots:
    void on_pushButton_clicked();
*/

#endif // MAINWINDOW_H
