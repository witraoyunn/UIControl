#ifndef CBMPMOVEBUTTON_H
#define CBMPMOVEBUTTON_H

#include "qpushbutton.h"
#include "QPainter"
#include <QEvent>

// 可以移动位置的图片按钮 单击可以让按钮位置在A和B之间切换
class CBmpMoveButton : public QPushButton
{
public:
    CBmpMoveButton(const QPixmap *pNor1, const QPixmap *pOver1, const QPixmap *pNor2, const QPixmap *pOver2,
                   const QRect &rtArea1, const QRect &rtArea2, const QPoint &ptA, const QPoint &ptB, QWidget *parent = Q_NULLPTR);
    ~CBmpMoveButton();

    void SetShowState(const int &nState);           // 0：正常 1：有异常  2：spare
    bool ButtonInA();
    void SetAPoint(const QPoint &ptA);              // 改变A点位置
private:
    QPixmap m_pmNor1;
    QPixmap m_pmOver1;
    QPixmap m_pmNor2;
    QPixmap m_pmOver2;

    QPixmap *m_pDrawNor;
    QPixmap *m_pDrawOver;
    QPixmap *m_pDraw;

    QPoint m_ptA;
    QPoint m_ptB;
    bool m_bInA;        // 判断当前按钮位置在哪里

    QRect m_rtAreaA;
    QRect m_rtAreaB;

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual bool event(QEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

#endif // CBMPMOVEBUTTON_H
