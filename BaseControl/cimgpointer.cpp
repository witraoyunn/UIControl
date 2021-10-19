#include "cimgpointer.h"

CImgPointer::CImgPointer(QPixmap *pImage, const QPoint &ptImgStart, const QPoint &ptLeftTop,
                         const QSize &size, QWidget *parent)
    :QPushButton(parent)
{
    m_pImgShow = pImage;
    m_rlAngle = 0.00;

    resize(size);
    move(ptLeftTop);
    m_ptImgStart = ptImgStart;
}

CImgPointer::~CImgPointer()
{
    m_pImgShow = NULL;
}

void CImgPointer::ShowNewAngle(qreal angle, bool bH)
{
    if (bH)
    {
        m_rlAngle = -angle;
    }
    else
    {
        m_rlAngle = angle;
    }
    update();
}

void CImgPointer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.translate(width()/2, height()/2);
    painter.rotate(m_rlAngle);
    painter.drawPixmap(m_ptImgStart, *m_pImgShow);
}
