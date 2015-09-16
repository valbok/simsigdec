/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "Server.hpp"
#include <QThreadPool>
#include <QDebug>
#include <core/config.hpp>
#include <core/Index.hpp>

namespace server
{

bool Server::start()
{
    core::TSignatures sigs;
    if (!core::config::read("signatures.txt", sigs))
    {
        qCritical() << "Could not find signatures";
        return false;
    }

    mIndex.set(sigs);

    if (!this->listen(QHostAddress::Any, 6666))
    {
        qCritical() << "Could not start server";
        return false;
    }

    qDebug() << "Server started!";
    return true;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    auto task = new Connection(socketDescriptor, mIndex);
    task->setAutoDelete(true);

    QThreadPool::globalInstance()->start(task);
}

} // namespace server

