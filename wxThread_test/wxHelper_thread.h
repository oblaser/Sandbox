/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#ifndef WXHELPER_THREAD_H
#define WXHELPER_THREAD_H

#include "wxHelper.h"
#include <wx/thread.h>

#include <stdexcept>
#include <vector>


namespace wxh
{
    class Thread;
    class ThreadHost
    {
    public:
        ThreadHost();
        virtual ~ThreadHost();

        const wxh::Thread** const getThreadPtr(int id);
        wxCriticalSection* getThreadCSPtr(int id);
        virtual wxEvtHandler* getEventHandler() = 0;

        void csEnter();
        void csLeave();

    protected:
        int registerThread(wxh::Thread* th); // has to be called when wxh::Thread::Run() returned wxTHREAD_NO_ERROR. Does take control over the pointer (allocated memory) and frees it in the cleanUp method.
        void cleanUpThreads(); // should be called in OnClose() when not vetoing (see comment in MyFrame::~MyFrame() on https://docs.wxwidgets.org/3.0/classwx_thread.html)

    private:

        class ThreadObject
        {
        public:
            ThreadObject() {}
            ThreadObject(const ThreadObject& other) : th(other.th) {}
            ThreadObject(wxh::Thread* thread) : th(thread) {}
            virtual ~ThreadObject() {}

            wxh::Thread* th = nullptr;
            wxCriticalSection cs;
        };

        std::vector<wxh::ThreadHost::ThreadObject> thread;

        wxCriticalSection csAllocate; // to avoid dangeling pointers to not anymore allocated memory of this->thread. So that an allocation can only happen, if no cs in any ThreadObject is used ad the moment.
        size_t csAllocateLayer;
    };

    class Thread : public wxThread
    {
    public:
        Thread(wxh::ThreadHost* parentThHost);
        virtual ~Thread();

        int getID() const;
        void setID(int id);

        wxCriticalSection* getThreadCSPtr();

    protected:
        wxEvtHandler* const evtHandler;
        wxh::ThreadHost* const parent;

    private:
        Thread(const Thread&);

        int id;
    };

    class CSLocker
    {
    public:
        CSLocker(wxCriticalSection* generalPurposeCS)
            : gpcs(generalPurposeCS), thread(nullptr), host(nullptr)
        {
            gpcs->Enter();
        }

        CSLocker(wxh::Thread* currentThread, wxh::ThreadHost* threadHost)
            : gpcs(nullptr), thread(currentThread), host(threadHost) 
        {
            thread->getThreadCSPtr()->Enter();
            host->csEnter();
        }

        ~CSLocker()
        {
            if (gpcs)
            {
                gpcs->Leave();
            }
            else if (thread && host)
            {
                thread->getThreadCSPtr()->Leave();
                host->csLeave();
            }
            else throw std::runtime_error("invalid wxh::CSLocker object");
        }

    private:
        wxCriticalSection* gpcs;
        wxh::Thread* thread;
        wxh::ThreadHost* host;

    private:
        CSLocker(const CSLocker&) = delete;
        CSLocker& operator=(const CSLocker&);
    };
}


wxDECLARE_EVENT(wxhEVT_THREAD_COMPLETED, wxThreadEvent);
wxDECLARE_EVENT(wxhEVT_THREAD_UPDATE, wxThreadEvent);


#endif // WXHELPER_THREAD_H
