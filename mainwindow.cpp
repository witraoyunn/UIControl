#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "QDateTime"

// 主界面 后续每个界面创建一个dig
MainWindow::MainWindow(QString strAppPath, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    m_pImgMainHideNor = NULL;
    m_pImgMainNor = NULL;
    m_pImgMainOver = NULL;
    m_pImgMainDown = NULL;
    m_pMainImgDis = NULL;

    m_pImgMainShow = NULL;
    m_pImgPointerH = NULL;
    m_pImgPointerV = NULL;

    m_pBtnClose = NULL;
    m_pBtnDateTime = NULL;
    m_pBtnCanon = NULL;
    m_pBtnPointerH = NULL;
    m_pBtnPointerV = NULL;
    m_pBtnStateGroup = NULL;
    m_pBtnShoot = NULL;
    m_pBtnSup = NULL;
    m_pBtnRepair = NULL;
    m_pBtnReset = NULL;
    m_pBtnShowRecord = NULL;
    for (int i = 0; i<28; i++)
    {
        m_ppBtnState[i] = NULL;
    }

    m_pImgMainSysHideNor = NULL;
    m_pImgMainSysNor = NULL;
    m_pImgMainSysOver = NULL;
    m_pImgStateAreaNor = NULL;
    m_pImgStateAreaPackUp = NULL;
    m_pImgInputAreaNor = NULL;
    m_pImgInputAreaOver = NULL;
    m_pImgInputAreaPackUp = NULL;
    m_pImgNoticeAreaNor = NULL;
    m_pImgNoticeAreaPackUp = NULL;
    for (int i = 0; i < 4; i++)
    {
        m_pCInputSys[i] = NULL;
    }
    for (int i = 0; i < 4; i++)
    {
        m_pBtnInputSys[i] = NULL;
    }

    m_pBtnAngleH = NULL;
    m_pBtnErrorH = NULL;
    m_pBtnUpAngleH = NULL;
    m_pBtnUpErrorH = NULL;
    m_pBtnPosCmdH = NULL;
    m_pBtnSpeedCmdH = NULL;
    m_pBtnSysPointerV = NULL;

    m_pBtnAngleV = NULL;
    m_pBtnErrorV = NULL;
    m_pBtnBaiAngleV = NULL;
    m_pBtnBaiErrorV = NULL;
    m_pBtnPosCmdV = NULL;
    m_pBtnSpeedCmdV = NULL;

    m_pImgMainRepairNor = NULL;
    m_pImgMainRepairOver = NULL;
    m_pImgRepairState = NULL;
    m_pImgSingalShowNor = NULL;
    m_pImgSingalShowPackUp = NULL;

    m_pBtnSignalShowState = NULL;
    m_PBtnStateCheck = NULL;

    m_pBtnSuiD = NULL;
    m_pBtnFangW = NULL;
    m_pBtnGaodi = NULL;
    m_pBtnShangY = NULL;
    m_pBtnBai = NULL;
    m_pBtnAllS = NULL;
    m_pBtnStateShow = NULL;
    m_pBtnSport1 = NULL;
    m_pBtnSport2 = NULL;
    for (int i = 0; i < 14; i++)
    {
        m_pBtnCurve[i] = NULL;
    }
    for (int i = 0; i < 10; i++)
    {
        m_pCInputCurve[i] = NULL;
    }
    m_pageCur = PageMain;
    m_strCurPath = strAppPath;

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);

    InitSkins();
    m_nTimerID = startTimer(1000);

    m_pSecondWindowDlg = new CSecondWindowDlg(m_strCurPath);        // 分屏的第二屏 仓库界面
    //m_pSecondWindowDlg->show();

    m_pSecondWinAimDlg = new CSecondWindowAimDlg();     // 分屏的第二屏 光电瞄准界面
    m_pSecondWinAimDlg->hide();


    m_pDataManager = new CDataManager();
    m_pCommCan = new CComCan(1);
    m_pCommCan->RegistDataManager(m_pDataManager);
    m_pCommCan->start();

    m_pCcomUdp = new ccomudp(this);
    m_pDataManager_Udp = new CDataManager();
    m_pCcomUdp->RegistDataManager(m_pDataManager);

    connect(m_pCommCan, SIGNAL(SigUpdateUIData(int)), this, SLOT(slotUpdateUIData(int)));
    connect(m_pCcomUdp, SIGNAL(SigUpdateUIData(int)), this, SLOT(slotUpdateUIData(int)));
//    connect(this, SIGNAL(SigDrawCurveV(int)), m_pCurveShowV, SLOT(slotDrawCurve(int)));
//    connect(this, SIGNAL(SigDrawCurveH(int)), m_pCurveShowH, SLOT(slotDrawCurve(int)));
}

MainWindow::~MainWindow()
{
    delete ui;

    if (m_pImgMainNor)
    {
        delete m_pImgMainNor;
        m_pImgMainNor = NULL;
    }
    if (m_pImgMainOver)
    {
        delete m_pImgMainOver;
        m_pImgMainOver = NULL;
    }
    if (m_pImgMainDown)
    {
        delete m_pImgMainDown;
        m_pImgMainDown = NULL;
    }
    if (m_pMainImgDis)
    {
        delete m_pMainImgDis;
        m_pMainImgDis = NULL;
    }
    if (m_pImgPointerH)
    {
        delete m_pImgPointerH;
        m_pImgPointerH = NULL;
    }
    if (m_pImgPointerV)
    {
        delete m_pImgPointerV;
        m_pImgPointerV = NULL;
    }

    if (m_pBtnClose)
    {
        delete m_pBtnClose;
        m_pBtnClose = NULL;
    }
    if (m_pBtnDateTime)
    {
        delete m_pBtnDateTime;
        m_pBtnDateTime = NULL;
    }
    if (m_pBtnCanon)
    {
        delete m_pBtnCanon;
        m_pBtnCanon = NULL;
    }
    if (m_pBtnPointerH)
    {
        delete m_pBtnPointerH;
        m_pBtnPointerH = NULL;
    }
    if (m_pBtnPointerV)
    {
        delete m_pBtnPointerV;
        m_pBtnPointerV = NULL;
    }
    if (m_pBtnStateGroup)
    {
        delete m_pBtnStateGroup;
        m_pBtnStateGroup = NULL;
    }
    if (m_pBtnShoot)
    {
        delete m_pBtnShoot;
        m_pBtnShoot = NULL;
    }
    if (m_pBtnSup)
    {
        delete m_pBtnSup;
        m_pBtnSup = NULL;
    }
    if (m_pBtnRepair)
    {
        delete m_pBtnRepair;
        m_pBtnRepair = NULL;
    }
    if (m_pBtnReset)
    {
        delete m_pBtnReset;
        m_pBtnReset = NULL;
    }
    if (m_pBtnShowRecord)
    {
        delete m_pBtnShowRecord;
        m_pBtnShowRecord = NULL;
    }

    if (m_pSecondWindowDlg)
    {
        delete m_pSecondWindowDlg;
        m_pSecondWindowDlg = NULL;
    }
    if (m_pDataManager)
    {
        delete m_pDataManager;
        m_pDataManager = NULL;
    }
    if (m_pCommCan)
    {
        m_pCommCan->exit();
        delete m_pCommCan;
        m_pCommCan = NULL;
    }
    for (int i = 0; i<28; i++)
    {
        delete m_ppBtnState[i];
        m_ppBtnState[i] = NULL;
    }

    if (m_pBtnHAngle)
    {
        delete m_pBtnHAngle;
        m_pBtnHAngle = NULL;
    }
    if (m_pBtnHError)
    {
        delete m_pBtnHError;
        m_pBtnHError = NULL;
    }
    if (m_pBtnVAngle)
    {
        delete m_pBtnVAngle;
        m_pBtnVAngle = NULL;
    }
    if (m_pBtnVError)
    {
        delete m_pBtnVError;
        m_pBtnVError = NULL;
    }

    if (m_pImgMainSysHideNor)
    {
        delete m_pImgMainSysHideNor;
        m_pImgMainSysHideNor = NULL;
    }
    if (m_pImgMainSysNor)
    {
        delete m_pImgMainSysNor;
        m_pImgMainSysNor = NULL;
    }
    if (m_pImgMainSysOver)
    {
        delete m_pImgMainSysOver;
        m_pImgMainSysOver = NULL;
    }
    if (m_pImgStateAreaNor)
    {
        delete m_pImgStateAreaNor;
        m_pImgStateAreaNor = NULL;
    }
    if (m_pImgStateAreaPackUp)
    {
        delete m_pImgStateAreaPackUp;
        m_pImgStateAreaPackUp = NULL;
    }
    if (m_pImgInputAreaNor)
    {
        delete m_pImgInputAreaNor;
        m_pImgInputAreaNor = NULL;
    }
    if (m_pImgInputAreaOver)
    {
        delete m_pImgInputAreaOver;
        m_pImgInputAreaOver = NULL;
    }

    if (m_pImgInputAreaPackUp)
    {
        delete m_pImgInputAreaPackUp;
        m_pImgInputAreaPackUp = NULL;
    }
    if (m_pImgNoticeAreaNor)
    {
        delete m_pImgNoticeAreaNor;
        m_pImgNoticeAreaNor = NULL;
    }
    if (m_pImgNoticeAreaPackUp)
    {
        delete m_pImgNoticeAreaPackUp;
        m_pImgNoticeAreaPackUp = NULL;
    }
    for (int i = 0; i < 4; i++)
    {
        delete m_pCInputSys[i];
        m_pCInputSys[i] = NULL;
    }
    for (int i = 0; i < 4; i++)
    {
        delete m_pBtnInputSys[i];
        m_pBtnInputSys[i] = NULL;
    }

    if (m_pBtnSysPointerV)
    {
        delete m_pBtnSysPointerV;
        m_pBtnSysPointerV = NULL;
    }
    if (m_pBtnAngleH)
    {
        delete m_pBtnAngleH;
        m_pBtnAngleH = NULL;
    }
    if (m_pBtnErrorH)
    {
        delete m_pBtnErrorH;
        m_pBtnErrorH = NULL;
    }
    if (m_pBtnUpAngleH)
    {
        delete m_pBtnUpAngleH;
        m_pBtnUpAngleH = NULL;
    }
    if (m_pBtnUpErrorH)
    {
        delete m_pBtnUpErrorH;
        m_pBtnUpErrorH = NULL;
    }
    if (m_pBtnPosCmdH)
    {
        delete m_pBtnPosCmdH;
        m_pBtnPosCmdH = NULL;
    }
    if (m_pBtnSpeedCmdH)
    {
        delete m_pBtnSpeedCmdH;
        m_pBtnSpeedCmdH = NULL;
    }
    if (m_pBtnAngleV)
    {
        delete m_pBtnAngleV;
        m_pBtnAngleV = NULL;
    }
    if (m_pBtnErrorV)
    {
        delete m_pBtnErrorV;
        m_pBtnErrorV = NULL;
    }
    if (m_pBtnBaiAngleV)
    {
        delete m_pBtnBaiAngleV;
        m_pBtnBaiAngleV = NULL;
    }
    if (m_pBtnBaiErrorV)
    {
        delete m_pBtnBaiErrorV;
        m_pBtnBaiErrorV = NULL;
    }
    if (m_pBtnPosCmdV)
    {
        delete m_pBtnPosCmdV;
        m_pBtnPosCmdV = NULL;
    }
    if (m_pBtnSpeedCmdV)
    {
        delete m_pBtnSpeedCmdV;
        m_pBtnSpeedCmdV = NULL;
    }
    if (m_pImgMainRepairOver)
    {
        delete m_pImgMainRepairOver;
        m_pImgMainRepairOver = NULL;
    }
    if (m_pImgMainRepairNor)
    {
        delete m_pImgMainRepairNor;
        m_pImgMainRepairNor = NULL;
    }
    if (m_pImgRepairState)
    {
        delete m_pImgRepairState;
        m_pImgRepairState = NULL;
    }
    if (m_pImgSingalShowNor)
    {
        delete m_pImgSingalShowNor;
        m_pImgSingalShowNor = NULL;
    }
    if (m_pImgSingalShowPackUp)
    {
        delete m_pImgSingalShowPackUp;
        m_pImgSingalShowPackUp = NULL;
    }
    if (m_pBtnSignalShowState)
    {
        delete m_pBtnSignalShowState;
        m_pBtnSignalShowState = NULL;
    }
    if (m_PBtnStateCheck)
    {
        delete m_PBtnStateCheck;
        m_PBtnStateCheck = NULL;
    }


    for (int i = 0; i<14; i++)
    {
        delete m_pBtnCurve[i];
        m_pBtnCurve[i] = NULL;
    }
    for (int i = 0; i < 10; i++)
    {
        delete m_pCInputCurve[i];
        m_pCInputCurve[i] = NULL;
    }
}

