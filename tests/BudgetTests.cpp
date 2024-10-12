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
    
    User user1;
    User user2;

    void SetUp() override {
        userRep.clearUsersTable();
        categoryRep.clearCategoryTable();
        transactionRep.clearTransactionTable();

        user1 = User("testUser", "testPassword", UserRole::USER, "test@gmail.com");
        user2 = User("testUser2", "testPassword2", UserRole::USER, "test2@gmail.com", "FAMILY_MEMBER", 10000.0, "HUSBAND", 2);
        userRep.addUser(user1);
        userRep.addUser(user2);
    }

    void TearDown() override {
        budget.clearTransactions();
    }
};

TEST_F(BudgetTests, AddTransactionTest) {
    Transaction incomeTransaction("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction expenseTransaction("Groceries", 200.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(incomeTransaction);
    budget.addTransaction(expenseTransaction);

    EXPECT_DOUBLE_EQ(budget.getBalance(), 800.0); 
}

TEST_F(BudgetTests, GetTotalIncomeTest) {
    Transaction income1("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction income2("Freelance", 500.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());

    budget.addTransaction(income1);
    budget.addTransaction(income2);

    EXPECT_DOUBLE_EQ(budget.getTotalIncome(), 1500.0);  
}

TEST_F(BudgetTests, GetTotalExpenseTest) {
    Transaction expense1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction expense2("Transport", 50.0, TransactionType::EXPENSE, "Transport", 1, user1.getFamilyId());

    budget.addTransaction(expense1);
    budget.addTransaction(expense2);

    EXPECT_DOUBLE_EQ(budget.getTotalExpense(), 150.0); 
}

TEST_F(BudgetTests, GetBalanceVariationsTest) {
    Transaction income1("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction expense1("Groceries", 200.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction expense2("Rent", 300.0, TransactionType::EXPENSE, "Housing", 2, user2.getFamilyId());
    Transaction expense3("Restaurant", 100.0, TransactionType::EXPENSE, "Food", 2, user1.getFamilyId());

    budget.addTransaction(income1);
    budget.addTransaction(expense1);
    budget.addTransaction(expense2);
    budget.addTransaction(expense3);

    EXPECT_DOUBLE_EQ(budget.getBalance(), 400.0); 
}

TEST_F(BudgetTests, GetTransactionsVariationsTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    vector<Transaction> foodTransactions = budget.getTransactionsByCategory("Food");
    ASSERT_EQ(foodTransactions.size(), 2); 
    EXPECT_EQ(foodTransactions[0].getDescription(), "Groceries");
    EXPECT_EQ(foodTransactions[1].getDescription(), "Dinner");

    vector<Transaction> family1Transactions = budget.getTransactionsByFamilyId(user1.getFamilyId());
    ASSERT_EQ(family1Transactions.size(), 3);
    EXPECT_EQ(family1Transactions[0].getDescription(), "Groceries");
    EXPECT_EQ(family1Transactions[1].getDescription(), "Salary");
    EXPECT_EQ(family1Transactions[2].getDescription(), "Dinner");
}

TEST_F(BudgetTests, GetBalanceByCategoryTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    EXPECT_DOUBLE_EQ(budget.getBalanceByCategory("Food"), -150.0);
    EXPECT_DOUBLE_EQ(budget.getBalanceByCategory("Transport"), -40.0);
}

TEST_F(BudgetTests, GetBalanceByFamilyIdTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    EXPECT_DOUBLE_EQ(budget.getBalanceByFamilyId(user1.getFamilyId()), 850.0);
    EXPECT_DOUBLE_EQ(budget.getBalanceByFamilyId(user2.getFamilyId()), -40.0);
}

TEST_F(BudgetTests, GetTransactionsByUserIdTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    vector<Transaction> user1Transactions = budget.getTransactionsByUserId(1);
    ASSERT_EQ(user1Transactions.size(), 3);
    EXPECT_EQ(user1Transactions[0].getDescription(), "Groceries");
    EXPECT_EQ(user1Transactions[1].getDescription(), "Salary");
    EXPECT_EQ(user1Transactions[2].getDescription(), "Dinner");

    vector<Transaction> user2Transactions = budget.getTransactionsByUserId(2);
    ASSERT_EQ(user2Transactions.size(), 1);
    EXPECT_EQ(user2Transactions[0].getDescription(), "Fuel");
}

TEST_F(BudgetTests, GetBalanceByUserIdTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    EXPECT_DOUBLE_EQ(budget.getBalanceByUserId(1), 850.0);
    EXPECT_DOUBLE_EQ(budget.getBalanceByUserId(2), -40.0);
}

TEST_F(BudgetTests, ClearTransactionsTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    ASSERT_NE(budget.getTransactionsByFamilyId(user1.getFamilyId()).size(), 0);
    budget.clearTransactions();
    ASSERT_EQ(budget.getTransactionsByFamilyId(user1.getFamilyId()).size(), 0);
}

TEST_F(BudgetTests, GetTransactionsByFamilyIdAndCategoryTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    vector<Transaction> filteredTransactions = budget.getTransactionsByFamilyIdAndCategory(user1.getFamilyId(), "Food");
    ASSERT_EQ(filteredTransactions.size(), 2);
    EXPECT_EQ(filteredTransactions[0].getDescription(), "Groceries");
    EXPECT_EQ(filteredTransactions[1].getDescription(), "Dinner");
}

TEST_F(BudgetTests, GetBalanceByFamilyIdAndCategoryTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    EXPECT_DOUBLE_EQ(budget.getBalanceByFamilyIdAndCategory(user1.getFamilyId(), "Food"), -150.0);
    EXPECT_DOUBLE_EQ(budget.getBalanceByFamilyIdAndCategory(user2.getFamilyId(), "Transport"), -40.0);
}

TEST_F(BudgetTests, GetTransactionsByFamilyIdAndTypeTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    vector<Transaction> filteredTransactions = budget.getTransactionsByFamilyIdAndType(user1.getFamilyId(), TransactionType::EXPENSE);
    ASSERT_EQ(filteredTransactions.size(), 2);
    EXPECT_EQ(filteredTransactions[0].getDescription(), "Groceries");
    EXPECT_EQ(filteredTransactions[1].getDescription(), "Dinner");
}

TEST_F(BudgetTests, GetBalanceByFamilyIdAndTypeTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    EXPECT_DOUBLE_EQ(budget.getBalanceByFamilyIdAndType(user1.getFamilyId(), TransactionType::EXPENSE), -150.0);
    EXPECT_DOUBLE_EQ(budget.getBalanceByFamilyIdAndType(user2.getFamilyId(), TransactionType::EXPENSE), -40.0);
}

TEST_F(BudgetTests, GetTransactionsByCategoryAndTypeTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    vector<Transaction> filteredTransactions = budget.getTransactionsByCategoryAndType("Food", TransactionType::EXPENSE);
    ASSERT_EQ(filteredTransactions.size(), 2);
    EXPECT_EQ(filteredTransactions[0].getDescription(), "Groceries");
    EXPECT_EQ(filteredTransactions[1].getDescription(), "Dinner");
}

TEST_F(BudgetTests, GetBalanceByCategoryAndTypeTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    EXPECT_DOUBLE_EQ(budget.getBalanceByCategoryAndType("Food", TransactionType::EXPENSE), -150.0);
    EXPECT_DOUBLE_EQ(budget.getBalanceByCategoryAndType("Transport", TransactionType::EXPENSE), -40.0);
}

TEST_F(BudgetTests, GetTransactionsByFamilyIdAndCategoryAndTypeTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    vector<Transaction> filteredTransactions = budget.getTransactionsByFamilyIdAndCategoryAndType(user1.getFamilyId(), "Food", TransactionType::EXPENSE);
    ASSERT_EQ(filteredTransactions.size(), 2);
    EXPECT_EQ(filteredTransactions[0].getDescription(), "Groceries");
    EXPECT_EQ(filteredTransactions[1].getDescription(), "Dinner");
}

TEST_F(BudgetTests, GetBalanceByFamilyIdAndCategoryAndTypeTest) {
    Transaction transaction1("Groceries", 100.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());
    Transaction transaction2("Fuel", 40.0, TransactionType::EXPENSE, "Transport", 2, user2.getFamilyId());
    Transaction transaction3("Salary", 1000.0, TransactionType::INCOME, "Work", 1, user1.getFamilyId());
    Transaction transaction4("Dinner", 50.0, TransactionType::EXPENSE, "Food", 1, user1.getFamilyId());

    budget.addTransaction(transaction1);
    budget.addTransaction(transaction2);
    budget.addTransaction(transaction3);
    budget.addTransaction(transaction4);

    EXPECT_DOUBLE_EQ(budget.getBalanceByFamilyIdAndCategoryAndType(user1.getFamilyId(), "Food", TransactionType::EXPENSE), -150.0);
    EXPECT_DOUBLE_EQ(budget.getBalanceByFamilyIdAndCategoryAndType(user2.getFamilyId(), "Transport", TransactionType::EXPENSE), -40.0);
}
