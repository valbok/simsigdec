/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "Scanner.hpp"
#include <sstream>

namespace core
{

Scanner::Scanner(const TSignaturesBySizes& signatures) noexcept
    : mSignatures(signatures)
{
}

bool Scanner::scan(
    const char* bytes,
    unsigned long long size,
    TSignatures& result) const
{
    for (unsigned long long i = 0; i < size; ++i)
    {
        // Go through signatures grouped by length.
        for (auto& sigMap: mSignatures)
        {
            unsigned length = sigMap.first;
            auto& signatures = sigMap.second;

            if (i + length > size)
            {
                continue;
            }

            std::string s(bytes + i, length);

            auto it = signatures.find(s);
            if (it != signatures.end())
            {
                result[it->first] = it->second;
            }
        }
    }

    return result.size() != 0;
}

} // namespace core
