#pragma once

typedef void (*ProgressCallback)(float progress);

enum EncodingType {
    UTF8,
    UTF16,
    UTF32
};

enum WordMatchMethod
{
    Exact,
    Within
};

