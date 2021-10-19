#include "cimgstatearea.h"

CImgStateArea::CImgStateArea(QPixmap *pimgNor, QPixmap *pimgPackUp,
                             const QPoint &ptNor, const QPoint &ptPackUp, QWidget *parent):QPushButton(parent)
{
    m_pDraw = NULL;
    m_pImgNor = NULL;
    m_pImgPackUp = NULL;
    m_bPackUp = false;

    if (pimgNor != NULL)
    {
        m_pImgNor = pimgNor;
    }
    else
    {
        //QDebug()<<"No Normal State Image\r\n";
        return;
    }
    if (pimgPackUp != NULL)
    {
        m_pImgPackUp = pimgPackUp;
    }
    m_ptNor = ptNor;
    m_ptPackUp = ptPackUp;

    move(ptNor);
    resize(m_pImgNor->size());
    m_pDraw = m_pImgNor;
    installEventFilter(parent);
}

CImgStateArea::~CImgStateArea()
{

}

void CImgStateArea::SwitchShowState(const bool &bPackUp)
{
    if (bPackUp)
    {
       m_pDraw = m_pImgPackUp;
       //move(m_ptPackUp);
    }
    else
    {
       m_pDraw = m_pImgNor;
       //move(m_ptNor);
    }
    m_bPackUp = bPackUp;
    update();
}

void CImgStateArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    resize(m_pDraw->size());
    painter.drawPixmap(0, 0, *m_pDraw);
}

bool CImgStateArea::IsPackUp()
{
    return m_bPackUp;
}
