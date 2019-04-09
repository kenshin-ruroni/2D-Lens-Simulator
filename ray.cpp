#include <cmath>
#include <limits>
#include "source.h"
#include "ray.h"
#include <QLineF>
#include <QRandomGenerator64>
#include <QTime>
#include <algorithm>
#include <QtGlobal>
#include "circle.h"
#include <QPainter>
#include <QDebug>

double Ray::epsilon = 1E-8;

Ray::Ray(QString name,Source *parent):angle( 1.5 * M_PI ),distanceFromSourceCenter(50),maxLength(10000),n(1),thePath(NULL),c1(NULL),c2(NULL)
{
    ((QObject *)this)->setObjectName( name );

    QRandomGenerator64 prng1;
    angle = prng1.global()->generateDouble() * 2 * M_PI;
    setParentItem(parent);
    head.setParentItem(this);
    head.setRect(-5,-5,10,10);

    head.distanceFromMorigin = distanceFromSourceCenter;

    SetDirection(angle);
    origin = - originalDirection * distanceFromSourceCenter;
    start = origin;
    end = start + direction * maxLength;
    head.setPos( start );
    RayCast();
    update();

}

void Ray::SetDirection( double angle )
{
    this->angle = angle;
    originalDirection = QPointF(cos(angle),sin(angle));

}

void Ray::SetHeadPosition(QPointF scenePosition)
{
    QPointF localPosition = this->parentItem()->mapFromScene(scenePosition);
    angle = atan2(localPosition.y(),localPosition.x());
    SetDirection(angle);
    direction = originalDirection;
    start = direction * distanceFromSourceCenter;
    end = start + direction * maxLength;
    head.setPos( start );
    //setLine( QLineF( start , end) );
}


double  Ray::clamp(double n, double lower, double upper) {
  return std::max(lower, std::min(n, upper));
}

QVector2D Ray::ComputeReflectionVector(QVector2D i,QVector2D n)
{
    double cosi = -QVector2D::dotProduct(i,n);
    return (i + 2.0*cosi*n).normalized();
}

bool Ray::ComputeRefractionVector(QVector2D i, double ni, double nr, QVector2D normal, QVector2D *out)
{

    double cosi = clamp( QVector2D::dotProduct(i,normal) ,-1, 1);
    double etai = ni, etat = nr;

    QVector2D n = normal;
    if (cosi < 0) {
        cosi = -cosi;
    } else {
        double temp = etai;
        etai = etat;
        etat = temp;
        n = -normal;
    }
    double eta = ni / nr;
    double k = 1 - (eta * eta) * (1 - (cosi * cosi));
    if (k <= 0) {
        return false;
    } else {
        *out = eta*i + (eta*cosi - sqrt(k) ) * n;
    }
    return true;
}

void Ray::SetDefaultRay()
{
    thePath->lineTo(end);

}

void Ray::InitializePath()
{
    if ( thePath != NULL )
    {
        delete thePath;
    }

    thePath =new QPainterPath();
    start = origin;
    direction = originalDirection;
    thePath->moveTo(start);
    end = start + maxLength * direction;
}

void Ray::RayCast()
{
    InitializePath();
    if ( c1 == NULL || c2 == NULL )
    {
        SetDefaultRay();
        return;
    }
    int count = 0;
    start = mapToScene(start);
    double nn = n;
    RayCast( start, QVector2D(direction),nn,&count);
    end = start + maxLength * direction;
    AddPointToPath(end);
    for (int i =0; i < thePath->elementCount();i++)
    {
        qDebug()<<i<<" "<<thePath->elementAt(i).x<<" "<<thePath->elementAt(i).y;
    }
    update();
}

bool Ray::isInsideCircle(QPointF position, Circle *c)
{
    QVector2D delta = QVector2D(position-c->pos());
    return QVector2D::dotProduct( delta,delta ) <= pow(c->radius,2);
}

bool Ray::CirclesIntersect(Circle *c1,Circle *c2)
{
    QVector2D delta = QVector2D( c1->pos() - c2->pos());
    return QVector2D::dotProduct(delta,delta) <= pow(c1->radius+c2->radius,2);
}

