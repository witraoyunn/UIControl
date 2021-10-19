#ifndef CDATAMANAGER_H
#define CDATAMANAGER_H

#include "UIControldefine.h"
#include "QReadWriteLock"

// 这个类用于通信层与界面层的数据传输，通信层线程负责将数据解析后放入然后通过信号的方式通知界面层更新
// 界面层收到更新信号后 将数据取出更新到界面

class CDataManager
{
public:
    CDataManager();
    void SetVAngleData(const TVAngle &tAngle);        // 通信层将需要显示的数据解析后 放到DM 并通过信号通知界面层
    void GetVAngleData(TVAngle &tAngle);              // 界面层收到信号后 通过本方法从DM取出数据

    void SetSwayAngleData(const TSwayAngle &tAngle);
    void GetSwayAngleData(TSwayAngle &tAngle);

    void SetCmdUpData(const TCmdUp &tCmdUp);
    void GetCmdUpData(TCmdUp &tCmdUp);

    void SetHAngleData(const THAngle &tAngle);
    void GetHAngleData(THAngle &tAngle);

    void SetUpAngleData(const TUpAngle &tAngle);
    void GetUpAngleData(TUpAngle &tAngle);

    void SetCmdHData(const TCmdH &tAngle);
    void GetCmdHData(TCmdH &tAngle);

    void SetKeyStateData(const CKeyState &tAngle);
    void GetKeyStateData(CKeyState &tAngle);

private:
    QReadWriteLock m_readWriteLock[10];                 // 用于线程互斥 每一块内存拥有各自的互斥锁
    TVAngle m_tVAngle;       // 高低角度和误差
    TSwayAngle m_tSwayAngle;        // 摆角度和误差
    TCmdUp m_tCmdUp;                // 高低摆的位置指令和速度指令
    THAngle m_tHAngle;              // 水平（方位）角度和误差
    TUpAngle m_tUpAngle;            // 上扬角和误差
    TCmdH m_tCmdH;                  // 方位 上扬位置指令和速度指令
    CKeyState m_keyState;           // 关键状态
};

#endif // CDATAMANAGER_H
