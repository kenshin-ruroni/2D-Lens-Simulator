#include "source.h"
#include "ray.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <sourcecontextmenu.h>

int Source::counter = 0;

Source::Source(QString name):Circle(),mycontextMenu(this)
{
   ((QObject *)this)->setObjectName( name );

    setPen( QPen(QBrush(Qt::blue ,Qt::SolidPattern),3.5,Qt::SolidLine ));
    mycontextMenu.hide();
}

void Source::AddARay()
{
     mycontextMenu.hide();
   Ray *aRay =  new Ray(QString::fromUtf8("Ray#")+QString::number(counter++),this);
   rays.push_back(aRay);
   aRay->c1 = c1;
   aRay->c2 = c2;
   aRay->RayCast();
}

void Source::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Circle::mouseReleaseEvent(event);
    QPoint p = event->screenPos()+QPoint(8,8);
    if ( event->button()==Qt::RightButton )
    {
        mycontextMenu.show();
        mycontextMenu.move(p);
    }
    else
    {
        mycontextMenu.hide();
    }
}

void Source::advance(int step)
{
    QGraphicsEllipseItem::advance(step);

}

void Source::UpdateRays()
{
    std::list<Ray *>::iterator i = rays.begin();
    for( ;i!=rays.end();i++){
         (*i)->RayCast();
    }
}

void Source::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ( !mousePressed )
    {
        return;
    }
    SetCenterPosition(event->scenePos()  - localMousePosition);
    update();
    UpdateRays();

}
