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

vector<Transaction> Budget::getTransactions() const {
    return transactions;
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

double Budget::getBalanceByCategory(const string &category) const {
    double balance = 0;
    for (const auto &transaction : transactions) {
        if (transaction.getCategory() == category) {
            if (transaction.getType() == TransactionType::INCOME) {
                balance += transaction.getAmount();
            } else if (transaction.getType() == TransactionType::EXPENSE) {
                balance -= transaction.getAmount();
            }
        }
    }
    return balance;
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

double Budget::getBalanceByFamilyId(int familyId) const {
    double balance = 0;
    for (const auto &transaction : transactions) {
        if (transaction.getFamilyId() == familyId) {
            if (transaction.getType() == TransactionType::INCOME) {
                balance += transaction.getAmount();
            } else if (transaction.getType() == TransactionType::EXPENSE) {
                balance -= transaction.getAmount();
            }
        }
    }
    return balance;
}

vector<Transaction> Budget::getTransactionsByUserId(int userId) const {
    vector<Transaction> userTransactions;
    for (const auto &transaction : transactions) {
        if (transaction.getUserId() == userId) {
            userTransactions.push_back(transaction);
        }
    }
    return userTransactions;
}

double Budget::getBalanceByUserId(int userId) const {
    double balance = 0;
    for (const auto &transaction : transactions) {
        if (transaction.getUserId() == userId) {
            if (transaction.getType() == TransactionType::INCOME) {
                balance += transaction.getAmount();
            } else if (transaction.getType() == TransactionType::EXPENSE) {
                balance -= transaction.getAmount();
            }
        }
    }
    return balance;
}

vector<Transaction> Budget::getTransactionsByFamilyIdAndCategory(int familyId, const string &category) const {
    vector<Transaction> filteredTransactions;
    for (const auto &transaction : transactions) {
        if (transaction.getFamilyId() == familyId && transaction.getCategory() == category) {
            filteredTransactions.push_back(transaction);
        }
    }
    return filteredTransactions;
}

double Budget::getBalanceByFamilyIdAndCategory(int familyId, const string &category) const {
    double balance = 0;
    for (const auto &transaction : transactions) {
        if (transaction.getFamilyId() == familyId && transaction.getCategory() == category) {
            if (transaction.getType() == TransactionType::INCOME) {
                balance += transaction.getAmount();
            } else if (transaction.getType() == TransactionType::EXPENSE) {
                balance -= transaction.getAmount();
            }
        }
    }
    return balance;
}

vector<Transaction> Budget::getTransactionsByFamilyIdAndType(int familyId, TransactionType type) const {
    vector<Transaction> filteredTransactions;
    for (const auto &transaction : transactions) {
        if (transaction.getFamilyId() == familyId && transaction.getType() == type) {
            filteredTransactions.push_back(transaction);
        }
    }
    return filteredTransactions;
}

double Budget::getBalanceByFamilyIdAndType(int familyId, TransactionType type) const {
    double balance = 0;
    for (const auto &transaction : transactions) {
        if (transaction.getFamilyId() == familyId && transaction.getType() == type) {
            if (transaction.getType() == TransactionType::INCOME) {
                balance += transaction.getAmount();
            } else if (transaction.getType() == TransactionType::EXPENSE) {
                balance -= transaction.getAmount();
            }
        }
    }
    return balance;
}

vector<Transaction> Budget::getTransactionsByCategoryAndType(const string &category, TransactionType type) const {
    vector<Transaction> filteredTransactions;
    for (const auto &transaction : transactions) {
        if (transaction.getCategory() == category && transaction.getType() == type) {
            filteredTransactions.push_back(transaction);
        }
    }
    return filteredTransactions;
}

double Budget::getBalanceByCategoryAndType(const string &category, TransactionType type) const {
    double balance = 0;
    for (const auto &transaction : transactions) {
        if (transaction.getCategory() == category && transaction.getType() == type) {
            if (transaction.getType() == TransactionType::INCOME) {
                balance += transaction.getAmount();
            } else if (transaction.getType() == TransactionType::EXPENSE) {
                balance -= transaction.getAmount();
            }
        }
    }
    return balance;
}

vector<Transaction> Budget::getTransactionsByFamilyIdAndCategoryAndType(int familyId, const string &category, TransactionType type) const {
    vector<Transaction> filteredTransactions;
    for (const auto &transaction : transactions) {
        if (transaction.getFamilyId() == familyId && transaction.getCategory() == category && transaction.getType() == type) {
            filteredTransactions.push_back(transaction);
        }
    }
    return filteredTransactions;
}

double Budget::getBalanceByFamilyIdAndCategoryAndType(int familyId, const string &category, TransactionType type) const {
    double balance = 0;
    for (const auto &transaction : transactions) {
        if (transaction.getFamilyId() == familyId && transaction.getCategory() == category && transaction.getType() == type) {
            if (transaction.getType() == TransactionType::INCOME) {
                balance += transaction.getAmount();
            } else if (transaction.getType() == TransactionType::EXPENSE) {
                balance -= transaction.getAmount();
            }
        }
    }
    return balance;
}


void Budget::clearTransactions() {
    transactions.clear();
}