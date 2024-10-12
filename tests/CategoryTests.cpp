#include <gtest/gtest.h>

#include "User.h"
#include "UserRepository.h"
#include "Category.h"
#include "CategoryRepository.h"

class CategoryTests: public Category, public ::testing::Test {
protected:
    User user;
    Category category;
    UserRepository userRep;
    CategoryRepository categoryRep;

    void SetUp() override {
        userRep.clearUsersTable();
        categoryRep.clearCategoryTable();
        user = User("testUser", "testPassword", UserRole::USER, "testEmail@gmail.com");
        userRep.addUser(user);
    }
};

TEST_F(CategoryTests, GetIdTest) {
    ASSERT_EQ(category.getId(), 0);
}

TEST_F(CategoryTests, GetNameTest) {
    ASSERT_EQ(category.getName(), "GENERAL");
}

TEST_F(CategoryTests, GetDescriptionTest) {
    ASSERT_EQ(category.getDescription(), "General category for all products");
}

TEST_F(CategoryTests, GetFamilyIdTest) {
    ASSERT_EQ(category.getFamilyId(), 0);
}

TEST_F(CategoryTests, SetNameTest) {
    category.setName("New Name");
    ASSERT_EQ(category.getName(), "New Name");
}

TEST_F(CategoryTests, SetDescriptionTest) {
    category.setDescription("New Description");
    ASSERT_EQ(category.getDescription(), "New Description");
}

TEST_F(CategoryTests, SetFamilyIdTest) {
    category.setFamilyId(1);
    ASSERT_EQ(category.getFamilyId(), 1);
}

TEST_F(CategoryTests, CreateCategoryTest) {
    Category newCategory = Category::createCategory(1, "Food", "Food expenses", 1);
    ASSERT_EQ(newCategory.getId(), 1);
    ASSERT_EQ(newCategory.getName(), "Food");
    ASSERT_EQ(newCategory.getDescription(), "Food expenses");
    ASSERT_EQ(newCategory.getFamilyId(), 1);
}

TEST_F(CategoryTests, ConstructorTest) {
    Category newCategory("Food", "Food expenses", 1);
    ASSERT_EQ(newCategory.getName(), "Food");
    ASSERT_EQ(newCategory.getDescription(), "Food expenses");
    ASSERT_EQ(newCategory.getFamilyId(), 1);
}