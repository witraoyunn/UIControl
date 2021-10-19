#ifndef CCOMSERVER_H
#define CCOMSERVER_H

#include <QTcpServer>
#include "ccomtcpclient.h"

// 创建服务端socket 进行端口监听 响应新的连接 创建客户端连接资源 连接断开时释放连接资源
class CComTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CComTcpServer(QObject *parent = 0);
    ~CComTcpServer();

    void SetDataBase(CDataBase *pDataBase);   // 将数据库指针传递给Server类
    void BeginWork();

    QList<CComTcpClient*> m_lstClient;                 // 保存客户端的连接资源 该连接资源由QTcpServer管理

    // 定义Server端收到的所有报文的对象 收到数据后通过该对象解析并保存数据
    //CMsgLogin m_msgLogin;

protected:
    void incomingConnection(int nSocketDesptr);
    CDataBase *m_pDataBase;

signals:

public slots:
//    void OnNewConnect(int nDescriptor);           // 有新的连接
    void OnDisConnect(int nDescriptor);             // 客户端断开连接
};

#endif // CCOMSERVER_H
