/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "config.hpp"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <sstream>

namespace core
{
namespace config
{

bool read(const char* name, TSignatures& result) noexcept
{
    QFile file(name);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            // Line could be like: "FFFF.{123}"
            // Spliets to "FFF" and "123}"
            QStringList strings = in.readLine().split(".{");
            if (strings.size() != 2)
            {
                continue;
            }
            std::string sig(strings[0].toLocal8Bit().constData());
            // Splits to "123" and ""
            QStringList tmp = strings[1].split("}");
            if (tmp.size() == 0)
            {
                continue;
            }
            std::string guid(tmp[0].toLocal8Bit().constData());

            // Convert hex string to number value.
            std::string signature;
            for (unsigned i = 0; i < sig.size(); i += 2)
            {
                std::stringstream ss;
                ss << std::hex << sig.substr(i, 2);
                unsigned int ch;
                ss >> ch;
                signature.push_back((char)ch);
            }
            result[signature] = guid;
        }
    }

    return result.size() != 0;
}

} // namespace config
} // namespace core

