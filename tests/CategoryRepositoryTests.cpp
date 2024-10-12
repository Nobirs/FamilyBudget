#include <gtest/gtest.h>

#include "User.h"
#include "UserRepository.h"
#include "Category.h"
#include "CategoryRepository.h"

class CategoryRepositoryTests : public ::testing::Test {
protected:
    UserRepository userRepository;
    CategoryRepository categoryRepository;

    void SetUp() override {
        userRepository.clearUsersTable();
        categoryRepository.clearCategoryTable();

        User user("testUser", "testPassword", UserRole::USER, "testEmail@gmail.com");
        userRepository.addUser(user);
    }
};

TEST_F(CategoryRepositoryTests, AddCategoryTest) {
    Category category("Entertainment", "Entertainment expenses", 1);

    ASSERT_TRUE(categoryRepository.addCategory(category));
    ASSERT_EQ(categoryRepository.getCategoriesByFamilyId(1)[0].getName(), "Entertainment");
}

TEST_F(CategoryRepositoryTests, UpdateCategoryTest) {
    Category category("Entertainment", "Entertainment expenses", 1);
    ASSERT_TRUE(categoryRepository.addCategory(category));

    category.setName("Movies & Music");
    category.setDescription("Expenses for movies and music");
    ASSERT_TRUE(categoryRepository.updateCategory(1, category)); 

    Category updatedCategory = categoryRepository.getCategoryByCategoryIdFamilyId(1, 1);
    EXPECT_EQ(updatedCategory.getName(), "Movies & Music");
    EXPECT_EQ(updatedCategory.getDescription(), "Expenses for movies and music");
}

TEST_F(CategoryRepositoryTests, DeleteCategoryTest) {
    Category category("Entertainment", "Entertainment expenses", 1);
    Category category2("General", "General expenses", 1);

    ASSERT_TRUE(categoryRepository.addCategory(category));
    ASSERT_TRUE(categoryRepository.addCategory(category2));
    ASSERT_TRUE(categoryRepository.deleteCategory(2)); 

    std::vector<Category> categories = categoryRepository.getCategoriesByFamilyId(1);
    ASSERT_EQ(categories.size(), 1); 
    EXPECT_EQ(categories[0].getName(), "Entertainment");
}

TEST_F(CategoryRepositoryTests, GetAllCategoriesTest) {
    EXPECT_EQ(categoryRepository.getAllCategories().size(), 0);
    Category category1("TEST Category 1", "ONLY FOR TEST", 1);
    Category category2("TEST Category 2", "ONLY FOR TEST", 1);
    categoryRepository.addCategory(category1);
    categoryRepository.addCategory(category2);

    EXPECT_EQ(categoryRepository.getAllCategories().size(), 2);
    EXPECT_EQ(categoryRepository.getAllCategories()[0].getName(), "TEST Category 1");
    EXPECT_EQ(categoryRepository.getAllCategories()[1].getName(), "TEST Category 2");
}

TEST_F(CategoryRepositoryTests, GetCategoriesByFamilyIdTest) {
    Category category("Entertainment", "Entertainment expenses", 1);
    Category category2("General", "General expenses", 1);
    ASSERT_TRUE(categoryRepository.addCategory(category));
    ASSERT_TRUE(categoryRepository.addCategory(category2));

    vector<Category> categories = categoryRepository.getCategoriesByFamilyId(1);
    ASSERT_GT(categories.size(), 0);  
    EXPECT_EQ(categories[0].getName(), "Entertainment");
    EXPECT_EQ(categories[1].getName(), "General");
}

TEST_F(CategoryRepositoryTests, GetCategoryByCategoryIdFamilyIdTest) {
    Category category("Entertainment", "Entertainment expenses", 1);
    ASSERT_TRUE(categoryRepository.addCategory(category));

    Category retrievedCategory = categoryRepository.getCategoryByCategoryIdFamilyId(1, 1);
    EXPECT_EQ(retrievedCategory.getName(), "Entertainment");
    EXPECT_EQ(retrievedCategory.getDescription(), "Entertainment expenses");
}

TEST_F(CategoryRepositoryTests, GetCategoryByNameFamilyIdTest) {
    Category category("Entertainment", "Entertainment expenses", 1);
    ASSERT_TRUE(categoryRepository.addCategory(category));

    Category retrievedCategory = categoryRepository.getCategoryByNameFamilyId("Entertainment", 1);
    EXPECT_EQ(retrievedCategory.getName(), "Entertainment");
    EXPECT_EQ(retrievedCategory.getDescription(), "Entertainment expenses");
}

TEST_F(CategoryRepositoryTests, ClearCategoryTableTest) {
    Category category1("TEST Category 1", "ONLY FOR TEST", 1);
    Category category2("TEST Category 2", "ONLY FOR TEST", 1);
    categoryRepository.addCategory(category1);
    categoryRepository.addCategory(category2);

    EXPECT_EQ(categoryRepository.getCategoriesByFamilyId(1).size(), 2);
    categoryRepository.clearCategoryTable();
    ASSERT_EQ(categoryRepository.getCategoriesByFamilyId(1).size(), 0);
}
