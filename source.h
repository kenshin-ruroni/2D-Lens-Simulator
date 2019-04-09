#ifndef SOURCE_H
#define SOURCE_H
#include "circle.h"
#include <list>
#include <QMenu>
#include <sourcecontextmenu.h>
class Ray;

class Source : public Circle
{


    static int counter;
public:
    Source(QString );

    Circle *c1,*c2;

    std::list<Ray *> rays;
    void AddARay();

     void advance(int phase);

     inline bool IsSource(){return true;}

   SourceContextMenu  mycontextMenu;

   void UpdateRays();

protected :
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);


};

#endif // SOURCE_H
