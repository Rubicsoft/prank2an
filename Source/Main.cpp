/*

    Bapak Mulyono Raja Tipu-tipu
    Code by Reymo Je

    Library used : Raylib
    Compile using w64devkit (win64_mingw_w64)

    btw press F8 key to exit, 🗿

    Pesan dari kreator : "Maaf tuan, telah mengganggu birokrasi anda 🗿"

*/

/* App Settings */
#define INIT_SCREEN_WIDTH           1280
#define INIT_SCREEN_HEIGHT          720
#define INIT_SCREEN_INCH            1468.6047800549f
#define WINDOW_TITLE                "Bapak Mulyono si Raja Tipu-tipu"
#define DEFAULT_TITLE_FONT          30
#define DEFAULT_PARAGRAPH_FONT      25
#define DEFAULT_LINE_SPACING        40

/* User Settings */
#define VSYNC_ON
#define NO_CURSOR
// #define DRAW_FPS
#define WINDOW_FULLSCREEN


/* WARNING : Line below is the app instruction. Please don't change unless for experiments */


// #include <cstdio>
#include <vector>
#include <string>
#include <cmath>
#include <raylib.h>

#include "PackedText.hpp"

// Pre-compiled data
#include "Lyrics.hpp"
#include "Music.h"
#include "UnispaceFont.h"
#include "Images/ImgMeme1.h"
#include "Images/ImgMeme2.h"
#include "Images/ImgMeme3.h"

// Global variables
int 
    screenWidth = INIT_SCREEN_WIDTH, 
    screenHeight = INIT_SCREEN_HEIGHT;
float 
    screenInch = INIT_SCREEN_INCH, 
    normalizedInch = 1.0f;
int 
    titleFont = DEFAULT_TITLE_FONT, 
    paragraphFont = DEFAULT_PARAGRAPH_FONT, 
    lineSpacing = DEFAULT_LINE_SPACING;
const char* appTitle = "Indonesia gelap, yang gelap kau (N1GG4), bukan Indonesia";


// Render the image texture based on the alignment to the screen
inline void renderImage(Texture2D tex, Vector2 alignment, float scale = 1.0, float rotation = 0.0) {
    DrawTextureEx(
        tex, (Vector2){
            (screenWidth - tex.width * scale * normalizedInch) * alignment.x, 
            (screenHeight - tex.height * scale * normalizedInch) * alignment.y, 
        }, 
        rotation, scale * normalizedInch, 
        WHITE
    );
}

// Shrink up-and-down animation (used for scaling)
inline float shrinkAnim(float scale, float frequency) {
    return scale * (0.5f * (std::sin(GetTime() * frequency) + 1.0f));
}


int main() {
    // Initialize raylib window and sound
    InitWindow(INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT, WINDOW_TITLE);
    SetWindowState(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN);
    #ifdef WINDOW_FULLSCREEN
        SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE | FLAG_WINDOW_UNDECORATED);
    #else
        #undef NO_CURSOR
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    #endif
    #ifdef VSYNC_ON
        SetWindowState(FLAG_VSYNC_HINT);
    #endif
    #ifdef NO_CURSOR
        DisableCursor();
    #endif
    SetExitKey(KEY_F8);
    InitAudioDevice();

    // RESOURCE LOADING
    // Load the meme images
    Image meme1_img = LoadImageFromMemory(".jpg", meme1_jpg, meme1_jpg_len);
    Image meme2_img = LoadImageFromMemory(".jpg", meme2_jpg, meme2_jpg_len);
    Image meme3_img = LoadImageFromMemory(".jpg", meme3_jpg, meme3_jpg_len);
    Texture2D meme1_tex = LoadTextureFromImage(meme1_img);
    Texture2D meme2_tex = LoadTextureFromImage(meme2_img);
    Texture2D meme3_tex = LoadTextureFromImage(meme3_img);
    UnloadImage(meme1_img);
    UnloadImage(meme2_img);
    UnloadImage(meme3_img);
    // Load the Unispace BD font
    Font unispaceFont = LoadFontFromMemory(".ttf", unispace_bd_ttf, unispace_bd_ttf_len, DEFAULT_PARAGRAPH_FONT, nullptr, 0);
    // Initialize music and play it
    Music music = LoadMusicStreamFromMemory(".ogg", bapak_mulyono_ogg, bapak_mulyono_ogg_len);
    music.looping = false;
    if (IsMusicValid(music))
        PlayMusicStream(music);
    

    // Window loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Get the screen/window information
        screenWidth = GetRenderWidth();
        screenHeight = GetRenderHeight();
        screenInch = std::sqrt((screenWidth * screenWidth) + (screenHeight * screenHeight));
        normalizedInch = screenInch / INIT_SCREEN_INCH;

        // Normalized the variables based on the window inch (for dynamic resolution)
        titleFont = DEFAULT_TITLE_FONT * normalizedInch;
        paragraphFont = DEFAULT_PARAGRAPH_FONT * normalizedInch;
        lineSpacing = DEFAULT_LINE_SPACING * normalizedInch;

        UpdateMusicStream(music);

        // Draw meme images
        renderImage(meme1_tex, (Vector2){0.0833333333f,  0.9f}, shrinkAnim(0.2f, 2.0f));
        renderImage(meme2_tex, (Vector2){0.9f, 0.1f}, shrinkAnim(0.5f, 4.0f), GetTime() * 100.0f);
        renderImage(meme3_tex, (Vector2){0.0833333333f, 0.1f}, 1.0f, GetTime() * 200.0f);
        
        // Draw title
        DrawTextEx(unispaceFont, appTitle, (Vector2){PackedText::getAligned(appTitle, screenWidth, titleFont, 0.5f), screenHeight * 0.1f}, titleFont, 1.0f, RED);
        
        // Draw lyrics
        PackedText::printPackedText(
            unispaceFont, Lyrics::lyrics1, 
            PackedText::getAligned(Lyrics::lyrics1[1], screenWidth, paragraphFont, 0.1666666667f), 
            (screenHeight - (lineSpacing * 8)) * 0.5f, 
            WHITE, 
            paragraphFont, lineSpacing
        );
        PackedText::printPackedText(
            unispaceFont, Lyrics::lyrics2, 
            PackedText::getAligned(Lyrics::lyrics2[1], screenWidth, paragraphFont, 0.8333333333f), 
            (screenHeight - (lineSpacing * 8)) * 0.5f, 
            WHITE, 
            paragraphFont, lineSpacing
        );

        #ifdef DRAW_FPS
            DrawFPS(50, 80);
        #endif

        EndDrawing();

        if (!IsMusicStreamPlaying(music))
            break;
    }

    // Free the resources from the memory
    UnloadTexture(meme1_tex);
    UnloadTexture(meme2_tex);
    UnloadTexture(meme3_tex);
    UnloadMusicStream(music);
    UnloadFont(unispaceFont);

    // Close the raylib window and sound
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
