/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#ifndef SSD_CONFIG
#define SSD_CONFIG

#include "types.hpp"
#include <vector>

namespace core
{
namespace config
{

/**
 * Reads from signature file and makes proper result set.
 * @return true If found.
 */
bool read(const char* name, TSignaturesBySizes& result) noexcept;

} // namespace config
} // namespace core

#endif // SSD_CONFIG