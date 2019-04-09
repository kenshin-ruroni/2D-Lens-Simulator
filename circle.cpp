#include <cmath>
#include <QObject>
#include "circle.h"
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include<QColor>
#include <qbrush.h>
#include <QDebug>
#include <QList>
#include <QPainter>
#include <QGraphicsScene>
#include "source.h"

int Circle::counter = 0;

Circle::Circle():Circle( "none",QPointF(50,50))
{
    ((QObject *)this)->setObjectName( "Circle#"+QString::number( counter++ ) );
}

Circle::Circle(QString name,QPointF centerPos):n(2),radius(10),myDialog(NULL),theSource(NULL),mousePressed(false),localMousePosition(QPointF(0,0))
{
  ((QObject *)this)->setObjectName( name );

    qDebug() << ((QObject *)this)->objectName();

    arc.setParentItem(this);

   // center.setParentItem(this);

    SetRadius(radius);
    setPen( QPen( QBrush(QColor::fromRgbF(0.5,0.5,0.5,0.2)),4,Qt::DashDotLine,Qt::SquareCap,Qt::BevelJoin ));
    update();

    center.setRect(-2,-2,4,4);

    center.setPen(QColor::fromRgbF(0,0,1,1));

    P1.setParentItem(this);
    P1.setPos(0,0);
    P1.setRect(-5,-5,10,10);
    P1.setPen(QPen( QBrush(QColor::fromRgbF(1,0,1,1)),2,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin ));
    tP1.setParentItem(&P1);
    tP1.setPlainText("P1");

    P2.setParentItem(this);
    P2.setRect(-5,-5,10,10);
    P2.setPen(QPen( QBrush(QColor::fromRgbF(1,0,1,1)),2,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin ));
    P2.setPos(0,0);
    tP2.setParentItem(&P2);
    tP2.setPlainText("P2");

    MIDDLE.setPen(QPen( QBrush(QColor::fromRgbF(0,1,1,1)),6,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin ));
    MIDDLE.setRect(-5,-5,10,10);
    MIDDLE.setParentItem(this);

    arc.startAngle = 0;
    arc.endAngle = 50 * 16;

    l1.setParentItem(this);
    l2.setParentItem(this);
    SetCenterPosition(centerPos);

    myDialog.myCircle = this;

}


void Circle::SetRadius(double r)
{
    setRect( QRect(-r,-r,2*r,2*r));
    radius = r;

    arc.startAngle = 10;
    arc.endAngle = 90;
    arc.radius = radius-4;
    arc.circle =  QRectF(-arc.radius,-arc.radius,2*arc.radius,2*arc.radius) ;

    qDebug()<<"SetRadius rect "<<rect();


    DrawLines();
    center.setPos( QPointF(0,0));
    update();
    arc.update();
    if ( theSource != NULL)
    {
        theSource->UpdateRays();
    }
}

void Circle::DrawLines()
{
    return;
    l1.setLine( 0,0,radius,0 );
    l1.setPen(QPen( QBrush(QColor::fromRgbF(1,1,1,1)),4,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin ));


    l2.setLine( 0,0,radius*cos(-50*M_PI/180),radius*sin(-50*M_PI/180) );
    l2.setPen(QPen( QBrush(QColor::fromRgbF(1,1,1,1)),4,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin ));

}

void Circle::SetCenterPosition(QPointF p)
{
    // - QPointF( rect().width()*0.5,rect().height()*0.5);
    setPos(p);
    DrawLines();

    update();
    center.setPos( pos() );
    arc.update();
    if ( theSource != NULL)
    {
        theSource->UpdateRays();
    }
}


void Circle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressed = true;
    localMousePosition = event->pos() ;
}



void Circle::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if (!mousePressed)
    {
        return;
    }
    double delta  = double(event->delta());
   radius +=    delta * 0.1;
    SetRadius(radius);

    update();

}

