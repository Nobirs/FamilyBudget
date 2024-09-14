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
    string query = "INSERT INTO users (username, password_hash, role) VALUES ('" +
        user.getUsername() + "', '" + user.getPasswordHash() + "', '" + role + "')";
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Failed to insert user: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

User UserRepository::getUserByUsername(const std::string &username) {
    string query = "SELECT username, password_hash, role FROM users WHERE username = '" + username + "'";
    mysql_query(conn, query.c_str());
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    if (row) {
        string role = row[2];

        UserRole userRole = UserRole::USER;
        if (role == "ADMIN") userRole = UserRole::ADMIN;
        else if (role == "FAMILY_MEMBER") userRole = UserRole::FAMILY_MEMBER;

        User user = User::createUser(row[0], row[1], userRole);
        mysql_free_result(result);
        return user;
    }

    mysql_free_result(result);
    throw std::runtime_error("User not found");
}

vector<User> UserRepository::getAllUsers() {
    string query = "SELECT username, password_hash, role FROM users";
    mysql_query(conn, query.c_str());
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    vector<User> users;

    while ((row = mysql_fetch_row(result))) {
        string role = row[2];

        UserRole userRole = UserRole::USER;
        if (role == "ADMIN") userRole = UserRole::ADMIN;
        else if (role == "FAMILY_MEMBER") userRole = UserRole::FAMILY_MEMBER;
        User user = User::createUser(row[0], row[1], userRole);
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


UserRepository::~UserRepository() {
    if(conn != NULL) mysql_close(conn);
}