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
    int userId;
    int familyId;
    int categoryId;

    static Transaction createTransaction(const string &description, double amount, time_t date, 
                                    TransactionType type, int userId, int familyId, int categoryId);
    

public:
    Transaction();
    Transaction(const string &description, double amount, TransactionType type,
                                const string &category,int userId, int familyId);


    const string &getDescription() const;
    void setDescription(const string& value);

    double getAmount() const;
    void setAmount(int value);

    time_t getDate() const;
    void setDate(time_t value);
    void setDate(const string& value);

    TransactionType getType() const;
    string getTypeStr() const;
    void setType(const string& value);


    int getUserId() const;
    void setUserId(int newUserId);

    int getFamilyId() const;
    void setFamilyId(int newFamilyId);
    
    const string getCategory() const;
    int getCategoryId() const;
    void setCategory(const string &categoryName);
    void setCategoryId(int categoryId);

    // Метод для удобного вывода транзакции
    string toString() const;

    friend class TransactionRepository;
};

#endif // TRANSACTION_H
