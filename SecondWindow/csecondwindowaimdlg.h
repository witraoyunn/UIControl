#ifndef CSECONDWINDOWAIMDLG_H
#define CSECONDWINDOWAIMDLG_H

#include <QDialog>

namespace Ui {
class CSecondWindowAimDlg;
}

class CSecondWindowAimDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CSecondWindowAimDlg(QWidget *parent = 0);
    ~CSecondWindowAimDlg();

private:
    Ui::CSecondWindowAimDlg *ui;

    QPixmap *m_pMainImgNor;          // 主界面Nor图片
    QPixmap *m_pMainImgOver;         // 主界面Over图片
    QPixmap *m_pMainImgDown;         // 主界面Down图片
    QPixmap *m_pMainImgDis;          // 主界面Disable图片

    void InitSkins();                // 将界面图片资源加载到内存

    void paintEvent(QPaintEvent *);
};

#endif // CSECONDWINDOWAIMDLG_H
