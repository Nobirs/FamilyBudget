#include <gtest/gtest.h>
#include "User.h"

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
