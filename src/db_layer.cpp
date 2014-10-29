#include "db_layer.h"
#include <exception>
#include <QtWidgets/QMessageBox>

//#define PRINTERROR(exp, error) if(!exp) { std::cout<<error.text().toStdString()<<std::endl; }
#define PRINTERROR(exp, text) if(!exp) { QMessageBox::information(NULL, "Error", text, QMessageBox::Yes, QMessageBox::Yes); }

Database::Database(const QString& schemaName,
                   const QString& userName,
                   const QString& password,
                   const QString& hostName)
    : _schemaName(schemaName), _database(QSqlDatabase::addDatabase("QMYSQL", "em_sys"))
{
    _database.setHostName(hostName);
    _database.setDatabaseName(schemaName);
    _database.setUserName(userName);
    _database.setPassword(password);
    
    if (!_database.open())
    {
        throw std::logic_error(_database.lastError().text().toStdString());
    }

    QSqlError error = checkTables();

    login("admin", "123456");
    
    if (error.isValid())
    {
        throw std::logic_error(error.text().toStdString());
    }

   /* 
   //²âÊÔ
   registration(
    {0, "name", 
    "description", 
    "2014-10-18", 
    "registrationOperator",
    0, 0, false, 0, QImage(), "" });
    
    auto lst = getEquipmentList(0, 1000);
    
    auto v = lst.front();
    v._name = ".";
    updateEquipment(v);
	*/
    
    //std::cout<< x <<std::endl;
}

Database::~Database()
{
    if (_database.isOpen())
        _database.close();
    QSqlDatabase::removeDatabase("em_sys");
}

bool Database::login(const QString& user, const QString& password)
{
    QSqlQuery query(_database);

    PRINTERROR(query.exec("SELECT * FROM t_user WHERE name = \"" + user + "\";"), query.lastError().text());

    while (query.next()) {
        QString pwd = query.value(1).toString();
        if (password == pwd)
        {
            _currentUser = query.value(0).toString();
            return true;
        }
    }

    return false;
}

std::vector<EquipmentData> Database::getEquipmentList(uint pos, uint len)
{
    if (_currentUser.isEmpty())
        return {};
    
    std::vector<EquipmentData> result;
    
    QSqlQuery query(_database);
    
    query.prepare(R"(SELECT * FROM t_equipment LIMIT ?, ?)");
    
    query.addBindValue(pos);
    query.addBindValue(len);
    
    PRINTERROR(query.exec(), query.lastError().text());
    
    while (query.next()) {
        EquipmentData d = {
            query.value(0).toUInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toUInt(),
            query.value(6).toUInt(),
            query.value(7).toBool(),
            query.value(8).toUInt(),
            QImage(),
            query.value(10).toString()
        };
        result.push_back(d);
    }

    return std::move(result);
}

bool Database::updateEquipment(const EquipmentData& equipment)
{
    if (_currentUser.isEmpty())
        return false;
    
    QSqlQuery query(_database);
    
    query.prepare(R"(UPDATE t_equipment SET
                  name = ?,
                  description = ?,
                  registration_date = ?,
                  registration_operator = ?,
                  value = ?,
                  lendPrice = ?,
                  is_lending = ?,
                  recent_lend_record = ?,
                  image = ?,
                  remark = ?
                  WHERE id = ?)");
    
    query.addBindValue(equipment._name);
    query.addBindValue(equipment._description);
    query.addBindValue(equipment._registrationDate);
    query.addBindValue(_currentUser);
    query.addBindValue(equipment._value);
    query.addBindValue(equipment._lendPrice);
    query.addBindValue(equipment._isLending ? "Y" : "N");
    query.addBindValue(equipment._recentLendRecord);
    query.addBindValue(QByteArray());
    query.addBindValue(equipment._remark);
    query.addBindValue(equipment._id);
    
    PRINTERROR(query.exec(), query.lastError().text());
    
    return true;

}

std::size_t Database::getEquipmentCount() const
{
    if (_currentUser.isEmpty())
        return 0;
    
    QSqlQuery query(_database);
    
    PRINTERROR(query.exec("SELECT * FROM t_equipment;"), query.lastError().text());
    
    return query.size();
}

bool Database::registration(const EquipmentData& equipment)
{
    if (_currentUser.isEmpty())
        return false;

    QSqlQuery query(_database);

    query.prepare(R"(INSERT INTO t_equipment(
        name,
        description, 
        registration_date, 
        registration_operator, 
        value, 
        lendPrice, 
        is_lending, 
        recent_lend_record, 
        image,
        remark)
        VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?);)");

    query.addBindValue(equipment._name);
    query.addBindValue(equipment._description);
    query.addBindValue(equipment._registrationDate);
    query.addBindValue(_currentUser);
    query.addBindValue(equipment._value);
    query.addBindValue(equipment._lendPrice);
    query.addBindValue(equipment._isLending ? "Y" : "N");
    query.addBindValue(equipment._recentLendRecord);
    query.addBindValue(QByteArray());
    query.addBindValue(equipment._remark);

    PRINTERROR(query.exec(), query.lastError().text());

    return true;
}

QSqlError Database::checkTables()
{
    QSqlQuery query(_database);

    if (!query.exec("SELECT * FROM t_user;"))
    {
        if (!query.exec(R"(
            CREATE TABLE t_user
            ( 
                name VARCHAR(64) PRIMARY KEY NOT NULL,
                pwd VARCHAR(64)
            );)"))
        {
            return query.lastError();
        }

        query.exec(R"(SET names gbk; INSERT INTO t_user VALUES("admin", "123456"))");

    }

    if (!query.exec("SELECT * FROM t_equipment;"))
    {
        if (!query.exec(R"(
            CREATE TABLE t_equipment
            ( 
                id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
                name VARCHAR(64),
                description VARCHAR(128) NOT NULL, 
                registration_date DATE NOT NULL,
                registration_operator VARCHAR(64) NOT NULL,
                value INT NOT NULL,
                lendPrice INT NOT NULL,
                is_lending SET("Y", "N") NOT NULL,
                recent_lend_record INT,
                image LONGBLOB, 
                remark VARCHAR(128)
            );)"))
        {
            return query.lastError();
        }
    }

    if (!query.exec("SELECT * FROM t_record;"))
    {
        if (!query.exec(R"(
            CREATE TABLE t_record
            ( 
                id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
                is_lend SET("Y", "N") NOT NULL,
                operator VARCHAR(64) NOT NULL,
                record_date DATE NOT NULL,
                receivables INT NOT NULL,
                remark VARCHAR(128)
            );)"))
        {
            return query.lastError();
        }
    }

    return QSqlError();
}
