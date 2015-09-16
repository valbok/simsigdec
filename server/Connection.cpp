/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "Connection.hpp"
#include <server/ThreadScanner.hpp>

#include <QString>
#include <QStringList>
#include <QThreadPool>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

namespace server
{

Connection::Connection(qintptr socketDescriptor, const core::Index& index)
    : mIndex(index)
    , mProcessed(0)
    , mTotal(0)
    , mInfected(0)
{
    mSocket.setSocketDescriptor(socketDescriptor);

    connect(&mSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Connection::run()
{
    // Do not quite the function if connection is still established.
    while (mSocket.state() != QAbstractSocket::UnconnectedState)
    {
    }
}

void Connection::readyRead()
{
    QString array = mSocket.readAll();
    if (array.isEmpty())
    {
        return;
    }

    QStringList files = array.split("\n");
    mTotal = files.size();

    const int numFiles = files.size() > QThread::idealThreadCount() ? files.size() / QThread::idealThreadCount() : files.size();
    QStringList batch;
    for (int i = 0; i < files.size(); ++i)
    {
        if (files[i].isEmpty())
        {
            continue;
        }

        batch.push_back(files[i]);
        if (batch.size() >= numFiles)
        {
            startTask(batch);
            batch.clear();
        }
    }

    if (!batch.empty())
    {
        startTask(batch);
    }
}

void Connection::startTask(const QStringList& files)
{
    ThreadScanner* task = new ThreadScanner(files, mIndex);
    task->setAutoDelete(true);

    QObject::connect(task, SIGNAL(finished(const QString&, const QStringList&)),
        this, SLOT(finishedTask(const QString&, const QStringList&)));

    QThreadPool::globalInstance()->start(task);
}

void Connection::finishedTask(const QString& filename, const QStringList& result)
{
    ++mProcessed;
    mInfected += result.size() != 0;

    QJsonArray array;
    QJsonObject json;
    json["processed"] = QString::number(mProcessed);
    json["total"] = QString::number(mTotal);
    json["infected"] = QString::number(mInfected);
    json["filename"] = filename;
    for (auto& r: result)
    {
        array.append(r);
    }

    json["result"] = array;
    QString response = QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n";
    mSocket.write(response.toLocal8Bit().constData());

    // If all files processed, close connection.
    if (mProcessed >= mTotal)
    {
        mSocket.disconnectFromHost();
    }
}

} // namespace server
