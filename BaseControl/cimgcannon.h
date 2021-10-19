#ifndef CIMGCANNON_H
#define CIMGCANNON_H

#include "qpushbutton.h"
#include "QPainter"

// 用于展示舰炮的动态效果
class CImgCannon : public QPushButton
{
public:
    CImgCannon(const QString &strCurDir,const QRect &rtArea, QWidget *parent = Q_NULLPTR);
    ~CImgCannon();

public:
    void ShowCurAngle(const int &nv, const int &nh);        // 显示当前的角度状态

private:
    QPixmap *m_ppImageCannon[114][301];                     // 保存图片数据
    QPixmap *m_pDraw;

    void LoadImageCannon(const QString &strCurDir);         // 将舰炮数据加载进来

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // CIMGCANNON_H
