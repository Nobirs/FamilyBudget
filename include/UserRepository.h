#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H


#include <mysql/mysql.h>
#include "User.h"
#include <vector>


using std::string;
using std::vector;


class UserRepository {
private:
    MYSQL *conn;

public:
    UserRepository();
    UserRepository(MYSQL *connection);
    ~UserRepository();

    bool addUser(const User &user);
    User getUserByUsername(const string &username);
    vector<User> getAllUsers();
    void clearUsersTable();
};

#endif