#ifndef CCOMCAN_H
#define CCOMCAN_H

#include "./Porotocol/cporotocol.h"

// 19.8.23确认的通信方式为CAN 驱动未定
class CComCan : public QThread
{
    Q_OBJECT
public:
    CComCan(const int &nInterval);
    ~CComCan();
    void RegistDataManager(CDataManager *pDataManager);
    int SendData(const char *pBuffer, int nSize);

protected:
    void run();

private:
    int m_nInterval;
    CDataManager *m_pDataManager;
    CPorotocol *m_pPorotocolDecode;

public:
signals:
    void SigUpdateUIData(int nRecvType);

public slots:
    void SlotUpdateUIData(int nRecvType);
};

#endif // CCOMCAN_H
