#include "custom_view.h"
#include <QMouseEvent>

Custom_View::Custom_View(QWidget *parent): QGraphicsView(parent)
{

}

void Custom_View::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(AnchorUnderMouse);
    double scaleFactor = 1.5;
    if (event->Scroll > 0)
    {
        scale(scaleFactor, scaleFactor);
    }
    else
    {
        scale(1/scaleFactor, 1/scaleFactor);
    }
}
