#include <cmath>
#include "qgraphicsarcitem.h"
#include <QPainterPath>
#include <QBrush>
#include <QPen>
#include<QPainter>
#include <QDebug>

QGraphicsArcItem::QGraphicsArcItem():QGraphicsItem ()
{
    myPen = QPen( QBrush(QColor::fromRgbF(1,0,1,1)),4,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin );
}

void QGraphicsArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPainterPath path;

    int sA = (int) round( startAngle );
    int eA = (int) round(endAngle);
    painter->setPen( myPen );
    painter->drawArc(circle, sA*16, (eA - sA) * 16 );

}


QPainterPath QGraphicsArcItem::shape() const
{

    QPainterPath path;

        path.arcMoveTo(circle,startAngle);
        path.arcTo(circle, startAngle, endAngle-startAngle);

         return path;
}

QRectF QGraphicsArcItem::boundingRect() const
{
    double xmax = fmax( p1.x(), p2.x() );
    double xmin = fmin( p1.x(), p2.x() );
    double ymax = fmax( p1.y(), p2.y() );
    double ymin = fmin( p1.y(), p2.y() );

    QPointF topLeft = QPointF( xmin,ymax);
    QPointF rightBottom =  QPointF( xmax,ymin);

    qDebug()<<"bounding rect "<<QRectF(topLeft,rightBottom);
    qDebug()<<"top left "<<topLeft<<"  bottom right "<<rightBottom;
    return QRectF(topLeft,rightBottom);
}
