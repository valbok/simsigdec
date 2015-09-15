/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include <core/Index.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace core;

TEST(IndexTest, testIndex)
{
    TSignatures sigMap;
    sigMap["4567"] = "1";
    sigMap["45678"] = "111";
    sigMap["567"] = "7";
    sigMap["5678"] = "8";

    Index index(sigMap);

    EXPECT_EQ(9, index.size());
    EXPECT_TRUE(index.value("4567").matches.find("4567") != index.value("4567").matches.end());
    EXPECT_TRUE(index.value("4567").matches.find("567") != index.value("4567").matches.end());
    EXPECT_EQ(4, index.value("4567").counts.size());
    EXPECT_EQ(1, index.value("4567").counts[0]);
    EXPECT_EQ(1, index.value("4567").counts[1]);
    EXPECT_EQ(0, index.value("4567").counts[2]);
    EXPECT_EQ(0, index.value("4567").counts[3]);

    EXPECT_TRUE(index.value("45678").matches.find("45678") != index.value("45678").matches.end());
    EXPECT_EQ(5, index.value("45678").counts.size());
    EXPECT_EQ(0, index.value("45678").counts[0]);
    EXPECT_EQ(0, index.value("45678").counts[1]);
    EXPECT_EQ(0, index.value("45678").counts[2]);
    EXPECT_EQ(0, index.value("45678").counts[3]);
    EXPECT_EQ(0, index.value("45678").counts[4]);
}
