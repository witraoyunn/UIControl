#include "ccurveshow.h"
#include "qpainter.h"
#include "QDebug"
CCurveShow::CCurveShow(const QPixmap *pImg, const QRect &rtArea, QWidget *parent)
    :QPushButton(parent)
{
    m_bDrawNow = false;
    m_bZero = true;

    if (pImg != NULL)
    {
        m_imgShow = pImg->copy(rtArea);
    }
    else
    {
        //QDebug()<<"No Normal State Image\r\n";
        return;
    }

    m_rtRect = rtArea;
    m_size = rtArea.size();
    move(QPoint(rtArea.left(), rtArea.top()));
    resize(m_size);

    //connect(parent, SIGNAL(SigDrawCurveV(int)), this, SLOT(slotDrawCurve(int)));
    //connect(parent, SIGNAL(SigDrawCurveH(int)), this, SLOT(slotDrawCurve(int)));
}

CCurveShow::~CCurveShow()
{
}

void CCurveShow::StartStopDrawLine(bool bStart)
{
    QDateTime dtStart;

    m_bDrawNow = bStart;
    if (bStart)
    {
        m_lstSpeed.clear();
        m_lstError.clear();
        m_nMsecStart = dtStart.currentDateTime().toMSecsSinceEpoch();
    }
}

void CCurveShow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!isVisible())
    {
        painter.drawPixmap(0, 0, m_imgShow);
    }

    if (m_bDrawNow)
    {
        QPen pen;
        pen.setColor(QColor(248,124,64));
        pen.setWidth(1);
        painter.setPen(pen);

        QList<QPointF>::iterator it;
        for (it = m_lstSpeed.begin(); it!=m_lstSpeed.end(); it++)
        {
            //painter.drawLine(m_ptLastSpeed, m_ptDesSpeed);
            QPointF pt = *it;
            painter.drawPoint(QPointF(pt));
        }

        pen.setColor(QColor(0,255,219));
        painter.setPen(pen);
        QList<QPointF>::iterator itE;
        for (itE = m_lstError.begin(); itE!=m_lstError.end(); itE++)
        {
            //painter.drawLine(m_ptLastSpeed, m_ptDesSpeed);
            QPointF pt = *itE;
            painter.drawPoint(pt);
        }
    }


}

// 绘制方式跟水平角度绘制方式一样，分开写是因为对应的角度范围不一样
void CCurveShow::DrawLinesV(const TVAngle &tVAngle)
{
    // 绘制垂直运动速度曲线和误差曲线
    // 首先根据时间和速度值将速度转化为坐标
    // 然后根据坐标调用painter的DrawLine函数直接绘制对应颜色
    if (!m_bDrawNow)        // 开始绘制的时候这个变量置为真
    {
        return;
    }

    QPointF ptDesSpeed, ptDesError;
    int nRangle = 200;      // 界面上的Y值范围（角度范围）正负100°

    // 转化速度坐标并绘制
//    float fTemp = tVAngle.fAngle / ((float)nRangle);
    float fTemp = 0 / ((float)nRangle);
    int nySpeed = m_size.height() * fTemp;       // 水平角度 记录正负150度 10000ms
    if (nySpeed >= 0)
    {
        nySpeed = (m_size.height() / 2) - nySpeed;
    }
    else
    {
        nySpeed = (m_size.height() / 2) + nySpeed;
    }
    ptDesSpeed.setY(nySpeed);


    QDateTime dateTime = QDateTime::currentDateTime();
    qint64 nMSecNow = dateTime.toMSecsSinceEpoch();

    qint64 nDev = nMSecNow - m_nMsecStart;

    QDateTime dtStart2;
    if(nDev>100000)
    {
        m_nMsecStart = dtStart2.currentDateTime().toMSecsSinceEpoch();

        m_lstError.clear();
        m_lstSpeed.clear();

    }

    fTemp = ((float)nDev)/((float)100000);
    int nx = m_size.width() * fTemp;
    ptDesSpeed.setX(nx);
    m_lstSpeed.push_back(ptDesSpeed);


    // 转化误差坐标并绘制
    nRangle = 10;
    fTemp = tVAngle.fError / ((float)nRangle);
    int nyError = m_size.height() * fTemp;       // 水平角度 记录正负150度 10000ms
    if (nyError >= 0)
    {
        nyError = (m_size.height() / 2) - nyError;
    }
    else
    {
        nyError = (m_size.height() / 2) + nyError;
    }
    ptDesError.setY(nyError);
    ptDesError.setX(nx);
    m_lstError.push_back(ptDesError);

    update();
}

void CCurveShow::DrawLinesH(const THAngle &tHAngle)
{
    // 绘制水平运动速度曲线和误差曲线
    // 首先根据时间和速度值将速度转化为坐标
    // 然后根据坐标调用painter的DrawLine函数直接绘制对应颜色
    if (!m_bDrawNow)        // 开始绘制的时候这个变量置为真
    {
        return;
    }

    QPointF ptDesSpeed, ptDesError;
    int nRangle = 300;      // 界面上的Y值范围（角度范围）正负150°

    // 转化速度坐标并绘制
    float fTemp = tHAngle.fAngle/((float)nRangle);
    int nySpeed = m_size.height() * fTemp;       // 水平角度 记录正负150度 10000ms
    if (nySpeed >= 0)
    {
        nySpeed = (m_size.height()/2) - nySpeed;
    }
    else
    {
        nySpeed = (m_size.height()/2) + nySpeed;
    }
//    ptDesSpeed.setY(nySpeed);

    QDateTime dateTime = QDateTime::currentDateTime();
    qint64 nMSecNow = dateTime.toMSecsSinceEpoch();
    qint64 nDev = nMSecNow - m_nMsecStart;




    QDateTime dtStart2;
    if(nDev>100000)
    {
        m_nMsecStart = dtStart2.currentDateTime().toMSecsSinceEpoch();

        m_lstError.clear();
        m_lstSpeed.clear();

    }

    fTemp = ((float)nDev)/((float)100000);
    int nx = m_size.width() * fTemp;
    ptDesSpeed.setX(nx);

//    if(m_bZero)
//    {
//        ptDesSpeed.setY(0);
//    }
//    else
//    {
        ptDesSpeed.setY(nySpeed);
        ptDesSpeed.setX(nx);
//    }



    m_lstSpeed.push_back(ptDesSpeed);
    update();


    // 转化误差坐标并绘制
    nRangle = 10;
    fTemp = tHAngle.fError / ((float)nRangle);
    int nyError = fTemp * m_size.height();       // 水平角度 记录正负150度 10000ms
    if (nyError >= 0)
    {
        nyError = (m_size.height()/2) - nyError;
    }
    else
    {
        nyError = (m_size.height()/2) + nyError;
    }
    ptDesError.setY(nyError);
    ptDesError.setX(nx);

    m_lstError.push_back(ptDesError);
    update();

    // 转化误差坐标并绘制
//    nRangle = 10;
//    fTemp = tHAngle.fError / ((float)nRangle);
//    int nyError = fTemp * m_size.height();       // 水平角度 记录正负150度 10000ms
//    if (nyError >= 0)
//    {
//        nyError = (m_size.height()/2) - nyError;
//    }
//    else
//    {
//        nyError = (m_size.height()/2) + nyError;
//    }
//    ptDesError.setY(nyError);
//    ptDesError.setX(nx);

//    m_lstError.push_back(ptDesError);
//    update();
}
