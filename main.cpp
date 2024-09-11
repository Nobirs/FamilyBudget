#include <mysql/mysql.h>
#include <iostream>


void connectToDatabase() {
    MYSQL *conn;
    conn = mysql_init(nullptr);

    if (conn == nullptr) {
        std::cerr << "mysql_init() failed\n";
        return;
    }

    if (mysql_real_connect(conn, "localhost", "alex", "0811Hades", "family_budget", 0, nullptr, 0) == nullptr) {
        std::cerr << "mysql_real_connect() failed\n";
        mysql_close(conn);
        return;
    }

    std::cout << "Connected to database successfully!" << std::endl;

    mysql_close(conn);
}


int main() {
    std::cout << "Family Budget Manager" << std::endl;
    connectToDatabase();
    std::cout << "After connection" << std::endl;
    return 0;
}
