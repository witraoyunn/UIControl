#include "cdatamanager.h"
#include <QDebug>
CDataManager::CDataManager()
{

}

void CDataManager::SetVAngleData(const TVAngle &tAngle)
{
    m_readWriteLock[0].lockForWrite();
    m_tVAngle = tAngle;
    m_readWriteLock[0].unlock();
}

void CDataManager::GetVAngleData( TVAngle &tAngle)
{
    m_readWriteLock[0].lockForRead();
    //qDebug()<<m_tVAngle.fAngle;
    tAngle = m_tVAngle;
    //qDebug()<<tAngle.fAngle;
    m_readWriteLock[0].unlock();
}

void CDataManager::SetSwayAngleData(const TSwayAngle &tAngle)
{
    m_readWriteLock[1].lockForWrite();
    m_tSwayAngle = tAngle;
    m_readWriteLock[1].unlock();
}

void CDataManager::GetSwayAngleData(TSwayAngle &tAngle)
{
    m_readWriteLock[1].lockForRead();
    tAngle = m_tSwayAngle;
    m_readWriteLock[1].unlock();
}

void CDataManager::SetCmdUpData(const TCmdUp &tCmdUp)
{
    m_readWriteLock[2].lockForWrite();
    m_tCmdUp = tCmdUp;
    m_readWriteLock[2].unlock();
}

void CDataManager::GetCmdUpData(TCmdUp &tCmdUp)
{
    m_readWriteLock[2].lockForRead();
    tCmdUp = m_tCmdUp;
    m_readWriteLock[2].unlock();
}

void CDataManager::SetHAngleData(const THAngle &tAngle)
{
    m_readWriteLock[3].lockForWrite();
    m_tHAngle = tAngle;
    m_readWriteLock[3].unlock();
}

void CDataManager::GetHAngleData(THAngle &tAngle)
{
    m_readWriteLock[3].lockForRead();
    tAngle = m_tHAngle;
    m_readWriteLock[3].unlock();
}

void CDataManager::SetUpAngleData(const TUpAngle &tAngle)
{
    m_readWriteLock[4].lockForWrite();
    m_tUpAngle = tAngle;
    m_readWriteLock[4].unlock();
}

void CDataManager::GetUpAngleData(TUpAngle &tAngle)
{
    m_readWriteLock[4].lockForRead();
    tAngle = m_tUpAngle;
    m_readWriteLock[4].unlock();
}

void CDataManager::SetCmdHData(const TCmdH &tAngle)
{
    m_readWriteLock[5].lockForWrite();
    m_tCmdH = tAngle;
    m_readWriteLock[5].unlock();
}

void CDataManager::GetCmdHData(TCmdH &tAngle)
{
    m_readWriteLock[5].lockForRead();
    tAngle = m_tCmdH;
    m_readWriteLock[5].unlock();
}

void CDataManager::SetKeyStateData(const CKeyState &tAngle)
{
    m_readWriteLock[6].lockForWrite();
    m_keyState = tAngle;
    m_readWriteLock[6].unlock();
}

void CDataManager::GetKeyStateData(CKeyState &tAngle)
{
    m_readWriteLock[6].lockForRead();
    tAngle = m_keyState;
    m_readWriteLock[6].unlock();
}
