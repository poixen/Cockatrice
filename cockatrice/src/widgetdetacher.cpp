#include "widgetdetacher.h"
#include <QMenu>

WidgetDetacher::WidgetDetacher(QTabWidget* _parent, QWidget* _subject) :
    QObject(_parent) 
    {
    parentTabWidget = _parent;
    subject = _subject;
    if (subject != 0) {
        subject->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(subject, SIGNAL(customContextMenuRequested(const QPoint &)),
                this, SLOT(showContextMenu(const QPoint &)));
    }
}
 
void WidgetDetacher::detachWidget() {
    if (subject != 0) {
        if (subject->parentWidget() != 0) {
            tabPos = parentTabWidget->currentIndex();
            tabLabel = parentTabWidget->tabText(tabPos);
            parentTabWidget->removeTab(tabPos);
            subject->setParent(0);
            subject->show();
        }
    }
}
 
void WidgetDetacher::attachWidget() {
    if (subject != 0 && subject->parentWidget() == 0) {
        disconnect(parentTabWidget, SIGNAL(destroyed(QObject*)), subject, SLOT(close()));
        parentTabWidget->insertTab(tabPos, subject, tabLabel);
        parentTabWidget->setCurrentIndex(tabPos);
    }
 
}
 
void WidgetDetacher::showContextMenu(const QPoint &_pos) {
    QMenu menu;
    if (subject != 0) {
        if (subject->parentWidget() != 0) {
            menu.addAction(tr("Detach"), this, SLOT(detachWidget()));
        } else {
            menu.addAction(tr("Attach"), this, SLOT(attachWidget()));
        }
        menu.exec(((QWidget*) subject)->mapToGlobal(_pos));
    }
}