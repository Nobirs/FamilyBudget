#ifndef TEDITSTRATEGIES_H
#define TEDITSTRATEGIES_H

#include <iostream>

#include "Transaction.h"
#include "TransactionRepository.h"

// Интерфейс TEditStrategy
class TEditStrategy {
public:
    virtual ~TEditStrategy() {}
    virtual void apply(Transaction& tr, const std::string& value) = 0;
};

// Стратегия для изменения email
class TEditDescriptionStrategy : public TEditStrategy {
public:
    void apply(Transaction& tr, const std::string& value) override {
        tr.setDescription(value);
        std::cout << "Description updated to " << value << std::endl;
    }
};

// Стратегия для изменения username
class TEditAmountStrategy : public TEditStrategy {
public:
    void apply(Transaction& tr, const std::string& value) override {
        tr.setAmount(std::stoi(value));
        std::cout << "Amount updated to " << value << std::endl;
    }
};

// Стратегия для изменения password
class TEditDateStrategy : public TEditStrategy {
public:
    void apply(Transaction& tr, const std::string& value) override {
        tr.setDate(value); 
        std::cout << "Date updated" << std::endl;
    }
};

// Стратегия для изменения role
class TEditTypeStrategy : public TEditStrategy {
public:
    void apply(Transaction& tr, const std::string& value) override {
        tr.setType(value);
        std::cout << "Type updated" << std::endl;
    }
};

// Стратегия для изменения budgetLimit
class TEditUserIdStrategy : public TEditStrategy {
public:
    void apply(Transaction& tr, const std::string& value) override {
        double newUserId = std::stoi(value);
        tr.setUserId(newUserId);
        std::cout << "UserId updated to " << newUserId << std::endl;
    }
};

// Стратегия для изменения budgetLimit
class TEditFamilyIdStrategy : public TEditStrategy {
public:
    void apply(Transaction& tr, const std::string& value) override {
        double newFamilyId = std::stoi(value);
        tr.setFamilyId(newFamilyId);
        std::cout << "FamilyId updated to " << newFamilyId << std::endl;
    }
};

// Стратегия для изменения budgetLimit
class TEditCategoryIdStrategy : public TEditStrategy {
public:
    void apply(Transaction& tr, const std::string& value) override {
        double newCategoryId = std::stoi(value);
        tr.setCategoryId(newCategoryId);
        std::cout << "UserId updated to " << newCategoryId << std::endl;
    }
};


#endif  // TEDITSTRATEGIES_H
