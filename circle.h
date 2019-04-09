#ifndef CIRCLE_H
#define CIRCLE_H
#include <QVector2D>
#include <QGraphicsEllipseItem>
#include <QLineF>
#include "qgraphicsarcitem.h"
#include "dialogeditcircle.h"

class Source;

class Circle : public QGraphicsEllipseItem
{


public:

    static int counter;
    Circle();
    Circle(QString name,QPointF centerPosition);
    double n; // indice refraction
    double radius;

    QGraphicsLineItem l1,l2;

    QGraphicsEllipseItem center;

    QGraphicsTextItem tP1,tP2;
     QGraphicsEllipseItem P1,P2, MIDDLE;

    QGraphicsArcItem arc;

    DialogEditCircle myDialog;

    bool isPurelyReflexive(){return myDialog.IsPurelyReflexive();}

    double GetRefractiveIndex(){return myDialog.GetRefractiveIndex();}

    Source *theSource;

    void SetRadius(double r);

    void SetCenterPosition(QPointF p);

    void DrawLines();

    bool mousePressed;
    QPointF localMousePosition;

    void advance(int phase);

    inline QVector2D normalAtPoint(QPointF p){
        return ( QVector2D( p) - QVector2D(this->pos()) ).normalized();
    }

    virtual inline bool IsSource(){return false;}

    void SetIntersectionData(QPointF p1,QPointF p2);
    bool ComputeCircleCircleIntersection(Circle *c,QPointF *p1, QPointF *p2);


protected :
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);


};

#endif // CIRCLE_H
