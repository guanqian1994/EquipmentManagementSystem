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

    /// 登录账户
    bool login(const std::string& user, const std::string& password);
    /// 登录账户
    bool isLogin();

    /// 查询设备列表
    std::vector<EquipmentData> search(const std::string& name);
    /// 获得设备列表
    std::vector<EquipmentData> equipmentList(const std::string& name);
    /// 登记新设备
    bool registration(const EquipmentData& equipment);
    /// 获得被借出的列表
    std::vector<EquipmentData> lendlist;
    /// 获得借出记录
    std::vector<EquipmentData> lendRecord;
    /// 借出设备
    bool lend(const EquipmentData& equipment);
    /// 退还设备
    bool refund(const EquipmentData& equipment);
    
private:
};

#endif