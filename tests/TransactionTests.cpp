#include <gtest/gtest.h>

#include "User.h"
#include "UserRepository.h"
#include "Category.h"
#include "CategoryRepository.h"
#include "Transaction.h"

class TransactionTest : public ::testing::Test {
protected:
    // Указатели на транзакции, чтобы очистить память после каждого теста
    Transaction* incomeTransaction;
    Transaction* expenseTransaction;
    UserRepository userRep;
    CategoryRepository categoryRep;

    // SetUp вызывается перед каждым тестом
    void SetUp() override {
        // Инициализация тестовых транзакций
        User user1("testUser", "testPassword", UserRole::USER, "testEmail@gmail.com");
        User user2("testUser2", "testPassword2", UserRole::USER, "test2Email@gmail.com");
        userRep.addUser(user1);
        userRep.addUser(user2);

        Category category1("Work", "", 1);
        Category category2("Food", "", 1);
        categoryRep.addCategory(category1);
        categoryRep.addCategory(category2);

        incomeTransaction = new Transaction("Salary", 1000.0, TransactionType::INCOME, "Work", 1, 1);
        expenseTransaction = new Transaction("Groceries", 50.0, TransactionType::EXPENSE, "Food", 1, 1);
    }

    // TearDown вызывается после каждого теста
    void TearDown() override {
        // Освобождаем память, выделенную для транзакций
        delete incomeTransaction;
        delete expenseTransaction;
        userRep.clearUsersTable();
        categoryRep.clearCategoryTable();
    }
};

// Тест для проверки описания транзакции
TEST_F(TransactionTest, GetDescriptionTest) {
    ASSERT_EQ(incomeTransaction->getDescription(), "Salary");
    ASSERT_EQ(expenseTransaction->getDescription(), "Groceries");
}

// Тест для проверки суммы транзакции
TEST_F(TransactionTest, GetAmountTest) {
    ASSERT_DOUBLE_EQ(incomeTransaction->getAmount(), 1000.0);
    ASSERT_DOUBLE_EQ(expenseTransaction->getAmount(), 50.0);
}

// Тест для проверки типа транзакции (доход или расход)
TEST_F(TransactionTest, GetTypeTest) {
    ASSERT_EQ(incomeTransaction->getType(), TransactionType::INCOME);
    ASSERT_EQ(expenseTransaction->getType(), TransactionType::EXPENSE);
}

// Тест для проверки категории транзакции
TEST_F(TransactionTest, GetCategoryTest) {
    ASSERT_EQ(incomeTransaction->getCategory(), "Work");
    ASSERT_EQ(expenseTransaction->getCategory(), "Food");
}

// Тест для проверки идентификатора семьи
TEST_F(TransactionTest, GetFamilyIdTest) {
    ASSERT_EQ(incomeTransaction->getFamilyId(), 1);
    ASSERT_EQ(expenseTransaction->getFamilyId(), 1);
}
