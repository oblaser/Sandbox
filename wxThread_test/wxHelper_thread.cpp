/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#include "wxHelper_thread.h"



wxh::ThreadHost::ThreadHost()
    : thread(), csAllocateLayer(0)
{
}

wxh::ThreadHost::~ThreadHost()
{
    cleanUpThreads(); // just in case someone forgets to call it in OnClose()
}

const wxh::Thread** const wxh::ThreadHost::getThreadPtr(int id)
{
    if (id < 0) return nullptr;
    return (const wxh::Thread** const)(&thread[id].th);
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
    id(-1)
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
    // (*th)->setID(0); // error, because of the 1st const of "const wxh::Thread** const th"
    //Thread* thp;
    //const Thread* cthp;
    // thp = *th; // error, because of the 1st const of "const wxh::Thread** const th"
    //cthp = *th; // OK

    if (th) *th = nullptr;

    // *th resolves to "wxh::Thread* wxh::ThreadHost::thread[id].th" the actual pointer to the thread object (in the wxThread example it is called m_pThread)
}

int wxh::Thread::getID() const
{
    return id;
}

void wxh::Thread::setID(int id)
{
    this->id = id;
}

wxCriticalSection* wxh::Thread::getThreadCSPtr()
{
    return parent->getThreadCSPtr(id);
}



wxDEFINE_EVENT(wxhEVT_THREAD_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(wxhEVT_THREAD_UPDATE, wxThreadEvent);
