#pragma once
#include <vector>
#include <string>
/*******************************************************************************************

Function set for UTF StrLwr, StrUpr and case insensitive StrCmp and  StrStr

by Jan Bergström, Alphabet AB, 2021 Open source code

2021-10-21

*******************************************************************************************/

class UTFConverter {
public:
    // Definition of the Utf8Char type
    using Utf8Char = unsigned char;  // must be 1 byte, 8 bits, can be char, the UTF consortium specifies unsigned 

    // Static methods for UTF-32
    static void StrToLwrUtf32(std::vector<char32_t>& utf32Text);

    // Static methods for UTF-16
    static size_t CharLenUtf16(const wchar_t* pUtf16);
    static std::vector<char32_t> Utf16ToUtf32(const std::u16string& utf16String);

    // Static methods for UTF-8
    static size_t CharLenUtf8(const Utf8Char* pUtf8);
    static size_t StrLenUtf32AsUtf8(const uint32_t* pUtf32);
    static std::vector<char32_t> Utf8ToUtf32(const std::u8string& utf8String);
};
