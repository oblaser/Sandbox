/*

\author         Oliver Blaser
\date           04.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#include "threadC.h"



app::ThreadC::ThreadC(wxh::ThreadHost* parentThHost)
    : wxh::Thread(parentThHost)
{
}

int app::ThreadC::doWork()
{
    int cnt = 0;
    while (!TestDestroy() && (cnt < 5))
    {
        wxThread::This()->Sleep(2000);

        queueDefaultEvent(cEVT_MYTHREADC_UPDATE);

        ++cnt;
    }

    wxThreadEvent e = getDefaultEvent(cEVT_MYTHREADC_COMPLETED);
    e.SetPayload<std::string>("some thread completed data.");
    queueEvent(e);

    return 0;
}



wxDEFINE_EVENT(cEVT_MYTHREADC_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(cEVT_MYTHREADC_UPDATE, wxThreadEvent);
