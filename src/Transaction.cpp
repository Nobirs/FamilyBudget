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
void Transaction::setDescription(const string& value) {
    this->description = value;
}

double Transaction::getAmount() const { return amount; }
void Transaction::setAmount(int value) {
    this->amount = value;
}

time_t Transaction::getDate() const { return date; }
void Transaction::setDate(time_t value) { this->date = value; }
void Transaction::setDate(const string& value) {
    tm tmReg = {};
    strptime(value.c_str(), "%Y-%m-%d %H:%M:%S", &tmReg);
    time_t date = std::mktime(&tmReg);
    this->date = date;
}

TransactionType Transaction::getType() const { return type; }
string Transaction::getTypeStr() const {
    switch(this->type){
        case TransactionType::INCOME: return "INCOME";
        case TransactionType::EXPENSE: return "EXPENSE";
        default: return "EXPENSE";
    }
    return "EXPENSE";
}
void Transaction::setType(const string& value) {
    if(value == "INCOME") this->type = TransactionType::INCOME;
    else if(value == "EXPENSE") this->type = TransactionType::EXPENSE;
    else throw std::invalid_argument("argument must be INCOME or EXPENSE");
}

int Transaction::getUserId() const { return userId; }
void Transaction::setUserId(int newUserId) {
    this->userId = newUserId;
}

int Transaction::getFamilyId() const { return familyId; }
void Transaction::setFamilyId(int newFamilyId) {
    this->familyId = newFamilyId;
}

const string Transaction::getCategory() const {
    CategoryRepository rep;
    Category repCategory = rep.getCategoryByCategoryIdFamilyId(categoryId, familyId);
    const string categoryName = repCategory.getName();
    return categoryName;
}
int Transaction::getCategoryId() const { return categoryId; }

void Transaction::setCategory(const string &categoryName) {
    CategoryRepository rep;
    Category repCategory = rep.getCategoryByNameFamilyId(categoryName, familyId);

    if (repCategory.getId() == 0) {
        std::clog << "Category '" + categoryName + "' not found in repository. Creating a new one!";
        
        // Create a new category:
        Category newCategory(categoryName, "", familyId);
        rep.addCategory(newCategory);
        repCategory = rep.getCategoryByNameFamilyId(categoryName, familyId); 
    }

    this->categoryId = repCategory.getId();
}

void Transaction::setCategoryId(int categoryId) { this->categoryId = categoryId; }

string Transaction::toString() const {
    std::ostringstream oss;
    oss << "Description: " << description 
        << ", Amount: " << (type == TransactionType::INCOME ? "+" : "-") << amount 
        << ", Date: " << std::put_time(std::localtime(&date), "%Y-%m-%d %H:%M:%S") 
        << ", Type: " << this->getTypeStr() 
        << ", Category: " << categoryId;
    return oss.str();
}
