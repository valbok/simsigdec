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

typedef unsigned char* TBytes;
typedef unsigned long long TSize;

typedef std::unordered_map<std::string, std::string> TSignaturesMap;
typedef std::vector<std::pair<std::string, std::string> > TSignatures;

typedef std::unordered_map<unsigned, TSignaturesMap> TSignaturesBySizes;

} // namespace core

#endif // SSD_TYPES