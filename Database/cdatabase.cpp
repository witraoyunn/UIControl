#include "cdatabase.h"
#include <QSqlError>

CDataBase::CDataBase()
{
    // 数据库初始化
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("uicontrol.db");
    if (!m_db.open())
    {
        QString strError = m_db.lastError().text();
        qDebug()<<"Open DataBase Error!";
    }
}

CDataBase::~CDataBase()
{
    m_db.close();
}

int CDataBase::InsertHLAngle(const TVAngle &hlAngle)
{
    QSqlQuery queryInsert(m_db);

    m_mutex.lock();
    queryInsert.prepare("insert into t_hl_angle(StoreTime,DataTime,Angle,Error)"
                        "values(:StoreTime,:DataTime,:Angle,:Error)");
    queryInsert.bindValue(0, m_nStoreTime);
    queryInsert.bindValue(1, hlAngle.nDataTime);
    queryInsert.bindValue(2, hlAngle.fAngle);
    queryInsert.bindValue(3, hlAngle.fError);
    if (!queryInsert.exec())
    {
        QString strError = queryInsert.lastError().text();
        qDebug()<<"Insert into t_user_info error";
    }
    m_mutex.unlock();

    return 0;
}

void CDataBase::SelectCurHLAngle(QList<TVAngle> &lstHLAngle)
{
    QString strSql;
    TVAngle tHLAngle;
    QSqlQuery querySelect(m_db);

    m_mutex.lock();
    strSql = QString("select * from t_hl_angle where StoreTime = %1").arg(m_nStoreTime, 1);
    querySelect.prepare(strSql);
    if (!querySelect.exec())
    {
        QString strError = querySelect.lastError().text();
        qDebug()<<"Select all from t_user_info error!";
    }

    while (querySelect.next())
    {
        tHLAngle.nDataTime = querySelect.value(1).toInt();
        tHLAngle.fAngle = querySelect.value(2).toFloat();
        tHLAngle.fError = querySelect.value(3).toFloat();
        lstHLAngle.push_back(tHLAngle);
    }
    m_mutex.unlock();
}

void CDataBase::SelectLastHLAngle(QList<TVAngle> &lstHLAngle)
{
    QString strSql;
    TVAngle tHLAngle;
    QSqlQuery querySelect(m_db);

    m_mutex.lock();
    strSql = QString("select * from t_hl_angle where StoreTime = %1").arg(m_nLastStoreTime, 1);
    querySelect.prepare(strSql);
    if (!querySelect.exec())
    {
        QString strError = querySelect.lastError().text();
        qDebug()<<"Select all from t_user_info error!";
    }

    while (querySelect.next())
    {
        tHLAngle.nDataTime = querySelect.value(1).toInt();
        tHLAngle.fAngle = querySelect.value(2).toFloat();
        tHLAngle.fError = querySelect.value(3).toFloat();
        lstHLAngle.push_back(tHLAngle);
    }
    m_mutex.unlock();
}
