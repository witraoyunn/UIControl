#ifndef CBMPBUTTON_H
#define CBMPBUTTON_H

#include "qpushbutton.h"

class CBmpButton : public QPushButton
{
public:
    // 按钮的图片从一整张图中抠出来，需要将整张界面的四个状态的图片指针传入
    CBmpButton(const QPixmap *pNor, const QPixmap *pOver, const QPixmap *pDown,
               const QPixmap *pDis, const QRect &rtArea, QWidget *parent = Q_NULLPTR);
    ~CBmpButton();
    void SetImg(const QPixmap *pNor, const QPixmap *pOver, const QPixmap *pDown, const QPixmap *pDis, const QRect &rtArea);

private:
    QPixmap m_pmNor;
    QPixmap m_pmOver;
    QPixmap m_pmDown;
    QPixmap m_pmDis;
    QPixmap *m_pDraw;

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    virtual void paintEvent(QPaintEvent *);

};

#endif // CBMPBUTTON_H
