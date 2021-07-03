/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#ifndef WXHELPER_H
#define WXHELPER_H



#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 26812)
#pragma warning(disable: 26495)
#pragma warning(disable: 26437)
#pragma warning(disable: 26451)
#endif

#include <wx/wx.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <wx/display.h>

#include <string>



#define WXH_Auml "\xC3\x84"
#define WXH_Ouml "\xC3\x96"
#define WXH_Uuml "\xC3\x9C"
#define WXH_auml "\xC3\xA4"
#define WXH_ouml "\xC3\xB6"
#define WXH_uuml "\xC3\xBC"

// passthrough macro, to find strings which have to be translated, if the software ever gets translated
#define WXH_DISPSTR(x) (x)



namespace wxh
{
    namespace defSize
    {
        constexpr int margin = 5;
        constexpr int btn_width = 75;
        constexpr int btn_height = 23;
        constexpr int tc_width = 100;
        constexpr int tc_height = 20;

        const wxSize button = wxSize(btn_width, btn_height);
        const wxSize textCtrl = wxSize(tc_width, tc_height);
    }

    enum
    {
        // link
        idAny = wxID_ANY,

        // global customn IDs
        idApply = wxID_HIGHEST + 1,
        idCancel,
        idIgnore,
        idNo,
        idOK,
        idYes,

        // local custom ID start
        idBeginLocalCustom
    };

    inline wxPoint winPosCenterRect(const wxSize& windowSize, const wxRect& rect)
    {
        return wxPoint(rect.x + (rect.width - windowSize.GetWidth()) / 2, rect.y + (rect.height - windowSize.GetHeight()) / 2);
    }
    inline wxPoint winPosCenterRect(const wxSize& windowSize, const wxPoint& rectPos, const wxSize& rectSize, const wxPoint& fallback = wxDefaultPosition)
    {
        return winPosCenterRect(windowSize, wxRect(rectPos, rectSize));
    }
    inline wxPoint winPosCenterRect(const wxSize& windowSize, int x, int y, int width, int height, const wxPoint& fallback = wxDefaultPosition)
    {
        return winPosCenterRect(windowSize, wxRect(x, y, width, height));
    }
    inline wxPoint winPosCenterRect(const wxSize& windowSize, const wxWindow* parent, const wxPoint& fallback = wxDefaultPosition)
    {
        wxPoint r = fallback;
        if (parent) r = winPosCenterRect(windowSize, parent->GetPosition(), parent->GetSize());
        return r;
    }

    inline wxPoint winPosCenterScreen(const wxSize& windowSize, const wxPoint& fallback = wxDefaultPosition, const wxPoint& screenDetectPoint = wxPoint(50, 50))
    {
        wxPoint r = fallback;

        int mainDisplayIndex = wxDisplay::GetFromPoint(screenDetectPoint);
        if (mainDisplayIndex != wxNOT_FOUND)
        {
            wxDisplay d(mainDisplayIndex);
            wxRect rect = d.GetClientArea();
            r = winPosCenterRect(windowSize, rect);
        }

        return r;
    }

    inline wxString u8tos(const char* u8str) { return wxString::FromUTF8(u8str); }
    inline wxString u8tos(const std::string& u8str) { return u8tos(u8str.c_str()); }
}



#endif // WXHELPER_H
