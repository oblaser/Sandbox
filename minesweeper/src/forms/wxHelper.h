/*!

\author         Oliver Blaser

\date           27.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#ifndef _WXHELPER_H_
#define _WXHELPER_H_



#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable: 26812)

#pragma warning(push)
#pragma warning(disable: 26495)

#pragma warning(push)
#pragma warning(disable: 26437)

#pragma warning(push)
#pragma warning(disable: 26451)

#endif

#include "wx/wx.h"

#ifdef _MSC_VER
#pragma warning(pop)
#pragma warning(pop)
#pragma warning(pop)
#pragma warning(pop)
#endif



namespace wxHelper
{
    namespace defaultSize
    {
        const wxSize button = wxSize(75, 23);
        const wxSize textBox = wxSize(100, 20);
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
}



#endif // _WXHELPER_H_
