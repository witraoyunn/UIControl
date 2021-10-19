#include "cbmpbutton.h"
#include "qpainter.h"
#include "qdebug.h"

CBmpButton::CBmpButton(const QPixmap *pNor, const QPixmap *pOver, const QPixmap *pDown,
                       const QPixmap *pDis, const QRect &rtArea, QWidget *parent)
    :QPushButton(parent)
{
    m_pDraw = NULL;

    if (pNor != NULL)
    {
        m_pmNor = pNor->copy(rtArea);
    }
    else
    {
        //QDebug()<<"No Normal State Image\r\n";
        return;
    }
    if (pOver != NULL)
    {
        m_pmOver = pOver->copy(rtArea);
    }
    if (pDown != NULL)
    {
        m_pmDown = pDown->copy(rtArea);
    }
    if (pDis != NULL)
    {
        m_pmDis = pDis->copy(rtArea);
    }
    move(QPoint(rtArea.left(), rtArea.top()));
    resize(rtArea.size());
    m_pDraw = &m_pmNor;
    installEventFilter(parent);
}

CBmpButton::~CBmpButton()
{

}

void CBmpButton::enterEvent(QEvent *)
{
   m_pDraw = &m_pmOver;
   update();
}

void CBmpButton::leaveEvent(QEvent *)
{
    m_pDraw = &m_pmNor;
    update();
}

void CBmpButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (isChecked())
    {
        m_pDraw = &m_pmDown;

    }
    else if (!isEnabled())
    {
        m_pDraw = &m_pmDis;
    }
    painter.drawPixmap(0, 0, *m_pDraw);

}

void CBmpButton::SetImg(const QPixmap *pNor, const QPixmap *pOver, const QPixmap *pDown, const QPixmap *pDis, const QRect &rtArea)
{
    if (pNor != NULL)
    {
        m_pmNor = pNor->copy(rtArea);
    }
    if (pOver != NULL)
    {
        m_pmOver = pOver->copy(rtArea);
    }
    if (pDown != NULL)
    {
        m_pmDown = pDown->copy(rtArea);
    }
    if (pDis != NULL)
    {
        m_pmDis = pDis->copy(rtArea);
    }
    move(QPoint(rtArea.left(), rtArea.top()));
    resize(rtArea.size());
    m_pDraw = &m_pmNor;
}
