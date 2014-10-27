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

/// �豸��Ϣ
struct EquipmentData
{
    std::size_t _id;
    QString     _name;              /// �豸����
    QString     _description;       /// �豸����
    QString     _registrationDate;  /// �Ǽ�����
    QString     _registrationOperator;/// �Ǽǲ���Ա����ǰ�û���
    std::size_t _value;             /// ��ֵ
    std::size_t _lendPrice;         /// ����۸񣨽��飩
    bool        _isLending;         /// �Ƿ����ڽ��״̬
    std::size_t _recentLendRecord;  /// ���һ�ν����¼
    QImage      _image;             /// �豸ͼƬ
    QString     _remark;            ///��ע
};

/// ������黹����¼
struct LendRecord
{
    std::size_t _id;
    bool        _isLend;            /// �Ƿ��ǽ���ļ�¼
    QString     _operator;          /// �Ǽǲ���Ա����ǰ�û���
    QString     _date;              /// ����
    std::size_t _receivables;       /// �տ�
    QString     _remark;            /// ��ע
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
    std::size_t Database::getEquipmentCount() const;
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