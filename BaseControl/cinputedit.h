#ifndef CINPUTEDIT_H
#define CINPUTEDIT_H

#include "qpushbutton.h"
#include <QKeyEvent>

// 用于实现图片界面上的图片类型的输入框，实现原理为实际上是一个按钮，整个页面的输入框互斥，当选中了之后
// 将状态置为Over状态，获取keyevent事件，将输入信息通过string的方式实时显示到界面，并通过全局变量记录
class CInputEdit : public QPushButton
{
public:
    CInputEdit(const QPixmap *pNor, const QPixmap *pOver, const QRect &rtArea, QWidget *parent = Q_NULLPTR);
    ~CInputEdit();
    void EditNow(bool bEdit);
    QString GetInput();
    float GetInputNum();
    void ClearData();

private:
    QPixmap m_pmNor;
    QPixmap m_pmOver;
    QPixmap *m_pDraw;
    QString m_strInput;
    bool m_bEditNow;
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // CINPUTEDIT_H
