#include "sourcecontextmenu.h"
#include <QMouseEvent>
#include <QAction>
#include "source.h"

SourceContextMenu::SourceContextMenu(Source *source):mySource(source)
{
   QAction *action = addAction(("Add A Ray"));
    actions.push_back(action);
    connect(action, &QAction::triggered, this, &SourceContextMenu::ProcessAddARayAction);
}

void SourceContextMenu::ProcessAddARayAction()
{
    mySource->AddARay();

}

SourceContextMenu::~SourceContextMenu()
{
    std::list<QAction *>::iterator b= actions.begin();
    while( b != actions.end() )
    {
        QAction * a = *b;
        delete a;
    }
    actions.clear();
}

void SourceContextMenu::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint p = QPoint( event->localPos().x(),event->localPos().y() );
    QAction *action = this->actionAt(p);
    if ( action != NULL )
    {
        action->trigger();
    }
}
