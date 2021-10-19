#include "csecondwindowaimdlg.h"
#include "ui_csecondwindowaimdlg.h"
#include "qdesktopwidget.h"
#include "qpainter.h"

CSecondWindowAimDlg::CSecondWindowAimDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSecondWindowAimDlg)
{
    ui->setupUi(this);

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
    showFullScreen();
}

CSecondWindowAimDlg::~CSecondWindowAimDlg()
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

void CSecondWindowAimDlg::InitSkins()
{
    move(QPoint(0,00));
    resize(QSize(1600,1200));

    // 1.主界面nor状态图片、over、down、disable状态图片读入内存
    m_pMainImgNor = new QPixmap("E:\StudyInfo\ZX_UIControl\build-UIControl-Desktop_Qt_5_7_0_MinGW_32bit-Debug\debug\images\second_warehouse_nor.jpg");    // 后续需要改成实时获取当前路径
    m_pMainImgOver = new QPixmap("E:\StudyInfo\ZX_UIControl\build-UIControl-Desktop_Qt_5_7_0_MinGW_32bit-Debug\debug\images\second_warehouse_over.jpg");    // 后续需要改成实时获取当前路径
}

void CSecondWindowAimDlg::paintEvent(QPaintEvent *)      // 将窗口背景加载进来，并且将窗口放置到中间位置
{
    QPainter backPainter(this);

    backPainter.drawPixmap(this->rect(), *m_pMainImgNor);
}
