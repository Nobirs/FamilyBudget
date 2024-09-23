#include "Transaction.h"
#include <sstream>
#include <iomanip>

Transaction::Transaction() {
    description = "default transaction";
    amount = 100.0;
    date = time(nullptr);
    type = TransactionType::INCOME;
    userId = 1;
    familyId = 1;
    categoryId = 1;
}

Transaction::Transaction(const string &description, double amount, TransactionType type, const string &category, int userId, int familyId)
    : description(description), amount(amount), type(type), date(std::time(nullptr)), userId(userId), familyId(familyId) {
    CategoryRepository rep;
    Category repCategory = rep.getCategoryByNameFamilyId(category, familyId);
    if (repCategory.getName() == "GENERAL" and repCategory.getName() != category) {
        Category newCategory(category, "", familyId);
        rep.addCategory(newCategory);
        repCategory = rep.getCategoryByNameFamilyId(category, familyId);
    }
    categoryId = repCategory.getId();
}

Transaction Transaction::createTransaction(const string &description, double amount, time_t date,
                                    TransactionType type, int userId, int familyId, int categoryId) {
    Transaction tr;
    tr.description = description;
    tr.amount = amount;
    tr.date = date;
    tr.type = type;
    tr.userId = userId;
    tr.familyId = familyId;
    tr.categoryId = categoryId;
    return tr;
}

const string &Transaction::getDescription() const { return description; }
double Transaction::getAmount() const { return amount; }
time_t Transaction::getDate() const { return date; }
TransactionType Transaction::getType() const { return type; }
int Transaction::getUserId() const { return userId; }
int Transaction::getFamilyId() const { return familyId; }

const string Transaction::getCategory() const {
    CategoryRepository rep;
    Category repCategory = rep.getCategoryByCategoryIdFamilyId(categoryId, familyId);
    const string categoryName = repCategory.getName();
    return categoryName;
}
int Transaction::getCategoryId() const { return categoryId; }
void Transaction::setCategoryId(int categoryId) { this->categoryId = categoryId; }

string Transaction::toString() const {
    std::ostringstream oss;
    oss << "Description: " << description 
        << ", Amount: " << (type == TransactionType::INCOME ? "+" : "-") << amount 
        << ", Date: " << std::put_time(std::localtime(&date), "%Y-%m-%d %H:%M:%S") 
        << ", Type: " << (type == TransactionType::INCOME ? "Income" : "Expense") 
        << ", Category: " << categoryId;
    return oss.str();
}
