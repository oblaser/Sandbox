/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#include "threadA.h"

#include <ctime>


app::ThreadA::ThreadA(wxh::ThreadHost* parentThHost)
    : wxh::Thread(parentThHost)
{
}

wxThread::ExitCode app::ThreadA::Entry()
{
    int x = 0;
    time_t tFired = 0;

    while (!TestDestroy())
    {
        time_t t = time(NULL);

        if ((t % 1 == 0) && (tFired != t))
        {
            tFired = t;

            wxThreadEvent e(wxhEVT_THREAD_UPDATE);
            e.SetId(getID());
            e.SetPayload<int>(x);
            evtHandler->QueueEvent(e.Clone());
        }

        ++x;
    }

    wxThreadEvent e(wxhEVT_THREAD_COMPLETED);
    e.SetId(getID());
    evtHandler->QueueEvent(e.Clone());

    return (wxThread::ExitCode)0;
}
