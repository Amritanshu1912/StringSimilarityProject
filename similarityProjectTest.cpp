
// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
// 
// gtest.h, declares the testing framework.

#include "gtest/gtest.h"
#include "similarityProject.h"

namespace
{

    // Step 2. Use the TEST macro to define your tests.
    //
    // TEST has two parameters: the test case name and the test name.
    // After using the macro, you should define your test logic between a
    // pair of braces.  You can use a bunch of macros to indicate the
    // success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
    // examples of such macros.  For a complete list, see gtest.h.
    //
    // In Google Test, tests are grouped into test cases.  This is how
    // test code is kept organized.  You should put logically related
    // tests into the same test case.
    //
    // The test case name and the test name should both be valid C++
    // identifiers.  And you should not use underscore (_) in the names.

    // Tests levenschtein_distance_algorithm().

    // Tests levenschtein_distance_algorithm on such cases where one or both of the strings are empty
    TEST(findSimilarityLevenshtein1, anyEmpty)
    {
        // This test is named "anyEmpty", and belongs to the "levenschtein_distance_algorithm" test case.

        EXPECT_EQ((0.0), levenschtein_distance_algorithm({"", ""}));       // both strings are empty
        EXPECT_EQ((0.0), levenschtein_distance_algorithm({"", "abcdef"})); // first string is empty
        EXPECT_EQ((0.0), levenschtein_distance_algorithm({"abcdef", ""})); // second string is  empty
    }

    // Tests levenschtein_distance_algorithm on non-empty strings
    TEST(findSimilarityLevenshtein2, noneEmpty)
    {
        EXPECT_EQ((1.0), levenschtein_distance_algorithm({"abcdef", "abcdef"}));
        EXPECT_EQ((0.0), levenschtein_distance_algorithm({"abcdef", "software"}));
        EXPECT_EQ((0.50), levenschtein_distance_algorithm({"a", "ab"}));
        EXPECT_EQ((0.56), levenschtein_distance_algorithm({"abbdeffff", "abceff"}));
        EXPECT_EQ((0.33), levenschtein_distance_algorithm({"aa", "aaaaaa"})); // 2,6 a's
        EXPECT_EQ((0.50), levenschtein_distance_algorithm({"lawn", "flaw"}));
    }
    // Tests levenschtein_distance_algorithm on non-empty strings with spaces in between
    TEST(findSimilarityLevenshtein3, withSpaces)
    {
        EXPECT_EQ((0.50), levenschtein_distance_algorithm({"ab cde f", "a bc def"}));
        EXPECT_EQ((0.60), levenschtein_distance_algorithm({"  aa", "a   a"})); // 2 spaces in beginning and 3 spaces in between
        EXPECT_EQ((0.33), levenschtein_distance_algorithm({"ml awn", "fl cdz aw"}));
    }

    //--------------------------------------------------------------------------------------//
    //--------------------------------------------------------------------------------------//

    // Tests dice_coefficient_algorithm on such cases where one or both of the strings are empty
    TEST(findSimilarityDiceCoefficient1, anyEmpty)
    {
        // This test is named "anyEmpty", and belongs to the "dice_coefficient_algorithm" test case.

        EXPECT_EQ((0.0), dice_coefficient_algorithm({"", ""}));       // both strings are empty
        EXPECT_EQ((0.0), dice_coefficient_algorithm({"", "abcdef"})); // first string is empty
        EXPECT_EQ((0.0), dice_coefficient_algorithm({"abcdef", ""})); // second string is  empty
    }

    // Tests dice_coefficient_algorithm on non-empty strings
    TEST(findSimilarityDiceCoefficient2, noneEmpty)
    {
        EXPECT_EQ((1.0), dice_coefficient_algorithm({"abcdef", "abcdef"}));
        EXPECT_EQ((0.0), dice_coefficient_algorithm({"abcdef", "software"}));
        EXPECT_EQ((0.0), dice_coefficient_algorithm({"a", "ab"}));
        EXPECT_EQ((0.46), dice_coefficient_algorithm({"abbdeffff", "abceff"}));
        EXPECT_EQ((0.33), dice_coefficient_algorithm({"aa", "aaaaaa"})); // 2,6 a's
        EXPECT_EQ((0.67), dice_coefficient_algorithm({"lawn", "flaw"}));
    }
    // Tests dice_coefficient_algorithm on non-empty strings with spaces in between
    TEST(findSimilarityDiceCoefficient3, withSpaces)
    {
        EXPECT_EQ((0.14), dice_coefficient_algorithm({"ab cde f", "a bc def"}));
        EXPECT_EQ((0.57), dice_coefficient_algorithm({"  aa", "a   a"})); // 2 spaces in beginning and 3 spaces in between
        EXPECT_EQ((0.46), dice_coefficient_algorithm({"ml awn", "fl cdz aw"}));
    }

} // namespace

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
