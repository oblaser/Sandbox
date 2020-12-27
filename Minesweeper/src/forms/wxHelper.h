/*!

\author         Oliver Blaser

\date           26.12.2020

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
    enum { idStart = wxID_HIGHEST + 1 };
}



#endif // _WXHELPER_H_
