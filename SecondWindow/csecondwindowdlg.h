#ifndef CSECONDWINDOWDLG_H
#define CSECONDWINDOWDLG_H

#include <QDialog>
#include "QMouseEvent"

namespace Ui {
class CSecondWindowDlg;
}

class CSecondWindowDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CSecondWindowDlg(QString strCurDir, QWidget *parent = 0);
    ~CSecondWindowDlg();

private:
    Ui::CSecondWindowDlg *ui;

    QPixmap *m_pMainImgNor;          // 主界面Nor图片
    QPixmap *m_pMainImgOver;         // 主界面Over图片
    QPixmap *m_pMainImgDown;         // 主界面Down图片
    QPixmap *m_pMainImgDis;          // 主界面Disable图片
    QPoint m_ptWindowPosPress;       // 保存鼠标左键按下时候的窗口位置
    QPoint m_ptGlobalPos;            // 保存鼠标左键按下时的鼠标位置
    QPoint m_ptDlgPos;               // 移动后窗口所在的位置
    QString m_strDir;

    void InitSkins();                // 将界面图片资源加载到内存

    void paintEvent(QPaintEvent *);
    //void mousePressEvent(QMouseEvent *event);   //  用于拖拽窗口
    //void mouseMoveEvent(QMouseEvent *event);    //  用于拖拽窗口
};

#endif // CSECONDWINDOWDLG_H
