#ifndef USER_H  
#define USER_H

#include <ctime>
#include <regex>
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
using std::time;
using std::time_t;


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
    string email;
    time_t registrationDate;
    time_t lastLogin;
    string financialRole;  // For example: "BUDGET_MANAGER", "FAMILY_MEMBER"
    double budgetLimit;         // Budget limit for current user
    string familyStatus;   // For example: "FAMILY_HEAD", "CHILD"

    static string hashPassword(const string &password);
    static User createUser(const string &username, const string &passwordHash, UserRole role, 
                        const string &email, time_t registrationDate, const string &financialRole, 
                        double budgetLimit, const string& familyStatus);

public:
    User();
    User(const string &username, const string &passwordHash, UserRole role, 
                        const string &email, const string &financialRole="FAMILY_MEMBER", 
                        double budgetLimit=0.0, const string& familyStatus="CHILD");

    const string &getUsername() const;
    void setUsername(const string &newUsername);

    const string &getEmail() const;
    void setEmail(const string &newEmail);

    UserRole getRole() const;
    void setRole(UserRole newRole);

    time_t getRegistrationDate() const;
    string getRegDateStr() const;
    void setRegistrationDate(time_t regDate);

    time_t getLastLogin() const;
    string getLastLoginStr() const;
    void setLastLogin(time_t lastLogin);

    const string &getFinancialRole() const;
    void setFinancialRole(const string &role);

    double getBudgetLimit() const;
    void setBudgetLimit(double limit);
    
    const string &getFamilyStatus() const;
    void setFamilyStatus(const string &status);

    static bool isAdmin(const User &user);
    static bool isValidEmail(const string &email);

    const string &getPasswordHash() const;

    bool authenticate(const string &inputPassword) const;
    void changePassword(const string &newPassword);



    friend class UserRepository;
};

#endif // USER_H