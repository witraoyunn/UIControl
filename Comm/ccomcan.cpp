#include "ccomcan.h"

CComCan::CComCan(const int &nInterval)
{
    m_nInterval = nInterval;
    m_pPorotocolDecode = new CPorotocol();
    connect(m_pPorotocolDecode, SIGNAL(SigProtoDecodedData(int)), this, SLOT(SlotUpdateUIData(int)));
}

CComCan::~CComCan()
{
    if (m_pPorotocolDecode)
    {
        delete m_pPorotocolDecode;
        m_pPorotocolDecode = NULL;
    }
}

int CComCan::SendData(const char *pBuffer, int nSize)
{
    return 0;
}

void CComCan::RegistDataManager(CDataManager *pDataManager)
{
    m_pDataManager = pDataManager;
    m_pPorotocolDecode->RegistDataManager(m_pDataManager);
}

void CComCan::run()
{
    int nReadCnt = 0;
    char byBufferRecv[64];

    while (true)
    {
        // 1.读取CAN数据
        if (nReadCnt > 0 && nReadCnt < 64)
        {
            m_pPorotocolDecode->m_nDecodeDataLen = nReadCnt;
            memcpy(m_pPorotocolDecode->m_byBuffer, byBufferRecv, nReadCnt);

            // 2.数据读取完成后马上交给协议层解析
            m_pPorotocolDecode->DecodeData();
        }
        msleep(m_nInterval);
    }
}

void CComCan::SlotUpdateUIData(int nRecvType)
{
    emit SigUpdateUIData(nRecvType);
}
