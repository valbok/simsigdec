/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#ifndef SSD_TYPES
#define SSD_TYPES

#include <string>
#include <unordered_map>
#include <vector>

namespace core
{

/**
 * Target bytes to check.
 */
typedef unsigned char* TBytes;

/**
 * Size of target bytes.
 */
typedef unsigned long long TSize;

/**
 * Maps predefinded sequence of bytes that should be considered as a malware and its GUID.
 */
typedef std::unordered_map<std::string, std::string> TSignatures;

/**
 * Grouped sequences by length: {length of sequences: {sequences: GUIDs}}
 */
typedef std::unordered_map<unsigned, TSignatures> TSignaturesBySizes;

} // namespace core

#endif // SSD_TYPES