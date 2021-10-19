#include "ccomudp.h"

ccomudp::ccomudp(QObject *parent) :
    QObject(parent)
{
    m_pPorotocolDecode = new CPorotocol();
    m_pUdpSocket = new QUdpSocket(this);

    int nbind = m_pUdpSocket->bind(QHostAddress::Any, 8192);
    if(nbind)
    {
        qDebug()<<"UDP bind OK!";
    }
    else
    {
        qDebug()<<"UDP bind Error!";
    }

    connect(m_pUdpSocket, &QUdpSocket::readyRead, this, &ccomudp::ReceiveUDP);
    connect(m_pPorotocolDecode, SIGNAL(SigProtoDecodedData(int)), this, SLOT(SlotUpdateUIData(int)));
}

ccomudp::~ccomudp()
{
    if(m_pUdpSocket)
    {
        m_pUdpSocket->close();
        delete m_pUdpSocket;
        m_pUdpSocket = NULL;
    }

    if (m_pPorotocolDecode)
    {
        delete m_pPorotocolDecode;
        m_pPorotocolDecode = NULL;
    }
}

void ccomudp::RegistDataManager(CDataManager *pDataManager)
{
    m_pDataManager = pDataManager;
    m_pPorotocolDecode->RegistDataManager(m_pDataManager);
}

void ccomudp::ReceiveUDP()
{
    QByteArray byRecv;
    if(m_pUdpSocket->hasPendingDatagrams())
    {
        byRecv.resize(m_pUdpSocket->pendingDatagramSize());
        m_pUdpSocket->readDatagram(byRecv.data(), byRecv.size());
        qDebug()<<"RecvData:"<<byRecv.toHex().toUpper();

        int nReadLen = byRecv.size();
        m_pPorotocolDecode->m_nDecodeDataLen = nReadLen;
        memcpy(m_pPorotocolDecode->m_byBuffer, byRecv.data(), nReadLen);
        m_pPorotocolDecode->DecodeData();
    }
}

int ccomudp::nSendData(const QByteArray &bySendData, int nSendLen)
{
    m_pUdpSocket->writeDatagram(bySendData, nSendLen, QHostAddress("193.0.0.61"), 8192);
}

void ccomudp::SlotUpdateUIData(int nRecvType)
{
    emit SigUpdateUIData(nRecvType);
}
