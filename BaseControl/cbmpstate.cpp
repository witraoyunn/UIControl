#include "cbmpstate.h"

CBmpState::CBmpState(const QPixmap *pStateImg1, const QPixmap *pStateImg2, const QPixmap *pStateImg3,
                                   const QRect &rtArea, QWidget *parent)
                :QPushButton(parent)
{
    m_pDraw = NULL;

    if (pStateImg1 != NULL)
    {
        m_stateImg1 = pStateImg1->copy(rtArea);
    }
    else
    {
        //QDebug()<<"No Normal State Image\r\n";
        return;
    }
    if (pStateImg2 != NULL)
    {
        m_stateImg2 = pStateImg2->copy(rtArea);
    }
    if (pStateImg3 != NULL)
    {
        m_stateImg3 = pStateImg3->copy(rtArea);
    }
    move(QPoint(rtArea.left(), rtArea.top()));
    resize(rtArea.size());
    m_pDraw = &m_stateImg1;
    installEventFilter(parent);
}

CBmpState::~CBmpState()
{

}

void CBmpState::SetShowText(const QString &strText)
{
    m_strText = strText;
    update();
}

void CBmpState::SetTextColor(const QColor &color)
{
    QPalette pal;
    pal.setColor(QPalette::ButtonText, color);
    setPalette(pal);
}

void CBmpState::SetShowState(const int &nState)
{
    switch (nState)
    {
    case 0:
        m_pDraw = &m_stateImg1;
        break;
    case 1:
        m_pDraw = &m_stateImg2;
        break;
    case 2:
        m_pDraw = &m_stateImg3;
        break;
    default:
        m_pDraw = &m_stateImg1;
        break;
    }
    update();
}

void CBmpState::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, *m_pDraw);
    painter.drawText(rect(), Qt::AlignHCenter|Qt::AlignVCenter, m_strText);
}
