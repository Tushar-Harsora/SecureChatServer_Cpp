#include <mysql_connection.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include "SQLManager.h"

SQLManager& SQLManager::the(){
    static SQLManager m_manager;
    return m_manager;
}

SQLManager::SQLManager(){
    m_driver = get_driver_instance();
}

std::string SQLManager::get_driver_name() const {
    return std::string(m_driver->getName().c_str());
}
