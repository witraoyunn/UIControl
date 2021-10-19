#ifndef CPOROTOCOL_H
#define CPOROTOCOL_H

#include <QString>
#include <QThread>
#include "./DataManager/cdatamanager.h"

// 本类一个对象代表着一条报文  成员变量存储报文解析后的结果 每条报文对应一个类 重写自己的打包和解析函数

class CPorotocol : public QObject
{
    Q_OBJECT
public:
    CPorotocol();
    ~CPorotocol();

    void DecodeData();
    int EncodeData();
    void RegistDataManager(CDataManager *pDataManager);
public:
    char m_byBuffer[64];      // 全局的Buffer保存接收到的/要发送的数据
    int m_nDecodeDataLen;     // 保存需要解析的数据长度

    CDataManager *m_pDataManager;
    QWidget *m_pWgtReceiver;

    void DecodeVAngle();
    void DecodeHAngle();
    void DecodeSpeed();

    int m_nTestHAngle = -13;       // 用于测试
    int m_nTestVAngle = -0;       // 用于测试
    bool m_bTestBigH = false;        // 用于测试
    bool m_bTestBigV = false;        // 用于测试
    virtual void timerEvent(QTimerEvent *event);    //  用于测试
    float convert2short(char a,char b);         //用于转换2个char到一个short
    int checkHead();      //检查报文头
    int nHeadState;
    bool checkLengh();      //检查报文长度
    bool bLenghState;
    int random();           //获取随机数


signals:
    void SigProtoDecodedData(int nRecvType);
};

#endif // CPOROTOCOL_H
