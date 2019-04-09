#ifndef RAYORIGIN_H
#define RAYORIGIN_H



#include <QGraphicsEllipseItem>


class RayOrigin : public QGraphicsEllipseItem
{
public:
    RayOrigin();

    bool mousePressed;
    QPointF mouseLocalPosition;

    QPointF direction;


    double distanceFromMorigin;


    void UpdateRay();

    void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) ;
};

#endif // RAYORIGIN_H
