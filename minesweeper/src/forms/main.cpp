/*!

\author         Oliver Blaser

\date           29.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#include "main.h"

#include "wx/dcclient.h"
#include "wx/dcbuffer.h"
#include "wx/dcmemory.h"

#include "settingsDialog.h"


using namespace wxHelper;

namespace
{
    enum
    {
        // same as wxID_x
        id_menu_file_exit = wxID_EXIT,
        id_menu_options_settings = wxID_PREFERENCES,

        _begin = wxHelper::idBeginLocalCustom,

        // menus
        id_mwnu_help_gitHubPage,
        id_menu_help_about,

        // controls
        id_buttonReset,
        id_mineField,

        // child windows
        id_settingsDialog,

        _end
    };
}



wxBEGIN_EVENT_TABLE(forms::main, wxFrame)
wxEND_EVENT_TABLE()



forms::main::main(int x, int y, int w, int h) : wxFrame(nullptr, idAny, "Minesweeper", wxPoint(x, y), wxSize(w, h))
{
    int loadSettingsResult = application::settingsFile::load(application::settingsFile::defaultFileName, settings);
    if (loadSettingsResult != 0)
    {
        settings.setFieldWidth(30);
        settings.setFieldHeight(20);
        settings.setRelNMines(0.16f);
        wxMessageBox("Settingsfile could not be loaded. Using default values.\nresult: " + wxString::FromCDouble(loadSettingsResult, 0), " ", wxOK | wxCENTRE | wxICON_WARNING);
    }

    SetMinSize(wxSize(270, 250));

    initMenuBar();
    initControls();

    //Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(forms::main::OnClose));

    mineField->Bind(cEVT_MINEFIELD_DONE, &forms::main::mineField_done, this);
    mineField->Bind(cEVT_MINEFIELD_FAIL, &forms::main::mineField_fail, this);
    //mineField->Bind(cEVT_MINEFIELD_DISCOVER, &forms::main::mineField_discover, this);
}

forms::main::~main()
{
    
}

void forms::main::initControls()
{
    wxPanel* panel = new wxPanel(this, idAny);
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* ss1 = new wxBoxSizer(wxVERTICAL);
    btn_reset = new wxButton(panel, id_buttonReset, "reset", wxDefaultPosition, wxSize(40,30));
    btn_reset->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &forms::main::buttonReset_click, this);
    st_status = new wxStaticText(panel, idAny, "");
    st_status->SetFont(wxFont(13, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    ss1->Add(btn_reset, 0, wxALIGN_CENTER);
    ss1->Add(st_status, 0, wxALIGN_CENTER | wxTOP, 5);
    mainSizer->Add(ss1, 0, wxALIGN_CENTER | wxTOP  | wxLEFT | wxRIGHT, 5);

    wxBoxSizer* ss2 = new wxBoxSizer(wxHORIZONTAL);
    mineField = new controls::mineField(panel, idAny, wxDefaultPosition, wxDefaultSize);
    mineField->setFieldParams(settings.getFieldWidth(), settings.getFieldHeight(), settings.getRelNMines());
    ss2->Add(mineField, 0, wxALIGN_CENTER);
    mainSizer->Add(ss2, 1, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(mainSizer);
    mainSizer->Layout();

    panel->Bind(wxEVT_CHAR_HOOK, &forms::main::OnKeyDown, this);
}

void forms::main::initMenuBar()
{
    wxMenuBar* menuBar = new wxMenuBar();

    wxMenu* menu_file = new wxMenu();
    menu_file->Append(id_menu_file_exit, "Exit");
    menuBar->Append(menu_file, "File");
    
    wxMenu* menu_options = new wxMenu();
    menu_options->Append(id_menu_options_settings, "Settings");
    menuBar->Append(menu_options, "Options");

    wxMenu* menu_help = new wxMenu();
    menu_help->Append(id_mwnu_help_gitHubPage, "GitHub page");
    menu_help->AppendSeparator();
    menu_help->Append(id_menu_help_about, "About");
    menuBar->Append(menu_help, "Help");

    SetMenuBar(menuBar);

    Connect(id_menu_file_exit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(forms::main::menu_file_exit_click));
    Connect(id_menu_options_settings, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(forms::main::menu_options_settings_click));
    Connect(id_mwnu_help_gitHubPage, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(forms::main::mwnu_help_gitHubPage_click));
    Connect(id_menu_help_about, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(forms::main::menu_help_about_click));
}

void forms::main::menu_file_exit_click(wxCommandEvent& e)
{
    Close();
}

void forms::main::menu_options_settings_click(wxCommandEvent& e)
{
    settingsDialog* setDlg = new settingsDialog(this, id_settingsDialog);
    setDlg->setSettings(settings);

    int dlgResult = setDlg->ShowModal();

    if (dlgResult == idOK)
    {
        application::Settings tmpSettings = setDlg->getSettings();

        if (tmpSettings != settings)
        {
            settings = tmpSettings;

            mineField->setFieldParams(settings.getFieldWidth(), settings.getFieldHeight(), settings.getRelNMines());

            mainSizer->Layout();

            setStatusText("");

            int saveSettingsResult = application::settingsFile::save(application::settingsFile::defaultFileName, settings);
            if (saveSettingsResult != 0)
            {
                wxMessageBox("Settingsfile could not be written.\nresult: " + wxString::FromCDouble(saveSettingsResult, 0), " ", wxOK | wxCENTRE | wxICON_WARNING);
            }
        }
    }/*
    else
    {
        switch (dlgResult)
        {
        case wxID_CANCEL:
            wxMessageBox("settings wxID_CANCEL");
            break;

        case idCancel:
            wxMessageBox("settings idCancel");
            break;

        default:
            wxMessageBox("settings result: " + wxString::FromCDouble(dlgResult));
            break;
        }
    }*/
}

