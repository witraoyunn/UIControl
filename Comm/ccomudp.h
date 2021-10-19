#ifndef CCOMUDP_H
#define CCOMUDP_H

#include <QObject>
#include <QUdpSocket>
#include "Porotocol/cporotocol.h"


class ccomudp : public QObject
{
    Q_OBJECT
public:
    ccomudp(QObject *parent);
    ~ccomudp();

    int nSendData(const QByteArray &bySendData, int nSendLen);

    void RegistDataManager(CDataManager *pDataManager);

private:
    QUdpSocket *m_pUdpSocket;
    CPorotocol *m_pPorotocolDecode;
    CDataManager *m_pDataManager;


signals:
    void SigUpdateUIData(int nRecvType);
public slots:
    void ReceiveUDP();
    void SlotUpdateUIData(int nRecvType);
};

#endif // CCOMUDP_H
