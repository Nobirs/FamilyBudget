#include <gtest/gtest.h>
#include "User.h"
#include "UserRepository.h"

TEST(UserTest, AuthenticateUser) {
    User user("testuser", "password", UserRole::USER);

    ASSERT_TRUE(user.authenticate("password"));
    ASSERT_FALSE(user.authenticate("wrongpassword"));
}

TEST(UserTest, ChangePassword) {
    User user("testuser", "password", UserRole::USER);
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
    User newUser("testUser", "testPassword", UserRole::USER);
    userRepository.addUser(newUser);
    User fetchedUser = userRepository.getUserByUsername("testUser");
    
    EXPECT_EQ(fetchedUser.getUsername(), newUser.getUsername());
    EXPECT_EQ(fetchedUser.getRole(), newUser.getRole());
}

TEST_F(UserRepositoryTests, GetUserByUsernameTest) {
    User user("testUser", "testPassword", UserRole::USER);
    userRepository.addUser(user);
    User retrievedUser = userRepository.getUserByUsername("testUser");
    
    EXPECT_EQ(retrievedUser.getUsername(), "testUser");
}

TEST_F(UserRepositoryTests, GetAllUsersTest) {
    userRepository.addUser(User("user1", "password1", UserRole::USER));
    userRepository.addUser(User("user2", "password2", UserRole::USER));
    vector<User> users = userRepository.getAllUsers();
    
    EXPECT_EQ(users.size(), 2);
    EXPECT_EQ(users[0].getUsername(), "user1");
    EXPECT_EQ(users[1].getUsername(), "user2");
}

TEST_F(UserRepositoryTests, GetNonExistingUserTest) {
    EXPECT_THROW(userRepository.getUserByUsername("nonExistent"), std::runtime_error);
}

TEST_F(UserRepositoryTests, DuplicateUserTest) {    
    User user("duplicateUser", "password123", UserRole::USER);
    userRepository.addUser(user);
    bool result = userRepository.addUser(user);  // Modify addUser to return a boolean if successful
    
    EXPECT_FALSE(result);
}

TEST_F(UserRepositoryTests, DeleteUserTest) {
    UserRepository userRepository;
    User user("testUser", "testPassword", UserRole::USER);
    userRepository.addUser(user);
    
    ASSERT_TRUE(userRepository.deleteUser("testUser"));
    ASSERT_THROW(userRepository.getUserByUsername("testUser"), std::runtime_error);
}

TEST_F(UserRepositoryTests, ResetPasswordTest) {
    UserRepository userRepository;
    User user("testUser", "testPassword", UserRole::USER);
    userRepository.addUser(user);
    
    ASSERT_TRUE(userRepository.resetPassword("testUser", "newPassword"));
    User updatedUser = userRepository.getUserByUsername("testUser");
    ASSERT_TRUE(updatedUser.authenticate("newPassword"));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
