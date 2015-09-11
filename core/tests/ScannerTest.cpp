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

TEST(ScannerTest, testScanSignatures) 
{
    QFile file("data/shell.php");
    file.open(QFile::ReadOnly);
    unsigned long long size = file.size();
    char* bytes = (char*)file.map(0, size);

    TSignaturesBySizes sigMap;
    sigMap[11]["eval($_POST"] = "1";
    sigMap[10]["if(@$_POST"] = "3";
    sigMap[6]["uknown"] = "4";
    sigMap[6]["beware"] = "5";
    sigMap[5]["virus"] = "6";    
    
    Scanner s(sigMap);
    TSignatures result;
    EXPECT_TRUE(s.scan(bytes, size, result));

    EXPECT_EQ(2, result.size());
    EXPECT_EQ("3", result[0].second);
    EXPECT_EQ("1", result[1].second);
}

TEST(ScannerTest, testScanSignaturesFromFile) 
{
    QFile file("data/shell.php");
    file.open(QFile::ReadOnly);
    unsigned long long size = file.size();
    char* bytes = (char*)file.map(0, size);
    
    TSignaturesBySizes sigMap;
    EXPECT_TRUE(config::read("data/signatures.txt", sigMap));
    
    Scanner s(sigMap);
    TSignatures result;
    EXPECT_TRUE(s.scan(bytes, size, result));
    EXPECT_EQ(2, result.size());
    EXPECT_EQ("1", result[0].second);
    EXPECT_EQ("5c34b10f-3f6d-4cbb-09ec-0faa1ee17660", result[1].second);
    
}
