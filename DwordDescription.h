#pragma once
#include <cstdint>

struct DwordDescription {
    uint8_t isBeginningOfTheWord; // 0 for _not_ beginning of the word
    uint8_t charIndex; // Position in the word
    uint8_t wordLength; // Length of the word
    uint8_t charIndexFromTheEnd; // Distance from the end of the word

    DwordDescription(uint32_t value) {
        // Constructor accepting a uint32_t value
    }
    DwordDescription() : isBeginningOfTheWord(0), charIndex(0), wordLength(0), charIndexFromTheEnd(0) {
        // Default constructor
    }
};