bool Ray::ComputeNearestIntersection(QPointF p,QVector2D d, QPointF *i, double *n, QVector2D *normal, Circle **c)
{
    int count = 0;
    QPointF p1,p2;
    bool intersectsC1 = IntersectsCircle(p,d,c1,&p1);
    bool intersectsC2 = IntersectsCircle(p,d,c2,&p2);
    double distanceToC1 = std::numeric_limits<double>::max();
    double distanceToC2 = std::numeric_limits<double>::max();
    if ( intersectsC1 )
    {
        QVector2D delta = QVector2D(p1 - p);
        distanceToC1 = QVector2D::dotProduct(delta,delta);
        count ++;
    }
    if ( intersectsC2 )
    {
        QVector2D delta = QVector2D(p2 - p);
        distanceToC2 = QVector2D::dotProduct(delta,delta);
        count ++;
    }
    if ( count == 0)
    {
        return false;
    }

    if ( distanceToC1 < distanceToC2 )
    {
        *i = p1;
        isInsideCircle(p1 + 0.0001 * d.toPointF(),c1) ? *n = c1->GetRefractiveIndex() : *n= this->n ;
        *normal = c1->normalAtPoint(p1);
        *c = c1;
    }
    else
    {
        *i = p2;
        isInsideCircle(p2+ 0.0001 * d.toPointF() ,c2) ? *n = c2->GetRefractiveIndex() : *n= this->n ;
        *normal = c2->normalAtPoint(p2);
        *c = c2;
    }
    return true;
}

void Ray::AddPointToPath(QPointF p)
{
    p = mapFromScene(p);
    thePath->lineTo(p);
}
int Ray::RayCast(QPointF p,QVector2D d, double current_n, int *count)
{

    bool insideC1 =  isInsideCircle(p,c1);
    bool insideC2 = isInsideCircle(p,c2);
    bool circlesIntersect = CirclesIntersect(c1,c2);
    if ( insideC1 && insideC2 && circlesIntersect )
    {
        current_n = 0.5*(c1->GetRefractiveIndex()+c2->GetRefractiveIndex() );
    }
    else if( insideC1 )
    {
        current_n = c1->GetRefractiveIndex();
    }
    else
    if ( insideC2 )
    {
        current_n = c2->GetRefractiveIndex();
    }
    else
    {
        current_n = n;
    }
    QPointF intersection;
    double nr;
    QVector2D normal;
    Circle *c = NULL;
    if ( ComputeNearestIntersection(p,d,&intersection,&nr,&normal,&c) )
    {
       AddPointToPath(intersection);
       QVector2D out;
       (*count)++;
       if( !c->isPurelyReflexive() && ComputeRefractionVector(d,current_n,nr,normal,&out) )
       {
           intersection += 0.0001 * out.toPointF();
           RayCast(intersection,out, nr, count );
           return 0;
       }
       // reflection totale
       out = ComputeReflectionVector(d,normal);
       intersection += 0.0001 * normal.toPointF();
       RayCast(intersection,out, current_n, count );
       return 0;
    }
    start = p;
    direction = d.toPointF();

}


bool Ray::IntersectsCircle(QPointF rayOrigin, QVector2D rayDirection, Circle *c, QPointF *intersectionPoint )
{
      QVector2D h = QVector2D( c->pos()-rayOrigin );

      double lf =  QVector2D::dotProduct( rayDirection, h);                  // lf=e.h
      double s = pow(c->radius,2)- QVector2D::dotProduct(h,h)+pow(lf,2);   // s=r^2-h^2+lf^2
      if (s < 0.0) return false;                    // no intersection points ?
      s = sqrt(s);                              // s=sqrt(r^2-h^2+lf^2)

      int result = 0;
      if (lf < s)                               // S1 behind A ?
      { if (lf+s >= 0)                          // S2 before A ?}
        { s = -s;                               // swap S1 <-> S2}
          result = 1;                           // one intersection point
      } }
      else result = 2;                          // 2 intersection points

      double lambda1 = lf+s;
      double lambda2 = lf-s;
      if ( lambda1 < 0 && lambda2 < 0)
      {
          return false;
      }
      double lambda = lambda1;
      if ( lambda1< 0 )
      {
          lambda = lambda2;
      }
      else if ( lambda1 > 0 && lambda2 > 0 )
      {
          lambda = fmin(lambda1,lambda2);
      }
      *intersectionPoint = rayOrigin + lambda *rayDirection.toPointF();

      return true;


}

void Ray::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    setPath( *thePath);
    painter->drawPath( this->path());
}
