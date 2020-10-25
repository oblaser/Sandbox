/*

author:     Oliver Blaser

date c:     15.10.2020
date e:     25.10.2020

*/

#include <iostream>

#include "cli.h"
#include "project.h"

#if(PRJ_WIN32)
#include <Windows.h>
#endif

using namespace std;

namespace
{
#if(PRJ_WIN32)

    const uint16_t FOREGROUND_MASK = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    const uint16_t BACKGROUND_MASK = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;

    bool setAttr(uint16_t attr)
    {
        return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
    }

    uint16_t getCurrentAttr()
    {
        CONSOLE_SCREEN_BUFFER_INFO cInfo;
        uint16_t attr;

        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cInfo)) attr = cInfo.wAttributes;
        else attr = 0x0007;

        return attr;
    }

    bool convertColorBitsAnsiToWin(uint8_t ansiColor, uint16_t* winAttr)
    {
        bool result;

        if ((ansiColor >= 0) && (ansiColor <= 7))
        {
            *winAttr &= ~0x0007;
            if (ansiColor & cli::SGRCOLOR_RED) *winAttr |= 0x0004;
            if (ansiColor & cli::SGRCOLOR_GREEN) *winAttr |= 0x0002;
            if (ansiColor & cli::SGRCOLOR_BLUE) *winAttr |= 0x0001;
            result = true;
        }
        else result = false;

        return result;
    }

    bool setAnsiColorToWinAttr(uint8_t ansiColor, uint16_t* winAttr)
    {
        bool result;
        uint16_t attr = 0;

        // foreground
        if ((ansiColor >= 30) && (ansiColor <= 37))
        {
            convertColorBitsAnsiToWin(ansiColor - 30, &attr);
            *winAttr &= ~FOREGROUND_MASK;
            *winAttr |= attr & FOREGROUND_MASK;
            result = true;
        }

        // background
        else if ((ansiColor >= 40) && (ansiColor <= 47))
        {
            convertColorBitsAnsiToWin(ansiColor - 40, &attr);
            attr <<= 4;
            *winAttr &= ~BACKGROUND_MASK;
            *winAttr |= attr & BACKGROUND_MASK;
            result = true;
        }

        // foreground intens
        else if ((ansiColor >= 90) && (ansiColor <= 97))
        {
            convertColorBitsAnsiToWin(ansiColor - 90, &attr);
            *winAttr &= ~FOREGROUND_MASK;
            *winAttr |= (attr & FOREGROUND_MASK) | FOREGROUND_INTENSITY;
            result = true;
        }

        // background intens
        else if ((ansiColor >= 100) && (ansiColor <= 107))
        {
            convertColorBitsAnsiToWin(ansiColor - 100, &attr);
            attr <<= 4;
            *winAttr &= ~BACKGROUND_MASK;
            *winAttr |= (attr & BACKGROUND_MASK) | BACKGROUND_INTENSITY;
            result = true;
        }

        else result = false;

        return result;
    }

#else

    string uiToStr(uint64_t value)
    {
        string result = "";
        char str_rev[27];
        int str_rev_ind = 0;
        int digitCnt = 0;
        size_t len = 0;

        if (value == 0)
        {
            result += "0";
            return result;
        }

        while (value != 0)
        {
            str_rev[str_rev_ind] = (value % 10) + 0x30;
            ++str_rev_ind;
            value /= 10;

            ++digitCnt;
        }

        len += str_rev_ind;

        --str_rev_ind;

        while (str_rev_ind > (-1))
        {
            result += str_rev[str_rev_ind];
            --str_rev_ind;
        }

        return result;
    }

#endif
}

void cli::print(std::string& str)
{
    cout << str;
}

void cli::print(const char* str)
{
    string s = string(str);
    print(s);
}

void cli::print(std::string& str, uint8_t fgColor)
{
    print(str, fgColor, FS_NORMAL);
}

void cli::print(const char* str, uint8_t fgColor)
{
    string s = string(str);
    print(s, fgColor);
}

void cli::print(std::string& str, uint8_t fgColor, uint32_t fontStyle)
{
    if (fgColor & 0x08) sgrParam(SGR_FGCOLOR_BRIGHT_SET_BASE + (fgColor & 0x07));
    else sgrParam(SGR_FGCOLOR_SET_BASE + (fgColor & 0x07));
    print(str, fontStyle);
    sgrParam(SGR_FGCOLOR_DEFAULT);
}