void Circle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ( !mousePressed )
    {
        return;
    }
    SetCenterPosition(event->scenePos()  - localMousePosition);
    update();

}
void Circle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressed = false;

    if ( !IsSource() && event->button() == Qt::RightButton )
    {
        myDialog.move(event->screenPos()+QPoint(8,8));
        myDialog.setModal(false);
        myDialog.show();
        /*myDialog.exec();
        if (myDialog.result() == QDialog::Accepted )
        {
            isPurelyReflexive = myDialog.IsPurelyReflexive();
            this->n = myDialog.GetRefractiveIndex();
        }*/
    }
}

 void Circle::advance(int phase)
 {

     if ( IsSource() )
     {
         return;
     }
    // QGraphicsEllipseItem::advance(phase);


      QList<QGraphicsItem *> colliding = collidingItems(Qt::IntersectsItemShape);
      if ( colliding.size() > 0)
      {
          for (int i = 0;i < colliding.size();i++)
          {

              Circle  *item = dynamic_cast<Circle *> ( colliding[i] );
              if ( item == this || item == NULL  || item->IsSource()  )
              {
                  continue;
              }
             QPointF p1,p2;
              if( ComputeCircleCircleIntersection(item, &p1,&p2 ) )
              {
                SetIntersectionData(p1,p2);
              }
              else{
                  arc.startAngle = arc.endAngle = 0;
                  arc.update();
              }

          }
      }


 }

void Circle::SetIntersectionData(QPointF p1,QPointF p2)
{
    p1 = mapFromScene(p1 );

    p2 = mapFromScene(p2 );

    double dP1 = sqrt(QPointF::dotProduct(p1,p1));
    double dP2 = sqrt(QPointF::dotProduct(p2,p2));


    P1.setPos(p1);
    P2.setPos(p2);

    QVector2D normalP1 = QVector2D(p1.x(),p1.y()).normalized();
    QVector2D normalP2 = QVector2D(p2.x(),p2.y()).normalized();


    QVector2D normal = (normalP1+normalP2).normalized() ;

    QPointF middle = radius * normal.toPointF();

    MIDDLE.setPos(middle);

    double angleP1= -atan2(p1.y(),p1.x()) * 180/M_PI;
    double angleP2 = -atan2(p2.y(),p2.x()) * 180/M_PI;
    double angleMIDDLE = atan2(MIDDLE.y(),MIDDLE.x()) * 180/M_PI;

    double angle = atan2(p1.y(),p1.x());
    double x1 = radius * cos( angle),y1 = radius * sin(angle);

    angle = atan2(p2.y(),p2.x());
    double x2 = radius * cos( angle),y2 = radius * sin(angle);


   /* if ( angleMIDDLE < 0 )
    {
        angleMIDDLE +=360;

    }

    if (angleMIDDLE > 360 )
    {
        angleMIDDLE -= 360;
    }

    if ( angleP1 < 0 )
    {
        angleP1 += 360;
    }
    if ( angleP2 < 0)
    {
        angleP2 += 360;
    }

    if ( angleP1 > 180 && angleP2 < 180 )
    {
        angleP2 += 360;
    }
    else if ( angleP2 > 180 && angleP1 < 180 )
    {
        angleP1 += 360;
    }*/


    double start =  fmin(angleP1,angleP2);
    double end = fmax(angleP1,angleP2);
    if ( end - start > 180 )
    {
        end -= 360;
    }

    if ( start > 360)
    {
        start -= 360;
    }
    if ( end > 360 )
    {
        end -= 360;
    }

    double final_end = fmax(start,end);
    double final_start = fmin(start,end);

/*    if ( angleMIDDLE < final_start || angleMIDDLE > final_end )
    {
        final_end -= 360;
        start = final_start;
        end = final_end;
        final_end = fmax(start,end);
        final_start = fmin(start,end);

    }*/

    arc.startAngle = final_start;
    arc.endAngle   = final_end;
    arc.p1 = p1;
    arc.p2 = p2;

    update();
    arc.update();



}


bool Circle::ComputeCircleCircleIntersection(Circle *c,QPointF *p1, QPointF *p2)
{

    QPointF delta = c->pos()-pos();
    double d = sqrt( QPointF::dotProduct( delta , delta ) );

    if (d <= radius + c->radius && d >= fabs(c->radius - radius)) {

      double ex = delta.x() / d;
      double ey = delta.y() / d;

      double x = (radius * radius - c->radius * c->radius + d * d) / (2 * d);
      double y = sqrt(radius * radius - x * x);

      *p1 =  pos() + QPointF(x * ex - y * ey, x * ey + y * ex);


      *p2 = pos() + QPointF( x * ex + y * ey,x * ey -y * ex);
        return true;
    }
        // No Intersection, far outside or one circle within the other
    return false;
}