void MainWindow::InitSkins()
{
    move(QPoint(0,0));
    resize(QSize(1600,1200));

    // 1.1 加载主界面nor状态图片、over、down、disable状态图片读入内存
    QString strDir = m_strCurPath + "/images/main_work_nor.jpg";
    m_pImgMainNor = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_work_over.jpg";
    m_pImgMainOver = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_work_down.jpg";
    m_pImgMainDown = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_hide.jpg";
    m_pImgMainHideNor = new QPixmap(strDir);
    m_pImgMainShow = m_pImgMainHideNor;

    // 1.2 创建主界面按钮并初始化
    strDir = m_strCurPath + "/images/main_pointerH.png";
    m_pImgPointerH = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_pointerV.png";
    m_pImgPointerV = new QPixmap(strDir);
    m_pBtnPointerH = new CImgPointer(m_pImgPointerH, QPoint(-63,-154), QPoint(36,236), QSize(328,328), this);
    m_pBtnPointerV = new CImgPointer(m_pImgPointerV, QPoint(-163,-34), QPoint(37,793), QSize(328,328), this);
    m_pBtnPointerSysH = new CImgPointer(m_pImgPointerH, QPoint(-63,-154), QPoint(36,236), QSize(328,328), this);
    m_pBtnPointerSysV = new CImgPointer(m_pImgPointerV, QPoint(-163,-34), QPoint(37,793), QSize(328,328), this);
    m_pBtnPointerSysH->hide();
    m_pBtnPointerSysV->hide();

    // 1.2.1
    m_pBtnClose = new CBmpButton(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, m_pMainImgDis, QRect(QPoint(1556,21), QPoint(1586,49)), this);
    m_pBtnCanon = new CImgCannon(m_strCurPath,  QRect(QPoint(482,63), QPoint(1382,963)), this);

    // 1.2.2
    m_pBtnStateGroup = new CBmpMoveButton(m_pImgMainNor, m_pImgMainOver, m_pImgMainNor, m_pImgMainOver, QRect(QPoint(1530,736), QPoint(1590,797)), QRect(QPoint(1530,736), QPoint(1590,797)), QPoint(1530,736), QPoint(1530,736), this);
    m_pBtnShoot = new CBmpButton(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, m_pMainImgDis, QRect(QPoint(1530,807), QPoint(1590,868)), this);
    m_pBtnSup = new CBmpButton(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, m_pMainImgDis, QRect(QPoint(1530,877), QPoint(1590,938)), this);
    m_pBtnRepair = new CBmpButton(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, m_pMainImgDis, QRect(QPoint(1530,948), QPoint(1590,1009)), this);
    m_pBtnReset = new CBmpButton(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, m_pMainImgDis, QRect(QPoint(1530,1019), QPoint(1590,1080)), this);
    m_pBtnShowRecord = new CBmpButton(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, m_pMainImgDis, QRect(QPoint(1530,1090), QPoint(1590,1151)), this);

    m_pBtnStateGroup->setCheckable(true);
    m_pBtnShoot->setCheckable(true);
    m_pBtnSup->setCheckable(true);
    m_pBtnRepair->setCheckable(true);
    m_pBtnReset->setCheckable(true);
    m_pBtnShowRecord->setCheckable(true);

    // 1.2.3
    QFont font;
    font.setFamily("微软雅黑");
    font.setBold(true);
    font.setPointSize(14);
    font.setWeight(30);

    // 1.2.4 创建4个角度数据显示控件
    m_pBtnDateTime = new CBmpState(m_pImgMainNor, NULL, NULL, QRect(QPoint(1299,23), QPoint(1548,49)), this);
    m_pBtnHAngle = new CBmpState(m_pImgMainNor, NULL, NULL, QRect(QPoint(375,320), QPoint(457,358)), this);
    m_pBtnHError = new CBmpState(m_pImgMainNor, NULL, NULL, QRect(QPoint(375,419), QPoint(457,458)), this);
    m_pBtnVAngle = new CBmpState(m_pImgMainNor, NULL, NULL, QRect(QPoint(375,862), QPoint(457,901)), this);
    m_pBtnVError = new CBmpState(m_pImgMainNor, NULL, NULL, QRect(QPoint(375,962), QPoint(457,1001)), this);
    m_pBtnDateTime->setFont(font);
    m_pBtnDateTime->SetTextColor(QColor(120,193,255));
    m_pBtnHAngle->setFont(font);
    m_pBtnHAngle->SetTextColor(QColor(120,193,255));
    m_pBtnHError->setFont(font);
    m_pBtnHError->SetTextColor(QColor(120,193,255));
    m_pBtnVAngle->setFont(font);
    m_pBtnVAngle->SetTextColor(QColor(120,193,255));
    m_pBtnVError->setFont(font);
    m_pBtnVError->SetTextColor(QColor(120,193,255));

    // 1.2.5 创建28个关键状态按钮
    m_ppBtnState[0] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,109), QPoint(1744,159)), this);
    m_ppBtnState[1] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,109), QPoint(1805,159)), this);
    m_ppBtnState[2] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,109+64), QPoint(1744,159+64)), this);
    m_ppBtnState[3] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,109+64), QPoint(1805,159+64)), this);
    m_ppBtnState[4] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,109+64*2), QPoint(1744,159+64*2)), this);
    m_ppBtnState[5] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,109+64*2), QPoint(1805,159+64*2)), this);
    m_ppBtnState[6] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,109+64*3), QPoint(1744,159+64*3)), this);
    m_ppBtnState[7] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,109+64*3), QPoint(1805,159+64*3)), this);
    m_ppBtnState[8] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,109+64*4), QPoint(1744,159+64*4)), this);
    m_ppBtnState[9] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,109+64*4), QPoint(1805,159+64*4)), this);
    m_ppBtnState[10] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,109+64*5), QPoint(1744,159+64*5)), this);
    m_ppBtnState[11] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,109+64*5), QPoint(1805,159+64*5)), this);
    m_ppBtnState[12] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,109+64*6), QPoint(1744,159+64*6)), this);
    m_ppBtnState[13] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,109+64*6), QPoint(1805,159+64*6)), this);
    m_ppBtnState[14] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,109+64*7), QPoint(1744,159+64*7)), this);
    m_ppBtnState[15] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,109+64*7), QPoint(1805,159+64*7)), this);
    m_ppBtnState[16] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,109+64*8), QPoint(1744,159+64*8)), this);
    m_ppBtnState[17] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,109+64*8), QPoint(1805,159+64*8)), this);
    m_ppBtnState[18] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,684), QPoint(1744,734)), this);
    m_ppBtnState[19] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,684), QPoint(1805,734)), this);
    m_ppBtnState[20] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,742), QPoint(1744,801)), this);
    m_ppBtnState[21] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,742), QPoint(1805,801)), this);
    m_ppBtnState[22] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,806), QPoint(1744,861)), this);
    m_ppBtnState[23] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,806), QPoint(1805,861)), this);
    m_ppBtnState[24] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,873), QPoint(1744,923)), this);
    m_ppBtnState[25] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,873), QPoint(1805,923)), this);
    m_ppBtnState[26] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1692,933), QPoint(1744,983)), this);
    m_ppBtnState[27] = new CBmpState(m_pImgMainNor, m_pImgMainOver, m_pImgMainDown, QRect(QPoint(1753,933), QPoint(1805,983)), this);
    for (int i = 0; i<28; i++)
    {
        m_ppBtnState[i]->SetShowState(1);
        m_ppBtnState[i]->hide();
    }

    // 2.1 加载系统页面图片
    strDir = m_strCurPath + "/images/main_sys_hide_nor.jpg";
    m_pImgMainSysHideNor = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_sys_nor.jpg";
    m_pImgMainSysNor = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_sys_over .jpg";
    m_pImgMainSysOver = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/stateshow_area_nor.jpg";
    m_pImgStateAreaNor = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/stateshow_area_pickup.jpg";
    m_pImgStateAreaPackUp = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/input_area_nor.jpg";
    m_pImgInputAreaNor = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/input_area_pickup.jpg";
    m_pImgInputAreaPackUp = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/input_area_over.jpg";
    m_pImgInputAreaOver = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/notice_area_nor.jpg";
    m_pImgNoticeAreaNor = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/notice_area_pickup.jpg";
    m_pImgNoticeAreaPackUp = new QPixmap(strDir);

    strDir = m_strCurPath + "/images/main_sys_pointer.png";
    m_pImgSysPointerV = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_sys_over_part1 .jpg";
    m_pImgYaoKong = new QPixmap(strDir);

    // 2.2 创建系统页面控件并初始化
    m_pBtnSys = new CBmpButton(m_pImgMainSysNor, m_pImgMainSysOver, m_pImgMainSysOver, m_pImgMainSysNor, QRect(QPoint(1528,668), QPoint(1591,727)), this);
    m_pBtnLocal = new CBmpButton(m_pImgMainSysNor, m_pImgMainSysOver, m_pImgMainSysOver, m_pImgMainSysNor, QRect(QPoint(1531,738), QPoint(1591,800)), this);
    m_pBtnAsLocal = new CBmpButton(m_pImgMainSysNor, m_pImgMainSysOver, m_pImgMainSysOver, m_pImgMainSysNor, QRect(QPoint(1530,808), QPoint(1591,870)), this);
    m_pBtnShowState = new CImgStateArea(m_pImgStateAreaNor, m_pImgStateAreaPackUp, QPoint(1025,200), QPoint(1518,501), this);
    m_pBtnInputState = new CImgStateArea(m_pImgInputAreaNor, m_pImgInputAreaPackUp, QPoint(1027,530), QPoint(1514,797), this);
    m_pBtnNoticeState = new CImgStateArea(m_pImgNoticeAreaNor, m_pImgNoticeAreaPackUp, QPoint(1025,820), QPoint(1515,1111), this);
    m_pBtnAngleH = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(370,320), QPoint(450,360)), this);
    m_pBtnErrorH = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(460,320), QPoint(540,360)), this);
    m_pBtnUpAngleH = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(370,410), QPoint(450,445)), this);
    m_pBtnUpErrorH = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(460,410), QPoint(540,445)), this);
    m_pBtnPosCmdH = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(370,490), QPoint(450,530)), this);
    m_pBtnSpeedCmdH = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(460,495), QPoint(540,530)), this);
    m_pBtnAngleV = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(370,840), QPoint(450,880)), this);
    m_pBtnErrorV = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(460,840), QPoint(540,880)), this);
    m_pBtnBaiAngleV = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(370,930), QPoint(450,970)), this);
    m_pBtnBaiErrorV = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(460,930), QPoint(540,970)), this);
    m_pBtnPosCmdV = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(370,1020), QPoint(450,1055)), this);
    m_pBtnSpeedCmdV = new CBmpState(m_pImgMainSysNor, NULL, NULL, QRect(QPoint(460,1020), QPoint(540,1055)), this);

    m_pBtnSysPointerV = new CImgPointer(m_pImgSysPointerV, QPoint(-317,-29), QPoint(548,77), QSize(635,635), this);
    m_pBtnSysYaoKong = new CImgStateArea(m_pImgYaoKong, m_pImgYaoKong, QPoint(1528,668), QPoint(1591,727), this);

    m_pCInputSys[0] = new CInputEdit(m_pImgMainSysHideNor, m_pImgMainSysOver, QRect(QPoint(1122, 616), QPoint(1256, 650)), this);
    m_pCInputSys[1] = new CInputEdit(m_pImgMainSysHideNor, m_pImgMainSysOver, QRect(QPoint(1342, 613), QPoint(1478, 650)), this);
    m_pCInputSys[2] = new CInputEdit(m_pImgMainSysHideNor, m_pImgMainSysOver, QRect(QPoint(1122, 676), QPoint(1257, 711)), this);
    m_pCInputSys[3] = new CInputEdit(m_pImgMainSysHideNor, m_pImgMainSysOver, QRect(QPoint(1342, 673), QPoint(1478, 710)), this);
