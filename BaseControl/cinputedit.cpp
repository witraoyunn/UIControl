#include "cinputedit.h"
#include "qpainter.h"

CInputEdit::CInputEdit(const QPixmap *pNor, const QPixmap *pOver, const QRect &rtArea, QWidget *parent)
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

    move(QPoint(rtArea.left(), rtArea.top()));
    resize(rtArea.size());
    m_pDraw = &m_pmNor;
    installEventFilter(parent);
    m_bEditNow = false;

    QPalette pal;
    pal.setColor(QPalette::ButtonText, QColor(120,193,255));
    setPalette(pal);
}
CInputEdit::~CInputEdit()
{

}

void CInputEdit::enterEvent(QEvent *)
{
   m_pDraw = &m_pmOver;
   update();
}

void CInputEdit::leaveEvent(QEvent *)
{
    m_pDraw = &m_pmNor;
    update();
}

void CInputEdit::EditNow(bool bEdit)
{
    m_bEditNow = bEdit;
}

void CInputEdit::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (m_bEditNow)
    {
        m_pDraw = &m_pmOver;
    }
    else
    {
        m_pDraw = &m_pmNor;
    }
    painter.drawPixmap(0, 0, *m_pDraw);
    painter.drawText(rect(), Qt::AlignHCenter|Qt::AlignVCenter, m_strInput);
}

void CInputEdit::keyPressEvent(QKeyEvent *event)
{
    if (!m_bEditNow)
    {
        return;
    }
    if (event->key() == Qt::Key_Backspace)
    {
        m_strInput.remove(-1, 1);
        update();
    }
    else if (event->key() == Qt::Key_0
             ||event->key() == Qt::Key_1
             ||event->key() == Qt::Key_2
             ||event->key() == Qt::Key_3
             ||event->key() == Qt::Key_4
             ||event->key() == Qt::Key_5
             ||event->key() == Qt::Key_6
             ||event->key() == Qt::Key_7
             ||event->key() == Qt::Key_8
             ||event->key() == Qt::Key_9
             ||event->key() == Qt::Key_NumberSign
             ||event->key() == Qt::Key_Period)
    {
        m_strInput += event->text();
        update();
    }
}

QString CInputEdit::GetInput()
{
    return m_strInput;
}

float CInputEdit::GetInputNum()
{
    float fRet = 0;

    // 将m_strInput转化成float

    return fRet;

}

void CInputEdit::ClearData()
{
    m_strInput.clear();
    update();
}
