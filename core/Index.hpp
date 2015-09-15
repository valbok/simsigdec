/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#ifndef SSD_INDEX
#define SSD_INDEX

#include "types.hpp"

namespace core
{

/**
 * Indexer of signatures. Prepends it for lookup.
 * Allows to lookup signatures in large byte sequence in linear time.
 */
class Index
{
public:

    /**
     * Default constructor.
     */
    Index() noexcept;

    /**
     * @param Input known signatures to check through.
     */
    Index(const TSignatures& signatures) noexcept;

    /**
     * Sets signatures and creates the index.
     * @param Signatures.
     */
    void set(const TSignatures& signatures);

    /**
     * Item to store by prefix.
     */
    struct SSignatureItem
    {
        /**
         * Matched signatures: {4567:id, 567:id}
         * Means these signatures matched by this item.
         */
        TSignatures matches;

        /**
         * Number of signatures per substring, based on its index:
         *     For a signature "4597": [2,1,0,0] means
         *     2: There are 2 signatures started with 4597: for example 45971 and 4597358 (45971+)
         *     1: There is 1 signature started with 597: 5972, 59765982 (597+)
         *     0: There is no signatures started with 97: (97+)
         */
        std::vector<int> counts;
    };

    /**
     * Returns size of the index.
     */
    unsigned size() const;

    /**
     * Returns value by a key.
     */
    const SSignatureItem& value(const std::string& key) const;

    /**
     * Checks if a key exists.
     */
    bool has(const std::string& key) const;

private:

    /**
     * Actual index structure.
     * key - is a substr of signature.
     *      "4567": {matches: {"4567":"guid"}, counts: [2,1,0,0]}
     */
    typedef std::unordered_map<std::string, SSignatureItem> TIndex;

    /**
     * Creates an index.
     * @param Input signatures.
     * @param[out] Result.
     */
    static void index(const TSignatures& signatures, TIndex& index);

    /**
     * Keeps created index.
     */
    TIndex mIndex;

};

} // namespace core

#endif // SSD_INDEX