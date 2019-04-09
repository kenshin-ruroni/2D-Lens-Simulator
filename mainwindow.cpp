#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QRectF>
#include "source.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect( QRectF(-800/2,-600/2,800,600));

    circle1 = new Circle("Circle1",QPointF(100,100));
    circle1->SetRadius(100);
    circle1->SetCenterPosition( QPointF(400,400) );
    ((QObject *)circle1)->setObjectName("Circle1");


    circle2 = new Circle("Circle2",QPointF(250,300));
    circle2->SetRadius(50);
    circle2->SetCenterPosition( QPointF(350,250) );
    ((QObject *)circle2)->setObjectName("Circle2");

    Source *source = new Source("Source0");
    source->SetCenterPosition( QPointF(300,300));
    scene->addItem(source);
    source->c1= circle1;
    source->c2 = circle2;

    circle2->theSource = circle1->theSource = source;


   // QGraphicsRectItem *r = new QGraphicsRectItem(QRectF(50,50,190,100));

  //  scene->addItem( r  );

    scene->addItem( circle1 );

    scene->addItem (circle2);

    scene->addRect( QRectF(-scene->width()/2,-scene->height()/2,scene->width(),scene->height()));

    view = new myGraphicsView(scene,this);
    view->setEnabled(true);
    view->setGeometry(0,0,1920,1080);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->show();


    connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer.start(10);



}

MainWindow::~MainWindow()
{
    delete ui;
}
