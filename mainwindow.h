#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "circle.h"
#include "mygraphicsview.h"
#include<QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGraphicsScene *scene;

    myGraphicsView *view;

    Circle *circle1;
    Circle *circle2;

        QTimer timer;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
