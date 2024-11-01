#include <gtest/gtest.h>

#include "User.h"
#include "UserRepository.h"

class UserRepositoryTests: public ::testing::Test {
protected:
    User *defaultUser;
    UserRepository userRepository;

    void SetUp() override {
        defaultUser = new User();
        userRepository.addUser(*defaultUser);
    }

    void TearDown() override {
        delete defaultUser;
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

TEST_F(UserRepositoryTests, DeleteUserTest) {
    vector<User> allUsers = userRepository.getAllUsers();
    EXPECT_EQ(allUsers.size(), 1);
    EXPECT_TRUE(allUsers[0] == *defaultUser);
    EXPECT_TRUE(userRepository.deleteUser(defaultUser->getUsername()));
    EXPECT_TRUE(userRepository.getAllUsers().size() == 0);

    User user("testUser", "testPassword", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user);
    ASSERT_TRUE(userRepository.deleteUser("testUser"));
    ASSERT_THROW(userRepository.getUserByUsername("testUser"), std::runtime_error);
}

TEST_F(UserRepositoryTests, UpdateUserTest) {
    string newUsername = "newUsername";
    defaultUser->setUsername(newUsername);
    EXPECT_TRUE(userRepository.updateUser(1, *defaultUser));
    EXPECT_TRUE(userRepository.getAllUsers().size() == 1);
    EXPECT_TRUE(userRepository.getUserByUsername(newUsername) == *defaultUser);
}

TEST_F(UserRepositoryTests, ResetPasswordTest) {
    User user("testUser", "testPassword", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user);
    
    ASSERT_TRUE(userRepository.resetPassword("testUser", "newPassword"));
    User updatedUser = userRepository.getUserByUsername("testUser");
    ASSERT_TRUE(updatedUser.authenticate("newPassword"));
}

TEST_F(UserRepositoryTests, ChangePasswordHashTest) {
    defaultUser->changePassword("newPassword");
    string newPasswordHash = defaultUser->getPasswordHash();
    EXPECT_TRUE(userRepository.changePasswordHash(defaultUser->getUsername(), newPasswordHash));
    EXPECT_TRUE(*defaultUser == userRepository.getUserByUsername(defaultUser->getUsername()));
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

TEST_F(UserRepositoryTests, UpdateFamilyIdTest) {
    User user("testUser", "testPassword", UserRole::USER, "test@gmail.com", "BUDGET_MANAGER", 1.0, "HUSBAND", 2);
    userRepository.addUser(user);
    ASSERT_EQ(userRepository.getUserByUsername("testUser").getFamilyId(), 2);
    userRepository.updateUserFamilyId("testUser", 15);
    ASSERT_EQ(userRepository.getUserByUsername("testUser").getFamilyId(), 15);
}

TEST_F(UserRepositoryTests, UpdateUserByIdTest) {
    // defaultUser ID in DB Table must be 1
    User user
    {
        "user1",
        "testpwd123",
        UserRole::USER, 
        "userEmail@gmail.com",
        "ALPHA",
        10000.0,
        "SINGLE"
    };
    EXPECT_TRUE(userRepository.getUserById(1) == *defaultUser);
    EXPECT_TRUE(userRepository.updateUserById(1, user));
    User dbUser = userRepository.getUserById(1);
    EXPECT_TRUE(dbUser == user);
}

TEST_F(UserRepositoryTests, GetUserByIdTest) {
    EXPECT_TRUE(userRepository.getUserById(1) == *defaultUser);
}

TEST_F(UserRepositoryTests, GetUserByUsernameTest) {
    User user(
        "alex",
        "qwerty1234",
        UserRole::USER, 
        "alexNobirs13@gmail.com",
        "BUSINESSMAN",
        100000.0,
        "SINGLE"
        );
    EXPECT_TRUE(userRepository.getUserByUsername("default") == *defaultUser);
    EXPECT_TRUE(userRepository.addUser(user));
    EXPECT_TRUE(userRepository.getUserByUsername("alex") == user);

    User user2("testUser", "testPassword", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user2);
    User retrievedUser = userRepository.getUserByUsername("testUser");
    EXPECT_EQ(retrievedUser.getUsername(), "testUser");
    EXPECT_EQ(retrievedUser, user2);
}

TEST_F(UserRepositoryTests, GetAllUsersTest) {
    userRepository.addUser(User("user1", "password1", UserRole::USER, "test1@gmail.com"));
    userRepository.addUser(User("user2", "password2", UserRole::USER, "test2@gmail.com"));
    vector<User> users = userRepository.getAllUsers();
    
    EXPECT_EQ(users.size(), 3);
    EXPECT_EQ(users[1].getUsername(), "user1");
    EXPECT_EQ(users[2].getUsername(), "user2");
}

TEST_F(UserRepositoryTests, ClearUsersTableTest) {
    EXPECT_EQ(userRepository.getAllUsers().size(), 1);
    userRepository.clearUsersTable();
    EXPECT_EQ(userRepository.getAllUsers().size(), 0);
}

TEST_F(UserRepositoryTests, UpdateEmailTest) {
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

// -----------------------UNIQUE CASE TESTS -----------------------------------------

TEST_F(UserRepositoryTests, GetNonExistingUserTest) {
    EXPECT_THROW(userRepository.getUserByUsername("nonExistent"), std::runtime_error);
}

TEST_F(UserRepositoryTests, DuplicateUserTest) {    
    User user("duplicateUser", "password123", UserRole::USER, "test@gmail.com");
    userRepository.addUser(user);
    EXPECT_FALSE(userRepository.addUser(user));  // Modify addUser to return a boolean if successful
}

TEST_F(UserRepositoryTests, AddSameUserTwiceTest) {
    User user1("testUser", "testPassword", UserRole::USER, "test1@gmail.com");
    User user2("testUser", "testPassword", UserRole::USER, "test2@gmail.com");
    // Add first User -> success
    ASSERT_TRUE(userRepository.addUser(user1));
    // Add second User -> must fail cause username should be unique
    ASSERT_FALSE(userRepository.addUser(user2));
}