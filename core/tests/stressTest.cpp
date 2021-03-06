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

    TSignatures sigMap;
    EXPECT_TRUE(config::read("data/bigfile.signatures.txt", sigMap));

    Index index(sigMap);
    Scanner s(index);
    TSignatures result;

    float  userTime;
    struct rusage startTime, stopTime;

    getrusage(RUSAGE_SELF, &startTime);

    EXPECT_TRUE(s.scan(bytes, size, result));

    getrusage(RUSAGE_SELF, &stopTime);
    userTime = ((float)(stopTime.ru_utime.tv_sec - startTime.ru_utime.tv_sec)) +
                ((float)(stopTime.ru_utime.tv_usec - startTime.ru_utime.tv_usec)) * 1e-6;

    std::cout << "Scan time: " << userTime << " seconds\n";

    std::cout <<"Found " << result.size() << " signatures.\n";
    for (auto& s: result)
    {
        std::cout << s.first <<":" <<s.second << std::endl;
    }
}
