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

class ThreadScanner : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ThreadScanner(const QString& filename, const core::TSignaturesBySizes& signatures);
    void run();

signals:
    void finished(const QString& filename, const QStringList& result);

private:
    const QString& mName;
    const core::TSignaturesBySizes& mSignatures;
};

} // namespace objects

#endif // SSD_THREADSCANNER