#include "cbmpmovebutton.h"

CBmpMoveButton::CBmpMoveButton(const QPixmap *pNor1, const QPixmap *pOver1, const QPixmap *pNor2, const QPixmap *pOver2,
                               const QRect &rtArea1, const QRect &rtArea2, const QPoint &ptA, const QPoint &ptB, QWidget *parent)
    :QPushButton(parent)
{
    m_pDraw = NULL;
    m_pDrawNor = NULL;
    m_pDrawOver = NULL;

    if (pNor1 != NULL)
    {
        m_pmNor1 = pNor1->copy(rtArea1);
    }
    else
    {
        //QDebug()<<"No Normal State Image\r\n";
        return;
    }
    if (pOver1 != NULL)
    {
        m_pmOver1 = pOver1->copy(rtArea1);
    }
    if (pNor2 != NULL)
    {
        m_pmNor2 = pNor2->copy(rtArea2);
    }
    else
    {
        //QDebug()<<"No Normal State Image\r\n";
        return;
    }
    if (pOver2 != NULL)
    {
        m_pmOver2 = pOver2->copy(rtArea2);
    }

    m_ptA = ptA;
    m_ptB = ptB;

    move(m_ptA);
    m_bInA = true;
    m_pDrawNor = &m_pmNor1;
    m_pDrawOver = &m_pmOver1;
    resize(rtArea1.size());
    m_pDraw = &m_pmNor1;
    installEventFilter(parent);

    m_rtAreaA = rtArea1;
    m_rtAreaB = rtArea2;
}

CBmpMoveButton::~CBmpMoveButton()
{
    m_pDraw = NULL;
}

void CBmpMoveButton::SetShowState(const int &nState)
{
    switch (nState)
    {
    case 1:
        m_pDrawNor = &m_pmNor1;
        m_pDrawOver = &m_pmOver1;
        resize(m_rtAreaA.size());
        break;
    case 2:
        m_pDrawNor = &m_pmNor2;
        m_pDrawOver = &m_pmOver2;
        resize(m_rtAreaB.size());
        break;
    default:
        m_pDrawNor = &m_pmNor1;
        m_pDrawOver = &m_pmOver1;
        resize(m_rtAreaA.size());
        break;
    }
    m_pDraw = m_pDrawNor;
}

bool CBmpMoveButton::ButtonInA()
{
    return m_bInA;
}

void CBmpMoveButton::SetAPoint(const QPoint &ptA)
{
    m_ptA = ptA;
}

void CBmpMoveButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, *m_pDraw);
}

bool CBmpMoveButton::event(QEvent *e)
{
    if (e->type() == QEvent::MouseButtonRelease)
    {
        if (m_bInA)
        {
            SetShowState(2);
            move(m_ptB);
        }
        else
        {
            SetShowState(1);
            move(m_ptA);
        }
        m_bInA = !m_bInA;
    }
    update();
    return QPushButton::event(e);
}


void CBmpMoveButton::enterEvent(QEvent *)
{
   m_pDraw = m_pDrawOver;
   update();
}

void CBmpMoveButton::leaveEvent(QEvent *)
{
    m_pDraw = m_pDrawNor;
    update();
}

