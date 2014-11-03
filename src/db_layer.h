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

#define SNPRINTF std::snprintf

/// 设备信息
struct EquipmentData
{
    uint        _id;
    QString     _name;              /// 设备名称
    QString     _description;       /// 设备描述
    QString     _registrationDate;  /// 登记日期
    QString     _registrationOperator;/// 登记操作员（当前用户）
    uint        _value;             /// 价值
    uint        _lendPrice;         /// 出租价格（建议）
    bool        _isLending;         /// 是否正在借出状态
    uint        _recentLendRecord;  /// 最近一次借出记录
    QImage      _image;             /// 设备图片
    QString     _remark;            ///备注
};

/// 借出（归还）记录
struct LendRecord
{
    uint        _id;
    uint        _equipment_id;
    bool        _isLend;            /// 是否是借出的记录
    QString     _operator;          /// 登记操作员（当前用户）
    QString     _date;              /// 日期
    uint        _receivables;       /// 收款
    QString     _remark;            /// 备注
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
    bool registration(const EquipmentData& equipment);
    std::size_t getEquipmentCount() const;
    std::vector<LendRecord> getLendRecordList(bool islend, uint yearWithin, uint monthWithin, uint dayWithin);
    bool lend(EquipmentData& equipment, uint receivables, QString remark = "");
    bool refund(EquipmentData& equipment, uint receivables, QString remark = "");

private:
    QSqlError checkTables();

private:
    QString _schemaName;

    QString _currentUser;

    QSqlDatabase _database;
};

#endif