//    m_pCInputSys[4] = new CInputEdit(m_pImgMainSysHideNor, m_pImgMainSysOver, QRect(QPoint(1121, 665), QPoint(1251, 695)), this);
//    m_pCInputSys[5] = new CInputEdit(m_pImgMainSysHideNor, m_pImgMainSysOver, QRect(QPoint(1344, 665), QPoint(1475, 695)), this);
//    m_pCInputSys[6] = new CInputEdit(m_pImgMainSysHideNor, m_pImgMainSysOver, QRect(QPoint(1121, 705), QPoint(1251, 735)), this);
//    m_pCInputSys[7] = new CInputEdit(m_pImgMainSysHideNor, m_pImgMainSysOver, QRect(QPoint(1344, 705), QPoint(1475, 735)), this);

    m_pBtnInputSys[0] = new CBmpButton(m_pImgMainSysHideNor, m_pImgMainSysOver, NULL, NULL, QRect(QPoint(1053, 748), QPoint(1120,775)),this);
    m_pBtnInputSys[1] = new CBmpButton(m_pImgMainSysHideNor, m_pImgMainSysOver, NULL, NULL, QRect(QPoint(1141, 747), QPoint(1210,775)),this);
    m_pBtnInputSys[2] = new CBmpButton(m_pImgMainSysHideNor, m_pImgMainSysOver, NULL, NULL, QRect(QPoint(1232, 748), QPoint(1325,775)),this);
    m_pBtnInputSys[3] = new CBmpButton(m_pImgMainSysHideNor, m_pImgMainSysOver, NULL, NULL, QRect(QPoint(1350, 745), QPoint(1445,775)),this);

    QFont font1;
    font1.setFamily("微软雅黑");
    font1.setBold(true);
    font1.setPointSize(12);
    font1.setWeight(30);
    for (int i = 0; i<4; i++)
    {
        m_pCInputSys[i]->hide();
        m_pCInputSys[i]->setFont(font1);
    }
    for (int i = 0; i<4; i++)
    {
        m_pBtnInputSys[i]->hide();
    }

    m_pBtnSysPointerV->hide();
    m_pBtnSys->hide();
    m_pBtnSys->setCheckable(true);
    m_pBtnLocal->hide();
    m_pBtnLocal->setCheckable(true);
    m_pBtnAsLocal->hide();
    m_pBtnAsLocal->setCheckable(true);
    m_pBtnShowState->hide();
    m_pBtnInputState->hide();
    m_pBtnNoticeState->hide();
    m_pBtnAngleH->hide();
    m_pBtnSysYaoKong->hide();
    m_pBtnAngleH->setFont(font);
    m_pBtnAngleH->SetTextColor(QColor(120,193,255));
    m_pBtnErrorH->hide();
    m_pBtnErrorH->setFont(font);
    m_pBtnErrorH->SetTextColor(QColor(120,193,255));
    m_pBtnUpAngleH->hide();
    m_pBtnUpAngleH->setFont(font);
    m_pBtnUpAngleH->SetTextColor(QColor(120,193,255));
    m_pBtnUpErrorH->hide();
    m_pBtnUpErrorH->setFont(font);
    m_pBtnUpErrorH->SetTextColor(QColor(120,193,255));
    m_pBtnPosCmdH->hide();
    m_pBtnPosCmdH->setFont(font);
    m_pBtnPosCmdH->SetTextColor(QColor(120,193,255));
    m_pBtnSpeedCmdH->hide();
    m_pBtnSpeedCmdH->setFont(font);
    m_pBtnSpeedCmdH->SetTextColor(QColor(120,193,255));
    m_pBtnAngleV->hide();
    m_pBtnAngleV->setFont(font);
    m_pBtnAngleV->SetTextColor(QColor(120,193,255));
    m_pBtnErrorV->hide();
    m_pBtnErrorV->setFont(font);
    m_pBtnErrorV->SetTextColor(QColor(120,193,255));
    m_pBtnBaiAngleV->hide();
    m_pBtnBaiAngleV->setFont(font);
    m_pBtnBaiAngleV->SetTextColor(QColor(120,193,255));
    m_pBtnBaiErrorV->hide();
    m_pBtnBaiErrorV->setFont(font);
    m_pBtnBaiErrorV->SetTextColor(QColor(120,193,255));
    m_pBtnPosCmdV->hide();
    m_pBtnPosCmdV->setFont(font);
    m_pBtnPosCmdV->SetTextColor(QColor(120,193,255));
    m_pBtnSpeedCmdV->hide();
    m_pBtnSpeedCmdV->setFont(font);
    m_pBtnSpeedCmdV->SetTextColor(QColor(120,193,255));

    // 维修/随动联调界面
    strDir = m_strCurPath + "/images/main_repair_nor.jpg";
    m_pImgMainRepairNor = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_repair_over.jpg";
    m_pImgMainRepairOver = new QPixmap(strDir);

    strDir = m_strCurPath + "/images/main_repair_state_check.jpg";
    m_pImgRepairState = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_repair_signal_nor.jpg";
    m_pImgSingalShowNor = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_repair_signal_over.jpg";
    m_pImgSingalShowPackUp = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_repair_sport.jpg";
    m_pImgRepairSport = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_repair_over_part3.jpg";
    m_pImgRepairSuiD = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_repair_over_part2.jpg";
    m_pImRepairStateCheck = new QPixmap(strDir);
    strDir = m_strCurPath + "/images/main_repair_over - Start.jpg";
    m_pImgRepairRecord = new QPixmap(strDir);


    m_pBtnSuiD = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1538,534), QPoint(1582,584)), this);
    m_pBtnFangW = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1539,606), QPoint(1583,652)), this);
    m_pBtnGaodi = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1542,672), QPoint(1581,721)), this);
    m_pBtnShangY = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1538,745), QPoint(1579,792)), this);
    m_pBtnBai = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1536,814), QPoint(1586,862)), this);
    m_pBtnAllS = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1521,885), QPoint(1595,930)), this);
    m_pBtnStateShow = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1538, 949), QPoint(1584, 998)), this);


