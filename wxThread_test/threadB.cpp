/*

\author         Oliver Blaser
\date           01.07.2021
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

wxThread::ExitCode app::ThreadB::Entry()
{
    while (!TestDestroy())
    {
        wxThread::This()->Sleep(2000);

        int tmpID = getID();

        // CriticalSection scope
        {
            wxh::CSLocker csl(this, parent);

            ++someThreadData;

            wxThreadEvent e(wxhEVT_THREAD_UPDATE);
            e.SetId(tmpID);
            e.SetPayload<std::string>("accessing thread data: " + std::to_string(someThreadData));
            evtHandler->QueueEvent(e.Clone());
        }
    }

    wxThreadEvent e(wxhEVT_THREAD_COMPLETED);
    e.SetId(getID());
    evtHandler->QueueEvent(e.Clone());

    return (wxThread::ExitCode)0;
}
