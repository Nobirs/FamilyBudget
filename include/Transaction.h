#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

#include "Category.h"
#include "CategoryRepository.h"

using std::string;
using std::time_t;

class TransactionRepository;

enum class TransactionType { INCOME, EXPENSE };

class Transaction {
private:
    string description;
    double amount;
    time_t date;
    TransactionType type;
    int familyId;
    int categoryId;

    static Transaction createTransaction(const string &description, double amount, time_t date, TransactionType type, int familyId, int categoryId);

public:
    Transaction();
    Transaction(const string &description, double amount, TransactionType type, const string &category, int familyId);


    const string &getDescription() const;
    double getAmount() const;
    time_t getDate() const;
    TransactionType getType() const;
    const string &getCategory() const;
    int getFamilyId() const;
    int getCategoryId() const;
    void setCategoryId(int categoryId);

    // Метод для удобного вывода транзакции
    string toString() const;

    friend class TransactionRepository;
};

#endif // TRANSACTION_H
