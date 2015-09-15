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
    TSignatures result;
    EXPECT_TRUE(config::read("data/signatures.txt", result));
    EXPECT_EQ(5, result.size());
    auto it = result.begin();
    EXPECT_EQ("meta-object-compiler", it->second);
    ++it;
    EXPECT_EQ("5c34b10f-3f6d-4cbb-09ec-0faa1ee17660", it->second);
}

