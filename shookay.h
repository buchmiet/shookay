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
    shookayEngine_API int* FindUTF8(shookayEngine* searchEngine, const std::u8string& wyrazenie, int* length, WordMatchMethod method);
    shookayEngine_API int* FindUTF16(shookayEngine* searchEngine, const std::u16string& wyrazenie, int* length, WordMatchMethod method);
    shookayEngine_API int* FindUTF32(shookayEngine* searchEngine, const std::u32string& wyrazenie, int* length, WordMatchMethod method);
    shookayEngine_API void PrepareEntries(shookayEngine* searchEngine, void* data, EncodingType encodingType);
    shookayEngine_API void DeliverEntries(shookayEngine* searchEngine, const char* data, EncodingType encodingType);
    shookayEngine_API void PrepareEntriesWithCallback(shookayEngine* searchEngine, void* data, EncodingType encodingType, ProgressCallback progressCallback);  
};