//    m_pBtnSport1 = new CImgStateArea(m_pImgRepairSport, m_pImgRepairSport, QPoint(925, 470), QPoint(1020,495), this);
//    m_pBtnSport2 = new CImgStateArea(m_pImgRepairSport, m_pImgRepairSport, QPoint(927, 820), QPoint(1020,845), this);

    m_PBtnStateCheck = new CImgStateArea(m_pImgRepairState, m_pImgRepairState, QPoint(560,144), QPoint(1508,1098), this);
    m_pBtnSignalShowState = new CImgStateArea(m_pImgSingalShowNor, m_pImgSingalShowPackUp, QPoint(568, 872), QPoint(1528, 1144), this);

    m_pBtnSport1 = new CImgStateArea(m_pImgRepairSport, m_pImgRepairSport, QPoint(925, 470), QPoint(1020,505), this);
    m_pBtnSport2 = new CImgStateArea(m_pImgRepairSport, m_pImgRepairSport, QPoint(924, 820), QPoint(1020,845), this);
    m_pBtnRecrd = new CImgStateArea(m_pImgRepairRecord, m_pImgRepairRecord, QPoint(1148, 468), QPoint(1243,493), this);
    m_pImgSuiD = new CImgStateArea(m_pImgRepairSuiD, m_pImgRepairSuiD, QPoint(1538, 534), QPoint(1582,584), this);
    m_pImgStateCheck = new CImgStateArea(m_pImRepairStateCheck, m_pImRepairStateCheck, QPoint(1538, 949), QPoint(1582,998), this);
    m_pCurveShowH = new CCurveShow(m_pImgMainRepairNor, QRect(QPoint(625,275),QPoint(1407,366)), this);
    m_pCurveShowV = new CCurveShow(m_pImgMainRepairNor, QRect(QPoint(625,625),QPoint(1407,716)), this);

    //创建14个联调按钮
    m_pBtnCurve[0] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(590, 470), QPoint(690,495)),this);
    m_pBtnCurve[1] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(710, 470), QPoint(790,495)),this);
    m_pBtnCurve[2] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(815, 470), QPoint(910,495)),this);
    m_pBtnCurve[3] = new CBmpButton(m_pImgMainRepairNor, m_pImgRepairSport, NULL, NULL, QRect(QPoint(925, 470), QPoint(1020,495)),this);
    m_pBtnCurve[4] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1040, 470), QPoint(1130,495)),this);
    m_pBtnCurve[5] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1150, 470), QPoint(1245,495)),this);
    m_pBtnCurve[6] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1260, 470), QPoint(1355,495)),this);
    m_pBtnCurve[7] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(590, 820), QPoint(690,845)),this);
    m_pBtnCurve[8] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(710, 820), QPoint(790,845)),this);
    m_pBtnCurve[9] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(816, 820), QPoint(910,845)),this);
    m_pBtnCurve[10] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(927, 820), QPoint(1020,845)),this);
    m_pBtnCurve[11] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1040, 820), QPoint(1130,845)),this);
    m_pBtnCurve[12] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1150, 820), QPoint(1245,845)),this);
    m_pBtnCurve[13] = new CBmpButton(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1260, 820), QPoint(1355,845)),this);
    for (int i = 0; i<14; i++)
    {
        m_pBtnCurve[i]->hide();
    }
    //创建10个联调输入框
    m_pCInputCurve[0] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(660, 425), QPoint(760, 455)), this);
    m_pCInputCurve[1] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(940, 425), QPoint(1038, 455)), this);
    m_pCInputCurve[2] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(1050, 425), QPoint(1150, 455)), this);
    m_pCInputCurve[3] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(1275, 425), QPoint(1375, 455)), this);
    m_pCInputCurve[4] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(1390, 425), QPoint(1490, 455)), this);
    m_pCInputCurve[5] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(660, 777), QPoint(760, 806)), this);
    m_pCInputCurve[6] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(940, 777), QPoint(1038, 806)), this);
    m_pCInputCurve[7] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(1050, 777), QPoint(1150, 806)), this);
    m_pCInputCurve[8] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(1275, 777), QPoint(1375, 806)), this);
    m_pCInputCurve[9] = new CInputEdit(m_pImgMainRepairNor, m_pImgMainRepairOver, QRect(QPoint(1390, 777), QPoint(1490, 806)), this);
    for (int i = 0; i<10; i++)
    {
        m_pCInputCurve[i]->hide();
        m_pCInputCurve[i]->setFont(font1);
    }


    m_pBtnSuiD->hide();
    m_pBtnSuiD->setCheckable(true);
    m_pBtnFangW->hide();
    m_pBtnFangW->setCheckable(true);
    m_pBtnGaodi->hide();
    m_pBtnGaodi->setCheckable(true);
    m_pBtnShangY->hide();
    m_pBtnShangY->setCheckable(true);
    m_pBtnBai->hide();
    m_pBtnBai->setCheckable(true);
    m_pBtnAllS->hide();
    m_pBtnAllS->setCheckable(true);
    m_pBtnStateShow->hide();
    m_pBtnStateShow->setCheckable(true);
    m_pCurveShowH->hide();
    m_pCurveShowV->hide();
    m_PBtnStateCheck->hide();
    m_pBtnSignalShowState->hide();
    m_pBtnSport1->hide();
    m_pBtnSport2->hide();
    m_pImgSuiD->hide();
    m_pImgStateCheck->hide();
    m_pBtnRecrd->hide();
}

