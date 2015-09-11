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

bool read(const char* name, TSignaturesBySizes& result) noexcept
{
    QFile file(name);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QStringList strings = in.readLine().split(".{");
            if (strings.size() != 2)
            {
                continue;
            }
            std::string sig(strings[0].toLocal8Bit().constData());
            QStringList tmp = strings[1].split("}");
            if (tmp.size() == 0)
            {
                continue;
            }
            std::string guid(tmp[0].toLocal8Bit().constData());

            std::string signature;
            for (unsigned i = 0; i < sig.size(); i += 2)
            {
                std::stringstream ss;
                ss << std::hex << sig.substr(i, 2);
                unsigned int ch;
                ss >> ch;
                signature.push_back((char)ch);
            }
            result[signature.size()][signature] = guid;
        }
    }

    return result.size() != 0;
}

} // namespace config
} // namespace core

