#include "ccomtcpserver.h"

CComTcpServer::CComTcpServer(QObject *parent):QTcpServer(parent)
{
    m_pDataBase = NULL;
}

CComTcpServer::~CComTcpServer()
{
    for (int i = 0; i < m_lstClient.count(); i++)
    {
        CComTcpClient *pClient = m_lstClient.at(i);
        pClient->deleteLater();
    }
    m_lstClient.clear();
}

// 将数据库对象指针传入 方便在处理Server端逻辑时使用
void CComTcpServer::SetDataBase(CDataBase *pDataBase)
{
    m_pDataBase = pDataBase;
}

// 开启服务端监听
void CComTcpServer::BeginWork()
{
    listen(QHostAddress::Any, 10001);
}

// 重载incomingconnection 接收新的连接，创建连接对象
void CComTcpServer::incomingConnection(int nSocketDesptr)
{
    CComTcpClient *pClient = new CComTcpClient();
    pClient->setSocketDescriptor(nSocketDesptr);
    pClient->SetDataBase(m_pDataBase);
    pClient->BeginWork();
    m_lstClient.push_back(pClient);
    connect(pClient, SIGNAL(ClientDisconnectedSigl(int)), this, SLOT(OnDisConnect(int)));
}

// 响应客户端主动断开连接 删除并释放client套接字
void CComTcpServer::OnDisConnect(int nDescriptor)
{
    // 断开连接时，可以在此处删除m_lstClient的节点
    for (int i = 0; i < m_lstClient.count(); i++)
    {
        CComTcpClient *pClient = m_lstClient.at(i);
        int nDesDelete = pClient->socketDescriptor();
        if (nDesDelete == -1 || nDesDelete == nDescriptor)
        {
            m_lstClient.removeAt(i);
            pClient->deleteLater();
            return;
        }
    }
}
