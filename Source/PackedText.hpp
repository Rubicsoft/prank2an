#ifndef _PACKED_TEXT_HPP
#define _PACKED_TEXT_HPP

#include <vector>
#include <raylib.h>

namespace PackedText {
    // Prints the chunks of vectorized characters
    // Defaults: Font Size: 30, Y Increment: 80
    void printPackedText(Font font, std::vector<const char*> packedText, const float xPos, const float yPos, Color textColor, const int fontSize = 30, const int yIncrement = 80);
    
    // Align the text element
    inline float getAligned(const char* text, int screenWidth, int fontSize, float align) {
        return (screenWidth - MeasureText(text, fontSize)) * align;
    }
}

#endif