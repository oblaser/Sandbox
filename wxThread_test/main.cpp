/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#include "main.h"

#include <ctime>
#include <string>




using namespace wxh;

namespace
{
    const size_t fileHistorySize = 10;

    enum
    {
        // same as wxID_x
        //none

        id_begin_ = wxh::idBeginLocalCustom,

        // menus
        //none

        // controls
        //none

        // child windows
        //none

        id_end_
    };
}



frames::Main::Main()
    : wxFrame(nullptr, idAny, "thread test app", wxDefaultPosition, wxSize(620, 740)), wxh::ThreadHost()
{
    SetIcon(wxICON(AAAAA_MainIcon));
    SetPosition(wxh::winPosCenterScreen(GetSize()));
    SetMinSize(wxSize(500, 500));

    initControls();

    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(frames::Main::OnClose));

    Bind(wxhEVT_THREAD_COMPLETED, &frames::Main::th_completed, this);
    Bind(wxhEVT_THREAD_UPDATE, &frames::Main::th_update, this);
    Bind(cEVT_MYTHREADC_COMPLETED, &frames::Main::thC_completed, this);
    Bind(cEVT_MYTHREADC_UPDATE, &frames::Main::thC_update, this);
}

wxEvtHandler* frames::Main::getEventHandler()
{
    return GetEventHandler();
}

void frames::Main::initControls()
{
    wxPanel* panel = new wxPanel(this, idAny);
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bs1 = new wxBoxSizer(wxHORIZONTAL);
    {
        btn_startA = new wxButton(panel, idAny, WXH_DISPSTR("A"), wxDefaultPosition, defSize::button);
        btn_startA->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &frames::Main::btn_startA_click, this);
        btn_terminateA = new wxButton(panel, idAny, WXH_DISPSTR("terminate"), wxDefaultPosition, defSize::button);
        btn_terminateA->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &frames::Main::btn_terminateA_click, this);

        btn_startB = new wxButton(panel, idAny, WXH_DISPSTR("B"), wxDefaultPosition, defSize::button);
        btn_startB->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &frames::Main::btn_startB_click, this);
        btn_terminateB = new wxButton(panel, idAny, WXH_DISPSTR("terminate"), wxDefaultPosition, defSize::button);
        btn_terminateB->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &frames::Main::btn_terminateB_click, this);

        btn_startC = new wxButton(panel, idAny, WXH_DISPSTR("C"), wxDefaultPosition, defSize::button);
        btn_startC->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &frames::Main::btn_startC_click, this);
        btn_terminateC = new wxButton(panel, idAny, WXH_DISPSTR("terminate"), wxDefaultPosition, defSize::button);
        btn_terminateC->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &frames::Main::btn_terminateC_click, this);

        bs1->Add(btn_startA, 0);
        bs1->Add(btn_terminateA, 0, wxLEFT, defSize::margin);
        bs1->Add(btn_startB, 0, wxLEFT, defSize::margin * 5);
        bs1->Add(btn_terminateB, 0, wxLEFT, defSize::margin);
        bs1->Add(btn_startC, 0, wxLEFT, defSize::margin * 5);
        bs1->Add(btn_terminateC, 0, wxLEFT, defSize::margin);
    }
    mainSizer->Add(bs1, 0, wxEXPAND | (wxALL & ~wxBOTTOM), defSize::margin);

    tc_log = new wxTextCtrl(panel, idAny, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
    mainSizer->Add(tc_log, 1, wxEXPAND | wxALL, defSize::margin);

    panel->SetSizer(mainSizer);
    mainSizer->Layout();

    panel->Bind(wxEVT_CHAR_HOOK, &frames::Main::OnKeyDown, this);
}

void frames::Main::btn_startA_click(wxCommandEvent& e)
{
    // it's totally fine to overwrite (if already instanciated) the threadX pointer here, because registerThread() takes control of the memory
    threadA = new app::ThreadA(this);

    if (threadA->Run() == wxTHREAD_NO_ERROR)
    {
        threadA->setID(registerThread(threadA));
    }
    else
    {
        delete threadA;
        threadA = nullptr;
    }
}

void frames::Main::btn_terminateA_click(wxCommandEvent& e)
{
    if (threadA) threadA->Delete();
}

void frames::Main::btn_startB_click(wxCommandEvent& e)
{
    // see btn_startA_click()
    threadB = new app::ThreadB(this, (threadB ? 1000 : 1000000));

    if (threadB->Run() == wxTHREAD_NO_ERROR)
    {
        threadB->setID(registerThread(threadB));
    }
    else
    {
        delete threadB;
        threadB = nullptr;
    }
}

