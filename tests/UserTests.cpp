#include <gtest/gtest.h>
#include "User.h"
#include "UserRepository.h"


TEST(UserTest, AuthenticateUser) {
    User user("testuser", "password", UserRole::USER, "test@gmail.com");

    ASSERT_TRUE(user.authenticate("password"));
    ASSERT_FALSE(user.authenticate("wrongpassword"));
}

TEST(UserTest, ChangePassword) {
    User user("testuser", "password", UserRole::USER, "test@gmail.com");
    user.changePassword("newpassword");

    ASSERT_TRUE(user.authenticate("newpassword"));
    ASSERT_FALSE(user.authenticate("password"));
}


class UserRepositoryTests: public ::testing::Test {
protected:
    UserRepository userRepository;

    void TearDown() override {
        userRepository.clearUsersTable();
    }

};


TEST_F(UserRepositoryTests, AddUserTest) {
    User newUser("testUser", "testPassword", UserRole::USER, "test@gmail.com");
    userRepository.addUser(newUser);
    User fetchedUser = userRepository.getUserByUsername("testUser");
    
    EXPECT_EQ(fetchedUser.getUsername(), newUser.getUsername());
    EXPECT_EQ(fetchedUser.getRole(), newUser.getRole());
}

TEST_F(UserRepositoryTests, GetUserByUsernameTest) {
    User user("testUser", "testPassword", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user);
    User retrievedUser = userRepository.getUserByUsername("testUser");
    
    EXPECT_EQ(retrievedUser.getUsername(), "testUser");
}

TEST_F(UserRepositoryTests, GetAllUsersTest) {
    userRepository.addUser(User("user1", "password1", UserRole::USER, "test1@gmail.com"));
    userRepository.addUser(User("user2", "password2", UserRole::USER, "test2@gmail.com"));
    vector<User> users = userRepository.getAllUsers();
    
    EXPECT_EQ(users.size(), 2);
    EXPECT_EQ(users[0].getUsername(), "user1");
    EXPECT_EQ(users[1].getUsername(), "user2");
}

TEST_F(UserRepositoryTests, GetNonExistingUserTest) {
    EXPECT_THROW(userRepository.getUserByUsername("nonExistent"), std::runtime_error);
}

TEST_F(UserRepositoryTests, DuplicateUserTest) {    
    User user("duplicateUser", "password123", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user);
    bool result = userRepository.addUser(user);  // Modify addUser to return a boolean if successful
    
    EXPECT_FALSE(result);
}

TEST_F(UserRepositoryTests, DeleteUserTest) {
    User user("testUser", "testPassword", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user);
    
    ASSERT_TRUE(userRepository.deleteUser("testUser"));
    ASSERT_THROW(userRepository.getUserByUsername("testUser"), std::runtime_error);
}

TEST_F(UserRepositoryTests, ResetPasswordTest) {
    User user("testUser", "testPassword", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user);
    
    ASSERT_TRUE(userRepository.resetPassword("testUser", "newPassword"));
    User updatedUser = userRepository.getUserByUsername("testUser");
    ASSERT_TRUE(updatedUser.authenticate("newPassword"));
}

TEST_F(UserRepositoryTests, UpdateUsernameTest) {
    User user("oldUser", "testPassword", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user);
    
    ASSERT_TRUE(userRepository.updateUsername("oldUser", "newUser"));
    User updatedUser = userRepository.getUserByUsername("newUser");
    ASSERT_EQ(updatedUser.getUsername(), "newUser");
}

TEST_F(UserRepositoryTests, UpdateUserRoleTest) {
    User user("testUser", "testPassword", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user);
    
    ASSERT_TRUE(userRepository.updateUserRole("testUser", UserRole::ADMIN));
    User updatedUser = userRepository.getUserByUsername("testUser");
    ASSERT_EQ(updatedUser.getRole(), UserRole::ADMIN);
}

TEST_F(UserRepositoryTests, AddSameUserTwiceTest) {
    User user1("testUser", "testPassword", UserRole::USER, "test1@gmail.com");
    User user2("testUser", "testPassword", UserRole::USER, "test2@gmail.com");

    // Add first User -> success
    ASSERT_TRUE(userRepository.addUser(user1));
    // Add second User -> must fail cause username should be unique
    ASSERT_FALSE(userRepository.addUser(user2));

}

TEST_F(UserRepositoryTests, UpdateUserEmailTest) {
    User user("testUser", "testPassword", UserRole::USER, "test1@gmail.com");
    userRepository.addUser(user);
    userRepository.updateEmail("testUser", "newEmail@gmail.com");
    User updatedUser = userRepository.getUserByUsername("testUser");

    ASSERT_EQ(updatedUser.getEmail(), "newEmail@gmail.com");
}

TEST_F(UserRepositoryTests, UpdateBudgetLimitTest) {
    User user("testUser", "testPassword", UserRole::USER, "test1@gmail.com", "BUDGET_MANAGER", 1.0);
    userRepository.addUser(user);
    ASSERT_DOUBLE_EQ(userRepository.getUserByUsername("testUser").getBudgetLimit(), 1.0);
    userRepository.updateBudgetLimit("testUser", 50000);
    ASSERT_DOUBLE_EQ(userRepository.getUserByUsername("testUser").getBudgetLimit(), 50000);
}

TEST_F(UserRepositoryTests, UpdateFamilyIdTest) {
    User user("testUser", "testPassword", UserRole::USER, "test@gmail.com", "BUDGET_MANAGER", 1.0, "HUSBAND", 2);
    userRepository.addUser(user);
    ASSERT_EQ(userRepository.getUserByUsername("testUser").getFamilyId(), 2);
    userRepository.updateUserFamilyId("testUser", 15);
    ASSERT_EQ(userRepository.getUserByUsername("testUser").getFamilyId(), 15);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
