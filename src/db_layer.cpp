#include "db_layer.h"

#include <ctime>
#include <exception>
#include <QtWidgets/QMessageBox>
#include <QtCore/QBuffer>

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
     registration(
     {0, "name",
     "description",
     "",
     "registrationOperator",
     0, 0, false, 0, QImage(), "" });
*/
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

bool Database::deleteEquipment(uint _id)
{
    if (_currentUser.isEmpty())
        return false;
    
    QSqlQuery query(_database);
    
    query.prepare(R"(DELETE FROM t_record WHERE equipment_id = ?;
                  DELETE FROM t_equipment WHERE id = ?;
                  )");
    
    query.addBindValue(_id);
    query.addBindValue(_id);

    //PRINTERROR(query.exec(), query.lastError().text());

    return query.exec();
}

std::vector<EquipmentData> Database::getEquipmentList(uint pos, uint len, EQUIPMENT_STATE state)
{
    if (_currentUser.isEmpty())
        return {};
    
    std::vector<EquipmentData> result;
    
    QSqlQuery query(_database);
    
    switch (state) {
        case STATE_ALL:
            query.prepare(R"(SELECT * FROM t_equipment LIMIT ?, ?)");
            break;
        case STATE_LENDING:
            query.prepare(R"(SELECT * FROM t_equipment WHERE is_lending='Y' LIMIT ?, ?)");
            break;
        case STATE_UNLENDING:
            query.prepare(R"(SELECT * FROM t_equipment WHERE is_lending='N' LIMIT ?, ?)");
            break;
        default:
            break;
    }
    
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
            query.value(5).toFloat(),
            query.value(6).toFloat(),
            query.value(7) == "Y" ? true:false,
            query.value(8).toUInt(),
            QImage(),
            query.value(10).toString()
        };
        d._image.loadFromData(query.value(9).toByteArray());
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
    // save img
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    equipment._image.save(&buffer, "JPG"); // writes image into ba in PNG format
    query.addBindValue(ba);
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
    // get current date str
    std::time_t t = std::time(NULL);
    char mbstr[24];
    std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d", std::localtime(&t));
    
    query.addBindValue((const char*)mbstr);
    query.addBindValue(_currentUser);
    query.addBindValue(equipment._value);
    query.addBindValue(equipment._lendPrice);
    query.addBindValue(equipment._isLending ? "Y" : "N");
    query.addBindValue(equipment._recentLendRecord);
    // save img
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    equipment._image.save(&buffer, "JPG"); // writes image into ba in PNG format
    query.addBindValue(ba);
    query.addBindValue(equipment._remark);
    
    //PRINTERROR(query.exec(), query.lastError().text());
    
    return query.exec();
}

std::vector<LendRecord> Database::getLendRecordList(EQUIPMENT_STATE state, const QString& from, const QString& to)
{
    if (_currentUser.isEmpty())
        return {};
    
    QSqlQuery query(_database);

    switch (state) {
    case STATE_ALL:
        query.prepare(R"(SELECT * FROM t_record WHERE record_date >= ? AND record_date <= ?;)");
        break;
    case STATE_LENDING:
        query.prepare(R"(SELECT * FROM t_record WHERE is_lend='Y' AND record_date >= ? AND record_date <= ?;)");
        break;
    case STATE_UNLENDING:
        query.prepare(R"(SELECT * FROM t_record WHERE is_lend='N' AND record_date >= ? AND record_date <= ?;)");
        break;
    default:
        break;
    }

    if (from.isEmpty())
    {
        std::time_t t = std::time(NULL);
        char mbstr[24];
        std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d", std::localtime(&t));

        query.addBindValue((const char*)mbstr);
    }
    else
        query.addBindValue(from);

    if (to.isEmpty())
    {
        std::time_t t = std::time(NULL);
        char mbstr[24];
        std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d", std::localtime(&t));

        query.addBindValue((const char*)mbstr);
    }
    else
        query.addBindValue(to);

    PRINTERROR(query.exec(), query.lastError().text());

    std::vector<LendRecord> result;

    while (query.next()) {
        LendRecord r = {
            query.value(0).toUInt(),
            query.value(1).toUInt(),
            query.value(2) == "Y" ? true : false,
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toFloat(),
            query.value(6).toString(),
        };
        result.push_back(r);
    }

    return std::move(result);
}

