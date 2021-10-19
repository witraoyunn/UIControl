#ifndef CCURVESHOW_H
#define CCURVESHOW_H

#include "QDateTime"
#include "qpushbutton.h"
#include "./DataManager/cdatamanager.h"

// 本类用于绘制曲线
class CCurveShow : public QPushButton
{
    Q_OBJECT
public:
    CCurveShow(const QPixmap *pImg, const QRect &rtArea, QWidget *parent = Q_NULLPTR);
    ~CCurveShow();

    bool m_bZero;
    void StartStopDrawLine(bool bStart);        // 是否开始绘制
    void DrawLinesV(const TVAngle &tVAngle);         // 绘制垂直运动曲线
    void DrawLinesH(const THAngle &tHAngle);         // 绘制水平运动曲线
private:
    QPixmap m_imgShow;
    QRect m_rtRect;
    QSize m_size;
    bool m_bDrawNow;
    qint64 m_nMsecStart;        // 记录开始绘制的时间点 作为横坐标轴的原点

    QList<QPointF> m_lstSpeed;       // 计算好了之后将需要绘制的点保存在这里
    QList<QPointF> m_lstError;

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // CCURVESHOW_H
