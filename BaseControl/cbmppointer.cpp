#include "cbmppointer.h"

CBmpPointer::CBmpPointer(QPixmap *pImage, const QPoint &ptCenter, const QRect &rtArea, QWidget *parent)
      :QPushButton(parent)
{
    m_pImgShow = pImage;
    m_ptCenter = ptCenter;

    move(QPoint(rtArea.left(), rtArea.top()));
    resize(rtArea.size());
}

CBmpPointer::~CBmpPointer()
{
    m_pImgShow = NULL;
}

void CBmpPointer::ShowNewAngle(qreal angle)
{
    m_rlAngle = angle;
    show();
}

void CBmpPointer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.translate(m_ptCenter);
    painter.rotate(m_rlAngle);
    painter.drawPixmap(0, 0, *m_pImgShow);
}
