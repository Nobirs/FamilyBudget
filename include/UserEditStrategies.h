#ifndef EDITSTRATEGIES_H
#define EDITSTRATEGIES_H

#include "User.h"
#include <iostream>
#include "UserRepository.h"

// Интерфейс IEditStrategy
class IEditStrategy {
public:
    virtual ~IEditStrategy() {}
    virtual void apply(User& user, const std::string& value) = 0;
};

// Стратегия для изменения email
class EditEmailStrategy : public IEditStrategy {
public:
    void apply(User& user, const std::string& value) override {
        user.setEmail(value);
        std::cout << "Email updated to " << value << std::endl;
    }
};

// Стратегия для изменения username
class EditUsernameStrategy : public IEditStrategy {
public:
    void apply(User& user, const std::string& value) override {
        user.setUsername(value);
        std::cout << "Username updated to " << value << std::endl;
    }
};

// Стратегия для изменения password
class EditPasswordStrategy : public IEditStrategy {
public:
    void apply(User& user, const std::string& value) override {
        user.changePassword(value); 
        std::cout << "Password updated" << std::endl;
    }
};

// Стратегия для изменения role
class EditRoleStrategy : public IEditStrategy {
public:
    void apply(User& user, const std::string& value) override {
        UserRole role = UserRole::USER;
        if (value == "ADMIN") role = UserRole::ADMIN;
        else if (value == "FAMILY_MEMBER") role = UserRole::FAMILY_MEMBER;
        user.setRole(role);
        std::cout << "Role updated" << std::endl;
    }
};

// Стратегия для изменения budgetLimit
class EditBudgetLimitStrategy : public IEditStrategy {
public:
    void apply(User& user, const std::string& value) override {
        try {
            double newLimit = std::stod(value);
            user.setBudgetLimit(newLimit);
            std::cout << "BudgetLimit updated to " << newLimit << std::endl;
        }
        catch (std::invalid_argument& e) {
            std::cerr << "Invalid value for budget limit: " << value << std::endl;
        }
    }
};

#endif  // EDITSTRATEGIES_H
