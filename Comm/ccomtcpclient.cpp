#include "ccomtcpclient.h"

CComTcpClient::CComTcpClient(QObject *parent) :
    QTcpSocket(parent)
{
}

void CComTcpClient::BeginWork()
{
    m_nDescriptor = this->socketDescriptor();
    connect(this, SIGNAL(readyRead()), this, SLOT(OnRecvData()));
    connect(this, SIGNAL(disconnected()), this, SLOT(OnClientDisconnected()));
}

int CComTcpClient::nSendData(const QByteArray &bySendData, int nLen)
{
    return writeData(bySendData.data(), nLen);
}

void CComTcpClient::SetDataBase(CDataBase *pDataBase)
{
    m_pDatabase = pDataBase;
}

void CComTcpClient::OnClientDisconnected()
{
    emit ClientDisconnectedSigl(m_nDescriptor);
}

void CComTcpClient::OnRecvData()
{
    QByteArray byRecvData;

    byRecvData = readAll();
    if (!byRecvData.isEmpty())
    {
        // 1.沾包


        // 2.根据报文不同交给协议层不同的结构体解析
        // 2.1先解析出报文头string
        // 2.2根据不同的报文头使用不同的对象进行解析
        // 3 将解析后的数据SetDM
        // 4 向界面层发送信号 使界面更新数据

/*        if (baowentou == "login")
        {
            memcpy(m_msgLogin.m_byBuffer, byRecvData, len);
            tLoginIN.DecodeData();

            // 查询数据库 验证用户名 密码 返回登录结果
            TLogin tLoginIN;
            m_pDatabase->Select1UserInfo(m_msgLogin.m_strUserName, tLoginIN);
            if (tLoginIN.strPassword == m_msgLogin.m_tlogin.strPassword)
            {
                // 登录成功
            }
            else
            {
                // 登录失败
            }
        }
        else if (baowentou == "")
        {

        }*/
    }
}
