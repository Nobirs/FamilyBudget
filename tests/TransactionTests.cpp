#include <gtest/gtest.h>


#include "User.h"
#include "UserRepository.h"

#include "Category.h"
#include "CategoryRepository.h"

#include "Transaction.h"

#include "Utils.h"

class TransactionTests : public ::testing::Test {
protected:
    Transaction* incomeTransaction;
    Transaction* expenseTransaction;
    UserRepository userRep;
    CategoryRepository categoryRep;

    void SetUp() override {
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

    void TearDown() override {
        delete incomeTransaction;
        delete expenseTransaction;
        userRep.clearUsersTable();
        categoryRep.clearCategoryTable();
    }
};

TEST_F(TransactionTests, GetDescriptionTest) {
    ASSERT_EQ(incomeTransaction->getDescription(), "Salary");
    ASSERT_EQ(expenseTransaction->getDescription(), "Groceries");
}

TEST_F(TransactionTests, SetDescriptionTest) {
    ASSERT_EQ(incomeTransaction->getDescription(), "Salary");
    incomeTransaction->setDescription("Something New");
    ASSERT_EQ(incomeTransaction->getDescription(), "Something New");

    ASSERT_EQ(expenseTransaction->getDescription(), "Groceries");
    expenseTransaction->setDescription("Something New2");
    ASSERT_EQ(expenseTransaction->getDescription(), "Something New2");
}

TEST_F(TransactionTests, GetAmountTest) {
    ASSERT_DOUBLE_EQ(incomeTransaction->getAmount(), 1000.0);
    ASSERT_DOUBLE_EQ(expenseTransaction->getAmount(), 50.0);
}

TEST_F(TransactionTests, SetAmountTest) {
    ASSERT_DOUBLE_EQ(incomeTransaction->getAmount(), 1000.0);
    incomeTransaction->setAmount(0);
    ASSERT_DOUBLE_EQ(incomeTransaction->getAmount(), 0);

    ASSERT_DOUBLE_EQ(expenseTransaction->getAmount(), 50.0);
    expenseTransaction->setAmount(0);
    ASSERT_DOUBLE_EQ(expenseTransaction->getAmount(), 0);
}

TEST_F(TransactionTests, GetDateTest) {
    string incomeDateStr = "1992-10-15 16:45:36";
    time_t incomeDate = stringToTimeT(incomeDateStr);
    incomeTransaction->setDate(incomeDateStr);
    ASSERT_EQ(incomeTransaction->getDate(), incomeDate);
    
    time_t expenseDate = stringToTimeT("2015-10-10 18:45:00");
    expenseTransaction->setDate(expenseDate);
    ASSERT_EQ(expenseTransaction->getDate(), expenseDate);
}

TEST_F(TransactionTests, GetTypeTest) {
    ASSERT_EQ(incomeTransaction->getType(), TransactionType::INCOME);
    ASSERT_EQ(expenseTransaction->getType(), TransactionType::EXPENSE);
}

TEST_F(TransactionTests, GetTypeStrTest) {
    ASSERT_EQ(incomeTransaction->getTypeStr(), "INCOME");
    ASSERT_EQ(expenseTransaction->getTypeStr(), "EXPENSE");
}

TEST_F(TransactionTests, SetTypeTest) {
    incomeTransaction->setType("EXPENSE");
    ASSERT_EQ(incomeTransaction->getType(), TransactionType::EXPENSE);
    expenseTransaction->setType("INCOME");
    ASSERT_EQ(expenseTransaction->getType(), TransactionType::INCOME);
    ASSERT_THROW(incomeTransaction->setType("GODS GIVEN"), std::invalid_argument);
    ASSERT_THROW(expenseTransaction->setType("GODS GIVEN"), std::invalid_argument);
}

TEST_F(TransactionTests, GetUserIdTest) {
    ASSERT_EQ(incomeTransaction->getUserId(), 1);
    ASSERT_EQ(expenseTransaction->getUserId(), 1);
}

TEST_F(TransactionTests, SetUserIdTest) {
    incomeTransaction->setUserId(4);
    expenseTransaction->setUserId(18);
    ASSERT_EQ(incomeTransaction->getUserId(), 4);
    ASSERT_EQ(expenseTransaction->getUserId(), 18);
}

TEST_F(TransactionTests, GetFamilyIdTest) {
    ASSERT_EQ(incomeTransaction->getFamilyId(), 1);
    ASSERT_EQ(expenseTransaction->getFamilyId(), 1);
}

TEST_F(TransactionTests, SetFamilyIdTest) {
    incomeTransaction->setFamilyId(44);
    expenseTransaction->setFamilyId(13);
    ASSERT_EQ(incomeTransaction->getFamilyId(), 44);
    ASSERT_EQ(expenseTransaction->getFamilyId(), 13);
}

TEST_F(TransactionTests, GetCategoryTest) {
    ASSERT_EQ(incomeTransaction->getCategory(), "Work");
    ASSERT_EQ(expenseTransaction->getCategory(), "Food");
}

TEST_F(TransactionTests, GetCategoryIdTest) {
    ASSERT_EQ(incomeTransaction->getCategoryId(), 1);
    ASSERT_EQ(expenseTransaction->getCategoryId(), 2);
}

TEST_F(TransactionTests, SetCategoryIdTest) {
    incomeTransaction->setCategoryId(11);
    expenseTransaction->setCategoryId(22);

    ASSERT_EQ(incomeTransaction->getCategoryId(), 11);
    ASSERT_EQ(expenseTransaction->getCategoryId(), 22);
}

TEST_F(TransactionTests, SetCategoryTest) {
    incomeTransaction->setCategory("Food");
    expenseTransaction->setCategory("Work");

    ASSERT_EQ(incomeTransaction->getCategoryId(), 2);
    ASSERT_EQ(expenseTransaction->getCategoryId(), 1);
}