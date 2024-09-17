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
    double getBalance() const;

    vector<Transaction> getTransactionsByCategory(const string &category) const;
    vector<Transaction> getTransactionsByFamilyId(int familyId) const;
};

#endif // BUDGET_H
