#pragma once

#ifdef shookayEngine_EXPORTS
#define shookayEngine_API __declspec(dllexport)
#else
#define shookayEngine_API __declspec(dllimport)
#endif

#include "common.h"
#include "shookayEngine.h"

extern "C" {
    shookayEngine_API shookayEngine* CreateSearchEngine();
    shookayEngine_API bool RemoveEntry(shookayEngine* searchEngine, int id);
    shookayEngine_API bool RefreshEntryUTF8(shookayEngine* searchEngine, int id, const char8_t* wyrazenie);
    shookayEngine_API bool RefreshEntryUTF16(shookayEngine* searchEngine, int id, const char16_t* wyrazenie);
    shookayEngine_API bool RefreshEntryUTF32(shookayEngine* searchEngine, int id, const char32_t* wyrazenie);
    shookayEngine_API int* FindUTF8(shookayEngine* searchEngine, const char8_t* wyrazenie, int* length, WordMatchMethod method);
    shookayEngine_API int* FindUTF16(shookayEngine* searchEngine, const char16_t* wyrazenie, int* length, WordMatchMethod method);
    shookayEngine_API int* FindUTF32(shookayEngine* searchEngine, const char32_t* wyrazenie, int* length, WordMatchMethod method);
    shookayEngine_API void AddEntryUTF8(shookayEngine* searchEngine, int id, const char8_t* wyrazenie);
    shookayEngine_API void AddEntryUTF16(shookayEngine* searchEngine, int id, const char16_t* wyrazenie);
    shookayEngine_API void AddEntryUTF32(shookayEngine* searchEngine, int id, const char32_t* wyrazenie);
    shookayEngine_API void PrepareEntries(shookayEngine* searchEngine, void* data, EncodingType encodingType);
    shookayEngine_API void DeliverEntries(shookayEngine* searchEngine, const char* data, EncodingType encodingType);
    shookayEngine_API void PrepareEntriesWithCallback(shookayEngine* searchEngine, void* data, EncodingType encodingType, ProgressCallback progressCallback);
    shookayEngine_API void DeliverEntriesWithCallback(shookayEngine* searchEngine, const char* data, EncodingType encodingType, ProgressCallback progressCallback);
};
