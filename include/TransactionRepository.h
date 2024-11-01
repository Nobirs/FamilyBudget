#ifndef TRANSACTIONREPOSITORY_H
#define TRANSACTIONREPOSITORY_H

#include <vector>
#include <iostream>
#include <mysql/mysql.h>

#include "Utils.h"
#include "Transaction.h"

using std::string;
using std::vector;
using std::cout;
using std::cerr;

class TransactionRepository {
private:
    MYSQL *conn;

public:
    TransactionRepository();
    TransactionRepository(MYSQL *connection);

    bool addTransaction(const Transaction &transaction);
    bool updateTransaction(int transactionId, const Transaction &transaction);
    bool deleteTransaction(int transactionId);

    Transaction getTransactionById(int transactionId);
    vector<Transaction> getTransactionsByUserId(int userId);
    vector<Transaction> getTransactionsByFamilyId(int familyId);
    vector<Transaction> getTransactionByCategoryId(int categoryId);

    vector<Transaction> getTransactionByUserIdCategoryId(int userId, int categoryId);
    vector<Transaction> getTransactionByFamilyIdCategoryId(int familyId, int categoryId);

    void clearTransactionTable();

};

#endif // TRANSACTIONREPOSITORY_H