void MainWindow::paintEvent(QPaintEvent *)      // 将窗口背景加载进来
{
    QPainter backPainter(this);

    backPainter.drawPixmap(this->rect(), *m_pImgMainShow);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)      // 界面所有的按钮操作消息都到这里
{
    if (watched == (QObject *)m_pBtnClose)
    {

        if (event->type() == QEvent::MouseButtonDblClick)      // 双击消息
        {
            CloseWindow();
        }
    }
    else if (watched == (QObject *)m_pBtnStateGroup)
    {
        /*if (event->type() == QEvent::MouseButtonRelease)
        {
            if (m_pBtnStateGroup->ButtonInA())      // 按钮当前位置在A（状态栏隐藏状态）
            {
                ShowStateBtn(true);
                //if (m_pageCur == PageMain)
                //{
                    m_pImgMainShow = m_pImgMainNor;
                //}
                //else
                //{
                   // m_pImgMainShow = m_pImgMainSysHideNor;
                //}
             }
            else                                    // 按钮当前位置在B（状态栏显示状态）
            {
                ShowStateBtn(false);
                //if (m_pageCur == PageMain)
                //{
                    m_pImgMainShow = m_pImgMainHideNor;
                //}
                //else
                //{
                    //m_pImgMainShow = m_pImgMainSysNor;
                //}
            }
        }
        update();*/
    }
    else if (watched == (QObject *)m_pBtnShoot)
    {
        if (event->type() == QEvent::MouseButtonPress)  // 按下射击按钮 展开/收起射击子菜单
        {
           if (m_pBtnShoot->isChecked())        // 如果当前是展开状态
           {
               ShowPage(PageMain);
           }
           else                                 // 如果当前是收起状态
           {
               ShowPage(PageShoot);
           }
        }
    }
    else if (watched == (QObject *)m_pBtnSys)       // 按下射击的系统按钮
    {
        if (event->type() == QEvent::MouseButtonPress)  // 按下系统按钮 展开/收起射击子菜单
        {
            ShowPage(PageShootSys);
        }
    }
    else if (watched == (QObject *)m_pBtnLocal)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            ShowPage(PageShootLocal);
        }
    }
    else if (watched == (QObject *)m_pBtnAsLocal)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            ShowPage(PageShootAsLocal);
        }
    }
    else if (watched == (QObject *)m_pBtnShowState)       // 按下状态显示收起/展开
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (m_pBtnShowState->IsPackUp())        // 如果当前是收起状态 则切换到展开
            {
                m_pBtnShowState->SwitchShowState(false);
                m_pBtnInputState->move(QPoint(1025,528));
                if (m_pBtnInputState->IsPackUp())       // 展开收起
                {
                    m_pBtnNoticeState->move(QPoint(1025,580));
                }
                else                                    // 展开展开
                {
                    m_pBtnNoticeState->move(QPoint(1025,820));
                }
                // 此处需要添加状态显示菜单控件的显示代码
            }
            else
            {
//                m_pBtnShowState->SwitchShowState(true);
//                m_pBtnInputState->move(QPoint(1025,280));
//                if (m_pBtnInputState->IsPackUp())       // 收起收起
//                {
//                    m_pBtnNoticeState->move(QPoint(1025,360));
//                }
//                else                                    // 收起展开
//                {
//                    m_pBtnNoticeState->move(QPoint(1025,560));
//                }

                // 此处需要添加状态显示控件的隐藏代码
            }
        }
    }
    else if (watched == (QObject *)m_pBtnInputState)       // 按下状态显示收起/展开
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (m_pBtnInputState->IsPackUp())        // 如果当前是收起状态 切换到展开 展开
            {
                m_pBtnInputState->SwitchShowState(false);
                m_pBtnNoticeState->move(QPoint(1025,m_pBtnInputState->pos().y()+ 280));
                //m_pBtnInputState->SwitchShowState(false);
                for(int i = 0; i < 4; i++)
                {
                    m_pCInputSys[i]->show();
                }
                for(int i = 0; i < 4; i++)
                {
                    m_pBtnInputSys[i]->show();
                }
                // 此处需要添加参数输入控件的显示代码
            }
            else                                    // 收起
            {
                m_pBtnInputState->SwitchShowState(true);
                m_pBtnNoticeState->move(QPoint(1025,m_pBtnInputState->pos().y()+95));
                for(int i = 0; i < 4; i++)
                {
                    m_pCInputSys[i]->hide();
                }
                for(int i = 0; i < 4; i++)
                {
                    m_pBtnInputSys[i]->hide();
                }
                // 此处需要添加参数输入控件的隐藏代码
            }
        }
    }
    else if (watched == (QObject *)m_pBtnNoticeState)       // 按下状态显示收起/展开
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (m_pBtnNoticeState->IsPackUp())        // 如果当前是展开状态
            {
                m_pBtnNoticeState->SwitchShowState(false);
                // 此处需要添加参数输入菜单控件的显示代码
            }
            else
            {
                m_pBtnNoticeState->SwitchShowState(true);

                // 此处需要添加参数输入显示控件的隐藏代码
            }
        }
    }
    else if (watched == (QObject *)m_pBtnRepair)       // 按下状态显示收起/展开
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (m_pBtnRepair->isChecked())
            {
                ShowPage(PageMain);
                m_pCurveShowH->StartStopDrawLine(true);
                m_pCurveShowV->StartStopDrawLine(true);
            }
            else
            {
                ShowPage(PageRepairSuiD);
                m_pCurveShowH->StartStopDrawLine(true);
                m_pCurveShowV->StartStopDrawLine(true);
            }
        }
    }
    else if (watched == (QObject *)m_pBtnCurve[3])     // 按下H方向联调开始绘制按钮
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if(m_pBtnCurve[3]->isChecked())
            {
                m_pBtnCurve[3]->setChecked(false);
                m_pCurveShowH->StartStopDrawLine(false);
                m_pBtnSport1->show();
            }
            else
            {
                m_pBtnCurve[3]->setChecked(true);
                m_pCurveShowH->StartStopDrawLine(true);
                m_pBtnSport1->show();
                m_pCurveShowH->m_bZero = false;
                m_pBtnCurve[3]->hide();
            }
            QByteArray BA;
            BA[0] = 0x54;
            BA[1] = 0x00;
            BA[2] = 0x11;
            BA[3] = 0x00;
            m_pCcomUdp->nSendData(BA, sizeof(BA));
        }
    }
    else if (watched == (QObject *)m_pBtnCurve[10])     // 按下V方向联调开始绘制按钮
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if(m_pBtnCurve[10]->isChecked())
            {
                m_pBtnCurve[10]->setChecked(false);
                m_pCurveShowV->StartStopDrawLine(false);
                m_pBtnSport2->show();
            }
            else
            {
                m_pBtnCurve[10]->setChecked(true);
                m_pCurveShowV->StartStopDrawLine(true);
                m_pBtnSport2->show();
                m_pBtnCurve[10]->hide();
            }
        }
    }

    else if (watched == (QObject *)m_pBtnCurve[4])     // 按下H方向联调结束绘制按钮
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if(m_pBtnCurve[4]->isChecked())
            {
                m_pBtnCurve[4]->setChecked(false);
                m_pCurveShowH->StartStopDrawLine(true);
            }
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    m_pCInputCurve[i]->ClearData();
                }
                m_pBtnCurve[4]->setChecked(true);
              //  m_pCurveShowH->StartStopDrawLine(false);
                m_pBtnSport1->hide();
                m_pBtnCurve[3]->show();
            }
            QByteArray BA;
            BA[0] = 0x54;
            BA[1] = 0x00;
            BA[2] = 0x22;
            BA[3] = 0x00;
            m_pCcomUdp->nSendData(BA, sizeof(BA));
        }
    }
    else if (watched == (QObject *)m_pBtnCurve[11])     // 按下V方向联调结束绘制按钮
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if(m_pBtnCurve[11]->isChecked())
            {
                m_pBtnCurve[11]->setChecked(false);
                m_pCurveShowV->StartStopDrawLine(true);
            }
            else
            {
                for(int i = 5; i < 9; i++)
                {
                    m_pCInputCurve[i]->ClearData();
                }
                m_pBtnCurve[11]->setChecked(true);
                m_pCurveShowV->StartStopDrawLine(false);
                m_pBtnSport1->hide();
                m_pBtnCurve[10]->show();
            }
        }
    }

    else if (watched == (QObject *)m_pBtnCurve[5])     // 按下开始记录按钮
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if(m_pBtnCurve[5]->isChecked())
            {
                m_pBtnCurve[5]->setChecked(false);
                m_pBtnRecrd->show();
            }
            else
            {
                m_pBtnCurve[5]->setChecked(true);
                m_pBtnRecrd->show();
                m_pBtnCurve[5]->hide();
            }
            QByteArray BA;
            BA[0] = 0x54;
            BA[1] = 0x00;
            BA[2] = 0x44;
            BA[3] = 0x00;
            m_pCcomUdp->nSendData(BA, sizeof(BA));
        }
    }

    else if (watched == (QObject *)m_pBtnCurve[6])     // 按下停止记录按钮
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if(m_pBtnCurve[6]->isChecked())
            {
                m_pBtnCurve[6]->setChecked(false);
                m_pBtnCurve[5]->show();
            }
            else
            {
                m_pBtnCurve[5]->setChecked(true);
                m_pBtnRecrd->hide();
                m_pBtnCurve[5]->show();
            }
            QByteArray BA;
            BA[0] = 0x54;
            BA[1] = 0x00;
            BA[2] = 0x88;
            BA[3] = 0x00;
            m_pCcomUdp->nSendData(BA, sizeof(BA));
        }
    }

    else if (watched == (QObject *)m_pBtnSignalShowState)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (m_pBtnSignalShowState->IsPackUp())
            {
                m_pBtnSignalShowState->SwitchShowState(false);
            }
            else
            {
                m_pBtnSignalShowState->SwitchShowState(true);
            }
        }
    }

    else if (watched == (QObject *)m_pBtnStateShow)    // 显示维修下的信号检测界面
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if(m_pBtnStateShow ->isChecked())
            {
               // m_pBtnStateShow->setChecked(false);
                ShowPage(PageRepairState);
                m_pImgStateCheck->show();
                m_pBtnStateShow->hide();
                m_pBtnSuiD->show();

            }
            else
            {
             //   m_pBtnStateShow->setChecked(true);
                ShowPage(PageRepairState);
                m_pImgStateCheck->show();
                m_pBtnStateShow->hide();
                m_pBtnSuiD->show();

            }

        }
    }
    else if (watched == (QObject *)m_pBtnSuiD)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if(m_pBtnSuiD->isChecked())
            {
               // m_pBtnSuiD->setChecked(false);
                ShowPage(PageRepairSuiD);
                m_pImgSuiD->show();
                m_pBtnSuiD->hide();
                m_pBtnStateShow->show();
            }
            else
            {
               // m_pBtnSuiD->setChecked(true);
                ShowPage(PageRepairSuiD);
                m_pImgSuiD->show();
                m_pBtnSuiD->hide();
                m_pBtnStateShow->show();

            }
        }
    }

    for (int i = 0; i < 14; i++)
    {
        if(watched == (QObject *)m_pCInputCurve[i] || watched == (QObject *)m_pCInputSys[i])
        {
            if(event->type() == QEvent::MouseButtonPress)
            {
                switch(i)
                {
                case 0:
                {
                    m_pCInputCurve[0]->EditNow(true);
                    for(int i = 1; i < 10; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }

                    m_pCInputSys[0]->EditNow(true);
                    for(int i = 1; i < 4; i++)
                    {
                        m_pCInputSys[i]->EditNow(false);
                    }
                    break;
                }
                case 1:
                {
                    m_pCInputCurve[0]->EditNow(false);
                    m_pCInputCurve[1]->EditNow(true);
                    for(int i = 2; i < 10; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }

                    m_pCInputSys[1]->EditNow(true);
                    m_pCInputSys[0]->EditNow(false);
                    for(int i = 2; i < 4; i++)
                    {
                        m_pCInputSys[i]->EditNow(false);
                    }
                    break;
                }
                case 2:
                {
                    m_pCInputCurve[0]->EditNow(false);
                    m_pCInputCurve[1]->EditNow(false);
                    m_pCInputCurve[2]->EditNow(true);
                    for(int i = 3; i < 10; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }

                    m_pCInputSys[0]->EditNow(false);
                    m_pCInputSys[1]->EditNow(false);
                    m_pCInputSys[2]->EditNow(true);
                    for(int i = 3; i < 4; i++)
                    {
                        m_pCInputSys[i]->EditNow(false);
                    }
                    break;
                }
                case 3:
                {
                    m_pCInputCurve[0]->EditNow(false);
                    m_pCInputCurve[1]->EditNow(false);
                    m_pCInputCurve[2]->EditNow(false);
                    m_pCInputCurve[3]->EditNow(true);
                    for(int i = 4; i < 10; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }

                    m_pCInputSys[0]->EditNow(false);
                    m_pCInputSys[1]->EditNow(false);
                    m_pCInputSys[2]->EditNow(false);
                    m_pCInputSys[3]->EditNow(true);
//                    for(int i = 4; i < 4; i++)
//                    {
//                        m_pCInputSys[i]->EditNow(false);
//                    }
                    break;
                }
                case 4:
                {
                    m_pCInputCurve[0]->EditNow(false);
                    m_pCInputCurve[1]->EditNow(false);
                    m_pCInputCurve[2]->EditNow(false);
                    m_pCInputCurve[3]->EditNow(false);
                    m_pCInputCurve[4]->EditNow(true);
                    for(int i = 5; i < 10; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }

//                    m_pCInputSys[0]->EditNow(false);
//                    m_pCInputSys[1]->EditNow(false);
//                    m_pCInputSys[2]->EditNow(false);
//                    m_pCInputSys[3]->EditNow(false);
//                    m_pCInputSys[4]->EditNow(true);
//                    for(int i = 5; i < 8; i++)
//                    {
//                        m_pCInputSys[i]->EditNow(false);
//                    }
                    break;
                }
                case 5:
                {
                    m_pCInputCurve[5]->EditNow(true);
                    for(int i = 0; i < 5; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }
                    for(int i = 6; i < 10; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }

//                    m_pCInputSys[5]->EditNow(true);
//                    for(int i = 0; i < 5; i++)
//                    {
//                        m_pCInputSys[i]->EditNow(false);
//                    }
//                    for(int i = 6; i < 8; i++)
//                    {
//                        m_pCInputSys[i]->EditNow(false);
//                    }
                    break;
                }
                case 6:
                {
                    m_pCInputCurve[6]->EditNow(true);
                    for(int i = 0; i < 6; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }
                    for(int i = 7; i < 10; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }

//                    m_pCInputSys[6]->EditNow(true);
//                    for(int i = 0; i < 6; i++)
//                    {
//                        m_pCInputSys[i]->EditNow(false);
//                    }
//                    for(int i = 7; i < 8; i++)
//                    {
//                        m_pCInputSys[i]->EditNow(false);
//                    }
                    break;
                }
                case 7:
                {
                    m_pCInputCurve[7]->EditNow(true);
                    for(int i = 0; i < 7; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }
                    for(int i = 8; i < 10; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }

//                    m_pCInputSys[7]->EditNow(true);
//                    for(int i = 0; i < 7; i++)
//                    {
//                        m_pCInputSys[i]->EditNow(false);
//                    }
//                    for(int i = 8; i < 8; i++)
//                    {
//                        m_pCInputSys[i]->EditNow(false);
//                    }
                    break;
                }
                case 8:
                {
                    m_pCInputCurve[8]->EditNow(true);
                    m_pCInputCurve[9]->EditNow(false);
                    for(int i = 0; i < 8; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }
                    break;
                }
                case 9:
                {
                    m_pCInputCurve[9]->EditNow(true);
                    for(int i = 0; i < 9; i++)
                    {
                        m_pCInputCurve[i]->EditNow(false);
                    }
                    break;
                }
                default:
                    break;
                }
            }
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_nTimerID)
    {
        QDateTime dateTime;
        dateTime = QDateTime::currentDateTime();
        QString strTimeCur = dateTime.toString("yyyy-MM-dd hh:mm:ss");

        m_pBtnDateTime->SetShowText(strTimeCur);
    }
}

