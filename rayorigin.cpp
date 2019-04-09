#include <cmath>
#include "rayorigin.h"
#include <QGraphicsSceneMouseEvent>
#include "ray.h"
RayOrigin::RayOrigin():mousePressed(false)
{

}

void RayOrigin::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if ( !mousePressed)
    {
        mousePressed = true;
        mouseLocalPosition = event->pos();
    }
}
void RayOrigin::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ( !mousePressed )
    {
        return;
    }

    QPointF mousePos = event->scenePos();
    mousePos = this->parentItem()->mapFromScene(mousePos);

    double angle = atan2(mousePos.y(),mousePos.x());
    mousePos = distanceFromMorigin * (direction =   QPointF( cos(angle),sin(angle)) );
    setPos( mousePos );
    UpdateRay();
}

void RayOrigin::UpdateRay()
{
    ((Ray *)parentItem() )->origin =  pos();
    ((Ray *)parentItem() )->originalDirection = - direction;
    ((Ray *)parentItem() )->RayCast();
    parentItem()->update();
    update();
}
void RayOrigin::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressed = false;
}
