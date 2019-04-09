#ifndef QGRAPHICSARCITEM_H
#define QGRAPHICSARCITEM_H

#include <QGraphicsItem>
#include <QPen>

class QGraphicsArcItem : public QGraphicsItem
{
public:

    QGraphicsArcItem();

    QPen myPen;
        QRectF circle;
        double radius, startAngle,endAngle;
        QPointF p1,p2;

    QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QPainterPath shape() const;
        void setPen(const QPen &pen){myPen = pen;}
};

#endif // QGRAPHICSARCITEM_H