void MainWindow::CloseWindow()
{
    m_pSecondWindowDlg->close();
    m_pSecondWinAimDlg->close();
    close();
}

void MainWindow::ShowStateBtn(bool bShow)
{
    for (int i = 0; i<28; i++)
    {
        if (bShow)
        {
            m_ppBtnState[i]->show();
            m_ppBtnState[i]->SetShowState(1);
        }
        else
        {
            m_ppBtnState[i]->hide();
            m_ppBtnState[i]->SetShowState(2);
        }
    }
}

// 这个接口用于切换第二屏的软件界面为仓库/光电瞄准，由于切换触发信息来自于通信，因此后续需要改为信号槽的方式来触发
void MainWindow::SwitchSecondWindow(int nType)
{
    if (nType == 0)
    {
        m_pSecondWindowDlg->show();
        m_pSecondWinAimDlg->hide();
    }
    else if (nType == 1)
    {
        m_pSecondWindowDlg->hide();
        m_pSecondWinAimDlg->show();
    }
    else        // 出现其他值的时候讲界面切换到仓库主界面
    {
        m_pSecondWindowDlg->show();
        m_pSecondWinAimDlg->hide();
    }
}

void MainWindow::slotUpdateUIData(int nRecvType)
{
    THAngle tHAngle;
    TVAngle tVAngle;
    TCmdUp tCmdUp;
    TCmdH tCmdH;
    TSwayAngle tSwayAngle;
    TUpAngle tUpAngle;
    QString strTxt;

    switch (nRecvType)
    {
    case 0:             // VAngle  垂直角度和误差
    {
        m_pDataManager->GetVAngleData(tVAngle);
        m_pDataManager->GetHAngleData(tHAngle);
        m_pBtnPointerV->ShowNewAngle(tVAngle.fAngle, false);
        m_pBtnPointerSysV->ShowNewAngle(tVAngle.fAngle, false);
        m_pBtnSysPointerV->ShowNewAngle(tVAngle.fAngle, false);

        strTxt = QString("%2").arg(tVAngle.fAngle);
        m_pBtnVAngle->SetShowText(strTxt);
        m_pBtnAngleV->SetShowText(strTxt);

        strTxt = QString::number(tVAngle.fError, 'f', 2);
        m_pBtnVError->SetShowText(strTxt);
        m_pBtnErrorV->SetShowText(strTxt);
        m_pBtnCanon->ShowCurAngle(tVAngle.fAngle+13, tHAngle.fAngle+150);    // 此处39为测试 实际应为“tHAngle.fVngle+10”

        m_pCurveShowV->DrawLinesV(tVAngle);
//        emit SigDrawCurveV(nRecvType);

        break;
    }
    case 1:             // SwayAngle  摆角度和误差
    {
        m_pDataManager->GetSwayAngleData(tSwayAngle);
        strTxt = QString("%2").arg(tSwayAngle.fAngle);
        m_pBtnBaiAngleV->SetShowText(strTxt);
        strTxt = QString::number(tSwayAngle.fError+0.35, 'f', 2);
        m_pBtnBaiErrorV->SetShowText(strTxt);
        break;
    }
    case 2:             // CmdUp  垂直指令
    {
        m_pDataManager->GetCmdUpData(tCmdUp);
        strTxt = QString("%2").arg(tCmdUp.fCmdPos);
        m_pBtnPosCmdV->SetShowText(strTxt);
        strTxt = QString::number(tCmdUp.fCmdSpeed, 'f', 2);
        m_pBtnSpeedCmdV->SetShowText(strTxt);
        break;
    }
    case 3:             // HAngle  水平方位角度和误差
    {
        m_pDataManager->GetHAngleData(tHAngle);
        m_pDataManager->GetVAngleData(tVAngle);
        m_pBtnPointerH->ShowNewAngle(tHAngle.fAngle, false);
        m_pBtnPointerSysH->ShowNewAngle(tHAngle.fAngle, false);

//        strTxt = QString("%2").arg(tHAngle.fAngle);
//        m_pBtnHAngle->SetShowText(strTxt);
//        m_pBtnAngleH->SetShowText(strTxt);

        strTxt = QString::number(tVAngle.fError, 'f', 2);
        m_pBtnHError->SetShowText(strTxt);
        m_pBtnErrorH->SetShowText(strTxt);
        //m_pBtnCanon->ShowCurAngle(tVAngle.fAngle+13, tHAngle.fAngle);    // 此处39为测试 实际应为“tHAngle.fVngle+10”
        m_pBtnCanon->ShowCurAngle(43, tHAngle.fAngle);    // 此处39为测试 实际应为“tHAngle.fVngle+10”



        m_pCurveShowH->DrawLinesV(tVAngle);
//        emit SigDrawCurveH(nRecvType);
        break;
    }
    case 4:             // UpAngle  上扬角度和误差
    {
        m_pDataManager->GetUpAngleData(tUpAngle);
        strTxt = QString("%2").arg(tUpAngle.fAngle);
        m_pBtnUpAngleH->SetShowText(strTxt);
        strTxt = QString::number(tUpAngle.fError, 'f', 2);
        m_pBtnUpErrorH->SetShowText(strTxt);
        break;
    }
    case 5:             // CmdH
    {
        m_pDataManager->GetCmdHData(tCmdH);
        strTxt = QString("%2").arg(tCmdH.fCmdPos);
        m_pBtnPosCmdH->SetShowText(strTxt);
        strTxt = QString("%2").arg(tCmdH.fCmdSpeed);
        m_pBtnSpeedCmdH->SetShowText(strTxt);

        break;
    }
    default:
        break;
    }

}

