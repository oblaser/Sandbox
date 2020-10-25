/*

author:     Oliver Blaser

date c:     15.10.2020
date e:     25.10.2020

*/

#ifndef _CLI_H_
#define _CLI_H_

#include <cstdint>
#include <string>

namespace cli
{
    // sgr parameters -  see https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_parameters
    const uint8_t SGR_RESET = 0;
    const uint8_t SGR_BOLD = 1;
    const uint8_t SGR_FAINT = 2;
    const uint8_t SGR_ITALIC = 3;
    const uint8_t SGR_UNDERLINE = 4;
    const uint8_t SGR_BLINK_SLOW = 5;
    const uint8_t SGR_BLINK_FAST = 6;
    const uint8_t SGR_REVERSE_VIDEO = 7;
    const uint8_t SGR_CONCEAL = 8;
    const uint8_t SGR_STRIKE_OUT = 9;
    const uint8_t SGR_FRAKTUR = 20;
    const uint8_t SGR_BOLD_FAINT_OFF = 22;
    const uint8_t SGR_ITALIC_FRAKTUR_OFF = 23;
    const uint8_t SGR_UNDERLINE_OFF = 24;
    const uint8_t SGR_BLINK_OFF = 25;
    const uint8_t SGR_PROPORTIONAL_SPACING = 26;
    const uint8_t SGR_REVERSE_VIDEO_OFF = 27;
    const uint8_t SGR_CONCEAL_OFF = 28;
    const uint8_t SGR_STRIKE_OUT_OFF = 29;
    const uint8_t SGR_FGCOLOR_SET_BASE = 30;
    const uint8_t SGR_FGCOLOR_SET = 38;
    const uint8_t SGR_FGCOLOR_DEFAULT = 39;
    const uint8_t SGR_BGCOLOR_SET_BASE = 40;
    const uint8_t SGR_BGCOLOR_SET = 48;
    const uint8_t SGR_BGCOLOR_DEFAULT = 49;
    const uint8_t SGR_PROPORTIONAL_SPACING_OFF = 50;
    const uint8_t SGR_FRAMED = 51;
    const uint8_t SGR_ENCIRCLED = 52;
    const uint8_t SGR_OVERLINED = 53;
    const uint8_t SGR_FRAME_ENCIRCLE_OFF = 54;
    const uint8_t SGR_OVERLINE_OFF = 55;
    const uint8_t SGR_ULCOLOR_SET = 58;
    const uint8_t SGR_ULCOLOR_DEFAULT = 59;
    const uint8_t SGR_FGCOLOR_BRIGHT_SET_BASE = 90;
    const uint8_t SGR_BGCOLOR_BRIGHT_SET_BASE = 100;

    // SGR colors
    const uint8_t SGRCOLOR_BLACK = 0;
    const uint8_t SGRCOLOR_RED = 1;
    const uint8_t SGRCOLOR_GREEN = 2;
    const uint8_t SGRCOLOR_YELLOW = 3;
    const uint8_t SGRCOLOR_BLUE = 4;
    const uint8_t SGRCOLOR_MAGENTA = 5;
    const uint8_t SGRCOLOR_CYAN = 6;
    const uint8_t SGRCOLOR_WHITE = 7;

    // fgColors
    const uint8_t FGC_BLACK = SGRCOLOR_BLACK;
    const uint8_t FGC_RED = SGRCOLOR_RED;
    const uint8_t FGC_GREEN = SGRCOLOR_GREEN;
    const uint8_t FGC_YELLOW = SGRCOLOR_YELLOW;
    const uint8_t FGC_BLUE = SGRCOLOR_BLUE;
    const uint8_t FGC_MAGENTA = SGRCOLOR_MAGENTA;
    const uint8_t FGC_CYAN = SGRCOLOR_CYAN;
    const uint8_t FGC_WHITE = SGRCOLOR_WHITE;
    const uint8_t FGC_BRIGHT_BLACK = SGRCOLOR_BLACK | 0x08;
    const uint8_t FGC_BRIGHT_RED = SGRCOLOR_RED | 0x08;
    const uint8_t FGC_BRIGHT_GREEN = SGRCOLOR_GREEN | 0x08;
    const uint8_t FGC_BRIGHT_YELLOW = SGRCOLOR_YELLOW | 0x08;
    const uint8_t FGC_BRIGHT_BLUE = SGRCOLOR_BLUE | 0x08;
    const uint8_t FGC_BRIGHT_MAGENTA = SGRCOLOR_MAGENTA | 0x08;
    const uint8_t FGC_BRIGHT_CYAN = SGRCOLOR_CYAN | 0x08;
    const uint8_t FGC_BRIGHT_WHITE = SGRCOLOR_WHITE | 0x08;

    // font style flagsflags
    const uint32_t FS_NORMAL = 0;
    const uint32_t FS_BOLD = 0x00000001;
    const uint32_t FS_UNDERLINE = 0x00000010;
    const uint32_t FS_REVERSED = 0x00000100;
    const uint32_t FS_BLINK = 0x00001000;

    void inline print(std::string& str);
    void print(const char* str);
    void print(std::string& str, uint8_t fgColor);
    void print(const char* str, uint8_t fgColor);
    void print(std::string& str, uint8_t fgColor, uint32_t fontStyle);
    void print(const char* str, uint8_t fgColor, uint32_t fontStyle);
    void print(std::string& str, uint32_t fontStyle);
    void print(const char* str, uint32_t fontStyle);
    void inline println(std::string& str);
    void println(const char* str);
    void println(std::string& str, uint8_t fgColor);
    void println(const char* str, uint8_t fgColor);
    void println(std::string& str, uint8_t fgColor, uint32_t fontStyle);
    void println(const char* str, uint8_t fgColor, uint32_t fontStyle);
    void println(std::string& str, uint32_t fontStyle);
    void println(const char* str, uint32_t fontStyle);

    void inline sgrParam(uint8_t param);
    void inline sgrParam(uint8_t param, uint8_t arg);
    void inline sgrParam(uint8_t param, uint8_t arg0, uint8_t arg1);
    void inline sgrParam(uint8_t param, uint8_t arg0, uint8_t arg1, uint8_t arg2);
    void sgrParam(const uint8_t* paramList, size_t n);
}

#endif // _CLI_H_
