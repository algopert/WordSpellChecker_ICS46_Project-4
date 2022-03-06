// AVLSet_SanityCheckTests.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// This is a set of "sanity checking" unit tests for your AVLSet
// implementation, provided primarily as a mechanism for ensuring that
// your implementation is compatible with the unit tests we'll be using
// to test it, and to give you a quick example of how each of the member
// functions works.  These tests don't verify all of the functionality
// you're implementing.
//
// As with the sanity-checking unit tests you saw in other projects, you
// should not modify these in any way -- don't add #include directives,
// and don't change the code within the tests.  These should all compile
// and pass before you submit your AVLSet implementation.

#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "AVLSet.hpp"


TEST(AVLSet_SanityCheckTests, inheritFromSet)
{
    AVLSet<int> s1;
    Set<int>& ss1 = s1;
    int sz1 = ss1.size();
    sz1 = 0;

    AVLSet<std::string> s2;
    Set<std::string>& ss2 = s2;
    int sz2 = ss2.size();
    sz2 = 0;
}


TEST(AVLSet_SanityCheckTests, canCreateAndDestroy)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;
}


TEST(AVLSet_SanityCheckTests, heightOfEmptyIsNegativeOne)
{
    AVLSet<int> s;
    ASSERT_EQ(-1, s.height());
}


TEST(AVLSet_SanityCheckTests, canCopyConstructToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s1Copy{s1};
    AVLSet<std::string> s2Copy{s2};
}


TEST(AVLSet_SanityCheckTests, canMoveConstructToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s1Copy{std::move(s1)};
    AVLSet<std::string> s2Copy{std::move(s2)};
}


TEST(AVLSet_SanityCheckTests, canAssignToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s3;
    AVLSet<std::string> s4;

    s1 = s3;
    s2 = s4;
}


TEST(AVLSet_SanityCheckTests, canMoveAssignToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s3;
    AVLSet<std::string> s4;

    s1 = std::move(s3);
    s2 = std::move(s4);
}


TEST(AVLSet_SanityCheckTests, isImplemented)
{
    AVLSet<int> s1;
    EXPECT_TRUE(s1.isImplemented());

    AVLSet<std::string> s2;
    EXPECT_TRUE(s2.isImplemented());
}


TEST(AVLSet_SanityCheckTests, containsElementsAfterAdding)
{
    AVLSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_TRUE(s1.contains(11));
    EXPECT_TRUE(s1.contains(1));
    EXPECT_TRUE(s1.contains(5));
}


TEST(AVLSet_SanityCheckTests, doesNotContainElementsNotAdded)
{
    AVLSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_FALSE(s1.contains(21));
    EXPECT_FALSE(s1.contains(2));
    EXPECT_FALSE(s1.contains(9));
}


TEST(AVLSet_SanityCheckTests, sizeIsNumberOfElementsAdded)
{
    AVLSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_EQ(3, s1.size());
}


TEST(AVLSet_SanityCheckTests, heightDependsOnBalancing)
{
    AVLSet<int> balanced{true};
    balanced.add(1);
    balanced.add(2);
    balanced.add(3);

    AVLSet<int> notBalanced{false};
    notBalanced.add(1);
    notBalanced.add(2);
    notBalanced.add(3);

    EXPECT_EQ(1, balanced.height());
    EXPECT_EQ(2, notBalanced.height());
}


TEST(AVLSet_SanityCheckTests, canProvideTraversals)
{
    AVLSet<int> s{false};
    s.add(10);
    s.add(20);
    s.add(30);
    s.add(40);
    s.add(50);

    std::vector<int> preElements;
    std::vector<int> inElements;
    std::vector<int> postElements;

    s.preorder([&](const int& element) { preElements.push_back(element); });
    s.inorder([&](const int& element) { inElements.push_back(element); });
    s.postorder([&](const int& element) { postElements.push_back(element); });

    std::vector<int> expectedPreElements{10, 20, 30, 40, 50};
    std::vector<int> expectedInElements{10, 20, 30, 40, 50};
    std::vector<int> expectedPostElements{50, 40, 30, 20, 10};

    ASSERT_EQ(5, preElements.size());
    ASSERT_EQ(5, inElements.size());
    ASSERT_EQ(5, postElements.size());

    for (unsigned int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(preElements[i], expectedPreElements[i]);
        EXPECT_EQ(inElements[i], expectedInElements[i]);
        EXPECT_EQ(postElements[i], expectedPostElements[i]);
    }
}

