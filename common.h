#pragma once

typedef void (*ProgressCallback)(int progress);

typedef void(__stdcall* YourCallback)(int, int);

enum EncodingType {
    UTF8,
    UTF16,
    UTF32
};
