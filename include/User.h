#ifndef USER_H  
#define USER_H

#include <string>
#include <iostream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>


using std::string;
using std::stringstream;
using std::cout;
using std::cin;
using std::cerr;


enum class UserRole {
    ADMIN,
    USER,
    FAMILY_MEMBER
};


class UserRepository;


class User {
private:
    string username;
    string passwordHash;
    UserRole role;

    User();
    string hashPassword(const string &password) const;
    static User createUser(const string &username, const string &passwordHash, UserRole role);

public:
    User(const string &username, const string &password, UserRole role);
    const string &getUsername() const;
    bool authenticate(const string &inputPassword) const;
    UserRole getRole() const;
    const string &getPasswordHash() const;
    void changePassword(const string &newPassword);

    friend class UserRepository;
};

#endif