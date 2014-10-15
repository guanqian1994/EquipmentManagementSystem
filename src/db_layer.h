#ifndef DB_LAYER_H
#define DB_LAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <QtSql/QSqlDatabase>
#include "singleton.h"

struct EquipmentData
{
    long long _id;
};

struct LendRecord
{
};

class Database : Singleton<Database>
{
public:
    Database(const QString& databaseName = "sa_user",
             const QString& userName = "sa",
             const QString& password = "_sa12345678",
             const QString& hostName = "127.0.0.1");
    ~Database();
    
    bool login(const QString& user, const QString& password);
    bool isLogin();

    std::vector<EquipmentData> searchEquipment(const QString& name);
    std::vector<EquipmentData> getEquipmentList(const QString& name);
    bool registration(const EquipmentData& equipment);
    std::vector<EquipmentData> getLendList;
    std::vector<EquipmentData> getLendRecord;
    bool lend(const EquipmentData& equipment);
    bool refund(const EquipmentData& equipment);
    
private:
    void setupDatabase();
    
private:
    QSqlDatabase _database;
};

#endif