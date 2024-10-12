#include <gtest/gtest.h>
#include <mysql/mysql.h>
#include "User.h"
#include "UserRepository.h"
#include "Category.h"
#include "CategoryRepository.h"
#include "Transaction.h"
#include "TransactionRepository.h"

// Класс тестов для TransactionRepository
class TransactionRepositoryTests : public ::testing::Test {
protected:
    User user;
    Category category;
    UserRepository userRep;
    CategoryRepository categoryRep;
    TransactionRepository repository;

    void SetUp() override {
        userRep.clearUsersTable();
        repository.clearTransactionTable();
        categoryRep.clearCategoryTable();
        user = User("testUser", "testPassword", UserRole::USER, "testEmail@gmail.com");
        User user2 = User("testUser2", "testPassword2", UserRole::USER, "test2Email@gmail.com", "FAMILY_HEAD", 10000.0, "HUSBAND", 2);
        userRep.addUser(user);
        userRep.addUser(user2);
        category = Category("Food", "Food expenses", 1);
        categoryRep.addCategory(category);
    }

    void TearDown() override {
        userRep.clearUsersTable();
        categoryRep.clearCategoryTable();
        repository.clearTransactionTable();
    }
};

TEST_F(TransactionRepositoryTests, AddTransactionTest) {
    Transaction transaction("Salary", 1000.0, TransactionType::INCOME, "Work", 1, 1);
    ASSERT_TRUE(repository.addTransaction(transaction));

    std::vector<Transaction> transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 1);
    EXPECT_EQ(transactions[0].getDescription(), "Salary");
    EXPECT_DOUBLE_EQ(transactions[0].getAmount(), 1000.0);
    EXPECT_EQ(transactions[0].getType(), TransactionType::INCOME);
}

TEST_F(TransactionRepositoryTests, UpdateTransactionTest) {
    Transaction transaction("Salary", 1000.0, TransactionType::INCOME, "Work", 1, 1);
    ASSERT_TRUE(repository.addTransaction(transaction));

    transaction.setDescription("New Salary");
    transaction.setAmount(1500.0);
    ASSERT_TRUE(repository.updateTransaction(1, transaction));

    std::vector<Transaction> transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 1);
    EXPECT_EQ(transactions[0].getDescription(), "New Salary");
    EXPECT_DOUBLE_EQ(transactions[0].getAmount(), 1500.0);
}

TEST_F(TransactionRepositoryTests, DeleteTransactionTest) {
    Transaction transaction("Groceries", 50.0, TransactionType::EXPENSE, "Food", 1, 1);
    repository.addTransaction(transaction);

    std::vector<Transaction> transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 1);
    ASSERT_TRUE(repository.deleteTransaction(1));
    transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 0);
}

TEST_F(TransactionRepositoryTests, GetTransactionByIdTest) {
    Transaction transaction("Salary", 1000.0, TransactionType::INCOME, "Work", 1, 1);
    ASSERT_TRUE(repository.addTransaction(transaction));

    Transaction retrievedTransaction = repository.getTransactionById(1);

    EXPECT_EQ(retrievedTransaction.getDescription(), "Salary");
    EXPECT_DOUBLE_EQ(retrievedTransaction.getAmount(), 1000.0);
    EXPECT_EQ(retrievedTransaction.getType(), TransactionType::INCOME);
}

TEST_F(TransactionRepositoryTests, GetTransactionsByUserIdTest) {
    Transaction transaction1("Freelance", 500.0, TransactionType::INCOME, "Work", 1, 1);
    Transaction transaction2("Groceries", 75.0, TransactionType::EXPENSE, "Food", 1, 1);
    repository.addTransaction(transaction1);
    repository.addTransaction(transaction2);

    std::vector<Transaction> transactions = repository.getTransactionsByUserId(1);
    ASSERT_EQ(transactions.size(), 2);
    EXPECT_EQ(transactions[0].getDescription(), "Freelance");
    EXPECT_EQ(transactions[1].getDescription(), "Groceries");
}

TEST_F(TransactionRepositoryTests, GetTransactionsByFamilyIdTest) {
    Transaction transaction1("Freelance", 500.0, TransactionType::INCOME, "Work", 1, 1);
    Transaction transaction2("Groceries", 75.0, TransactionType::EXPENSE, "Food", 1, 1);
    repository.addTransaction(transaction1);
    repository.addTransaction(transaction2);

    std::vector<Transaction> transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 2);
    EXPECT_EQ(transactions[0].getDescription(), "Freelance");
    EXPECT_EQ(transactions[1].getDescription(), "Groceries");
}

TEST_F(TransactionRepositoryTests, GetTransactionByCategoryIdTest) {
    Transaction transaction1("Restaurant", 100.0, TransactionType::EXPENSE, "Food", 1, 1);
    Transaction transaction2("Salary", 2000.0, TransactionType::INCOME, "Work", 1, 1);
    repository.addTransaction(transaction1);
    repository.addTransaction(transaction2);

    std::vector<Transaction> transactions = repository.getTransactionByCategoryId(1);
    ASSERT_EQ(transactions.size(), 1);
    EXPECT_EQ(transactions[0].getDescription(), "Restaurant");
}

TEST_F(TransactionRepositoryTests, GetTransactionByUserIdCategoryIdTest) {
    Transaction transaction1("Restaurant", 100.0, TransactionType::EXPENSE, "Food", 1, 1);
    Transaction transaction2("Salary", 2000.0, TransactionType::INCOME, "Work", 1, 1);
    Transaction transaction3("Cafe", 50.0, TransactionType::EXPENSE, "Food", 1, 1);
    repository.addTransaction(transaction1);
    repository.addTransaction(transaction2);
    repository.addTransaction(transaction3);

    std::vector<Transaction> transactions = repository.getTransactionByUserIdCategoryId(1, 1);
    ASSERT_EQ(transactions.size(), 2); 
    EXPECT_EQ(transactions[0].getDescription(), "Restaurant");
    EXPECT_EQ(transactions[1].getDescription(), "Cafe");
}

TEST_F(TransactionRepositoryTests, GetTransactionByFamilyIdCategoryIdTest) {
    Transaction transaction1("Restaurant", 100.0, TransactionType::EXPENSE, "Food", 1, 1);
    Transaction transaction2("Salary", 2000.0, TransactionType::INCOME, "Work", 2, 2);
    Transaction transaction3("Cafe", 50.0, TransactionType::EXPENSE, "Food", 1, 1);
    repository.addTransaction(transaction1);
    repository.addTransaction(transaction2);
    repository.addTransaction(transaction3);

    std::vector<Transaction> transactions = repository.getTransactionByFamilyIdCategoryId(1, 1);
    ASSERT_EQ(transactions.size(), 2); 
    EXPECT_EQ(transactions[0].getDescription(), "Restaurant");
    EXPECT_EQ(transactions[1].getDescription(), "Cafe");
}


TEST_F(TransactionRepositoryTests, ClearTransactionTableTest) {
    Transaction transaction("Car Repair", 300.0, TransactionType::EXPENSE, "Car", 1, 1);
    repository.addTransaction(transaction);

    std::vector<Transaction> transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 1);
    repository.clearTransactionTable();
    transactions = repository.getTransactionsByFamilyId(1);
    ASSERT_EQ(transactions.size(), 0);
}

