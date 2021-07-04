/*

\author         Oliver Blaser
\date           04.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#include "threadB.h"

#include <string>

app::ThreadB::ThreadB(wxh::ThreadHost* parentThHost, int data)
    : wxh::Thread(parentThHost), someThreadData(data)
{
}

int app::ThreadB::getData()
{
    wxh::CSLocker csl(this, parent);

    return someThreadData;
}

void app::ThreadB::setData(int data)
{
    wxh::CSLocker csl(this, parent);

    someThreadData = data;
}

int app::ThreadB::doWork()
{
    while (!TestDestroy())
    {
        wxThread::This()->Sleep(2000);

        // CriticalSection scope
        {
            wxh::CSLocker csl(this, parent);

            ++someThreadData;

            wxThreadEvent e = getDefaultUpdateEvent();
            e.SetPayload<std::string>("accessing thread data: " + std::to_string(someThreadData));
            queueEvent(e);
        }
    }

    queueDefaultCompletedEvent();

    /* alternative queueing procedure:

    wxThreadEvent e(wxhEVT_THREAD_COMPLETED);
    e.SetId(getThreadID());
    evtHandler->QueueEvent(e.Clone());
    */

    return 0;
}
