#include <vector>
#include <raylib.h>

#include "PackedText.hpp"


float textYPos;

void PackedText::printPackedText(Font font, std::vector<const char*> packedText, const float xPos, const float yPos, Color textColor, const int fontSize, const int yIncrement) {
    // Individual y-position of each text
    // Each text increments by 80 (default)
    textYPos = yPos;
    
    for (const char *text : packedText) {
        // DrawText(text, xPos, textYPos, fontSize, textColor);
        DrawTextEx(font, text, (Vector2){xPos, textYPos}, fontSize, 1.0f, textColor);
        
        textYPos += yIncrement;
    }
}
