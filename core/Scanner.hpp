/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#ifndef SSD_SCANNER
#define SSD_SCANNER

#include "types.hpp"

namespace core
{

/**
 * Handler to find malware byte sequences.
 */
class Scanner
{
public:

    /**
     * Input known signatures to check through.
     */
    Scanner(const TSignaturesBySizes& signatures) noexcept;

    /**
     * Scans bytes and finds predefined sequence of byte. If found, bytes considered infected.
     * @return true If found something.
     */
    bool scan(const char* bytes, unsigned long long size, TSignatures& result) const;

private:

    /**
     * Predefined set of signatures.
     */
    const TSignaturesBySizes& mSignatures;

};

} // namespace core

#endif // SSD_SCANNER