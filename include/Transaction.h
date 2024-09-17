#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

using std::string;
using std::time_t;

enum class TransactionType { INCOME, EXPENSE };

class Transaction {
private:
    string description;
    double amount;
    time_t date;
    TransactionType type;
    string category;
    int familyId;

public:
    Transaction(const string &description, double amount, TransactionType type, const string &category, int familyId);

    const string &getDescription() const;
    double getAmount() const;
    time_t getDate() const;
    TransactionType getType() const;
    const string &getCategory() const;
    int getFamilyId() const;

    // Метод для удобного вывода транзакции
    string toString() const;
};

#endif // TRANSACTION_H
