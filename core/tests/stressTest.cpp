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
#include <sys/resource.h>

using namespace std;
using namespace core;

TEST(StressTest, testScanRead)
{
    QFile file("data/bigfile");
    file.open(QFile::ReadOnly);
    unsigned long long size = file.size();
    char* bytes = (char*)file.map(0, size);

    TSignaturesBySizes sigMap;
    EXPECT_TRUE(config::read("data/bigfile.signatures.txt", sigMap));

    Scanner s(sigMap);
    TSignatures result;

    float  userTime;
    struct rusage startTime, stopTime;

    getrusage(RUSAGE_SELF, &startTime);

    EXPECT_FALSE(s.scan(bytes, size, result));

    getrusage(RUSAGE_SELF, &stopTime);
    userTime = ((float)(stopTime.ru_utime.tv_sec - startTime.ru_utime.tv_sec)) +
                ((float)(stopTime.ru_utime.tv_usec - startTime.ru_utime.tv_usec)) * 1e-6;

    std::cout << "Scan time: " << userTime << " seconds\n";

    EXPECT_EQ(4, result.size());
}
