/*!

\author         Oliver Blaser

\date           29.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/


#include "app.h"

#include <wx/display.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 28251)
#endif

wxIMPLEMENT_APP(app);

#ifdef _MSC_VER
#pragma warning(pop)
#endif

app::app()
{
}

app::~app()
{
}

bool app::OnInit()
{
    int mainDisplayIndex = wxDisplay::GetFromPoint(wxPoint(1, 1));

        int w = 650;
        int h = 550;

    if (mainDisplayIndex != wxNOT_FOUND)
    {
        wxDisplay d(mainDisplayIndex);
        wxRect rect = d.GetClientArea();

        mainForm = new forms::main(rect.x + rect.width / 2 - w / 2, rect.y + rect.height * 0.1, w, h);
    }
    else mainForm = new forms::main(30, 30, w, h);

    mainForm->SetIcon(wxICON(aaaaa_MainIcon));

    mainForm->Show();

    return true;
}