void cli::print(const char* str, uint8_t fgColor, uint32_t fontStyle)
{
    string s = string(str);
    print(s, fgColor, fontStyle);
}

void cli::print(std::string& str, uint32_t fontStyle)
{
    if (fontStyle & cli::FS_BOLD) sgrParam(SGR_BOLD);
    if (fontStyle & cli::FS_UNDERLINE) sgrParam(SGR_UNDERLINE);
    if (fontStyle & cli::FS_REVERSED) sgrParam(SGR_REVERSE_VIDEO);
    if (fontStyle & cli::FS_BLINK) sgrParam(SGR_BLINK_SLOW);
    print(str);
    if (fontStyle & cli::FS_BOLD) sgrParam(SGR_BOLD_FAINT_OFF);
    if (fontStyle & cli::FS_UNDERLINE) sgrParam(SGR_UNDERLINE_OFF);
    if (fontStyle & cli::FS_REVERSED) sgrParam(SGR_REVERSE_VIDEO_OFF);
    if (fontStyle & cli::FS_BLINK) sgrParam(SGR_BLINK_OFF);
}

void cli::print(const char* str, uint32_t fontStyle)
{
    string s = string(str);
    print(s, fontStyle);
}

void cli::println(std::string& str)
{
    print(str);
    cout << endl;
}

void cli::println(const char* str)
{
    string s = string(str);
    println(s);
}

void cli::println(std::string& str, uint8_t fgColor)
{
    print(str, fgColor);
    cout << endl;
}

void cli::println(const char* str, uint8_t fgColor)
{
    string s = string(str);
    println(s, fgColor);
}

void cli::println(std::string& str, uint8_t fgColor, uint32_t fontStyle)
{
    print(str, fgColor, fontStyle);
    cout << endl;
}

void cli::println(const char* str, uint8_t fgColor, uint32_t fontStyle)
{
    string s = string(str);
    println(s, fgColor, fontStyle);
}

void cli::println(std::string& str, uint32_t fontStyle)
{
    print(str, fontStyle);
    cout << endl;
}

void cli::println(const char* str, uint32_t fontStyle)
{
    string s = string(str);
    println(s, fontStyle);
}

void cli::sgrParam(uint8_t param)
{
    uint8_t p[] = { param };
    cli::sgrParam(p, sizeof(p) / sizeof(p[0]));
}

void cli::sgrParam(uint8_t param, uint8_t arg)
{
    uint8_t p[] = { param, arg };
    cli::sgrParam(p, sizeof(p) / sizeof(p[0]));
}

void cli::sgrParam(uint8_t param, uint8_t arg0, uint8_t arg1)
{
    uint8_t p[] = { param, arg0, arg1 };
    cli::sgrParam(p, sizeof(p) / sizeof(p[0]));
}

void cli::sgrParam(uint8_t param, uint8_t arg0, uint8_t arg1, uint8_t arg2)
{
    uint8_t p[] = { param, arg0, arg1, arg2 };
    cli::sgrParam(p, sizeof(p) / sizeof(p[0]));
}

void cli::sgrParam(const uint8_t* paramList, size_t n)
{
#if(PRJ_WIN32)

    uint16_t attr = getCurrentAttr();

    for (size_t i = 0; i < n; ++i)
    {
        if (!setAnsiColorToWinAttr(*(paramList + i), &attr))
        {
            switch (*(paramList + i))
            {
                case SGR_RESET:
                    attr = 0x0007;
                    break;

                case SGR_UNDERLINE:
                    attr |= COMMON_LVB_UNDERSCORE;
                    break;

                case SGR_UNDERLINE_OFF:
                    attr &= ~COMMON_LVB_UNDERSCORE;
                    break;

                case SGR_REVERSE_VIDEO:
                    attr |= COMMON_LVB_REVERSE_VIDEO;
                    break;

                case SGR_REVERSE_VIDEO_OFF:
                    attr &= ~COMMON_LVB_REVERSE_VIDEO;
                    break;

                case SGR_FGCOLOR_DEFAULT:
                    attr &= ~0x000F;
                    attr |= 0x0007;
                    break;

                case SGR_BGCOLOR_DEFAULT:
                    attr &= ~0x00F0;
                    break;

                default:
                    // nop 
                    break;
            }
        }
    }

    setAttr(attr);

#else

    cout << "\x1B[";

    for (size_t i = 0; i < n; ++i)
    {
        if (i > 0) cout << ';';
        cout << uiToStr(*(paramList + i));
    }

    cout << "m";

#endif
}
