#ifndef RAY_H
#define RAY_H
#include <QGraphicsLineItem>
#include <QVector2D>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include "rayorigin.h"

class Source;
class Circle;
class QPainterPath;

class Ray : public QGraphicsPathItem
{

    static double epsilon;

public:

    QString myName;
    Ray(QString name,Source *theSource);

    double angle;
    double distanceFromSourceCenter, maxLength;

    double n;

    QPainterPath *thePath;

    Circle *c1, *c2;

    QPointF direction;

    QPointF start,end;

    QPointF origin, originalDirection;

    RayOrigin head;

    void SetDirection( double angle );
    void SetHeadPosition(QPointF scenPosition);

    std::list<QLine *> segments;

    std::list<QPointF> points;

    int RayCast(QPointF incident_position, QVector2D incident_direction, double current_n, int *count);

    void InitializePath();

    void RayCast();

    void SetDefaultRay();

    QVector2D ComputeReflectionVector(QVector2D incident,QVector2D normal);

    double  clamp(double , double , double );

    bool ComputeRefractionVector(QVector2D i, double ni, double nr, QVector2D normal, QVector2D *out);

    bool IntersectsCircle(QPointF rayOrigin, QVector2D rayDirection, Circle *c, QPointF *intersectionPoint );

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);


    bool isInsideCircle(QPointF position, Circle *c);

    bool CirclesIntersect(Circle *c1,Circle *c2);

    bool ComputeNearestIntersection(QPointF p, QVector2D d, QPointF *i, double *n, QVector2D *normal, Circle **c);


    void AddPointToPath(QPointF p);
};

#endif // RAY_H
