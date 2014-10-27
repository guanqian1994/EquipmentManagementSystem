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

/// …Ë±∏–≈œ¢
struct EquipmentData
{
    uint        _id;
    QString     _name;              /// …Ë±∏√˚≥∆
    QString     _description;       /// …Ë±∏√Ë ˆ
    QString     _registrationDate;  /// µ«º«»’∆⁄
    QString     _registrationOperator;/// µ«º«≤Ÿ◊˜‘±£®µ±«∞”√ªß£©
    uint        _value;             /// º€÷µ
    uint        _lendPrice;         /// ≥ˆ◊‚º€∏Ò£®Ω®“È£©
    bool        _isLending;         ///  «∑Ò’˝‘⁄ΩË≥ˆ◊¥Ã¨
    uint        _recentLendRecord;  /// ◊ÓΩ¸“ª¥ŒΩË≥ˆº«¬º
    QImage      _image;             /// …Ë±∏Õº∆¨
    QString     _remark;            ///±∏◊¢
};

/// ΩË≥ˆ£®πÈªπ£©º«¬º
struct LendRecord
{
    uint        _id;
    bool        _isLend;            ///  «∑Ò «ΩË≥ˆµƒº«¬º
    QString     _operator;          /// µ«º«≤Ÿ◊˜‘±£®µ±«∞”√ªß£©
    QString     _date;              /// »’∆⁄
    uint        _receivables;       ///  ’øÓ
    QString     _remark;            /// ±∏◊¢
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