void frames::Main::btn_terminateB_click(wxCommandEvent& e)
{
    if (threadB) threadB->Delete();
}

void frames::Main::btn_startC_click(wxCommandEvent& e)
{
    // see btn_startA_click()
    threadC = new app::ThreadC(this);

    if (threadC->Run() == wxTHREAD_NO_ERROR)
    {
        threadC->setID(registerThread(threadC));
    }
    else
    {
        delete threadC;
        threadC = nullptr;
    }
}

void frames::Main::btn_terminateC_click(wxCommandEvent& e)
{
    if(threadC) threadC->Delete();
}

void frames::Main::th_completed(wxThreadEvent& e)
{
    const int idA = (threadA ? threadA->getID() : -1);
    const int idB = (threadB ? threadB->getID() : -1);

    if (e.GetId() == idA) log("A completed");
    else if (e.GetId() == idB) log("B completed");
    else log("thread " + std::to_string(e.GetId()) + " completed");
    e.Skip();
}

void frames::Main::th_update(wxThreadEvent& e)
{
    const int idA = (threadA ? threadA->getID() : -1);
    const int idB = (threadB ? threadB->getID() : -1);

    if (e.GetId() == idA) log("A update: " + std::to_string(e.GetPayload<int>()));
    else if (e.GetId() == idB) log("B update: " + e.GetPayload<std::string>());
    else log("thread " + std::to_string(e.GetId()) + " update");
    e.Skip();
}

void frames::Main::thC_completed(wxThreadEvent& e)
{
    log("C(" + std::to_string(e.GetId()) + ") completed");
    e.Skip();
}

void frames::Main::thC_update(wxThreadEvent& e)
{
    log("C(" + std::to_string(e.GetId()) + ") update");
    e.Skip();
}

void frames::Main::OnClose(wxCloseEvent& e)
{
    cleanUpThreads();

    e.Skip();
}

void frames::Main::OnKeyDown(wxKeyEvent& e)
{
    e.Skip();
}

void frames::Main::log(const wxString& msg)
{
    time_t t = time(nullptr);

    char tsStr[100];
    strftime(tsStr, 100, "%F %T", localtime(&t));

    tc_log->AppendText(tsStr + wxString("> ") + msg + "\n");
}



















#if 0

frames::Main::Main()
    : wxFrame(nullptr, idAny, "thread test app", wxDefaultPosition, wxSize(620, 740))
{
    SetIcon(wxICON(AAAAA_MainIcon));
    SetPosition(wxh::winPosCenterScreen(GetSize()));
    SetMinSize(wxSize(500, 500));

    initControls();

    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(frames::Main::OnClose));
}

void frames::Main::initControls()
{
    wxPanel* panel = new wxPanel(this, idAny);
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bs1 = new wxBoxSizer(wxHORIZONTAL);
    {
        btn_dosth = new wxButton(panel, idAny, "do something", wxDefaultPosition, wxSize(120, defSize::btn_height));
        btn_dosth->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &frames::Main::btn_dosth_click, this);

        st_result = new wxStaticText(panel, idAny, wxEmptyString, wxDefaultPosition, wxSize(200, -1), wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
        st_result->SetFont(wxFont(11, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        bs1->Add(btn_dosth, 0, wxALIGN_CENTER_VERTICAL);
        bs1->Add(st_result, 1, wxALIGN_CENTER_VERTICAL);
    }
    mainSizer->Add(bs1, 0, wxEXPAND | (wxALL & ~wxBOTTOM), defSize::margin);

    tc_log = new wxTextCtrl(panel, idAny, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
    mainSizer->Add(tc_log, 1, wxEXPAND | wxALL, defSize::margin);

    panel->SetSizer(mainSizer);
    mainSizer->Layout();

    panel->Bind(wxEVT_CHAR_HOOK, &frames::Main::OnKeyDown, this);
}

void frames::Main::btn_dosth_click(wxCommandEvent& e)
{
    st_result->SetLabel("test");
    log("test" + std::to_string(rand()));
}

void frames::Main::thA_completed(wxThreadEvent& e)
{
}

void frames::Main::thA_update(wxThreadEvent& e)
{
}

void frames::Main::OnClose(wxCloseEvent& e)
{
    e.Skip();
}

void frames::Main::OnKeyDown(wxKeyEvent& e)
{
    e.Skip();
}

void frames::Main::log(const wxString& msg)
{
    time_t t = time(nullptr);

    char tsStr[100];
    strftime(tsStr, 100, "%F %T", localtime(&t));

    tc_log->AppendText(tsStr + wxString("> ") + msg + "\n");
}

#endif


