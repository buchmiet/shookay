#include "pch.h"
#include "shookayEngine.h"
#include "shookay.h"
#include "StringConverter.h"
#include <iostream>
#include <iomanip>


extern "C" {
    shookayEngine* CreateSearchEngine() {

        return new shookayEngine();
    }

    int* FindWithinUTF8(shookayEngine* searchEngine,const char* wyrazenie, int* length) {
        if (searchEngine == nullptr) {
            return nullptr;
        }
        std::vector<int> results = searchEngine->FindWithinUTF8(wyrazenie);
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);
        return resultsArray;
    }


    void FindWithinUTF8WithCallBack(shookayEngine* searchEngine, const char* wyrazenie, ProgressCallback progressCallback) {

        if (searchEngine == nullptr) {
            return;
        }
        searchEngine->FindWithinUTF8WithCallback(wyrazenie, progressCallback);
    }

    int* FindWithinUTF16(shookayEngine* searchEngine, const char16_t* wyrazenie, int* length) {

        if (searchEngine == nullptr) {
            return nullptr;
        }     
        std::vector<int> results = searchEngine->FindWithinUTF16(wyrazenie);      
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);

        return resultsArray;
    }

    void FindWithinUTF16WithCallBack(shookayEngine* searchEngine, const char16_t* wyrazenie,  ProgressCallback progressCallback) {

        if (searchEngine == nullptr) {
            return;
        }
        searchEngine->FindWithinUTF16WithCallback(wyrazenie,progressCallback);
    }
 

    int* FindWithinUTF32(shookayEngine* searchEngine, const char32_t* wyrazenie, int* length) {
        if (searchEngine == nullptr) {
            return nullptr;
        }
        std::vector<int> results = searchEngine->FindWithinUTF32(wyrazenie);
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);
        return resultsArray;
    }

    void FindWithinUTF32WithCallBack(shookayEngine* searchEngine, const char32_t* wyrazenie, ProgressCallback progressCallback)
    {
        if (searchEngine == nullptr) {
            return;
        }
        searchEngine->FindWithinUTF32WithCallback(wyrazenie, progressCallback);
    }

    int* FindExactUTF8(shookayEngine* searchEngine, const char* wyrazenie, int* length) {
        if (searchEngine == nullptr) {
            return nullptr;
        }
        std::vector<int> results = searchEngine->FindExactUTF8(wyrazenie);
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);
        return resultsArray;
    }

    int* FindExactUTF16(shookayEngine* searchEngine, const char16_t* wyrazenie, int* length) {
        if (searchEngine == nullptr) {
            return nullptr;
        }
        std::vector<int> results = searchEngine->FindExactUTF16(wyrazenie);
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);
        return resultsArray;
    }

    int* FindExactUTF16WithCallback(shookayEngine* searchEngine, const char16_t* wyrazenie, int* length, ProgressCallback progressCallback) {
        if (searchEngine == nullptr) {
            return nullptr;
        }
        std::vector<int> results = searchEngine->FindExactUTF16(wyrazenie);
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);

        return resultsArray;
    }

    int* FindExactUTF32(shookayEngine* searchEngine, const char32_t* wyrazenie, int* length) {
        if (searchEngine == nullptr) {
            return nullptr;
        }
        std::vector<int> results = searchEngine->FindExactUTF32(wyrazenie);
        *length = results.size();
        auto* resultsArray = new int[*length];
        std::ranges::copy(results.begin(), results.end(), resultsArray);

        return resultsArray;
    }    
   
    void DeliverEntriesUTF8(shookayEngine* searchEngine, const char* data, int length) {
        auto mapEntries = shookayEngine::ReadEntries<std::string>(data, length, StringConverter::ConvertUTF8);
        searchEngine->DeliverEntriesUTF8(mapEntries);
    }
    void DeliverEntriesUTF8WithCallback(shookayEngine* searchEngine, const char* data, int length, ProgressCallback progressCallback) {
        auto mapEntries = shookayEngine::ReadEntries<std::string>(data, length, StringConverter::ConvertUTF8);
        searchEngine->DeliverEntriesUTF8WithCallback(mapEntries, progressCallback);
    }

    void DeliverEntriesUTF16(shookayEngine* searchEngine, const char* data, int length) {
        auto mapEntries = shookayEngine::ReadEntries<std::u16string>(data, length, StringConverter::ConvertUTF16);
        searchEngine->DeliverEntriesUTF16(mapEntries);
    }

    void DeliverEntriesUTF16WithCallback(shookayEngine* searchEngine, const char* data, int length, ProgressCallback progressCallback) {
     
        auto mapEntries = shookayEngine::ReadEntries<std::u16string>(data, length, StringConverter::ConvertUTF16);
        searchEngine->DeliverEntriesUTF16WithCallback(mapEntries,progressCallback);
    }

    void DeliverEntriesUTF32(shookayEngine* searchEngine, const char* data, int length) {
        auto mapEntries = shookayEngine::ReadEntries<std::u32string>(data, length, StringConverter::ConvertUTF32);
        searchEngine->DeliverEntriesUTF32(mapEntries);
    }

    void DeliverEntriesUTF32WithCallback(shookayEngine* searchEngine, const char* data, int length, ProgressCallback progressCallback) {
        auto mapEntries = shookayEngine::ReadEntries<std::u32string>(data, length, StringConverter::ConvertUTF32);
        searchEngine->DeliverEntriesUTF32WithCallback(mapEntries, progressCallback);
    }


    void DeliverEntries(shookayEngine* searchEngine, void* data, EncodingType encodingType) {
        switch (encodingType) {
        case UTF8: {
            auto dataUTF8 = static_cast<std::map<int, std::string>*>(data);
            searchEngine->DeliverEntriesUTF8(*dataUTF8);
            break; }
        case UTF16: {
            auto dataUTF16 = static_cast<std::map<int, std::u16string>*>(data);
            searchEngine->DeliverEntriesUTF16(*dataUTF16);
            break; }
        case UTF32: {
            auto dataUTF32 = static_cast<std::map<int, std::u32string>*>(data);
            searchEngine->DeliverEntriesUTF32(*dataUTF32);
            break; }
        default: {
            // Error
            break; }
        }
    }
    
    void DeliverEntriesWithCallback(shookayEngine* searchEngine, void* data, EncodingType encodingType, ProgressCallback progressCallback) {
        switch (encodingType) {
        case UTF8: {

            auto dataUTF8 = static_cast<std::map<int, std::string>*>(data);
            searchEngine->DeliverEntriesUTF8WithCallback(*dataUTF8, progressCallback);
            break; }
        case UTF16: {
            auto dataUTF16 = static_cast<std::map<int, std::u16string>*>(data);
            searchEngine->DeliverEntriesUTF16WithCallback(*dataUTF16, progressCallback);
            break; }
        case UTF32: {
            auto dataUTF32 = static_cast<std::map<int, std::u32string>*>(data);
            searchEngine->DeliverEntriesUTF32WithCallback(*dataUTF32, progressCallback);
            break; }
        default: {
            // Error
            break; }
        }
    }


    void FindWithinWithCallback(shookayEngine* searchEngine, void* data, EncodingType encodingType, ProgressCallback progressCallback) {
        switch (encodingType) {
        case UTF8: {
            auto wyrazenie = static_cast<std::string*>(data);
            searchEngine->FindWithinUTF8WithCallback(wyrazenie->c_str(), progressCallback);
            break; }
        case UTF16: {
            auto wyrazenie = static_cast<std::u16string*>(data);
            searchEngine->FindWithinUTF16WithCallback(wyrazenie->c_str(), progressCallback);
            break; }
        case UTF32: {
            auto wyrazenie = static_cast<std::u32string*>(data);
            searchEngine->FindWithinUTF32WithCallback(wyrazenie->c_str(), progressCallback);
            break; }
        default: {
            // Error
            break; }
        }
    }

    void FindExactWithCallback(shookayEngine* searchEngine, void* data, EncodingType encodingType, ProgressCallback progressCallback) {
        switch (encodingType) {
        case UTF8: {
            auto wyrazenie = static_cast<std::string*>(data);
            searchEngine->FindExactUTF8WithCallback(wyrazenie->c_str(), progressCallback);
            break; }
        case UTF16: {
            auto wyrazenie = static_cast<std::u16string*>(data);
            searchEngine->FindExactUTF16WithCallback(wyrazenie->c_str(), progressCallback);
            break; }
        case UTF32: {
            auto wyrazenie = static_cast<std::u32string*>(data);
            searchEngine->FindExactUTF32WithCallback(wyrazenie->c_str(), progressCallback);
            break; }
        default: {
            // Error
            break; }
        }
    }


    int* FindWithin(shookayEngine* searchEngine, void* data, int* length, EncodingType encodingType){
        switch (encodingType) {
        case UTF8: {
            auto wyrazenie = static_cast<std::string*>(data);
            std::vector<int> results = searchEngine->FindWithinUTF8(wyrazenie->c_str());
            *length = results.size();
            auto* resultsArray = new int[*length];
            std::ranges::copy(results.begin(), results.end(), resultsArray);
            return resultsArray;
            }
        case UTF16: {
            auto wyrazenie = static_cast<std::u16string*>(data);
            std::vector<int> results = searchEngine->FindWithinUTF16(wyrazenie->c_str());
            *length = results.size();
            auto* resultsArray = new int[*length];
            std::ranges::copy(results.begin(), results.end(), resultsArray);
            return resultsArray; }
        case UTF32: {
            auto wyrazenie = static_cast<std::u32string*>(data);
            std::vector<int> results = searchEngine->FindWithinUTF32(wyrazenie->c_str());
            *length = results.size();
            auto* resultsArray = new int[*length];
            std::ranges::copy(results.begin(), results.end(), resultsArray);
            return resultsArray;; }
        default: {
            // Error
            break; }
        }
    }

  
    int* FindExact(shookayEngine* searchEngine, void* data, int* length, EncodingType encodingType) {
        switch (encodingType) {
        case UTF8: {
            auto wyrazenie = static_cast<std::string*>(data);
            std::vector<int> results = searchEngine->FindExactUTF8(wyrazenie->c_str());
            *length = results.size();
            auto* resultsArray = new int[*length];
            std::ranges::copy(results.begin(), results.end(), resultsArray);
            return resultsArray;
        }
        case UTF16: {
            auto wyrazenie = static_cast<std::u16string*>(data);
            std::vector<int> results = searchEngine->FindExactUTF16(wyrazenie->c_str());
            *length = results.size();
            auto* resultsArray = new int[*length];
            std::ranges::copy(results.begin(), results.end(), resultsArray);
            return resultsArray; }
        case UTF32: {
            auto wyrazenie = static_cast<std::u32string*>(data);
            std::vector<int> results = searchEngine->FindExactUTF32(wyrazenie->c_str());
            *length = results.size();
            auto* resultsArray = new int[*length];
            std::ranges::copy(results.begin(), results.end(), resultsArray);
            return resultsArray;; }
        default: {
            // Error
            break; }
        }
    }
   

}