/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#ifndef SSD_THREADSCANNER
#define SSD_THREADSCANNER

#include <QRunnable>
#include <QStringList>
#include <core/types.hpp>

namespace objects
{

/**
 * Task to proceed in a thread. Hanldes a batch of files.
 */
class ThreadScanner : public QObject, public QRunnable
{
    Q_OBJECT
public:

    /**
     * @param Files to process
     */
    ThreadScanner(const QStringList& files, const core::TSignaturesBySizes& signatures);

    /**
     * @copydoc QRunnable::run()
     */
    void run();

signals:

    /**
     * Emited when file is finished to process.
     */
    void finished(const QString& filename, const QStringList& result);

private:

    /**
     * Batch of files to process.
     */
    const QStringList mFiles;

    /**
     * Predefined sequences of bytes.
     */
    const core::TSignaturesBySizes& mSignatures;
};

} // namespace objects

#endif // SSD_THREADSCANNER