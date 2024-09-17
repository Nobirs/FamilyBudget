#include "Budget.h"

void Budget::addTransaction(const Transaction &transaction) {
    transactions.push_back(transaction);
}

double Budget::getTotalIncome() const {
    double totalIncome = 0;
    for (const auto &transaction : transactions) {
        if (transaction.getType() == TransactionType::INCOME) {
            totalIncome += transaction.getAmount();
        }
    }
    return totalIncome;
}

double Budget::getTotalExpense() const {
    double totalExpense = 0;
    for (const auto &transaction : transactions) {
        if (transaction.getType() == TransactionType::EXPENSE) {
            totalExpense += transaction.getAmount();
        }
    }
    return totalExpense;
}

double Budget::getBalance() const {
    return getTotalIncome() - getTotalExpense();
}

vector<Transaction> Budget::getTransactionsByCategory(const string &category) const {
    vector<Transaction> filteredTransactions;
    for (const auto &transaction : transactions) {
        if (transaction.getCategory() == category) {
            filteredTransactions.push_back(transaction);
        }
    }
    return filteredTransactions;
}

vector<Transaction> Budget::getTransactionsByFamilyId(int familyId) const {
    vector<Transaction> familyTransactions;
    for (const auto &transaction : transactions) {
        if (transaction.getFamilyId() == familyId) {
            familyTransactions.push_back(transaction);
        }
    }
    return familyTransactions;
}

