# **Shookay Search Engine Library v0.6.2**

## **Overview**
Shookay is a versatile, high-performance search engine library designed to offer efficient and dynamic search capabilities. It is pretty universal, as you can integrate it with any application that can provide simple text data. 

## **Features**
- Fast Performance: It's based on Inverted Index method;
- Flexible Search Options: You can use parenthesis, logical AND, OR and NOT operators. You can also look for words being the very exact matches or words being only substrings;
- Multilingual Support: Compatible with UTF-8, UTF-16, and UTF-32 encoding - it accepts text in any language you can fit in that encoding; 
- Separate Search Engine Instances: you can run many separate search engines on different datasets at the same time

## **Installation and Integration**

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

**Initializing the search dictionary**

Create instance of the engine:

```cpp
shookayEngine* searchEngine = CreateSearchEngine();
```

Depending on the encoding type of your map, you will need to provide a value from the following enum

```cpp
enum EncodingType {
    UTF8,
    UTF16,
    UTF32
};
```

if you work with UTF-8:

```cpp
std::map<int, std::u8string> entries;
entries[0] = u8"Expenthisditure never  been these Expenthisditure go been Expenthisditure" ;
entries[1] = u8"asd every possession aaaaa" ;
entries[2] = u8"this young permeveryissionevery" ;
entries[3] = u8"understanding performance this young permeasdveryissionevery" ;
entries[4] = u8"asd every" ;
entries[5] = u8"had each another every industrial line change" ;
entries[6] = u8"keep specialization had America are leave realization by enough population here countryside back" ;
entries[7] = u8"its so say as had away white innovation" ;
entries[8] = u8" ŁukaSz, Ekąb. ZZÓ. Żźoa      ,,,/fTQs ..Ł \\aa,,,,grgtrUIOUK...." ;
PrepareEntries(searchEngine, &entries, UTF8);
```

for UTF-16 :

```cpp
std::map<int, std::u16string> entries;
entries[0] = { u"Expenthisditure never  been these Expenthisditure go been Expenthisditure" };
entries[1] = { u"asd every possession aaaaa" };
entries[2] = { u"this young permeveryissionevery" };
entries[3] = { u"understanding performance this young permeasdveryissionevery" };
entries[4] = { u"asd every" };
entries[5] = { u"had each another every industrial line change" };
entries[6] = { u"keep specialization had America are leave realization by enough population here countryside back" };
entries[7] = { u"its so say as had away white innovation" };
entries[8] = { u" ŁukaSz, Ekąb. ZZÓ. Żźoa      ,,,/fTQs ..Ł \\aa,,,,grgtrUIOUK...." };
PrepareEntries(searchEngine, &entries, UTF16);
```

for UTF-32:

```cpp
std::map<int, std::u32string> entries;
entries[0] = { U"Expenthisditure never  been these Expenthisditure go been Expenthisditure" };
entries[1] = { U"asd every possession aaaaa" };
entries[2] = { U"this young permeveryissionevery" };
entries[3] = { U"understanding performance this young permeasdveryissionevery" };
entries[4] = { U"asd every" };
entries[5] = { U"had each another every industrial line change" };
entries[6] = { U"keep specialization had America are leave realization by enough population here countryside back" };
entries[7] = { U"its so say as had away white innovation" };
entries[8] = { U" ŁukaSz, Ekąb. ZZÓ. Żźoa      ,,,/fTQs ..Ł \\aa,,,,grgtrUIOUK...." };
PrepareEntries(searchEngine, &entries, UTF32);
```

now entries are delivered to the engine. 

### Performing search

You will be using the following 

```cpp
enum WordMatchMethod
{
    Exact,
    Within
};
```

##for words that can be substrings 

for UTF-8:

```cpp
std::u8string searchTerm = u8"issio";
int resultLength;
int* results = FindUTF8(searchEngine, searchTerm.c_str(), &resultLength, Within);
```

for UTF-16:

```cpp
std::u16string searchTerm = u"issio";
int resultLength;
int* results = FindUTF16(searchEngine, searchTerm.c_str(), &resultLength, Within);
```

for UTF-32:

```cpp
std::u32string searchTerm = U"issio asd";
int resultLength;
int* results = FindUTF32(searchEngine, searchTerm.c_str(), &resultLength, Within);
```

