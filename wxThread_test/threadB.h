/*

\author         Oliver Blaser
\date           04.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#ifndef THREADB_H
#define THREADB_H

#include "wxHelper.h"
#include "wxHelper_thread.h"

namespace app
{
    class ThreadB : public wxh::Thread
    {
    public:
        ThreadB(wxh::ThreadHost* parentThHost, int data);
        virtual ~ThreadB() {}

        int getData();
        void setData(int data);

    protected:
        int doWork() override;

    private:
        int someThreadData;
    };
}

#endif // THREADB_H
