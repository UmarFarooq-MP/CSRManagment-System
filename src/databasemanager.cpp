#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

DatabaseManager::DatabaseManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("rates.db");

    if (m_db.open()) {
        qDebug() << "Database: connection ok";
        QSqlQuery query;
        query.prepare("CREATE TABLE IF NOT EXISTS RATEPERPOSTCODE("
                      "Postcode TEXT NOT NULL PRIMARY KEY,"
                      "Rate INT NOT NULL);");
        if (query.exec()) {
            qDebug() << "Tables Created";
        }else {
            qDebug() << "Error in creating Table";
        }
        m_db.close();
    }else {
        qDebug() << "Ërror In Opening Database";
    }
}

bool DatabaseManager::addToDatabase(const QString &Postcode,const QString &rate) {
    if (!m_db.open())
        return false;
    QSqlQuery query;
    query.prepare("INSERT INTO RATEPERPOSTCODE (Postcode,Rate) VALUES (:Postcode,:rate);");
    query.bindValue(":Postcode",Postcode);
    query.bindValue(":rate",rate.toInt());
    if (query.exec()){
        qDebug() << "Wao created";
        qDebug () << query.lastQuery();
        m_db.close();
        return true;
    }
    qDebug () << Postcode ;
    m_db.close();
    return false;
}

QString DatabaseManager::findCharges(const QString &postcode) {
    if (m_db.open()) {
        QSqlQuery query;
        query.prepare("SELECT Rate FROM RATEPERPOSTCODE WHERE Postcode = (:postcode);");
        query.bindValue(":postcode",postcode);
        if (query.exec()) {
            if (query.next()){
                qDebug () << query.value(0).toString();
                return query.value(0).toString();
            }else {
                qDebug() << "Warr gayee";
            }
        }return "-1";
    }return "-1";
}