now `resultLength` returns the number of hits and `x` returns the pointer to the map entries where keys are found to be matching the `searchTerm`.

so now you can iterate through results (for simplifaction I am using `std::map<int, std::string>` as entries)

```cpp
 for (int i = 0; i < resultLength; ++i) {
   
     std::cout << "Key: " << x[i] << ", Value: "<<entries[x[i]]<< std::endl;
 }
```

Results :
```Key: 1, Value: asd every possession aaaaa
Key: 2, Value: this young permeveryissionevery
Key: 3, Value: understanding performance this young permeasdveryissionevery
Key: 4, Value: asd every
Key: 5, Value: had each another every industrial line change
```

## for words that have to be exact matches:

for UTF-8:

```cpp
std::string searchTerm = "issio";
int resultLength;
int* results = FindUTF8(searchEngine, searchTerm.c_str(), &resultLength, Exact);
```

for UTF-16:

```cpp
std::u16string searchTerm = u"issio";
int resultLength;
int* results = FindUTF16(searchEngine, searchTerm.c_str(), &resultLength, Exact);
```

for UTF-32:

```cpp
std::u32string searchTerm = U"issio asd";
int resultLength;
int* results = FindUTF32(searchEngine, searchTerm.c_str(), &resultLength, Exact);
```

to get following results

```
Key: 1, Value: asd every possession aaaaa
Key: 4, Value: asd every
Key: 5, Value: had each another every industrial line change
```



#You can add entries for your dictionary:


for UTF-8:

```cpp
std::u8string noweentry = u8"never every these expenthisditure go been";
AddEntryUTF8(searchEngine,9, noweentry.c_str());
```

for UTF-16:

```cpp
std::u16string noweentry1 = u"never every these expenthisditure go been";
AddEntryUTF16(searchEngine, 10, noweentry1.c_str());
```

for UTF-32:

```cpp
std::u32string noweentry2 = U"never every these expenthisditure go been";
AddEntryUTF32(searchEngine, 11, noweentry2.c_str());
```



**Note**: Once you submit entries, data is converted to UTF-32, therefore search term and entries may use different encodings.






## For applications with Graphical User Interface:


shookay can indicate the progress of its processing.

first, you will need to create your own callback function that matches the following delegate :

```cpp
typedef void (*ProgressCallback)(float progress);
```

for instance 

```cpp
void PrintProgress(float progress) {
    std::cout << "Progress: " << progress << "%" << std::endl;
}
```

then deliver your dictionary 

for UTF-8

```cpp
PrepareEntriesWithCallback(searchEngine, &entries, UTF8, PrintProgress);
```

for UTF-16

```cpp
 DeliverEntriesWithCallback(searchEngine, &entries, UTF16, PrintProgress);
```

for UTF-32

```cpp
 DeliverEntriesWithCallback(searchEngine, &entries, UTF32, PrintProgress);
```

Result:

```
Progress: 0%
Progress: 11%
Progress: 22%
Progress: 33%
Progress: 44%
Progress: 55%
Progress: 66%
Progress: 77%
Progress: 88%
```


## **License**

This project is licensed under the MIT License - see the LICENSE file for details.

### MIT License Summary

The MIT License is a permissive license that is short and to the point. It lets people do anything they want with your code as long as they provide attribution back to you and don’t hold you liable.

- Permissions
- Commercial use
- Modification
- Distribution
- Private use
- Conditions
- Include the original license and copyright notice with the code
- Limitations
- No Liability
- No Warranty

## What's new:

### [0.5.1] - 2024-01-07
#### fixed:
- Fixed bug: preserving RDX for the duration of the function due to the MSVC calling convention.
### [0.5.2] - 2024-01-08
#### improved:
- removing text repetitions from the source 
- refactored `GetWordsFromString`methods
### [0.5.3] - 2024-01-09
#### added:
- ``` DeliverEntriesWithCallback``` methods that can report progress to your GUI
### [0.5.4] - 2024-01-10
#### added:
- ``` FindExactWithCallback``` and ``` FindWithinWithCallback``` search functions that report search results on the go to your to your GUI
### [0.6.0] - 2024-01-18
- Major changes to the API and search method
### [0.6.1] - 2024-01-19
- Minor big fixes
### [0.6.2] - 2024-01-23
- Added AddEntry method