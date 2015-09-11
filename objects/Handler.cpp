/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "Handler.hpp"
#include "ThreadScanner.hpp"
#include <QDirIterator>
#include <QThreadPool>

namespace objects 
{

Handler::Handler(const QStringList& files, 
    const core::TSignaturesBySizes& signatures
    ) noexcept
    : mFiles(files)
    , mSignatures(signatures)
    , mInfected(0)
{
}

void Handler::process() 
{
    for (auto& f: mFiles) 
    {
        ThreadScanner *task = new ThreadScanner(f, mSignatures);
        task->setAutoDelete(true);

        connect(task, SIGNAL(finished(const QString&, const QStringList&)), 
            this, SLOT(finishedTask(const QString&, const QStringList&)));

        QThreadPool::globalInstance()->start(task);
    }
}

void Handler::finishedTask(const QString& filename, const QStringList& result) 
{
    mProcessed[filename.toLocal8Bit().constData()] = result;
    emit finishedFile(filename, result);
    mInfected += result.size() != 0; 
    emit processed(mProcessed.size(), mFiles.size(), mInfected);
}

} // namespace objects

