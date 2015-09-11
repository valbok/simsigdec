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

namespace objects
{

ThreadScanner::ThreadScanner(
    const QStringList& files,
    const core::TSignaturesBySizes& signatures)
    : mFiles(files)
    , mSignatures(signatures)
{
}

void ThreadScanner::run()
{
    core::Scanner s(mSignatures);
    for (auto& name: mFiles) 
    {
        QFile file(name);
        QStringList result;
        if (file.open(QFile::ReadOnly))
        {
            unsigned long long size = file.size();
            char* bytes = (char*)file.map(0, size);

            core::TSignatures found;
            s.scan(bytes, size, found);
            for (auto& f: found)
            {
                result.push_back(f.second.c_str());
            }
        }
        emit finished(name, result);
    }
}

} // namespace objects