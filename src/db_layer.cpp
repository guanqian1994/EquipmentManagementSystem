#include "db_layer.h"
#include <exception>
#include <QtSql/QSqlError>

Database::Database(const QString& databaseName,
                   const QString& userName,
                   const QString& password,
                   const QString& hostName)
    : _database(QSqlDatabase::addDatabase("QMYSQL", "em_sys"))
{
    _database.setHostName(hostName);
    _database.setDatabaseName(databaseName);
    _database.setUserName(userName);
    _database.setPassword(password);
    
    if (!_database.open())
    {
        throw std::logic_error(_database.lastError().text().toStdString());
    }
}

Database::~Database()
{
    if (_database.isOpen())
        _database.close();
    QSqlDatabase::removeDatabase("em_sys");
}