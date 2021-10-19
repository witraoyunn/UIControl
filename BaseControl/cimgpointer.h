#ifndef CIMGPOINTER_H
#define CIMGPOINTER_H

#include "qpushbutton.h"
#include "QPainter"

// 该自绘控件用于仪表盘指针 具备实施设置角度效果 并且可以设置角度旋转原点
class CImgPointer : public QPushButton
{
public:
    CImgPointer(QPixmap *pImage, const QPoint &ptImgStart, const QPoint &ptLeftTop,
                const QSize &size, QWidget *parent = Q_NULLPTR);
    ~CImgPointer();

    void ShowNewAngle(qreal angle, bool bH = true);     // bH参数为了区分水平是逆时针小角度，垂直是顺时针小角度

private:
    QPixmap *m_pImgShow;
    QPoint m_ptImgStart;        // 绘制图片的起点 从控件中心点的偏移
    qreal m_rlAngle;            // 图片角度

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // CIMGPOINTER_H
