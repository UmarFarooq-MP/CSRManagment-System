#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager
{
    QSqlDatabase m_db;

public:
    DatabaseManager();
    bool addToDatabase(const QString &Postcode,const QString &rate);
    QString findCharges(const QString &postcode);

};

#endif // DATABASEMANAGER_H
