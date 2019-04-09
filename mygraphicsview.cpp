#include "mygraphicsview.h"
#include <QWheelEvent>
#include <QDebug>
#include <QScrollBar>
myGraphicsView::myGraphicsView():QGraphicsView (),mousePressed(false)
{

}

myGraphicsView::myGraphicsView(QGraphicsScene *scene, QWidget *parent):QGraphicsView (scene,parent)
{

}

void myGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    if ( event->button() == Qt::MidButton ){

        mousePressed = true;
        mousePosition =   event->localPos();
        }
    }

void myGraphicsView::mouseMoveEvent(QMouseEvent *event)
{

    qDebug()<< "mouse move event "<<event->localPos();
    QGraphicsView::mouseMoveEvent(event);

    if ( !mousePressed )
    {
        return;
    }

    QPointF tmp =  event->localPos();

    qreal dx = (tmp.x() - mousePosition.x()) * 0.1;
    qreal dy = (tmp.y()-mousePosition.y()) *0.1;

    qDebug()<< "dx "<<dx<<"  dy "<<dy;

    QRectF p = this->sceneRect();
    p.translate(dx,dy);

    scene()->setSceneRect(p);

    scene()->sceneRect().translate(dx,dy);

    QTransform transform = this->transform();
    transform.translate(-dx,-dy);
    setTransform(transform);
    setTransformationAnchor ( QGraphicsView::AnchorViewCenter);



    mousePosition = tmp;
}

void myGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    mousePressed = false;
}



void myGraphicsView::wheelEvent(QWheelEvent *event)
{

        double scaleFactor = 1.15;


            setTransformationAnchor (QGraphicsView::AnchorUnderMouse);
            if ( event->delta() > 0)
            {
                scale (scaleFactor, scaleFactor);
            }
            else{
                scale( 1/scaleFactor, 1/scaleFactor);
            }
}
