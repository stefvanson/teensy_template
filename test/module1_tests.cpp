#include "gtest/gtest.h"
#include "module1/module1.cpp"

TEST(Module1Tests, CorrectReturnValues) {
    ASSERT_EQ(1, module1_function(1));
    ASSERT_EQ(2, module1_function(2));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
