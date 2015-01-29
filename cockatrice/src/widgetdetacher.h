#ifndef WIDGET_DETACHER
#define WIDGET_DETACHER

#include <QObject>
#include <QTabWidget>

class WidgetDetacher : public QObject {
    Q_OBJECT
public:
    WidgetDetacher(QTabWidget* _parent, QWidget* _subject);
public slots:
    void detachWidget();
    void attachWidget();
    void showContextMenu(const QPoint &_pos);
private:
    QWidget* subject;
    QTabWidget* parentTabWidget;
    QString tabLabel;
    int tabPos;
};

#endif