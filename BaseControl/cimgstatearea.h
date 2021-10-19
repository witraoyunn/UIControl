#ifndef CIMGSTATEAREA_H
#define CIMGSTATEAREA_H

#include "qpushbutton.h"
#include "QPainter"

class CImgStateArea : public QPushButton
{
public:
    CImgStateArea(QPixmap *pimgNor, QPixmap *pimgPackUp,
               const QPoint &ptNor, const QPoint &ptPackUp, QWidget *parent = Q_NULLPTR);
    ~CImgStateArea();

    void SwitchShowState(const bool &bPackUp);
    bool IsPackUp();
private:
    QPixmap *m_pDraw;
    QPixmap *m_pImgNor;
    QPixmap *m_pImgPackUp;

    QPoint m_ptNor;
    QPoint m_ptPackUp;
    bool m_bPackUp;

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // CIMGSTATEAREA_H
