#ifndef BUDGET_H
#define BUDGET_H

#include <vector>
#include "Transaction.h"

using std::vector;
using std::string;

class Budget {
private:
    vector<Transaction> transactions;

public:
    void addTransaction(const Transaction &transaction);
    double getTotalIncome() const;
    double getTotalExpense() const;
    vector<Transaction> getTransactions() const;
    double getBalance() const;

    // Filtering by Category
    vector<Transaction> getTransactionsByCategory(const string &category) const;
    double getBalanceByCategory(const string &category) const;

    // Filtering by Family ID
    vector<Transaction> getTransactionsByFamilyId(int familyId) const;
    double getBalanceByFamilyId(int familyId) const;

    // Filtering by User ID
    vector<Transaction> getTransactionsByUserId(int userId) const;
    double getBalanceByUserId(int userId) const;

    // Combined Filtering
    vector<Transaction> getTransactionsByFamilyIdAndCategory(int familyId, const string &category) const;
    double getBalanceByFamilyIdAndCategory(int familyId, const string &category) const;

    vector<Transaction> getTransactionsByFamilyIdAndType(int familyId, TransactionType type) const;
    double getBalanceByFamilyIdAndType(int familyId, TransactionType type) const;

    vector<Transaction> getTransactionsByCategoryAndType(const string &category, TransactionType type) const;
    double getBalanceByCategoryAndType(const string &category, TransactionType type) const;

    vector<Transaction> getTransactionsByFamilyIdAndCategoryAndType(int familyId, const string &category, TransactionType type) const;
    double getBalanceByFamilyIdAndCategoryAndType(int familyId, const string &category, TransactionType type) const;

    void clearTransactions();
};

#endif // BUDGET_H
