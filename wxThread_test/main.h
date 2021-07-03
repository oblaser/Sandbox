/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#ifndef FRAMES_MAIN_H
#define FRAMES_MAIN_H

#include "wxHelper.h"
#include "wxHelper_thread.h"

#include "threadA.h"
#include "threadB.h"
#include "threadC.h"


namespace frames
{
    class Main : public wxFrame, public wxh::ThreadHost
    {
    public:
        Main();
        ~Main() {}

        virtual wxEvtHandler* getEventHandler();

    private:
        wxBoxSizer* mainSizer = nullptr;

        wxButton* btn_startA = nullptr;
        wxButton* btn_terminateA = nullptr;
        wxButton* btn_startB = nullptr;
        wxButton* btn_terminateB = nullptr;
        wxButton* btn_startC = nullptr;
        wxButton* btn_terminateC = nullptr;
        wxTextCtrl* tc_log = nullptr;

        app::ThreadA* threadA = nullptr;
        app::ThreadB* threadB = nullptr;
        app::ThreadC* threadC = nullptr;

        void initControls();

        void btn_startA_click(wxCommandEvent& e);
        void btn_terminateA_click(wxCommandEvent& e);
        void btn_startB_click(wxCommandEvent& e);
        void btn_terminateB_click(wxCommandEvent& e);
        void btn_startC_click(wxCommandEvent& e);
        void btn_terminateC_click(wxCommandEvent& e);

        void th_completed(wxThreadEvent& e);
        void th_update(wxThreadEvent& e);
        void thC_completed(wxThreadEvent& e);
        void thC_update(wxThreadEvent& e);

        void OnClose(wxCloseEvent& e);
        void OnKeyDown(wxKeyEvent& e);

        void log(const wxString& msg);
    };
}




#endif // FRAMES_MAIN_H
