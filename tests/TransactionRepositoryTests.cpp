#include <gtest/gtest.h>
#include <mysql/mysql.h>
#include "User.h"
#include "UserRepository.h"
#include "Category.h"
#include "CategoryRepository.h"
#include "Transaction.h"
#include "TransactionRepository.h"

// Класс тестов для TransactionRepository
class TransactionRepositoryTest : public ::testing::Test {
protected:
    UserRepository userRep;
    CategoryRepository categoryRep;
    TransactionRepository repository;

    void SetUp() override {
        userRep.clearUsersTable();
        repository.clearTransactionTable();
        categoryRep.clearCategoryTable();
        User user("testUser", "testPassword", UserRole::USER, "testEmail@gmail.com");
        userRep.addUser(user);
    }

    void TearDown() override {
        userRep.clearUsersTable();
        categoryRep.clearCategoryTable();
        repository.clearTransactionTable();
    }
};

TEST_F(TransactionRepositoryTest, AddTransactionTest) {
    Transaction transaction("Salary", 1000.0, TransactionType::INCOME, "Work", 1, 1);
    ASSERT_TRUE(repository.addTransaction(transaction));

    std::vector<Transaction> transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 1);
    EXPECT_EQ(transactions[0].getDescription(), "Salary");
    EXPECT_DOUBLE_EQ(transactions[0].getAmount(), 1000.0);
    EXPECT_EQ(transactions[0].getType(), TransactionType::INCOME);
}

TEST_F(TransactionRepositoryTest, DeleteTransactionTest) {
    Transaction transaction("Groceries", 50.0, TransactionType::EXPENSE, "Food", 1, 1);
    repository.addTransaction(transaction);

    std::vector<Transaction> transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 1);
    ASSERT_TRUE(repository.deleteTransaction(1));
    transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 0);
}

TEST_F(TransactionRepositoryTest, GetTransactionsByUserIdTest) {
    Transaction transaction1("Freelance", 500.0, TransactionType::INCOME, "Work", 1, 1);
    Transaction transaction2("Groceries", 75.0, TransactionType::EXPENSE, "Food", 1, 1);
    repository.addTransaction(transaction1);
    repository.addTransaction(transaction2);

    std::vector<Transaction> transactions = repository.getTransactionsByUserId(1);
    ASSERT_EQ(transactions.size(), 2);
    EXPECT_EQ(transactions[0].getDescription(), "Freelance");
    EXPECT_EQ(transactions[1].getDescription(), "Groceries");
}

TEST_F(TransactionRepositoryTest, GetTransactionByCategoryIdTest) {
    Transaction transaction1("Restaurant", 100.0, TransactionType::EXPENSE, "Food", 1, 1);
    Transaction transaction2("Salary", 2000.0, TransactionType::INCOME, "Work", 1, 1);
    repository.addTransaction(transaction1);
    repository.addTransaction(transaction2);

    std::vector<Transaction> transactions = repository.getTransactionByCategoryId(1);
    ASSERT_EQ(transactions.size(), 1);
    EXPECT_EQ(transactions[0].getDescription(), "Restaurant");
}

TEST_F(TransactionRepositoryTest, ClearTransactionTableTest) {
    Transaction transaction("Car Repair", 300.0, TransactionType::EXPENSE, "Car", 1, 1);
    repository.addTransaction(transaction);

    std::vector<Transaction> transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 1);
    repository.clearTransactionTable();
    transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 0);
}
