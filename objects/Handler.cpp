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

void run(const QStringList& files, const core::TSignaturesBySizes& signatures, Handler* handler)
{
    ThreadScanner* task = new ThreadScanner(files, signatures);
    task->setAutoDelete(true);

    QObject::connect(task, SIGNAL(finished(const QString&, const QStringList&)),
        handler, SLOT(finishedTask(const QString&, const QStringList&)));

    QThreadPool::globalInstance()->start(task);
}

void Handler::process()
{
    const int numThreads = 5;
    const int numFiles = mFiles.size() / numThreads;
    QThreadPool::globalInstance()->setMaxThreadCount(numThreads);

    QStringList files;
    for (int i = 0; i < mFiles.size(); ++i)
    {
        files.push_back(mFiles[i]);
        if (files.size() >= numFiles)
        {
            run(files, mSignatures, this);
            files.clear();
        }
    }
    if (!files.empty())
    {
        run(files, mSignatures, this);
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

