/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "Scanner.hpp"
#include <queue>

namespace core
{

Scanner::Scanner(const Index& index) noexcept
    : mIndex(index)
{
}

bool Scanner::scan(
    const char* bytes,
    unsigned long long size,
    TSignatures& result) const
{
    // Keeps prev sequences.
    std::queue<std::string> q;

    for (unsigned long long i = 0; i < size; ++i)
    {
        std::string curr = std::string(1, bytes[i]);
        q.push("");
        // At least 1 item exists here.
        while (!q.empty())
        {
            std::string prev = q.front();
            q.pop();

            std::string v = prev + curr;

            if (mIndex.has(v))
            {
                auto item = mIndex.value(v);
                // Clear queue.
                q = {};
                for (unsigned j = 0, cc = 0; j < item.counts.size() && cc < 2; ++j)
                {
                    if (item.counts[j] > 0)
                    {
                        q.push(v.substr(j));
                        ++cc;
                    }
                }

                for (auto& m: item.matches)
                {
                    result[m.first] = m.second;
                }

                // Quit queue loop.
                break;
            }
        }
    }

    return result.size() != 0;
}

} // namespace core
