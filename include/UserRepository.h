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
    bool deleteUser(const string &username);
    bool updateUser(int userId, const User &user);
    bool resetPassword(const string &username, const string &newPassword);
    bool changePasswordHash(const string &username, const string&newPasswordHash);
    bool updateUsername(const string &oldUsername, const string &newUsername);
    bool updateUserRole(const string &username, UserRole newRole);
    bool updateUserFamilyId(const string &username, int newFamilyId);
    bool updateUserById(int userId, const User &user);

    User getUserById(int userId);
    User getUserByUsername(const string &username);
    vector<User> getAllUsers();
    void clearUsersTable();

    bool updateEmail(const string &username, const string &newEmail);
    bool updateBudgetLimit(const string &username, double newLimit);
};

#endif
