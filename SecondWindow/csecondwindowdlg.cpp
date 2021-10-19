#include "csecondwindowdlg.h"
#include "ui_csecondwindowdlg.h"
#include "qdesktopwidget.h"
#include "qpainter.h"

CSecondWindowDlg::CSecondWindowDlg(QString strCurDir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSecondWindowDlg)
{
    ui->setupUi(this);
    m_strDir = strCurDir;

    m_pMainImgNor = NULL;
    m_pMainImgOver = NULL;
    m_pMainImgDown = NULL;
    m_pMainImgDis = NULL;
    InitSkins();

    QDesktopWidget *pDesktop = QApplication::desktop();
    int nScreenCount = pDesktop->screenCount();
    if (nScreenCount == 2)
    {
        setGeometry((pDesktop->screenGeometry(1)));
    }
    setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    move(0,1200);
    show();
}

CSecondWindowDlg::~CSecondWindowDlg()
{
    delete ui;

    if (m_pMainImgNor)
    {
        delete m_pMainImgNor;
        m_pMainImgNor = NULL;
    }
    if (m_pMainImgOver)
    {
        delete m_pMainImgOver;
        m_pMainImgOver = NULL;
    }
    if (m_pMainImgDown)
    {
        delete m_pMainImgDown;
        m_pMainImgDown = NULL;
    }
    if (m_pMainImgDis)
    {
        delete m_pMainImgDis;
        m_pMainImgDis = NULL;
    }
}

void CSecondWindowDlg::InitSkins()
{
    move(QPoint(0,00));
    resize(QSize(1600,1200));

    // 1.主界面nor状态图片、over、down、disable状态图片读入内存
    QString strDir = m_strDir + "/images/second_warehouse_nor.jpg";
    m_pMainImgNor = new QPixmap(strDir);
    strDir = m_strDir + "/images/second_warehouse_over.jpg";
    m_pMainImgOver = new QPixmap(strDir);
}

void CSecondWindowDlg::paintEvent(QPaintEvent *)      // 将窗口背景加载进来，并且将窗口放置到中间位置
{
    QPainter backPainter(this);

    backPainter.drawPixmap(this->rect(), *m_pMainImgNor);
}

// 由于是触摸屏，为防止误操作，去掉窗口拖动功能
/*
void CSecondWindowDlg::mousePressEvent(QMouseEvent *event)
{
    m_ptWindowPosPress = pos();
    m_ptGlobalPos = event->globalPos();
    m_ptDlgPos = m_ptGlobalPos - m_ptWindowPosPress;        // 用于实现窗口拖动
}

void CSecondWindowDlg::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - m_ptDlgPos);                 // 用于实现窗口拖动
}
*/
