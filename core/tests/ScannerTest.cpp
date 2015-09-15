/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include <core/Scanner.hpp>
#include <core/config.hpp>
#include <gtest/gtest.h>
#include <fstream>
#include <QFile>

using namespace std;
using namespace core;

TEST(ScannerTest, testScanCrossSignatures)
{
    const char* bytes = {"123456789"};
    unsigned size = 9;

    TSignatures sigMap;
    sigMap["4567"] = "1";
    sigMap["45678"] = "2";
    sigMap["567"] = "3";
    sigMap["5678"] = "4";

    Index index(sigMap);
    Scanner s(index);
    TSignatures result;
    EXPECT_TRUE(s.scan(bytes, size, result));

    EXPECT_EQ(4, result.size());
    EXPECT_TRUE(result.find("4567") != result.end());
    EXPECT_TRUE(result.find("45678") != result.end());
    EXPECT_TRUE(result.find("567") != result.end());
    EXPECT_TRUE(result.find("5678") != result.end());
}

TEST(ScannerTest, testScanSignatures)
{
    const char* bytes = {"0123456789ABCDEF"};
    unsigned size = 16;

    TSignatures sigMap;
    sigMap["4568"] = "1";
    sigMap["567"] = "111";
    sigMap["5678"] = "88";
    sigMap["5679"] = "88";
    sigMap["56789"] = "88";
    sigMap["56780"] = "88";
    sigMap["58"] = "9";
    sigMap["679"] = "10";
    sigMap["82"] = "11";
    sigMap["89"] = "11";
    sigMap["89A"] = "11";

    Index index(sigMap);
    Scanner s(index);
    TSignatures result;
    EXPECT_TRUE(s.scan(bytes, size, result));

    EXPECT_EQ(5, result.size());
    EXPECT_TRUE(result.find("567") != result.end());
    EXPECT_TRUE(result.find("5678") != result.end());
    EXPECT_TRUE(result.find("56789") != result.end());
    EXPECT_TRUE(result.find("89") != result.end());
    EXPECT_TRUE(result.find("89A") != result.end());
}



TEST(ScannerTest, testScanSignaturesFromFile)
{
    QFile file("data/shell.php");
    file.open(QFile::ReadOnly);
    unsigned long long size = file.size();
    char* bytes = (char*)file.map(0, size);

    TSignatures sigMap;
    EXPECT_TRUE(config::read("data/signatures.txt", sigMap));

    Index index(sigMap);
    Scanner s(index);

    TSignatures result;
    EXPECT_TRUE(s.scan(bytes, size, result));
    EXPECT_EQ(2, result.size());
    EXPECT_TRUE(result.find("if(@$_POST") != result.end());
    EXPECT_TRUE(result.find("eval($_POST") != result.end());
}
