/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#include "threadC.h"



app::ThreadC::ThreadC(wxh::ThreadHost* parentThHost)
    : wxh::Thread(parentThHost)
{
}

wxThread::ExitCode app::ThreadC::Entry()
{
    int cnt = 0;
    while (!TestDestroy() && (cnt < 5))
    {
        wxThread::This()->Sleep(2000);

        wxThreadEvent e(cEVT_MYTHREADC_UPDATE);
        e.SetId(getID());
        evtHandler->QueueEvent(e.Clone());

        ++cnt;
    }

    wxThreadEvent e(cEVT_MYTHREADC_COMPLETED);
    e.SetId(getID());
    evtHandler->QueueEvent(e.Clone());

    return (wxThread::ExitCode)0;
}



wxDEFINE_EVENT(cEVT_MYTHREADC_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(cEVT_MYTHREADC_UPDATE, wxThreadEvent);
