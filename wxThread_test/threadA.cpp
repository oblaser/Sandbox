/*

\author         Oliver Blaser
\date           04.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#include "threadA.h"

#include <ctime>


app::ThreadA::ThreadA(wxh::ThreadHost* parentThHost)
    : wxh::Thread(parentThHost)
{
}

int app::ThreadA::doWork()
{
    int x = 0;
    time_t tFired = 0;

    while (!TestDestroy())
    {
        time_t t = time(NULL);

        if ((t % 1 == 0) && (tFired != t))
        {
            tFired = t;

            wxThreadEvent e(getDefaultUpdateEvent());
            e.SetPayload<int>(x);
            queueEvent(e);

            /* alternative queueing procedure:
            
            wxThreadEvent e(wxhEVT_THREAD_UPDATE);
            e.SetId(getThreadID());
            e.SetPayload<int>(x);
            evtHandler->QueueEvent(e.Clone());
            */
        }

        ++x;
    }

    return 1;
}
