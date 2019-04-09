#include "mygraphicsscene.h"
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsView>
#include <QDebug>
myGraphicsScene::myGraphicsScene():QGraphicsScene (NULL)
{

}

myGraphicsScene::myGraphicsScene(QObject *parent):QGraphicsScene (parent)
{

}
myGraphicsScene::myGraphicsScene(const QRectF &sceneRect, QObject *parent):QGraphicsScene (sceneRect,parent)
{

}

void myGraphicsScene::RayCast( QVector2D *start_Position ,QVector2D *start_direction, std::list<QPointF> *history)
{


}




