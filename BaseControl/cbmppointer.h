#ifndef CBMPPOINTER_H
#define CBMPPOINTER_H

#include "qpushbutton.h"
#include "QPainter"

// 该自绘控件用于仪表盘指针 具备实施设置角度效果 并且可以设置角度旋转原点
class CBmpPointer : public QPushButton
{
public:
    CBmpPointer(QPixmap *pImage, const QPoint &ptCenter, const QRect &rtArea, QWidget *parent = Q_NULLPTR);
    ~CBmpPointer();

    void ShowNewAngle(qreal angle);

private:
    QPixmap *m_pImgShow;
    QPoint m_ptCenter;
    qreal m_rlAngle;

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // CBMPPOINTER_H
