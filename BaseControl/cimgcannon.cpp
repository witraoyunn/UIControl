#include "cimgcannon.h"

CImgCannon::CImgCannon(const QString &strCurDir, const QRect &rtArea, QWidget *parent):QPushButton(parent)
{
    move(QPoint(rtArea.left(), rtArea.top()));
    resize(rtArea.size());

    for (int i = 0; i < 114; i++)
    {
        for (int j = 0; j<301; j++)
        {
            m_ppImageCannon[i][j] = NULL;
        }
    }
    LoadImageCannon(strCurDir);
}

CImgCannon::~CImgCannon()
{
    for (int i = 0; i<114; i++)
    {
        for (int j=0; j<301; j++)
        {
            delete m_ppImageCannon[i][j];
            m_ppImageCannon[i][j] = NULL;
        }
        //delete []m_ppImageCannon[i];
    }
    //delete []m_ppImageCannon;
}

void CImgCannon::LoadImageCannon(const QString &strCurDir)
{
    QString strDir;
    QString strFolder;
    QString strFileName;

    for (int i = 43; i<44; i++)
    {
        strFolder = QString("/images/vedioimages/%1v/").arg(i).arg(1);
        for (int j=0; j<100; j++)
        {
            strFileName = QString("h (%1).jpg").arg(j+1).arg(1);
            strDir = strCurDir + strFolder + strFileName;
            m_ppImageCannon[i][j] = new QPixmap(strDir);
        }
    }

    m_pDraw = m_ppImageCannon[43][60];
}

void CImgCannon::ShowCurAngle(const int &nv, const int &nh)
{
    if (nv < 0 || nv >= 114)        // 必须做判断 防止数组越界
    {
        return;
    }
    if (nh < 0 || nh >= 301)
    {
        return;
    }
//    int nhTemp = 301 - nh;
    m_pDraw = m_ppImageCannon[nv][nh];
    update();
}


void CImgCannon::paintEvent(QPaintEvent *)
{
    if (!m_pDraw)
    {
        return;
    }

    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0), *m_pDraw, m_pDraw->rect());
}
