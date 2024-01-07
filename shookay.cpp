#include "pch.h"
#include "shookayEngine.h"
#include "shookay.h"
#include "StringConverter.h"

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

    void DeliverEntriesUTF16(shookayEngine* searchEngine, const char* data, int length) {
        auto mapEntries = shookayEngine::ReadEntries<std::u16string>(data, length, StringConverter::ConvertUTF16);
        searchEngine->DeliverEntriesUTF16(mapEntries);
    }

    void DeliverEntriesUTF32(shookayEngine* searchEngine, const char* data, int length) {
        auto mapEntries = shookayEngine::ReadEntries<std::u32string>(data, length, StringConverter::ConvertUTF32);
        searchEngine->DeliverEntriesUTF32(mapEntries);
    }




    void DeliverEntries(shookayEngine* searchEngine, void* data, EncodingType encodingType) {
        switch (encodingType) {
        case UTF8Map: {

            auto dataUTF8 = static_cast<std::map<int, std::string>*>(data);
            searchEngine->DeliverEntriesUTF8(*dataUTF8);
            break; }
        case UTF16Map: {
            auto dataUTF16 = static_cast<std::map<int, std::u16string>*>(data);
            searchEngine->DeliverEntriesUTF16(*dataUTF16);
            break; }
        case UTF32Map: {
            auto dataUTF32 = static_cast<std::map<int, std::u32string>*>(data);
            searchEngine->DeliverEntriesUTF32(*dataUTF32);
            break; }
        default: {
            // Error
            break; }
        }
    }





}