/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "Scanner.hpp"
#include <iostream>
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
        for (auto& sigMap: mSignatures) 
        {
            unsigned offset = sigMap.first;
            auto& signatures = sigMap.second;

            std::string s(bytes + i, bytes + i + offset);
            auto it = signatures.find(s);
            if (it != signatures.end()) 
            {
                result.push_back(*it);
            }
        }
    }

    return result.size() != 0;
}

} // namespace core
