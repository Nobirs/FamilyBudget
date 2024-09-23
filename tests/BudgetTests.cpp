#include <gtest/gtest.h>
#include "User.h"
#include "UserRepository.h"
#include "CategoryRepository.h"
#include "TransactionRepository.h"
#include "Budget.h"
#include "Transaction.h"

class BudgetTests : public ::testing::Test {
protected:
    Budget budget;
    UserRepository userRep;
    CategoryRepository categoryRep;
    TransactionRepository transactionRep;
    

    void SetUp() override {
        userRep.clearUsersTable();
        categoryRep.clearCategoryTable();
        transactionRep.clearTransactionTable();

        User newUser("testUser", "testPassword", UserRole::USER, "test@gmail.com");
        User newUser2("testUser2", "testPassword2", UserRole::USER, "test2@gmail.com", "FAMILY_MEMBER", 10000.0, "HUSBAND", 2);
        userRep.addUser(newUser);
        userRep.addUser(newUser2);
    }
};

TEST_F(BudgetTests, AddTransactionTest) {
    Transaction incomeTransaction("Salary", 1000.0, TransactionType::INCOME, "Work", 1, 1);
    Transaction expenseTransaction("Groceries", 200.0, TransactionType::EXPENSE, "Food", 1, 1);
    budget.addTransaction(incomeTransaction);
    budget.addTransaction(expenseTransaction);

    EXPECT_EQ(budget.getBalance(), 800.0);  // Проверяем, что баланс правильно вычислен
}

TEST_F(BudgetTests, GetTotalIncomeTest) {
    Transaction income1("Salary", 1000.0, TransactionType::INCOME, "Work", 1, 1);
    Transaction income2("Freelance", 500.0, TransactionType::INCOME, "Work", 1, 1);
    budget.addTransaction(income1);
    budget.addTransaction(income2);

    EXPECT_DOUBLE_EQ(budget.getTotalIncome(), 1500.0);  // Проверяем общий доход
}

TEST_F(BudgetTests, GetTotalExpenseTest) {
    Transaction expense1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, 1);
    Transaction expense2("Transport", 50.0, TransactionType::EXPENSE, "Transport", 1, 1);
    budget.addTransaction(expense1);
    budget.addTransaction(expense2);

    EXPECT_DOUBLE_EQ(budget.getTotalExpense(), 150.0);  // Проверяем общие расходы
}

TEST_F(BudgetTests, GetTransactionsByCategoryTest) {
    Transaction expense1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, 1);
    Transaction expense2("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, 1);
    Transaction expense3("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 1, 1);
    budget.addTransaction(expense1);
    budget.addTransaction(expense2);
    budget.addTransaction(expense3);
    vector<Transaction> foodTransactions = budget.getTransactionsByCategory("Food");

    ASSERT_EQ(foodTransactions.size(), 2);  // Должно быть 2 транзакции в категории "Food"
    EXPECT_EQ(foodTransactions[0].getDescription(), "Groceries");
    EXPECT_EQ(foodTransactions[1].getDescription(), "Dinner");
}

// Тест на фильтрацию транзакций по familyId
TEST_F(BudgetTests, GetTransactionsByFamilyIdTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, 1);
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 1, 2);
    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    vector<Transaction> family1Transactions = budget.getTransactionsByFamilyId(1);

    ASSERT_EQ(family1Transactions.size(), 1);  // Должна быть только одна транзакция для familyId = 1
    EXPECT_EQ(family1Transactions[0].getDescription(), "Groceries");
}
