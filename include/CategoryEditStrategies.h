#ifndef CEDITSTRATEGIES_H
#define CEDITSTRATEGIES_H

#include "Category.h"
#include <iostream>
#include "CategoryRepository.h"

// Интерфейс IEditStrategy
class CEditStrategy {
public:
    virtual ~CEditStrategy() {}
    virtual void apply(Category& category, const std::string& value) = 0;
};

// Стратегия для изменения name
class EditNameStrategy : public CEditStrategy {
public:
    void apply(Category& category, const std::string& value) override {
        category.setName(value);
        std::cout << "Name updated to " << value << std::endl;
    }
};

// Стратегия для изменения description
class EditDescriptionStrategy : public CEditStrategy {
public:
    void apply(Category& category, const std::string& value) override {
        category.setDescription(value);
        std::cout << "Description updated to " << value << std::endl;
    }
};

// Стратегия для изменения familyId
class EditFamilyIdStrategy : public CEditStrategy {
public:
    void apply(Category& category, const std::string& value) override {
        try {
            int newFamilyId = std::stoi(value);
            category.setFamilyId(newFamilyId);
            std::cout << "FamilyId updated to " << newFamilyId << std::endl;
        }
        catch (std::invalid_argument& e) {
            std::cerr << "Invalid value for family id: " << value << std::endl;
        }
    }
};

#endif  // EDITSTRATEGIES_H
