#pragma once

#ifdef shookayEngine_EXPORTS
#define shookayEngine_API __declspec(dllexport)
#else
#define shookayEngine_API __declspec(dllimport)
#endif
#include "shookayEngine.h"

enum EncodingType {
    UTF8Map,
    UTF16Map,
    UTF32Map
};

extern "C" {
    shookayEngine_API shookayEngine* CreateSearchEngine();
    shookayEngine_API void DeliverEntriesUTF8(shookayEngine* searchEngine, const char* data, int length);
    shookayEngine_API void DeliverEntriesUTF16(shookayEngine* searchEngine, const char* data, int length);
    shookayEngine_API void DeliverEntriesUTF32(shookayEngine* searchEngine, const char* data, int length);
    shookayEngine_API int* FindWithinUTF8(shookayEngine* searchEngine, const char* wyrazenie, int* length);
    shookayEngine_API int* FindWithinUTF16(shookayEngine* searchEngine, const char16_t* wyrazenie, int* length);
    shookayEngine_API int* FindWithinUTF32(shookayEngine* searchEngine, const char32_t* wyrazenie, int* length);
    shookayEngine_API int* FindExactUTF8(shookayEngine* searchEngine, const char* wyrazenie, int* length);
    shookayEngine_API int* FindExactUTF16(shookayEngine* searchEngine, const char16_t* wyrazenie, int* length);
    shookayEngine_API int* FindExactUTF32(shookayEngine* searchEngine, const char32_t* wyrazenie, int* length);
    shookayEngine_API void DeliverEntries(shookayEngine* searchEngine, void* data, EncodingType encodingType);

};
