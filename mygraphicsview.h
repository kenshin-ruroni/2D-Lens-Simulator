#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

class myGraphicsView : public QGraphicsView
{
public:
    myGraphicsView();
    myGraphicsView(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR);



    bool mousePressed;

    QPointF  mousePosition;

protected :

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

};

#endif // MYGRAPHICSVIEW_H
