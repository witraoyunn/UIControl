#ifndef PROTOCOLDEFINE_H
#define PROTOCOLDEFINE_H

#include <QInternal>

// 本头文件保存所有的结构体定义 通信协议结构体 界面与通信层结构体
// 结构体定义尽量增加复用性 避免出现大范围的结构体互转

// 界面角度相关结构体
typedef struct _TVAngle   // 保存舰炮的高低角度和误差
{
    qint64 nDataTime;
    float fAngle;
    float fError;
}TVAngle, *PVAngle;

typedef struct _TSwayAngle     // 保存舰炮的摆角度和误差
{
    qint64 nDataTime;
    float fAngle;
    float fError;
}TSwayAngle, *PTSwayAngle;

typedef struct _TCmdUp         // 保存舰炮的高低、摆的位置指令和速度指令
{
    qint64 nDataTime;
    float fCmdPos;
    float fCmdSpeed;
}TCmdUp, *PTCmdUp;

typedef struct _THAngle        // 保存舰炮的水平(方位)角度和误差
{
    qint64 nDataTime;
    float fAngle;
    float fError;
}THAngle, *PTHAngle;

typedef struct _TUpAngle        // 保存舰炮的上扬架位角度和误差
{
    qint64 nDataTime;
    float fAngle;
    float fError;
}TUpAngle, *PTUpAngle;

typedef struct _TCmdH           // 保存舰炮的方位、上扬位置指令和速度指令
{
    qint64 nDataTime;
    float fCmdPos;
    float fCmdSpeed;
}TCmdH, *PTCmdH;

// 界面关键状态相关
enum emState{
    IniState = 0,
    NorState = 1,
    ErrorState = 2
};
enum emPage{
    PageMain = 0,
    PageShoot,
    PageShootSys,
    PageShootLocal,
    PageShootAsLocal,
    PageSupply,
    PageRepair,
    PageRepairSuiD,
    PageRepairFangW,
    PageRepairGaoDi,
    PageRepairShangY,
    PageRepairBai,
    PageRepairAllS,
    PageRepairState,
    PageReset,
    PageRecordShow
};

class CKeyState           // 关键状态
{
public:
    CKeyState();
    ~CKeyState();
    bool AllStateNor();
    CKeyState operator =(const CKeyState &keyState);

    emState state[28];
};


#endif // PROTOCOLDEFINE_H
