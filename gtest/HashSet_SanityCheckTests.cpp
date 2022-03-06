// HashSet_SanityCheckTests.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// This is a set of "sanity checking" unit tests for your HashSet
// implementation, provided primarily as a mechanism for ensuring that
// your implementation is compatible with the unit tests we'll be using
// to test it, and to give you a quick example of how each of the member
// functions works.  These tests don't verify all of the functionality
// you're implementing.
//
// As with the sanity-checking unit tests you saw in other projects, you
// should not modify these in any way -- don't add #include directives,
// and don't change the code within the tests.  These should all compile
// and pass before you submit your HashSet implementation.

#include <string>
#include <gtest/gtest.h>
#include "HashSet.hpp"


namespace
{
    template <typename T>
    unsigned int zeroHash(const T& t)
    {
        return 0;
    }
}


TEST(HashSet_SanityCheckTests, inheritFromSet)
{
    HashSet<int> s1{zeroHash<int>};
    Set<int>& ss1 = s1;
    int sz1 = ss1.size();
    sz1 = 0;

    HashSet<std::string> s2{zeroHash<std::string>};
    Set<std::string>& ss2 = s2;
    int sz2 = ss2.size();
    sz2 = 0;
}


TEST(HashSet_SanityCheckTests, canCreateAndDestroy)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};
}


TEST(HashSet_SanityCheckTests, canCopyConstructToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s1Copy{s1};
    HashSet<std::string> s2Copy{s2};
}


TEST(HashSet_SanityCheckTests, canMoveConstructToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s1Copy{std::move(s1)};
    HashSet<std::string> s2Copy{std::move(s2)};
}


TEST(HashSet_SanityCheckTests, canAssignToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s3{zeroHash<int>};
    HashSet<std::string> s4{zeroHash<std::string>};

    s1 = s3;
    s2 = s4;
}


TEST(HashSet_SanityCheckTests, canMoveAssignToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s3{zeroHash<int>};
    HashSet<std::string> s4{zeroHash<std::string>};

    s1 = std::move(s3);
    s2 = std::move(s4);
}


TEST(HashSet_SanityCheckTests, isImplemented)
{
    HashSet<int> s1{zeroHash<int>};
    EXPECT_TRUE(s1.isImplemented());

    HashSet<std::string> s2{zeroHash<std::string>};
    EXPECT_TRUE(s2.isImplemented());
}


TEST(HashSet_SanityCheckTests, containsElementsAfterAdding)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_TRUE(s1.contains(11));
    EXPECT_TRUE(s1.contains(1));
    EXPECT_TRUE(s1.contains(5));
}


TEST(HashSet_SanityCheckTests, doesNotContainElementsNotAdded)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_FALSE(s1.contains(21));
    EXPECT_FALSE(s1.contains(2));
    EXPECT_FALSE(s1.contains(9));
}


TEST(HashSet_SanityCheckTests, sizeIsNumberOfElementsAdded)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_EQ(3, s1.size());
}


TEST(HashSet_SanityCheckTests, elementsAtIndexAccordingToHash)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_EQ(3, s1.elementsAtIndex(0));
    EXPECT_EQ(0, s1.elementsAtIndex(1));

    EXPECT_TRUE(s1.isElementAtIndex(11, 0));
    EXPECT_TRUE(s1.isElementAtIndex(1, 0));
    EXPECT_TRUE(s1.isElementAtIndex(5, 0));

    EXPECT_FALSE(s1.isElementAtIndex(11, 1));
    EXPECT_FALSE(s1.isElementAtIndex(1, 1));
    EXPECT_FALSE(s1.isElementAtIndex(5, 1));
}

