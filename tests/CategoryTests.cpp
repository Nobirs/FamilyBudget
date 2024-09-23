#include <gtest/gtest.h>

#include "User.h"
#include "UserRepository.h"
#include "Category.h"
#include "CategoryRepository.h"


class CategoryRepositoryTests: public ::testing::Test {
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

TEST_F(CategoryRepositoryTests, DeleteCategoryTest) {
    Category category("Entertainment", "Entertainment expenses", 1);
    Category category2("General", "General expenses", 1);

    ASSERT_TRUE(categoryRepository.addCategory(category));
    ASSERT_TRUE(categoryRepository.addCategory(category2));
    ASSERT_TRUE(categoryRepository.deleteCategory(2));
}

TEST_F(CategoryRepositoryTests, GetCategoriesByFamilyIdTest) {
    Category category("Entertainment", "Entertainment expenses", 1);
    Category category2("General", "General expenses", 1);
    ASSERT_TRUE(categoryRepository.addCategory(category));
    ASSERT_TRUE(categoryRepository.addCategory(category2));

    vector<Category> categories = categoryRepository.getCategoriesByFamilyId(1);
    // Проверяем, что категории были получены
    ASSERT_GT(categories.size(), 0);  // Должно быть больше 0 категорий
    
    // Проверяем первую категорию в списке (например, Entertainment)
    EXPECT_EQ(categories[0].getName(), "Entertainment");
    EXPECT_EQ(categories[1].getName(), "General");
}
