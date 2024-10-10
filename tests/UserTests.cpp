#include <gtest/gtest.h>
#include "User.h"
#include "UserRepository.h"


class UserTests : public User, public ::testing::Test {
protected: 
    User *defaultUser;
    User *customUser;
    time_t currentTime;

    void SetUp() override {
        currentTime = time(nullptr);
        defaultUser = new User();
        customUser = new User(
            "alex",
            "testpwd123",
            UserRole::USER,
            "alexNobirs13@gmail.com",
            "FAMILY_MEMBER",
            1000.0,
            "HUSBAND",
            NULL);
    }
};


TEST_F(UserTests, AuthenticateUser) {
    User user("testuser", "password", UserRole::USER, "test@gmail.com");

    ASSERT_TRUE(user.authenticate("password"));
    ASSERT_FALSE(user.authenticate("wrongpassword"));
}

TEST_F(UserTests, ChangePassword) {
    User user("testuser", "password", UserRole::USER, "test@gmail.com");
    user.changePassword("newpassword");

    ASSERT_TRUE(user.authenticate("newpassword"));
    ASSERT_FALSE(user.authenticate("password"));
}

TEST_F(UserTests, EqualOperator) {
    User newDefaultUser{};
    User newCustomUser(
        "alex",
        "testpwd123",
        UserRole::USER,
        "alexNobirs13@gmail.com",
        "FAMILY_MEMBER",
        1000.0,
        "HUSBAND",
        NULL);

    ASSERT_TRUE(newDefaultUser == *defaultUser);
    ASSERT_TRUE(newCustomUser == *customUser);
}

TEST_F(UserTests, StaticCreation) {
    customUser->setRegistrationDate(currentTime);
    customUser->setLastLogin(currentTime);
    User user = User::createUser(
        "alex",
        User::hashPassword("testpwd123"),
        UserRole::USER,
        "alexNobirs13@gmail.com",
        currentTime,
        "FAMILY_MEMBER",
        1000.0,
        "HUSBAND",
        NULL
    );
    user.setLastLogin(currentTime);

    ASSERT_TRUE(user == *customUser);
}

TEST_F(UserTests, GetFieldsCheck) {
    ASSERT_EQ(customUser->getUsername(), "alex");
    ASSERT_EQ(customUser->getEmail(), "alexNobirs13@gmail.com");
    ASSERT_EQ(customUser->getRole(), UserRole::USER);
    ASSERT_EQ(customUser->getRoleStr(), "USER");
    ASSERT_EQ(customUser->getRegistrationDate(), currentTime);
    ASSERT_EQ(customUser->getFinancialRole(), "FAMILY_MEMBER");
    ASSERT_DOUBLE_EQ(customUser->getBudgetLimit(), 1000.0);
    ASSERT_EQ(customUser->getFamilyStatus(), "HUSBAND");
    ASSERT_EQ(customUser->getFamilyId(), NULL);
    ASSERT_FALSE(customUser->isAdmin(*customUser));
    ASSERT_EQ(customUser->getPasswordHash(), User::hashPassword("testpwd123"));
}

TEST_F(UserTests, SetFieldsCheck) {
    customUser->setUsername("newUser");
    ASSERT_EQ(customUser->getUsername(), "newUser");

    customUser->setEmail("newEmail@gmail.com");
    ASSERT_EQ(customUser->getEmail(), "newEmail@gmail.com");

    customUser->setRole(UserRole::ADMIN);
    ASSERT_EQ(customUser->getRole(), UserRole::ADMIN);
    ASSERT_EQ(customUser->getRoleStr(), "ADMIN");

    customUser->setRegistrationDate(1234);
    ASSERT_EQ(customUser->getRegistrationDate(), 1234);

    customUser->setLastLogin(12345);
    ASSERT_EQ(customUser->getLastLogin(), 12345);

    customUser->setFinancialRole("BUSINESSMAN");
    ASSERT_EQ(customUser->getFinancialRole(), "BUSINESSMAN");

    customUser->setBudgetLimit(999.99);
    ASSERT_DOUBLE_EQ(customUser->getBudgetLimit(), 999.99);

    customUser->setFamilyStatus("PRESIDENT");
    ASSERT_EQ(customUser->getFamilyStatus(), "PRESIDENT");

    customUser->setFamilyId(13);
    ASSERT_EQ(customUser->getFamilyId(), 13);
}