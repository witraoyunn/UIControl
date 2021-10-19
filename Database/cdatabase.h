#ifndef CDATABASE_H
#define CDATABASE_H

#include <QtSql>
#include <QString>
#include "UIControldefine.h"

// 以下依照上述结构体定义方式定义数据库中所有的表的字段
// CDataBase整个类只能有一个对象 使用的时候创建一个全局成员指针 构造函数中构建一个对象 其他使用的地方通过传指针的方式 本类中针对m_db的操作要加互斥锁
// 以后有时间可以将该类改为单例模式
// 本类要完成数据的访问操作 对各个表进行增删查

class CDataBase
{
public:
    CDataBase();
    ~CDataBase();
    qint64 m_nStoreTime;
    qint64 m_nLastStoreTime;

    // 以下是对每个表的增、删、查的操作方法
    // 1.t_hl_angle
    int InsertHLAngle(const TVAngle &hlAngle);            // 向高低角度表中插入一条数据
    void SelectCurHLAngle(QList<TVAngle> &lstHLAngle);    // 把当前的高低角数据取出来
    void SelectLastHLAngle(QList<TVAngle> &lstHLAngle);   // 把上一条高低角数据取出来
    
private:
    QSqlDatabase m_db;
    QMutex m_mutex;
};

#endif // CDATABASE_H
