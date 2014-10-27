#ifndef DB_LAYER_H
#define DB_LAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtCore/QVariant>
#include <QtSql/QSqlRecord>
#include <QtGui/QImage>
#include "singleton.h"

struct EquipmentData
{
    uint        _id;
    QString     _name;             
    QString     _description;       
    QString     _registrationDate;  
    QString     _registrationOperator;
    uint        _value;            
    uint        _lendPrice;       
    bool        _isLending;        
    uint        _recentLendRecord;
    QImage      _image;            
    QString     _remark;           
};


struct LendRecord
{
    uint        _id;
    bool        _isLend;            
    QString     _operator;          
    QString     _date;              
    uint        _receivables;      
    QString     _remark;           
};

class Database : public Singleton<Database>
{
public:
    Database(const QString& schemaName = "sa_user",
             const QString& userName = "sa",
             const QString& password = "_sa12345678",
             const QString& hostName = "127.0.0.1");
    ~Database();
    
    bool login(const QString& user, const QString& password);
    bool isLogin();

    std::vector<EquipmentData> searchEquipment(const QString& name);
    std::vector<EquipmentData> getEquipmentList(uint pos, uint len);
    bool updateEquipment(const EquipmentData& equipment);
    std::size_t getEquipmentCount() const;
    bool registration(const EquipmentData& equipment);
    std::vector<EquipmentData> getLendList;
    std::vector<EquipmentData> getLendRecord;
    bool lend(const EquipmentData& equipment);
    bool refund(const EquipmentData& equipment);
    
private:
    QSqlError checkTables();
    
private:
    QString _schemaName;

    QString _currentUser;

    QSqlDatabase _database;
};

#endif