#ifndef CBMPSTATE_H
#define CBMPSTATE_H

#include "qpushbutton.h"
#include "QPainter"
#include "QBrush"


// 该自绘控件用于图片状态显示功能，支持三种图片状态，并且可以显示文字
class CBmpState : public QPushButton
{
public:
    CBmpState(const QPixmap *pStateImg1, const QPixmap *pStateImg2, const QPixmap *pStateImg3,
               const QRect &rtArea, QWidget *parent = Q_NULLPTR);
    ~CBmpState();

    void SetShowText(const QString &strText, const QColor &color, const QFont &font);
    void SetShowText(const QString &strText);
    void SetShowState(const int &nState);           // 0：初始化 1：正常  2：异常
    void SetTextColor(const QColor &color);
private:
    QPixmap *m_pDraw;
    QPixmap m_stateImg1;
    QPixmap m_stateImg2;
    QPixmap m_stateImg3;

    QString m_strText;

protected:
    virtual void paintEvent(QPaintEvent *);

};

#endif // CBMPSTATE_H
