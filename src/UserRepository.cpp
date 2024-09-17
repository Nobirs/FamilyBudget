#include "UserRepository.h"
#include <iostream>


UserRepository::UserRepository() {
    conn = mysql_init(nullptr);
    if (conn == nullptr) {
        cerr << "mysql_init() failed\n";
        return;
    }

    if (mysql_real_connect(conn, "localhost", "alex", "0811Hades", "family_budget", 0, nullptr, 0) == nullptr) {
        cerr << "mysql_real_connect() failed\n";
        mysql_close(conn);
        return;
    }
}

UserRepository::UserRepository(MYSQL *connection) : conn(connection) {}


bool UserRepository::addUser(const User &user) {
    string role;
    switch(user.getRole()){
        case UserRole::ADMIN: role = "ADMIN"; break;
        case UserRole::USER: role = "USER"; break;
        case UserRole::FAMILY_MEMBER: role = "FAMILY_MEMBER"; break;
        default: role = "USER";
    }
    string query = "INSERT INTO users (username, password_hash, role, email, last_login, financial_role, budget_limit, family_status, family_id) VALUES ('" +
        user.username + "', '" + user.passwordHash + "', '" + role + "', '" + user.email + "', '" + user.getLastLoginStr() + "', '" + 
        user.financialRole + "', '" + std::to_string(user.budgetLimit) + "', '" + user.familyStatus + "', '" + std::to_string(user.familyId) + "')";
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Failed to insert user: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

bool UserRepository::deleteUser(const string &username) {
    string query = "DELETE FROM users WHERE username = '" + username + "'";
    if(mysql_query(conn, query.c_str())) {
        cerr << "Error deleting user: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

bool UserRepository::resetPassword(const string &username, const string &newPassword) {
    string passwordHash = User::hashPassword(newPassword);
    string query = "UPDATE users SET password_hash = '" + passwordHash + "' WHERE username = '" + username + "'";
    if(mysql_query(conn, query.c_str())) {
        cerr << "Error resetting password: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

bool UserRepository::updateUsername(const string &oldUsername, const string &newUsername) {
    string query = "UPDATE users SET username = '" + newUsername + "' WHERE username = '" + oldUsername + "'";
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error updating username: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

bool UserRepository::updateUserRole(const string &username, UserRole newRole) {
    string roleStr = "USER";
    if (newRole == UserRole::ADMIN) roleStr = "ADMIN";
    else if (newRole == UserRole::FAMILY_MEMBER) roleStr = "FAMILY_MEMBER";

    string query = "UPDATE users SET role = '" + roleStr + "' WHERE username = '" + username + "'";
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error updating user role: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

bool UserRepository::updateUserFamilyId(const string &username, int newFamilyId) {
    string query = "UPDATE users SET family_id = '" + std::to_string(newFamilyId) + "' WHERE username = '" + username + "'";
    
    if(mysql_query(conn, query.c_str())) {
        cerr << "Error updating user familyId: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

User UserRepository::getUserByUsername(const std::string &username) {
    string query = "SELECT username, password_hash, role, email, registration_date, last_login, financial_role, budget_limit, family_status, family_id FROM users WHERE username = '" + username + "'";
    mysql_query(conn, query.c_str());
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    if (row) {
        string username = row[0];
        string passwordHash = row[1];

        string role = row[2];
        UserRole userRole = UserRole::USER;
        if (role == "ADMIN") userRole = UserRole::ADMIN;
        else if (role == "FAMILY_MEMBER") userRole = UserRole::FAMILY_MEMBER;
        
        string email = row[3];


        // Преобразование строки в time_t (registration_date)
        std::tm tmReg = {};
        strptime(row[4], "%Y-%m-%d %H:%M:%S", &tmReg);
        time_t registrationDate = std::mktime(&tmReg);

        std::tm tmLogin = {};
        strptime(row[5], "%Y-%m-%d %H:%M:%S", &tmLogin);
        time_t lastLogin = std::mktime(&tmLogin);

        string financialRole = row[6];
        double budgetLimit = std::stod(row[7]);
        string familyStatus = row[8];
        int familyId = std::stoi(row[9]);

        User user = User::createUser(username, passwordHash, userRole, email, registrationDate, financialRole, budgetLimit, familyStatus, familyId);
        return user;
    }

    mysql_free_result(result);
    throw std::runtime_error("User not found");
}

vector<User> UserRepository::getAllUsers() {
    string query = "SELECT username, password_hash, role, email, registration_date, last_login, financial_role, budget_limit, family_status, family_id FROM users";
    mysql_query(conn, query.c_str());
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    vector<User> users;

    while ((row = mysql_fetch_row(result))) {
        string username = row[0];
        string passwordHash = row[1];

        string role = row[2];
        UserRole userRole = UserRole::USER;
        if (role == "ADMIN") userRole = UserRole::ADMIN;
        else if (role == "FAMILY_MEMBER") userRole = UserRole::FAMILY_MEMBER;
        
        string email = row[3];


        // Преобразование строки в time_t (registration_date)
        std::tm tmReg = {};
        strptime(row[4], "%Y-%m-%d %H:%M:%S", &tmReg);
        time_t registrationDate = std::mktime(&tmReg);

        std::tm tmLogin = {};
        strptime(row[5], "%Y-%m-%d %H:%M:%S", &tmLogin);
        time_t lastLogin = std::mktime(&tmLogin);

        string financialRole = row[6];
        double budgetLimit = std::stod(row[7]);
        string familyStatus = row[8];
        int familyId = std::stoi(row[9]);

        User user = User::createUser(username, passwordHash, userRole, email, registrationDate, financialRole, budgetLimit, familyStatus, familyId);
        users.push_back(user);
    }

    mysql_free_result(result);
    return users;
}

void UserRepository::clearUsersTable() {
    if (conn) {
        const char* query = "DELETE FROM users";
        
        if (mysql_query(conn, query)) {
            cerr << "Error clearing users table: " << mysql_error(conn) << std::endl;
        } else {
            cout << "Users table cleared successfully." << std::endl;
        }
    } else {
        cerr << "MySQL connection is not established." << std::endl;
    }
}

bool UserRepository::updateEmail(const string &username, const string &newEmail) {
    if (!User::isValidEmail(newEmail)) {
        std::cerr << "Invalid email format" << std::endl;
        return false;
    }

    string query = "UPDATE users SET email = '" + newEmail + "' WHERE username = '" + username + "'";
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

bool UserRepository::updateBudgetLimit(const string &username, double newLimit) {
    string query = "UPDATE users SET budget_limit = '" + std::to_string(newLimit) + "' WHERE username = '" + username + "'";
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}


UserRepository::~UserRepository() {
    if(conn != NULL) mysql_close(conn);
}