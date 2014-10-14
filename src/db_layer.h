#ifndef DB_LAYER_H
#define DB_LAYER_H

#include <string>
#include <vector>
#include "singleton.h"

struct EquipmentData
{

};

struct LendRecord
{
};

class Database : Singleton<Database>
{
public:
    Database();
    ~Database();

    /// ��¼�˻�
    bool login(const std::string& user, const std::string& password);
    /// ��¼�˻�
    bool isLogin();

    /// ��ѯ�豸�б�
    std::vector<EquipmentData> search(const std::string& name);
    /// ����豸�б�
    std::vector<EquipmentData> equipmentList(const std::string& name);
    /// �Ǽ����豸
    bool registration(const EquipmentData& equipment);
    /// ��ñ�������б�
    std::vector<EquipmentData> lendlist;
    /// ��ý����¼
    std::vector<EquipmentData> lendRecord;
    /// ����豸
    bool lend(const EquipmentData& equipment);
    /// �˻��豸
    bool refund(const EquipmentData& equipment);
    
private:
};

#endif