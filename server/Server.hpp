/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#ifndef SSD_SERVER
#define SSD_SERVER

#include <QObject>
#include <QTcpServer>
#include "Connection.hpp"

namespace server
{

/**
 * TCP Server to handle requests from gui clients.
 */
class Server: public QTcpServer
{
public:

    /**
     * Starts the server.
     * @return true If successful.
     */
    bool start();

protected:

    /**
     * On connection creates a connection task in thread pool.
     * @copydoc QTcpServer::incomingConnection()
     */
    void incomingConnection(qintptr handle);

private:

    /**
     * Parsed index of signatures.
     */
    core::Index mIndex;
};

} // namespace server

#endif // SSD_SERVER