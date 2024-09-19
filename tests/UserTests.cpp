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
