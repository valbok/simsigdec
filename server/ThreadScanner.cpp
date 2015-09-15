/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "ThreadScanner.hpp"
#include <core/Scanner.hpp>
#include <QFile>

namespace server
{

ThreadScanner::ThreadScanner(
    const QStringList& files,
    const core::Index& index)
    : mFiles(files)
    , mIndex(index)
{
}

void ThreadScanner::run()
{
    core::Scanner s(mIndex);
    for (auto& name: mFiles) 
    {
        QFile file(name);
        QStringList result;
        if (file.open(QFile::ReadOnly))
        {
            unsigned long long size = file.size();
            char* bytes = (char*)file.map(0, size);
            if (bytes != 0)
            {
                core::TSignatures found;
                s.scan(bytes, size, found);
                for (auto& f: found)
                {
                    result.push_back(f.second.c_str());
                }
            }
        }
        emit finished(name, result);
    }
}

} // namespace objects