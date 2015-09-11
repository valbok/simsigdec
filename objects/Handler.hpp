/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#ifndef SSD_HANDLER
#define SSD_HANDLER

#include <QString>
#include <QStringList>
#include <unordered_map>
#include <core/types.hpp>

namespace objects 
{

/**
 * Handler collects target files and checks them for malware signatures.
 */
class Handler : public QObject 
{
    Q_OBJECT
public:

    /**
     * @param Target files.
     * @param Predefined signatures.
     */
    Handler(const QStringList& files, const core::TSignaturesBySizes& signatures) noexcept;

    /**
     * Processes the files, creates threads, using thread pool.
     */
    void process();

public slots:
    
    /**
     * Gets a signal when ThreadScanner finishes processing the file
     * @param Processed filename
     * @param List of found malware.
     */
    void finishedTask(const QString& filename, const QStringList& result);

signals:
    
    /**
     * Emitted this when gets response from ThreadScanner about finished task.
     * @param Number of processed files.
     * @param Number of found infected files.
     * @param Total number of files.
     */
    void processed(unsigned processed, unsigned found, unsigned total);

    /**
     * Emitted when gets response from ThreadScanner about finished task.
     * @param Processed filename
     * @param Found malware.
     */
    void finishedFile(const QString& filename, const QStringList& result);

private:
    /**
     * Target files.
     */
    QStringList mFiles;

    /**
     * Predefined sequenses of bytes.
     */
    core::TSignaturesBySizes mSignatures;

    /**
     * Result of processed files. Filename -> list of found signatures.
     */
    std::unordered_map<std::string, QStringList> mProcessed;
    
    /**
     * Number of infected files.
     */
    unsigned mInfected;
};

} // namespace objects

#endif // SSD_HANDLER