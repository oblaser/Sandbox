/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#ifndef THREADC_H
#define THREADC_H

#include "wxHelper.h"
#include "wxHelper_thread.h"


namespace app
{
    class ThreadC : public wxh::Thread
    {
    public:
        ThreadC(wxh::ThreadHost* parentThHost);
        virtual ~ThreadC() {}

    protected:
        wxThread::ExitCode Entry() override;
    };
}


wxDECLARE_EVENT(cEVT_MYTHREADC_COMPLETED, wxThreadEvent);
wxDECLARE_EVENT(cEVT_MYTHREADC_UPDATE, wxThreadEvent);


#endif // THREADC_H
