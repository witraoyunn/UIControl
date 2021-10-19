#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include "qpoint.h"
#include "QMouseEvent"
#include "QPushButton"
#include "./Comm/ccomcan.h"
#include "./BaseControl/cbmpbutton.h"
#include "./BaseControl/cbmpstate.h"
#include "./SecondWindow/csecondwindowdlg.h"
#include "./SecondWindow/csecondwindowaimdlg.h"
#include "./BaseControl/cbmppointer.h"
#include "./BaseControl/cbmpmovebutton.h"
#include "./BaseControl/cimgcannon.h"
#include "./BaseControl/cimgpointer.h"
#include "./BaseControl/cimgstatearea.h"
#include "./BaseControl/ccurveshow.h"
#include "./BaseControl/cinputedit.h"
#include "./Comm/ccomudp.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString strAppPath, QWidget *parent = 0);
    ~MainWindow();
    void SwitchSecondWindow(int nType);      // 切换第二屏的软件界面 0：仓库界面  1：光电瞄准界面

    QString m_strCurPath;

private:
    Ui::MainWindow *ui;
    CSecondWindowDlg *m_pSecondWindowDlg;    // 第二屏的仓库界面
    CSecondWindowAimDlg *m_pSecondWinAimDlg; // 第二屏的光电瞄准界面

    // 主界面
    QPixmap *m_pImgMainHideNor;         // 关键状态隐藏时初始化图片
    QPixmap *m_pImgMainShow;         // 当前显示的主页背景
    QPixmap *m_pImgMainNor;         // 当前显示的主页背景
    QPixmap *m_pImgMainOver;         // 当前显示的主页背景
    QPixmap *m_pImgMainDown;         // 当前显示的主页背景
    QPixmap *m_pMainImgDis;         // 当前显示的主页背景
    QPixmap *m_pImgPointerH;         // 主界面仪表盘指针
    QPixmap *m_pImgPointerV;         // 主界面仪表盘指针

    CBmpButton *m_pBtnClose;         // 关闭按钮
    CBmpState *m_pBtnDateTime;       // 显示时间控件
    CImgCannon *m_pBtnCanon;         // 舰炮三维形状
    CImgPointer *m_pBtnPointerH;     // 水平角仪表盘指针控件
    CImgPointer *m_pBtnPointerV;     // 垂直角仪表盘指针控件
    CBmpMoveButton *m_pBtnStateGroup;// 状态收放按钮
    CBmpButton *m_pBtnShoot;         // 射击
    CBmpButton *m_pBtnSup;           // 补供
    CBmpButton *m_pBtnRepair;        // 维修
    CBmpButton *m_pBtnReset;         // 复位
    CBmpButton *m_pBtnShowRecord;    // 记录显示
    CBmpState *m_pBtnHAngle;         // 水平角度
    CBmpState *m_pBtnHError;         // 水平角度误差
    CBmpState *m_pBtnVAngle;         // 上下角度
    CBmpState *m_pBtnVError;         // 上下角度误差
    CBmpState *m_ppBtnState[28];     // 28个关键状态按钮

    // 系统界面
    CImgPointer *m_pBtnPointerSysH;     // 水平角仪表盘指针控件
    CImgPointer *m_pBtnPointerSysV;     // 垂直角仪表盘指针控件
    QPixmap *m_pImgMainSysHideNor;      // 主界面Nor图片
    QPixmap *m_pImgMainSysNor;          // 主界面Nor图片
    QPixmap *m_pImgMainSysOver;         // 主界面Over图片
    QPixmap *m_pImgStateAreaNor;        //
    QPixmap *m_pImgStateAreaPackUp;     //
    QPixmap *m_pImgInputAreaNor;        //
    QPixmap *m_pImgInputAreaPackUp;     //
    QPixmap *m_pImgInputAreaOver;
    QPixmap *m_pImgNoticeAreaNor;       //
    QPixmap *m_pImgNoticeAreaPackUp;    //
    QPixmap *m_pImgSysPointerV;         // 主界面舰炮炮管
    QPixmap *m_pImgYaoKong;

    CImgPointer *m_pBtnSysPointerV;
    CImgStateArea *m_pBtnSysYaoKong;

    CBmpButton *m_pBtnSys;
    CBmpButton *m_pBtnLocal;
    CBmpButton *m_pBtnAsLocal;
    CBmpButton *m_pBtnInputSys[4];      // 4个输入按钮
    CImgStateArea *m_pBtnShowState;
    CImgStateArea *m_pBtnInputState;
    CImgStateArea *m_pBtnNoticeState;

    CBmpState *m_pBtnAngleH;            // 方位角度
    CBmpState *m_pBtnErrorH;            // 方位误差
    CBmpState *m_pBtnUpAngleH;          // 上扬角度
    CBmpState *m_pBtnUpErrorH;          // 上扬误差
    CBmpState *m_pBtnPosCmdH;           // 位置指令
    CBmpState *m_pBtnSpeedCmdH;         // 速度指令

    CBmpState *m_pBtnAngleV;            // 高低位置
    CBmpState *m_pBtnErrorV;            // 高低误差
    CBmpState *m_pBtnBaiAngleV;         // 摆位置
    CBmpState *m_pBtnBaiErrorV;         // 摆误差
    CBmpState *m_pBtnPosCmdV;           // 位置指令
    CBmpState *m_pBtnSpeedCmdV;         // 速度指令
    CInputEdit *m_pCInputSys[4];      // 8个输入框

    // 随动联调
    QPixmap *m_pImgMainRepairNor;          // 主界面Nor图片
    QPixmap *m_pImgMainRepairOver;         // 主界面Over图片
    QPixmap *m_pImgRepairState;
    QPixmap *m_pImgSingalShowNor;
    QPixmap *m_pImgSingalShowPackUp;
    QPixmap *m_pImgRepairSport;
    QPixmap *m_pImgRepairRecord;
    QPixmap *m_pImgRepairSuiD;
    QPixmap *m_pImRepairStateCheck;

    CImgStateArea *m_PBtnStateCheck;
    CImgStateArea *m_pBtnSignalShowState;
    CImgStateArea *m_pBtnSport1;
    CImgStateArea *m_pBtnSport2;
    CImgStateArea *m_pBtnRecrd;
    CImgStateArea *m_pImgSuiD;
    CImgStateArea *m_pImgStateCheck;


    CBmpButton *m_pBtnSuiD;
    CBmpButton *m_pBtnFangW;
    CBmpButton *m_pBtnGaodi;
    CBmpButton *m_pBtnShangY;
    CBmpButton *m_pBtnBai;
    CBmpButton *m_pBtnAllS;
    CBmpButton *m_pBtnStateShow;


    CCurveShow *m_pCurveShowV;        // 绘制水平运动曲线
    CCurveShow *m_pCurveShowH;        // 绘制垂直运动曲线
    CBmpButton *m_pBtnCurve[14];      // 14个联调按钮
    CInputEdit *m_pCInputCurve[10];   // 10个输入框



    int m_nTimerID;                   // 时间显示控件的定时器ID
    CDataManager *m_pDataManager;     // 用于数据互斥
    CComCan *m_pCommCan;              // 用于Can通信
    emPage m_pageCur;                 // 保存当前页面状态
    CDataManager *m_pDataManager_Udp;     // 用于数据互斥
    ccomudp *m_pCcomUdp;

private:
    // 用于窗口拖动
    QPoint m_ptWindowPosPress;       // 保存鼠标左键按下时候的窗口位置
    QPoint m_ptGlobalPos;            // 保存鼠标左键按下时的鼠标位置
    QPoint m_ptDlgPos;               // 移动后窗口所在的位置
    void mousePressEvent(QMouseEvent *event);   //  用于拖拽窗口
    void mouseMoveEvent(QMouseEvent *event);    //  用于拖拽窗口


private:
    void InitSkins();                // 将界面图片资源加载到内存
    void CloseWindow();              // 将程序所有窗口关闭
    void ShowStateBtn(bool bShow);   // 显示/隐藏状态显示按钮
    //void ShowShootSysPage(bool bShow);// 显示/隐藏系统界面
    void ShowPage(emPage pageTo);

    void paintEvent(QPaintEvent *);
    virtual void timerEvent(QTimerEvent *event);    //  用于显示时间

protected:
    bool eventFilter(QObject *watched, QEvent *event);      // 按钮操作路由

public slots:
    void slotUpdateUIData(int nRecvType);
signals:
    void SigDrawCurveV(int nRecvType);
    void SigDrawCurveH(int nRecvType);


};

#endif // MAINWINDOW_H
