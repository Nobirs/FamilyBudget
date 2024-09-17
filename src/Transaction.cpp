#include "Transaction.h"
#include <sstream>
#include <iomanip>

Transaction::Transaction(const string &description, double amount, TransactionType type, const string &category, int familyId)
    : description(description), amount(amount), type(type), category(category), date(std::time(nullptr)), familyId(familyId) {}

const string &Transaction::getDescription() const { return description; }
double Transaction::getAmount() const { return amount; }
time_t Transaction::getDate() const { return date; }
TransactionType Transaction::getType() const { return type; }
const string &Transaction::getCategory() const { return category; }
int Transaction::getFamilyId() const { return familyId; }

string Transaction::toString() const {
    std::ostringstream oss;
    oss << "Description: " << description 
        << ", Amount: " << (type == TransactionType::INCOME ? "+" : "-") << amount 
        << ", Date: " << std::put_time(std::localtime(&date), "%Y-%m-%d %H:%M:%S") 
        << ", Type: " << (type == TransactionType::INCOME ? "Income" : "Expense") 
        << ", Category: " << category;
    return oss.str();
}
