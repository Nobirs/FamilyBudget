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

bool UserRepository::updateUser(int userId, const User &user) {
    string query = "UPDATE users SET "
                    "username = '" + user.getUsername() + "', "
                    "email = '" + user.getEmail() + "', "
                    "password_hash = '" + user.getPasswordHash() + "', "
                    "role = " + "'" + user.getRoleStr() + "'" + ", "
                    "financial_role = '" + user.getFinancialRole() + "', "
                    "budget_limit = " + std::to_string(user.getBudgetLimit()) + ", "
                    "family_status = '" + user.getFamilyStatus() + "', "
                    "family_id = " + (user.getFamilyId() ? std::to_string(user.getFamilyId()) : "NULL") + " "
                    "WHERE id = " + std::to_string(userId);

    // Выполняем SQL-запрос
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
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

bool UserRepository::changePasswordHash(const string &username, const string &newPasswordHash) {
    string query = "UPDATE users SET password_hash = '" + newPasswordHash + "' WHERE username = '" + username + "'";
    if(mysql_query(conn, query.c_str())){
        cerr << "Error resetting passwordHash: " << mysql_error(conn) << std::endl;
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
    string familyId = newFamilyId == NULL ? "NULL" : std::to_string(newFamilyId);

    string query = "UPDATE users SET family_id = '" + familyId + "' WHERE username = '" + username + "'";
    
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
        int familyId = 0;
        if (row[9] != NULL) familyId = std::stoi(row[9]);

        User user = User::createUser(username, passwordHash, userRole, email, registrationDate, financialRole, budgetLimit, familyStatus, familyId);
        return user;
    }

    mysql_free_result(result);
    throw std::runtime_error("User not found");
}

User UserRepository::getUserById(int userId) {
    string query = "SELECT username, password_hash, role, email, registration_date, last_login, financial_role, budget_limit, family_status, family_id FROM users WHERE id = " + std::to_string(userId);
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
        int familyId = 0;
        if (row[9] != NULL) familyId = std::stoi(row[9]);

        User user = User::createUser(username, passwordHash, userRole, email, registrationDate, financialRole, budgetLimit, familyStatus, familyId);
        return user;
    }

    mysql_free_result(result);
    throw std::runtime_error("User not found");
}

bool UserRepository::updateUserById(int userId, const User &user) {
    string roleStr = "USER";
    if (user.getRole() == UserRole::ADMIN) roleStr = "ADMIN";
    else if (user.getRole() == UserRole::FAMILY_MEMBER) roleStr = "FAMILY_MEMBER";
    string query = "UPDATE users SET ";
    query += "username = '" + user.getUsername() + "', ";
    query += "email = '" + user.getEmail() + "', ";
    query += "password_hash = '" + user.getPasswordHash() + "', ";
    query += "role = '" + roleStr + "', ";
    query += "financial_role = '" + user.getFinancialRole() + "', ";
    query += "budget_limit = " + std::to_string(user.getBudgetLimit()) + ", ";
    query += "family_status = '" + user.getFamilyStatus() + "', ";
    query += "family_id = " + std::to_string(user.getFamilyId()) + " ";
    query += "WHERE id = " + std::to_string(userId);

    // Выполняем запрос
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
    
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
        int familyId = 0;
        if (row[9] != NULL) familyId = std::stoi(row[9]);

        User user = User::createUser(username, passwordHash, userRole, email, registrationDate, financialRole, budgetLimit, familyStatus, familyId);
        users.push_back(user);
    }

    mysql_free_result(result);
    return users;
}

void UserRepository::clearUsersTable() {
    if (conn) {
        const char* disable_fk_checks = "SET FOREIGN_KEY_CHECKS = 0;";
        const char* truncate_table = "TRUNCATE TABLE users;";
        const char* enable_fk_checks = "SET FOREIGN_KEY_CHECKS = 1;";

        if (mysql_query(conn, disable_fk_checks)) { cerr << "Error disabling foreign key checks: " << mysql_error(conn) << std::endl; }

        if (mysql_query(conn, truncate_table)) { cerr << "Error truncating users table: " << mysql_error(conn) << std::endl; }
        else { cout << "Users table cleared successfully." << std::endl; }

        if (mysql_query(conn, enable_fk_checks)) { cerr << "Error enabling foreign key checks: " << mysql_error(conn) << std::endl; }
    
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