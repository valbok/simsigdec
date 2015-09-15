/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#ifndef SSD_CONNECTION
#define SSD_CONNECTION

#include <core/Index.hpp>
#include <QObject>
#include <QRunnable>
#include <QTcpSocket>

namespace server
{

/**
 * Handles requests from users.
 * User is supposed to send files separated by "\n" that should be analysed for malware.
 * This handler will split these files to batches
 * and create a list of tasks to process them separately in threads using thread pool.
 */
class Connection: public QObject, public QRunnable
{
    Q_OBJECT
public:

    /**
     * @param Files to process.
     * @param Index.
     */
    Connection(qintptr socketDescriptor, const core::Index& index);

    /**
     * @copydoc QRunnable::run()
     */
    void run();

public slots:

    /**
     * Reads files to process.
     */
    void readyRead();

    /**
     * Emitted when gets response from ThreadScanner about finished task.
     * @param Processed filename.
     * @param Found malware.
     */
    void finishedTask(const QString& filename, const QStringList& result);

private:

    /**
     * Starts a task in separate thread to process batch of files.
     */
    void startTask(const QStringList& files);

    /**
     * TCP Socket.
     */
    QTcpSocket mSocket;

    /**
     * Predefined index of malware byte sequences.
     */
    const core::Index& mIndex;

    /**
     * Number of proccessed files.
     */
    unsigned mProcessed;

    /**
     * Total number of files to proccess.
     */
    unsigned mTotal;

    /**
     * Number of infected files.
     */
    unsigned mInfected;

};

} // namespace server

#endif // SSD_CONNECTION