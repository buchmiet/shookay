**Shookay Search Engine Library v0.5**

**Overview**
Shookay is a versatile, high-performance search engine library designed to offer efficient and dynamic search capabilities. This universal library is suitable for various applications, making it a valuable tool for developers seeking an advanced, yet easy-to-use search solution.

**Features**
Fast Performance: Optimized with C++ and x64 assembly, Shookay ensures rapid search results even with large datasets.
Flexible Search Options: Offers both 'FindWithin' and 'FindExact' search methods to cater to different search requirements.
Multilingual Support: Compatible with UTF-8, UTF-16, and UTF-32 encoding, providing versatility for international applications.
Dynamic Search Capabilities: Allows for searching by partial word fragments and associated terms, enhancing user experience.
Separate Search Engine Instances: Each application component can utilize its own instance of the search engine for specialized data handling.
Installation
Zakładając, że tworzysz bibliotekę DLL w C++, instrukcje instalacji i integracji mogą wyglądać mniej więcej tak:

**Installation and Integration**

**Compiling the Library**

**Clone the Repository:** Clone or download the shookay repository from GitHub.

git clone https://github.com/buchmiet/shookay 

**Open the Solution:** Open the shookay.sln file in Visual Studio or your preferred C++ IDE.

**Build the Solution:** Compile the solution to produce the shookay.dll file.

**Usage**

add 

```cpp
#include "shookay.h"
```

to your project

**Delivering Entries**

Create instance of the engine:

```cpp
shookayEngine* searchEngine = CreateSearchEngine();
```

if you work with UTF-8:

```cpp
std::map<int, std::string> entries;
entries[0] = { "never these expenthisditure go been" };
entries[1] = { "asd every possession aaaaa" };
entries[2] = { "this young permeveryissionevery" };
entries[3] = { "understanding performance this young permeasdveryissionevery" };
entries[4] = { "asd every" };
entries[5] = { "had each another every industrial line change" };
entries[6] = { "keep specialization had America are leave realization by enough population here countryside back" };
entries[7] = { "its so say as had away white innovation" };
entries[8] = { " ŁukaSz, Ekąb. ZZÓ. Żźoa ,,,/fTQs ..Ł \\aa,,,,grgtrUIOUK...." };
DeliverEntries(searchEngine, &entries, UTF8Map);
```

for UTF-16 :

```cpp
std::map<int, std::u16string> entries;
entries[0] = { u"never these expenthisditure go been" };
entries[1] = { u"asd every possession aaaaa" };
entries[2] = { u"this young permeveryissionevery" };
entries[3] = { u"understanding performance this young permeasdveryissionevery" };
entries[4] = { u"asd every" };
entries[5] = { u"had each another every industrial line change" };
entries[6] = { u"keep specialization had America are leave realization by enough population here countryside back" };
entries[7] = { u"its so say as had away white innovation" };
entries[8] = { u" ŁukaSz, Ekąb. ZZÓ. Żźoa ,,,/fTQs ..Ł \\aa,,,,grgtrUIOUK...." };
DeliverEntries(searchEngine, &entries, UTF16Map);
```

for UTF-32:

```cpp
std::map<int, std::u32string> entries;
entries[0] = { U"never these expenthisditure go been" };
entries[1] = { U"asd every possession aaaaa" };
entries[2] = { U"this young permeveryissionevery" };
entries[3] = { U"understanding performance this young permeasdveryissionevery" };
entries[4] = { U"asd every" };
entries[5] = { U"had each another every industrial line change" };
entries[6] = { U"keep specialization had America are leave realization by enough population here countryside back" };
entries[7] = { U"its so say as had away white innovation" };
entries[8] = { U" ŁukaSz, Ekąb. ZZÓ. Żźoa ,,,/fTQs ..Ł \\aa,,,,grgtrUIOUK...." };
DeliverEntries(searchEngine, &entries, UTF32Map);
```

now entries are delivered to the engine. then, perform search 

for UTF-8:

```cpp
std::string searchTerm = "issio";
int resultLength;
int* x = FindWithinUTF8(searchEngine, searchTerm.c_str(), &resultLength);
```

for UTF-16:

```cpp
std::string searchTerm = "issio";
int resultLength;
int* x = FindWithinUTF16(searchEngine, searchTerm.c_str(), &resultLength);
```

for UTF-32:

```cpp
std::string searchTerm = "issio asd";
int resultLength;
int* x = FindWithinUTF16(searchEngine, searchTerm.c_str(), &resultLength);
```

now x returns the pointer to the map entries.
**Note**: Once you submit entries, data is converted to UTF-32, therefore search term and entries may use different encodings.

**License**

This project is licensed under the MIT License - see the LICENSE file for details.

MIT License Summary

The MIT License is a permissive license that is short and to the point. It lets people do anything they want with your code as long as they provide attribution back to you and don’t hold you liable.

Permissions
Commercial use
Modification
Distribution
Private use
Conditions
Include the original license and copyright notice with the code
Limitations
No Liability
No Warranty

## [0.5.1] - 2024-01-08
### fixed:
- Fixed bug: preserving RDX for the duration of the function due to the MSVC calling convention.
