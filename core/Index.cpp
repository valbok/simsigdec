/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "Scanner.hpp"
#include <sstream>
#include <iostream>

namespace core
{

Index::Index() noexcept
{
}

Index::Index(const TSignatures& signatures) noexcept
{
    set(signatures);
}

void Index::set(const TSignatures& signatures)
{
    index(signatures, mIndex);
}

void Index::index(const TSignatures& signatures, TIndex& index)
{
    for (auto& sigItem: signatures)
    {
        auto& sig = sigItem.first;
        for (unsigned i = 1; i <= sig.size(); ++i)
        {
            std::string s = sig.substr(0, i);
            if (index.find(s) == index.end())
            {
                index[s] = {{}, std::vector<int>(s.size(), -1)};
            }

            auto& item = index[s];
            auto& vec = item.counts;
            auto& matches = item.matches;

            for (unsigned j = 0; j < i; ++j)
            {
                if (vec[j] > -1)
                {
                    continue;
                }
                else if (vec[j] == -1)
                {
                    vec[j] = 0;
                }

                std::string part = s.substr(j);
                for (auto& sgnt: signatures)
                {
                    // Starts with.
                    if (sgnt.first.find(part) == 0)
                    {
                        if (sgnt.first.size() == part.size())
                        {
                            matches[sgnt.first] = sgnt.second;
                        }
                        else
                        {
                            vec[j] += 1;
                        }
                    }
                }
            }
        }
    }
}

unsigned Index::size() const
{
    return mIndex.size();
}

const Index::SSignatureItem& Index::value(const std::string& key) const
{
    return mIndex.find(key)->second;
}

bool Index::has(const std::string& key) const
{
    return mIndex.find(key) != mIndex.end();
}

} // namespace core
