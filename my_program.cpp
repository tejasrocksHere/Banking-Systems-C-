#include <mysql_driver.h>
#include <mysql_connection.h>
#include <iostream>

int main() {
    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        // Create a connection to the database
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "admin", "");

        // Connect to the specific database
        con->setSchema("your_database");

        // Execute a simple query
        sql::Statement *stmt;
        sql::ResultSet *res;

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM your_table");

        // Process the results
        while (res->next()) {
            std::cout << "Column 1: " << res->getString(1) << std::endl;
        }

        // Clean up
        delete res;
        delete stmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }

    return 0;
}
