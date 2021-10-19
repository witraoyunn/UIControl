#include <QEvent>
#include "cporotocol.h"
#include "UIControldefine.h"
#include "QDebug"
#include <QtGlobal>
#include <QTime>

CPorotocol::CPorotocol()
{
    memset(m_byBuffer, 0, sizeof(m_byBuffer));
    m_nDecodeDataLen = 0;
    m_pDataManager = NULL;
    m_nTestHAngle = -13;
    startTimer(50);
    //init
    nHeadState = 4;
    bLenghState = true;
}

CPorotocol::~CPorotocol()
{

}

void CPorotocol::RegistDataManager(CDataManager *pDataManager)
{
    m_pDataManager = pDataManager;
}

void CPorotocol::DecodeData()
{
//    1.判断是否是报文头
    nHeadState =  checkHead();
    if(nHeadState == 0)
    {
        return;
    }
    bLenghState = checkLengh();
    if(!bLenghState)
    {
        return;
    }
    DecodeHAngle();
    DecodeVAngle();

    // 2.判断m_byBuffer的合法性，是否为空 长度
    // 3.验证校验和
    // 4.for循环从报文头开始解析报文头 根据报文头调用不同的报文解析函数
}

int CPorotocol::EncodeData()
{
    int nLen = 0;

    // 1.报文头赋值
    // 2.将报文长度在buffer中留空占位
    // 3.打包正文
    // 4.计算校验和 长度
    // 5.打包校验和 长度

    return nLen;        // 返回打包的报文的长度
}

void CPorotocol::DecodeVAngle()
{
//    if(m_nDecodeDataLen != 8)
//    {
//        return;
//    }

    TVAngle tVAngle;


//    // 1.解析高低角度
//    union twobyte
//    {
//        char buf[2];
//        short newbuf;
//    };
//    twobyte VAngle;
//    VAngle.buf[0] = m_byBuffer[1];
//    VAngle.buf[1] = m_byBuffer[2];

//    tVAngle.fAngle = VAngle.newbuf;

    int rd = random();
    tVAngle.fAngle = 30;
    tVAngle.fError = (float)rd*0.01;
    m_pDataManager->SetVAngleData(tVAngle);
    // 2.发送信号到界面 更新数据
    emit SigProtoDecodedData(0);

}

void CPorotocol::DecodeHAngle()
{
    THAngle tHAngle;
    TVAngle tVAngle;

    // 1.解析水平角度

    float fangle = convert2short(m_byBuffer[2],m_byBuffer[3]);
    tHAngle.fAngle = (fangle*180/32767);

//    float ferror = convert2short(m_byBuffer[6],m_byBuffer[7]);
//    tHAngle.fError = ferror/100;
    tHAngle.fError = tVAngle.fError;
    qDebug()<<"fError is"<< tHAngle.fError;

    m_pDataManager->SetHAngleData(tHAngle);
    // 2.发送信号到界面 更新数据
    emit SigProtoDecodedData(3);

}

void CPorotocol::timerEvent(QTimerEvent *event)
{
    //if (m_nTestHAngle > 150)
    if (m_nTestHAngle > 140)
    {
        m_bTestBigH = true;
    }
    //if (m_nTestHAngle < -150)
    if (m_nTestHAngle < 1)
    {
        m_bTestBigH = false;
    }
    if (m_bTestBigH)
    {
        m_nTestHAngle--;
    }
    else
    {
        m_nTestHAngle++;
    }

    if (m_nTestVAngle > 87)
    {
        m_bTestBigV = true;
    }
    if (m_nTestVAngle < -8)
    {
        m_bTestBigV = false;
    }
    if (m_bTestBigV)
    {
        m_nTestVAngle--;
    }
    else
    {
        m_nTestVAngle++;
    }

    TVAngle tVAngle;
    tVAngle.fAngle = m_nTestVAngle;
    tVAngle.fError = (float(m_nTestVAngle))/100.00;
    m_pDataManager->SetVAngleData(tVAngle);
    emit SigProtoDecodedData(0);

//    THAngle tHAngle;
//    tHAngle.fAngle = m_nTestHAngle;
//    tHAngle.fError = (float(m_nTestHAngle))/100.00;
//    m_pDataManager->SetHAngleData(tHAngle);
    emit SigProtoDecodedData(3);

    TSwayAngle tSwayAngle;
    tSwayAngle.fAngle = m_nTestVAngle;
    tSwayAngle.fError = (float(m_nTestVAngle))/101.00;
    m_pDataManager->SetSwayAngleData(tSwayAngle);
    emit SigProtoDecodedData(1);

    TCmdUp tCmdUp;
    tCmdUp.fCmdPos = m_nTestVAngle + 2;
    tCmdUp.fCmdSpeed = m_nTestVAngle % 3;
    m_pDataManager->SetCmdUpData(tCmdUp);
    emit SigProtoDecodedData(2);

    TUpAngle tUpAngle;
    tUpAngle.fAngle = m_nTestVAngle;
    tUpAngle.fError = (float(m_nTestVAngle))/102.00;
    m_pDataManager->SetUpAngleData(tUpAngle);
    emit SigProtoDecodedData(4);

    TCmdH tCmdH;
    tCmdH.fCmdPos = m_nTestVAngle + 1;
    tCmdH.fCmdSpeed = m_nTestVAngle % 3;
    m_pDataManager->SetCmdHData(tCmdH);
    emit SigProtoDecodedData(5);
}

float CPorotocol::convert2short(char a, char b)
{
    union twobyte
    {
        char buf[2];
        short newbuf;
    };
    twobyte VAngle;

    char sig;
    sig =b&0x80;

    VAngle.buf[0] = a;
    VAngle.buf[1] = b&0x7f;
    float tmp = (float)VAngle.newbuf;

    if((unsigned char)sig==0x80)
    {
       return 0-tmp;
    }
    else if((unsigned char)sig==0x00)
    {
        return tmp;
    }
    else
    {
        qDebug()<<"signa error 123";
    }
}

int CPorotocol::checkHead()
{
    if((unsigned char)m_byBuffer[1]==0x54)
    {
        if((unsigned char)m_byBuffer[0]==0x80)
            return 2;      //负数
        else if((unsigned char)m_byBuffer[0]==0x00)
        {
            return 1;    //正数
        }
    }
    else
    {
        qDebug()<<"protocol head is iligle";
        return 0;   //报文头错误
    }
}

bool CPorotocol::checkLengh()
{
    int len;
    len = sizeof(m_byBuffer);
    if(len == 64)  //是否等于64个字节
    {
       qDebug()<<"protocol Lengh is Right";
       return true;
    }
    else
    {
        qDebug()<<"Warning protocol Lengh is : "<<len<<"Byte";
        return false;
    }
}

int CPorotocol::random()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

        int test =qrand()%3+10;
        return test;
}

void CPorotocol::DecodeSpeed()
{
    THAngle tHAngle;

    // 1.解析水平角度

    float fangle = convert2short(m_byBuffer[3],m_byBuffer[4]);
    tHAngle.fAngle = (fangle*180/32767);

    float ferror = convert2short(m_byBuffer[6],m_byBuffer[7]);
    tHAngle.fError = ferror/100;
    qDebug()<<"fError is"<< tHAngle.fError;

    m_pDataManager->SetHAngleData(tHAngle);
    // 2.发送信号到界面 更新数据
    emit SigProtoDecodedData(3);
}
