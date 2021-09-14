#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <mysql_driver.h>

class SQLManager{
public:
    SQLManager(SQLManager&) = delete;
    void operator=(const SQLManager&) = delete;
    static SQLManager& the();
    std::string get_driver_name() const;
private:
    SQLManager();
    sql::Driver* m_driver;
};

#endif // SQLMANAGER_H
