#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <list>
#include <QGraphicsScene>
#include <QPointF>

class myGraphicsScene : public QGraphicsScene
{
public:
    myGraphicsScene();
    ~myGraphicsScene(){}
    myGraphicsScene(QObject *parent = Q_NULLPTR);
    myGraphicsScene(const QRectF &sceneRect, QObject *parent = Q_NULLPTR);

    void RayCast( QVector2D *startPosition ,QVector2D *start_direction, std::list<QPointF> *history);

};



#endif // MYGRAPHICSSCENE_H