void forms::main::mwnu_help_gitHubPage_click(wxCommandEvent& e)
{
    std::string urlStr = "https://github.com/oblaser/Sandbox";

    if (!wxLaunchDefaultBrowser(urlStr))
    {
        wxMessageDialog* dlg = new wxMessageDialog(this, "Could not open URL:\n" + urlStr, " ", wxOK | wxCENTRE | wxICON_NONE);
        dlg->ShowModal();
    }
}

void forms::main::menu_help_about_click(wxCommandEvent& e)
{
    wxMessageBox("Minesweeper " + version.toString() + "\n\nGNU GPLv3 Copyright (c) 2020 Oliver Blaser", "About");
}

void forms::main::buttonReset_click(wxCommandEvent& e)
{
    resetGame();
}

void forms::main::mineField_done(wxEvent& e)
{
    setStatusText("Hooray, you did it!", 0x005000);
}

void forms::main::mineField_fail(wxEvent& e)
{
    setStatusText("BOOOOM", 0x000096);
}

void forms::main::mineField_discover(forms::controls::MineFieldDiscoverEvent& e)
{
    if (e.getNLoops() > 1)
    {
        wxMessageBox("Looped " + wxString::FromCDouble(e.getNLoops()) + " times through the field.", "Discover the field");
    }
}

void forms::main::resetGame()
{
    mineField->resetGame();

    setStatusText("");
}

void forms::main::setStatusText(wxString str, wxColour colour)
{
    st_status->SetForegroundColour(colour);
    st_status->SetLabel(str);
    mainSizer->Layout();
}

void forms::main::setStatusText(wxString str, int colour)
{
    setStatusText(str, wxColour(colour));
}

void forms::main::OnClose(wxCloseEvent& e)
{
    if (wxMessageBox("Really leave the game?", " ", wxYES_NO | wxCENTRE | wxICON_QUESTION) == wxYES)
    {
        Destroy();
    }
    else
    {
        e.Veto();
    }
}

void forms::main::OnKeyDown(wxKeyEvent& e)
{
    if (e.GetKeyCode() == WXK_F1)
    {
        menu_help_about_click(wxCommandEvent());
    }
    //else if ...
    else e.Skip();
}
