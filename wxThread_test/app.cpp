/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#include "app.h"

#include "main.h"



#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 28251)
#endif

wxIMPLEMENT_APP(App);

#ifdef _MSC_VER
#pragma warning(pop)
#endif



App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
    bool r = true;

    if (!wxApp::OnInit())
    {
        wxMessageBox("Fatal Error!", "", wxICON_ERROR | wxOK);
        return false;
    }





    if (r)
    {
        mainForm = new frames::Main();
        mainForm->Show();
    }

    return r;
}
