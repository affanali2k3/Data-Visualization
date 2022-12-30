#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsScene>

class Custom_View : public QGraphicsView
{
    QOBJECT_H
   public:
        explicit Custom_View(QWidget *parent = nullptr);
protected:
    virtual void wheelEvent(QWheelEvent *event);
    using QGraphicsView::QGraphicsView;
};

#endif // CUSTOM_VIEW_H
