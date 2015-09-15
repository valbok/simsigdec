/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include <QApplication>
#include "Server.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    server::Server s;
    if (s.start()) 
    {
        return a.exec();
    }

    return 1;
}
