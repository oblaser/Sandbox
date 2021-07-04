/*

\author         Oliver Blaser
\date           04.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#ifndef THREADA_H
#define THREADA_H

#include "wxHelper.h"
#include "wxHelper_thread.h"

namespace app
{
    class ThreadA : public wxh::Thread
    {
    public:
        ThreadA(wxh::ThreadHost* parentThHost);
        virtual ~ThreadA() {}

    protected:
        int doWork() override;
    };
}

#endif // THREADA_H
