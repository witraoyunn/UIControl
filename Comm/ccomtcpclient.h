#ifndef CCOMCLIENT_H
#define CCOMCLIENT_H

#include <QTcpSocket>
#include "./Porotocol/cporotocol.h"
#include "./Database/cdatabase.h"

// 客户端连接资源 用于负责与客户端进行通信 并且引导数据到协议类进行解析
// 在此处处理客户端登录 答案结果计算 考试成绩反馈等业务逻辑 基于分层的架构：业务逻辑应该放到另一个类中处理，因为涉及消息处理等较复杂，以后再用，当前架构满足需求
class CComTcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CComTcpClient(QObject *parent = 0);
    int m_nDescriptor;      // 客户端的ID 用于客户端之间区别

    void BeginWork();
    int nSendData(const QByteArray &bySendData, int nLen);
    void SetDataBase(CDataBase *pDataBase);

    // 创建每一条报文的对象 进行数据解析
    //CMsgLogin m_msgLogin;

protected:
    QByteArray m_byRecvData;        // 用于保存接收数据的缓冲 沾包前
    CDataBase *m_pDatabase;

signals:
    void ClientDisconnectedSigl(int);

protected slots:
    void OnRecvData();
    void OnClientDisconnected();
};

#endif // CCOMCLIENT_H