bool Database::lend(EquipmentData& equipment, uint receivables, const QString& remark)
{
    if (_currentUser.isEmpty())
        return false;
    
    QSqlQuery query(_database);
    
    query.prepare(R"(SELECT * FROM t_equipment WHERE id = ?)");
    query.addBindValue(equipment._id);
    query.exec();
    
    if (query.next() == false)
        return false;   // equipment not exist
    
    if (query.value("is_lending").toString() == "Y")
    {
        equipment._isLending = true;
        return false;
    }
    
    query.prepare(R"(INSERT INTO t_record(
                  equipment_id,
                  is_lend,
                  operator,
                  record_date,
                  receivables,
                  remark)
    VALUES(?, ?, ?, ?, ?, ?);)");
    
    query.addBindValue(equipment._id);
    query.addBindValue("Y");
    query.addBindValue(_currentUser);
    
    // get current date str
    std::time_t t = std::time(NULL);
    char mbstr[24];
    std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d", std::localtime(&t));
    
    query.addBindValue((const char*)mbstr);
    query.addBindValue(receivables);
    query.addBindValue(remark);
    
    PRINTERROR(query.exec(), query.lastError().text());
    
    
    query.prepare(R"(UPDATE t_equipment SET
                  is_lending = ?
                  WHERE id = ?)");
    
    query.addBindValue("Y");
    query.addBindValue(equipment._id);
    query.exec();
    
    equipment._isLending = true;
    
    return true;
}

bool Database::refund(EquipmentData& equipment, uint receivables, const QString& remark)
{
    if (_currentUser.isEmpty())
        return false;
    
    QSqlQuery query(_database);
    
    query.prepare(R"(SELECT * FROM t_equipment WHERE id = ?)");
    query.addBindValue(equipment._id);
    query.exec();
    
    if (query.next() == false)
        return false;    // equipment not exist
    
    if (query.value("is_lending").toString() == "N")
    {
        equipment._isLending = false;
        return false;
    }
    
    query.prepare(R"(INSERT INTO t_record(
                  equipment_id,
                  is_lend,
                  operator,
                  record_date,
                  receivables,
                  remark)
    VALUES(?, ?, ?, ?, ?, ?);)");
    
    query.addBindValue(equipment._id);
    query.addBindValue("N");
    query.addBindValue(_currentUser);
    
    // get current date str
    std::time_t t = std::time(NULL);
    char mbstr[24];
    std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d", std::localtime(&t));
    
    query.addBindValue((const char*)mbstr);
    query.addBindValue(receivables);
    query.addBindValue(remark);
    
    PRINTERROR(query.exec(), query.lastError().text());
    
    
    query.prepare(R"(UPDATE t_equipment SET
                  is_lending = ?
                  WHERE id = ?)");
    
    query.addBindValue("N");
    query.addBindValue(equipment._id);
    query.exec();
    
    equipment._isLending = false;
    
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
                 value FLOAT NOT NULL,
                 lendPrice FLOAT NOT NULL,
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
                     equipment_id INT NOT NULL,
                     is_lend SET("Y", "N") NOT NULL,
                     operator VARCHAR(64) NOT NULL,
                     record_date DATE NOT NULL,
                     receivables FLOAT NOT NULL,
                     remark VARCHAR(128)
                     ); ALTER TABLE t_record ADD CONSTRAINT FK_RECORD_EQUIPMENT_ID FOREIGN KEY(equipment_id) REFERENCES t_equipment(id);)"))
        {
            return query.lastError();
        }
    }

    return QSqlError();
}
