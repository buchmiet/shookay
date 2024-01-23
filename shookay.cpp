#include "pch.h"
#include "shookayEngine.h"
#include "shookay.h"
#include "stringConverter.h"
#include <iostream>


extern "C" {
    shookayEngine* CreateSearchEngine() {

        return new shookayEngine();
    }

    int* FindUTF8(shookayEngine* searchEngine, const char8_t* wyrazenie, int* length, WordMatchMethod method) {
        if (searchEngine == nullptr) {
            return nullptr;
        }
        std::vector<int> results = searchEngine->FindUTF8(wyrazenie, method);
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);
        return resultsArray;
    }

  
    

 
    int* FindUTF16(shookayEngine* searchEngine, const char16_t* wyrazenie, int* length, WordMatchMethod method) {
        if (searchEngine == nullptr) {
            return nullptr;
        }
        std::vector<int> results = searchEngine->FindUTF16(wyrazenie,  method);
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);
        return resultsArray;
    }


    int* FindUTF32(shookayEngine* searchEngine, const char32_t* wyrazenie, int* length, WordMatchMethod method) {
        if (searchEngine == nullptr) {
            return nullptr;
        }
        std::vector<int> results = searchEngine->FindUTF32(wyrazenie,  method);
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);
        return resultsArray;
    }


    void DeliverEntries(shookayEngine* searchEngine, const char* data, EncodingType encodingType) {
        switch (encodingType) {
        case UTF8: {
            auto mapEntries = StringConverter::ReadEntries<std::u8string>(data, StringConverter::ConvertUTF8);
            searchEngine->PrepareEntriesUTF8(mapEntries);
            break; }
        case UTF16: {
            auto mapEntries = StringConverter::ReadEntries<std::u16string>(data,  StringConverter::ConvertUTF16);
            searchEngine->PrepareEntriesUTF16(mapEntries);
            break; }
        case UTF32: {
            auto mapEntries = StringConverter::ReadEntries<std::u32string>(data, StringConverter::ConvertUTF32);
            searchEngine->PrepareEntriesUTF32(mapEntries);
            break; }
        default: {
            // Error
            break; }
        }
    }

    void PrepareEntries(shookayEngine* searchEngine, void* data,  EncodingType encodingType) {
        switch (encodingType) {
        case UTF8: {
            auto dataUTF8 = static_cast<std::map<int, std::u8string>*>(data);
            searchEngine->PrepareEntriesUTF8(*dataUTF8);     
            break; }
        case UTF16: {
            auto dataUTF16 = static_cast<std::map<int, std::u16string>*>(data);
            searchEngine->PrepareEntriesUTF16(*dataUTF16);
            break; }
        case UTF32: {
            auto dataUTF32 = static_cast<std::map<int, std::u32string>*>(data);
            searchEngine->PrepareEntriesUTF32(*dataUTF32);
            break; }
        default: {
            // Error
            break; }
        }
    }
    
    void DeliverEntriesWithCallback(shookayEngine* searchEngine, const char* data, EncodingType encodingType, ProgressCallback progressCallback) {
        switch (encodingType) {
        case UTF8: {
            auto mapEntries = StringConverter::ReadEntries<std::u8string>(data, StringConverter::ConvertUTF8);
            searchEngine->PrepareEntriesUTF8WithCallback(mapEntries, progressCallback);
            break; }
        case UTF16: {
            auto mapEntries = StringConverter::ReadEntries<std::u16string>(data, StringConverter::ConvertUTF16);
            searchEngine->PrepareEntriesUTF16WithCallback(mapEntries, progressCallback);
            break; }
        case UTF32: {
            auto mapEntries = StringConverter::ReadEntries<std::u32string>(data, StringConverter::ConvertUTF32);
            searchEngine->PrepareEntriesUTF32WithCallback(mapEntries, progressCallback);
            break; }
        default: {
            // Error
            break; }
        }
    }


    void PrepareEntriesWithCallback(shookayEngine* searchEngine, void* data, EncodingType encodingType, ProgressCallback progressCallback) {
        switch (encodingType) {
        case UTF8: {

            auto dataUTF8 = static_cast<std::map<int, std::u8string>*>(data);
            searchEngine->PrepareEntriesUTF8WithCallback(*dataUTF8, progressCallback);
            break; }
        case UTF16: {
            auto dataUTF16 = static_cast<std::map<int, std::u16string>*>(data);
            searchEngine->PrepareEntriesUTF16WithCallback(*dataUTF16, progressCallback);
            break; }
        case UTF32: {
            auto dataUTF32 = static_cast<std::map<int, std::u32string>*>(data);
            searchEngine->PrepareEntriesUTF32WithCallback(*dataUTF32, progressCallback);
            break; }
        default: {
            // Error
            break; }
        }
    }

    void AddEntryUTF8(shookayEngine* searchEngine, int id, const char8_t* wyrazenie) {
        searchEngine->AddEntryUTF8(id, wyrazenie);
    }

    void AddEntryUTF16(shookayEngine* searchEngine, int id, const char16_t* wyrazenie) {
        searchEngine->AddEntryUTF16(id, wyrazenie);
    }
    void AddEntryUTF32(shookayEngine* searchEngine, int id, const char32_t* wyrazenie) {
        searchEngine->AddEntryUTF32(id, wyrazenie);
    }

}