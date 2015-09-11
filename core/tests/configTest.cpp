/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include <core/config.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace core;

TEST(ConfigTest, testRead)
{
    TSignaturesBySizes result;
    EXPECT_TRUE(config::read("data/signatures.txt", result));
    EXPECT_EQ(5, result.size());
    auto it = result.begin();
    EXPECT_EQ(20, it->first);
    ++it;
    EXPECT_EQ(11, it->first);
}

