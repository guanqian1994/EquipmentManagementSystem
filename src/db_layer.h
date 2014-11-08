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

#ifdef _MSC_VER
#   define SNPRINTF sprintf_s
#else
#   define SNPRINTF std::snprintf
#endif

/// �豸��Ϣ
struct EquipmentData
{
    uint        _id;
    QString     _name;              /// �豸����
    QString     _description;       /// �豸����
    QString     _registrationDate;  /// �Ǽ�����
    QString     _registrationOperator;/// �Ǽǲ���Ա����ǰ�û���
    float        _value;             /// ��ֵ
    float        _lendPrice;         /// ����۸񣨽��飩
    bool        _isLending;         /// �Ƿ����ڽ��״̬
    uint        _recentLendRecord;  /// ���һ�ν����¼
    QImage      _image;             /// �豸ͼƬ
    QString     _remark;            ///��ע
};

/// ������黹����¼
struct LendRecord
{
    uint        _id;
    uint        _equipment_id;
    bool        _isLend;            /// �Ƿ��ǽ���ļ�¼
    QString     _operator;          /// �Ǽǲ���Ա����ǰ�û���
    QString     _date;              /// ����
    float        _receivables;       /// �տ�
    QString     _remark;            /// ��ע
};

class Database : public Singleton<Database>
{
public:
    enum EQUIPMENT_STATE
    {
        STATE_ALL,
        STATE_LENDING,
        STATE_UNLENDING,
    };
    
    Database(const QString& schemaName = "sa_user",
        const QString& userName = "sa",
        const QString& password = "_sa12345678",
        const QString& hostName = "127.0.0.1");
    ~Database();

    bool login(const QString& user, const QString& password);
    bool isLogin();

    bool deleteEquipment(uint _id);
    std::vector<EquipmentData> getEquipmentList(uint pos, uint len, EQUIPMENT_STATE state = STATE_ALL);
    bool updateEquipment(const EquipmentData& equipment);
    bool registration(const EquipmentData& equipment);
    std::size_t getEquipmentCount() const;
    std::vector<LendRecord> getLendRecordList(EQUIPMENT_STATE state, const QString& from, const QString& to = NULL);
    bool lend(EquipmentData& equipment, uint receivables, const QString& remark = "");
    bool refund(EquipmentData& equipment, uint receivables, const QString& remark = "");

private:
    QSqlError checkTables();

private:
    QString _schemaName;

    QString _currentUser;

    QSqlDatabase _database;
};

#endif