void MainWindow::ShowPage(emPage pageTo)
{
    if (m_pageCur == pageTo)
    {
        return;
    }

    switch (pageTo)
    {
    case PageMain:
    {
        m_pImgMainShow = m_pImgMainHideNor;
        m_pBtnCanon->show();
        m_pBtnPointerH->show();
        m_pBtnPointerV->show();
        m_pBtnPointerSysH->hide();
        m_pBtnPointerSysV->hide();
        m_pBtnShoot->setChecked(false);
        m_pBtnSup->setChecked(false);
        m_pBtnRepair->setChecked(false);
        m_pBtnReset->setChecked(false);
        m_pBtnShowRecord->setChecked(false);
        m_pBtnHAngle->show();
        m_pBtnHError->show();
        m_pBtnVAngle->show();
        m_pBtnVError->show();
        m_pBtnSys->hide();
        m_pBtnLocal->hide();
        m_pBtnAsLocal->hide();
        m_pBtnShowState->hide();
        m_pBtnInputState->hide();
        m_PBtnStateCheck->hide();
        m_pBtnNoticeState->hide();
        m_pBtnSysPointerV->hide();
        m_pBtnSysYaoKong->hide();
        for (int i = 0; i<4; i++)
        {
            m_pCInputSys[i]->hide();
        }
        for (int i = 0; i<4; i++)
        {
            m_pBtnInputSys[i]->hide();
        }

        m_pBtnAngleH->hide();
        m_pBtnErrorH->hide();
        m_pBtnUpAngleH->hide();
        m_pBtnUpErrorH->hide();
        m_pBtnPosCmdH->hide();
        m_pBtnSpeedCmdH->hide();
        m_pBtnAngleV->hide();
        m_pBtnErrorV->hide();
        m_pBtnBaiAngleV->hide();
        m_pBtnBaiErrorV->hide();
        m_pBtnPosCmdV->hide();
        m_pBtnSpeedCmdV->hide();

        m_pBtnSuiD->hide();
        m_pBtnFangW->hide();
        m_pBtnGaodi->hide();
        m_pBtnShangY->hide();
        m_pBtnBai->hide();
        m_pBtnAllS->hide();
        m_pBtnStateShow->hide();
        m_pBtnSignalShowState->hide();
        m_pBtnSport1->hide();
        m_pBtnSport2->hide();
        m_pBtnRecrd->hide();
        m_pBtnSignalShowState->hide();
        m_pImgSuiD->hide();
        m_pImgStateCheck->hide();

        m_pCurveShowV->hide();
        m_pCurveShowH->hide();
        for(int i = 0; i < 14; i++)
        {
            m_pBtnCurve[i]->hide();
        }
        for (int i = 0; i<10; i++)
        {
            m_pCInputCurve[i]->hide();
        }

        m_pBtnShoot->SetImg(m_pImgMainNor, m_pImgMainOver, NULL, NULL, QRect(QPoint(1529,805), QPoint(1591,869)));
        m_pBtnSup->SetImg(m_pImgMainNor, m_pImgMainOver, NULL, NULL, QRect(QPoint(1529,876), QPoint(1591,937)));
        m_pBtnRepair->SetImg(m_pImgMainNor, m_pImgMainOver, NULL, NULL, QRect(QPoint(1529,947), QPoint(1591,1010)));
        m_pBtnReset->SetImg(m_pImgMainNor, m_pImgMainOver, NULL, NULL, QRect(QPoint(1529,1020), QPoint(1591,1080)));
        m_pBtnShowRecord->SetImg(m_pImgMainNor, m_pImgMainOver, NULL, NULL, QRect(QPoint(1529,1090), QPoint(1591,1150)));
        m_pBtnShoot->move(QPoint(1529,805));
        m_pBtnStateGroup->move(QPoint(1530,735));
        m_pBtnStateGroup->SetAPoint(QPoint(1530,735));
        update();
        break;
    }
    case PageShoot:
    {
        m_pImgMainShow = m_pImgMainSysNor;
        m_pBtnCanon->hide();        
        m_pBtnPointerH->hide();
        m_pBtnPointerV->hide();
        m_pBtnPointerSysH->show();
        m_pBtnPointerSysV->show();
        m_pBtnShoot->setChecked(true);
        m_pBtnSup->setChecked(false);
        m_pBtnRepair->setChecked(false);
        m_pBtnReset->setChecked(false);
        m_pBtnShowRecord->setChecked(false);
        m_pBtnHAngle->hide();
        m_pBtnHError->hide();
        m_pBtnVAngle->hide();
        m_pBtnVError->hide();
        m_pBtnSys->show();
        m_pBtnSys->setChecked(true);
        m_pBtnLocal->show();
        m_pBtnAsLocal->show();
        m_pBtnShowState->show();
        m_pBtnInputState->show();
        m_PBtnStateCheck->hide();
        m_pBtnNoticeState->show();
        m_pBtnSysPointerV->show();
        m_pBtnSysYaoKong->show();
        for (int i = 0; i<4; i++)
        {
            m_pCInputSys[i]->show();
            m_pCInputSys[i]->EditNow(false);
        }
        for (int i = 0; i<4; i++)
        {
            m_pBtnInputSys[i]->show();
        }


        m_pBtnAngleH->show();
        m_pBtnErrorH->show();
        m_pBtnUpAngleH->show();
        m_pBtnUpErrorH->show();
        m_pBtnPosCmdH->show();
        m_pBtnSpeedCmdH->show();
        m_pBtnAngleV->show();
        m_pBtnErrorV->show();
        m_pBtnBaiAngleV->show();
        m_pBtnBaiErrorV->show();
        m_pBtnPosCmdV->show();
        m_pBtnSpeedCmdV->show();

        m_pBtnSuiD->hide();
        m_pBtnFangW->hide();
        m_pBtnGaodi->hide();
        m_pBtnShangY->hide();
        m_pBtnBai->hide();
        m_pBtnAllS->hide();
        m_pBtnStateShow->hide();
        m_pBtnSignalShowState->hide();
        m_pBtnSport1->hide();
        m_pBtnSport2->hide();
        m_pBtnRecrd->hide();
        m_pImgSuiD->hide();
        m_pImgStateCheck->hide();

        m_pCurveShowV->hide();
        m_pCurveShowH->hide();
        for(int i = 0; i < 14; i++)
        {
            m_pBtnCurve[i]->hide();
        }
        for (int i = 0; i<10; i++)
        {
            m_pCInputCurve[i]->hide();
        }


        m_pBtnShoot->SetImg(m_pImgMainSysNor, m_pImgMainSysOver, NULL, NULL, QRect(QPoint(1530,597), QPoint(1591,658)));
        m_pBtnSup->SetImg(m_pImgMainSysNor, m_pImgMainSysOver, NULL, NULL, QRect(QPoint(1530,878), QPoint(1591,940)));
        m_pBtnRepair->SetImg(m_pImgMainSysNor, m_pImgMainSysOver, NULL, NULL, QRect(QPoint(1530,948), QPoint(1591,1010)));
        m_pBtnReset->SetImg(m_pImgMainSysNor, m_pImgMainSysOver, NULL, NULL, QRect(QPoint(1530,1018), QPoint(1591,1080)));
        m_pBtnShowRecord->SetImg(m_pImgMainSysNor, m_pImgMainSysOver, NULL, NULL, QRect(QPoint(1530,1090), QPoint(1591,1151)));

        m_pBtnShoot->move(QPoint(1530,598));
        m_pBtnStateGroup->move(QPoint(1530,526));
        m_pBtnStateGroup->SetAPoint(QPoint(1530,526));

        update();
        break;
    }
    case PageShootSys:
    {
        m_pBtnSys->setChecked(true);
        m_pBtnLocal->setChecked(false);
        m_pBtnAsLocal->setChecked(false);
        break;
    }
    case PageShootLocal:
    {
        m_pBtnSys->setChecked(false);
        m_pBtnLocal->setChecked(true);
        m_pBtnAsLocal->setChecked(false);
        break;
    }
    case PageShootAsLocal:
    {
        m_pBtnSys->setChecked(false);
        m_pBtnLocal->setChecked(false);
        m_pBtnAsLocal->setChecked(true);
        break;
    }
    case PageRepairSuiD:
    {
        m_pBtnShoot->setChecked(false);
        m_pBtnSup->setChecked(false);
        m_pBtnReset->setChecked(false);
        m_pBtnShowRecord->setChecked(false);
        m_pBtnRepair->setChecked(true);
        m_pBtnSuiD->hide();
        m_pBtnFangW->show();
        m_pBtnGaodi->show();
        m_pBtnShangY->show();
        m_pBtnBai->show();
        m_pBtnAllS->show();
        m_pBtnStateShow->show();
//        m_pBtnSport1->show();
//        m_pBtnSport2->show();
        m_pImgSuiD->show();

        m_pBtnSys->hide();
        m_pBtnLocal->hide();
        m_pBtnAsLocal->hide();
        m_pBtnShowState->hide();
        m_pBtnInputState->hide();
        m_PBtnStateCheck->hide();
        m_pBtnNoticeState->hide();
        m_pBtnSysPointerV->hide();
        m_pBtnSysYaoKong->hide();
        for (int i = 0; i<4; i++)
        {
            m_pCInputSys[i]->hide();
        }
        for (int i = 0; i<4; i++)
        {
            m_pBtnInputSys[i]->hide();
        }

        m_pBtnCanon->hide();
        m_pBtnHAngle->hide();
        m_pBtnHError->hide();
        m_pBtnVAngle->hide();
        m_pBtnVError->hide();
        m_pBtnAngleH->show();
        m_pBtnErrorH->show();
        m_pBtnUpAngleH->show();
        m_pBtnUpErrorH->show();
        m_pBtnPosCmdH->show();
        m_pBtnSpeedCmdH->show();
        m_pBtnAngleV->show();
        m_pBtnErrorV->show();
        m_pBtnBaiAngleV->show();
        m_pBtnBaiErrorV->show();
        m_pBtnPosCmdV->show();
        m_pBtnSpeedCmdV->show();
        m_pBtnSignalShowState->show();
        m_pBtnSport1->hide();
        m_pBtnSport2->hide();
        m_pBtnRecrd->hide();
        //m_pImgSuiD->hide();
        m_pImgStateCheck->hide();

        m_pCurveShowV->show();
        m_pCurveShowH->show();
        for(int i = 0; i < 14; i++)
        {
            m_pBtnCurve[i]->show();
        }
        for (int i = 0; i<10; i++)
        {
            m_pCInputCurve[i]->show();
            m_pCInputCurve[i]->EditNow(false);
        }


        //m_pBtnRepair->move(QPoint(1843,392));
        //m_pBtnSup->move(QPoint(1843,322));
        //m_pBtnShoot->move(QPoint(1843,251));

        m_pBtnShoot->SetImg(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1525,304), QPoint(1594,370)));
        m_pBtnSup->SetImg(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1529,376), QPoint(1594,445)));
        m_pBtnRepair->SetImg(m_pImgMainRepairNor, m_pImgMainRepairOver, NULL, NULL, QRect(QPoint(1529,447), QPoint(1594,513)));

        //m_pBtnShoot->move(QPoint(1530,530));
        m_pBtnStateGroup->move(QPoint(1530,237));
        m_pBtnStateGroup->SetAPoint(QPoint(1530,237));
        m_pImgMainShow = m_pImgMainRepairNor;

        update();
        break;
    }
    case PageRepairFangW:
    {
        break;
    }
    case PageRepairGaoDi:
    {
        break;
    }
    case PageRepairShangY:
    {
        break;
    }
    case PageRepairBai:
    {
        break;
    }
    case PageRepairAllS:
    {
        break;
    }
    case PageRepairState:
    {
        m_pBtnSuiD->setChecked(false);
        m_pBtnFangW->setChecked(false);
        m_pBtnGaodi->setChecked(false);
        m_pBtnShangY->setChecked(false);
        m_pBtnBai->setChecked(false);
        m_pBtnAllS->setChecked(false);
        m_pBtnStateShow->setChecked(true);
        m_PBtnStateCheck->show();
        m_pCurveShowV->hide();
        m_pCurveShowH->hide();
        m_pBtnSport1->hide();
        m_pBtnSport2->hide();
        m_pBtnRecrd->hide();
        m_pImgSuiD->hide();
        m_pImgStateCheck->show();
        m_pBtnSignalShowState->hide();
        for(int i = 0; i < 14; i++)
        {
            m_pBtnCurve[i]->hide();
        }
        for (int i = 0; i<10; i++)
        {
            m_pCInputCurve[i]->hide();
            m_pCInputCurve[i]->EditNow(false);
        }

        break;
    }


    default:
        break;
    }

    m_pageCur = pageTo;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_ptWindowPosPress = pos();
    m_ptGlobalPos = event->globalPos();
    m_ptDlgPos = m_ptGlobalPos - m_ptWindowPosPress;        // 用于实现窗口拖动
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - m_ptDlgPos);                 // 用于实现窗口拖动
}

