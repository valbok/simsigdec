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
#include "Index.hpp"

namespace core
{

/**
 * Handler to find malware byte sequences.
 */
class Scanner
{
public:

    /**
     * @param Known index of signatures to check through.
     */
    explicit Scanner(const Index& index) noexcept;

    /**
     * Scans bytes and finds predefined sequence of byte. If found, bytes considered infected.
     * @param Input bytes to check.
     * @param Size of bytes.
     * @param[out] Where to store found elements.
     * @return true If found something.
     */
    bool scan(const char* bytes, unsigned long long size, TSignatures& result) const;

private:

    /**
     * Predefinded search index of signatures.
     */
    const Index& mIndex;

};

} // namespace core

#endif // SSD_SCANNER