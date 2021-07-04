/*

\author         Oliver Blaser
\date           04.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#include "wxHelper_thread.h"

#include <string>


wxh::ThreadHost::ThreadHost()
    : thread(), csAllocateLayer(0)
{
}

wxh::ThreadHost::~ThreadHost()
{
    cleanUpThreads(); // just in case someone forgets to call it in OnClose()
}

const wxh::Thread** /*const - does not do anything here */ wxh::ThreadHost::getThreadPtr(int id)
{
    if (id < 0) return nullptr;
    return (const wxh::Thread**)(&thread[id].th);
}

wxCriticalSection* wxh::ThreadHost::getThreadCSPtr(int id)
{
    if (id < 0) return nullptr;
    return &thread[id].cs;
}

void wxh::ThreadHost::csEnter()
{
    if (csAllocateLayer == (size_t)-1) throw std::runtime_error("wxh::ThreadHost::csAllocateLayer overflow");

    if (csAllocateLayer == 0) csAllocate.Enter();

    ++csAllocateLayer;
}

void wxh::ThreadHost::csLeave()
{
    if (csAllocateLayer == 0) throw std::runtime_error("wxh::ThreadHost::csAllocateLayer underflow");

    --csAllocateLayer;

    if (csAllocateLayer == 0) csAllocate.Leave();
}

int wxh::ThreadHost::registerThread(wxh::Thread* th)
{
    // may invalidate pointers previously returned by getThreadPtr() and getThreadCSPtr()

    int newID = -1;

    try
    {
        int tmpID = (int)thread.size();

        thread.push_back(wxh::ThreadHost::ThreadObject(th));

        if ((((int)thread.size() - tmpID) == 1) && (tmpID >= 0)) // npos would be -1
        {
            newID = tmpID;
        }
        else
        {
            thread.pop_back();
        }
    }
    catch (...) { /* nop */ }

    return newID;
}

void wxh::ThreadHost::cleanUpThreads()
{
    
    // crashes when a start button is pushed more than once
    
    
    for (size_t i = 0; i < thread.size(); ++i)
    {
        // CriticalSection scope
        {
            wxCriticalSectionLocker csl(thread[i].cs);

            if (thread[i].th)
            {
                if (thread[i].th->Delete() != wxTHREAD_NO_ERROR)
                {
                    /* nop - "can't delete thread" */
                }
            }
        }
    }

    for (size_t i = 0; i < thread.size(); ++i)
    {
        while (1)
        {
            // CriticalSection scope
            {
                wxCriticalSectionLocker csl(thread[i].cs);
                if (!thread[i].th) break;
            }

            wxThread::This()->Sleep(1);
        }
    }
}



wxh::Thread::Thread(wxh::ThreadHost* parentThHost)
    : wxThread(wxTHREAD_DETACHED),
    evtHandler(parentThHost->getEventHandler()),
    parent(parentThHost),
    id(-1),
    idMirror(-1)
{
}

wxh::Thread::~Thread()
{
    wxh::CSLocker csl(this, parent);

    const wxh::Thread** const th = parent->getThreadPtr(id);

    // illustarating constness of pointer to pointer
    //
    // th = 0; // error, because of the 2nd const of "const wxh::Thread** const th"
    // th = &thp; // error, because of the 2nd const of "const wxh::Thread** const th"
    // (*th)->setThreadId(0); // error, because of the 1st const of "const wxh::Thread** const th"
    //Thread* thp;
    //const Thread* cthp;
    // thp = *th; // error, because of the 1st const of "const wxh::Thread** const th"
    //cthp = *th; // OK

    if (th) *th = nullptr;

    // *th resolves to "wxh::Thread* wxh::ThreadHost::thread[id].th" the actual pointer to the thread object (in the wxThread example it is called m_pThread)
}

int wxh::Thread::getThreadID()
{
    wxh::CSLocker csl(this, parent);
    return id;
}

void wxh::Thread::setThreadId(int id)
{
    if (this->getThreadCSPtr())
    {
        // CriticalSection scope
        {
            wxh::CSLocker csl(this, parent);
            this->id = id;
            this->idMirror = id;
        }
    }
    else
    {
        this->id = id;
        this->idMirror = id;
    }
}

wxCriticalSection* wxh::Thread::getThreadCSPtr()
{
    return parent->getThreadCSPtr(idMirror);
}

wxThreadEvent wxh::Thread::getDefaultEvent(wxEventType eventType) const
{
    return wxThreadEvent(eventType, idMirror);
}

wxThreadEvent wxh::Thread::getDefaultCompletedEvent() const
{
    return getDefaultEvent(wxhEVT_THREAD_COMPLETED);
}

wxThreadEvent wxh::Thread::getDefaultUpdateEvent() const
{
    return getDefaultEvent(wxhEVT_THREAD_UPDATE);
}

void wxh::Thread::queueEvent(const wxThreadEvent& e)
{
    evtHandler->QueueEvent(e.Clone());
}

void wxh::Thread::queueDefaultEvent(wxEventType eventType)
{
    queueEvent(getDefaultEvent(eventType));
}

void wxh::Thread::queueDefaultCompletedEvent()
{
    queueEvent(getDefaultCompletedEvent());
}

void wxh::Thread::queueDefaultUpdateEvent()
{
    queueEvent(getDefaultUpdateEvent());
}

wxThread::ExitCode wxh::Thread::Entry()
{
    bool wait;

    // wait for a valid thread ID
    wait = true;
    while (wait)
    {
        // CriticalSection scope
        {
            wxh::CSLocker csl(this, parent);
            if (id >= 0) wait = false;
        }

        if (wait) wxThread::This()->Sleep(1);
    }

    const wxh::Thread* const* th;

    // CriticalSection scope
    {
        wxh::CSLocker csl(this, parent);
        th = parent->getThreadPtr(id);
    }

    if (!th || !(*th))
    {
        char tmpStr[256];

        const unsigned long long ullThP = (unsigned long long)th;
        if (th)
        {
            const unsigned long long ullThPP = (unsigned long long)(*th);
            std::sprintf(tmpStr, "(%llu [0x%llX] - %llu [0x%llX])", ullThP, ullThP, ullThPP, ullThPP);
        }
        else std::sprintf(tmpStr, "(%llu [0x%llX])", ullThP, ullThP);

        const std::string msg("invalid thread pointer " + std::string(tmpStr));

        while (!TestDestroy())
        {
            wxThread::This()->Sleep(500);

            wxThreadEvent e(getDefaultUpdateEvent());
            e.SetString(msg);
            e.SetPayload<std::string>(msg);
            queueEvent(e);
        }
    }
    else
    {
        int r = doWork();

        if (r == 1) queueDefaultCompletedEvent();
    }

    return (wxThread::ExitCode)0;
}



wxDEFINE_EVENT(wxhEVT_THREAD_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(wxhEVT_THREAD_UPDATE, wxThreadEvent);
