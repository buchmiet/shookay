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
    shookayEngine_API void DeliverEntriesUTF8(shookayEngine* searchEngine, const char* data, int length);
    shookayEngine_API void DeliverEntriesUTF8WithCallback(shookayEngine* searchEngine, const char* data, int length, ProgressCallback progressCallback);
    shookayEngine_API void DeliverEntriesUTF16(shookayEngine* searchEngine, const char* data, int length);
    shookayEngine_API void DeliverEntriesUTF16WithCallback(shookayEngine* searchEngine, const char* data, int length, ProgressCallback progressCallback);
    shookayEngine_API void DeliverEntriesUTF32(shookayEngine* searchEngine, const char* data, int length);
    shookayEngine_API void DeliverEntriesUTF32WithCallback(shookayEngine* searchEngine, const char* data, int length,  ProgressCallback progressCallback);
    shookayEngine_API int* FindWithinUTF8(shookayEngine* searchEngine, const char* wyrazenie, int* length);
    shookayEngine_API int* FindWithinUTF16(shookayEngine* searchEngine, const char16_t* wyrazenie, int* length);
    shookayEngine_API int* FindWithinUTF32(shookayEngine* searchEngine, const char32_t* wyrazenie, int* length);
    shookayEngine_API int* FindExactUTF8(shookayEngine* searchEngine, const char* wyrazenie, int* length);
    shookayEngine_API int* FindExactUTF16(shookayEngine* searchEngine, const char16_t* wyrazenie, int* length);
    shookayEngine_API int* FindExactUTF32(shookayEngine* searchEngine, const char32_t* wyrazenie, int* length);
    shookayEngine_API void DeliverEntries(shookayEngine* searchEngine, void* data, EncodingType encodingType);
    shookayEngine_API void DeliverEntriesWithCallback(shookayEngine* searchEngine, void* data, EncodingType encodingType,  ProgressCallback progressCallback);

};
