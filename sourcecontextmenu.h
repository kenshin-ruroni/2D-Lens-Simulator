#ifndef SOURCECONTEXTMENU_H
#define SOURCECONTEXTMENU_H

#include <QMenu>
class QAction;
class Source;

class SourceContextMenu : public QMenu
{

    std::list<QAction *>actions;
public:
    SourceContextMenu(Source *);
    ~SourceContextMenu();

    Source *mySource;

    void ProcessAddARayAction();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // SOURCECONTEXTMENU_H
