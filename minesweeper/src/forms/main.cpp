/*!

\author         Oliver Blaser

\date           28.12.2020

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
        wxMessageBox("Settingsfile could not be loaded. Using default values.\nresult: " + wxString::FromCDouble(loadSettingsResult, 0), " ");
    }

    SetMinSize(wxSize(270, 250));

    initMenuBar();
    initControls();
}

forms::main::~main()
{
    
}

void forms::main::initControls()
{
    wxPanel* panel = new wxPanel(this, idAny);
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* ss1 = new wxBoxSizer(wxVERTICAL);
    btn_reset = new wxButton(panel, id_buttonReset, "reset");
    btn_reset->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &forms::main::buttonReset_click, this);
    st_status = new wxStaticText(panel, idAny, "status");
    ss1->Add(btn_reset, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    ss1->Add(st_status, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
    mainSizer->Add(ss1, 0, wxALIGN_CENTER);

    wxBoxSizer* ss2 = new wxBoxSizer(wxHORIZONTAL);
    mineField = new controls::mineField(panel, idAny, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    mineField->setFieldParams(settings.getFieldWidth(), settings.getFieldHeight(), settings.getRelNMines());
    ss2->Add(mineField, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(ss2, 1, wxALIGN_CENTER);

    panel->SetSizer(mainSizer);
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

            mineField->GetContainingSizer()->Fit(mineField);
            mainSizer->Layout();

            int saveSettingsResult = application::settingsFile::save(application::settingsFile::defaultFileName, settings);
            if (saveSettingsResult != 0)
            {
                wxMessageBox("Settingsfile could not be written.\nresult: " + wxString::FromCDouble(saveSettingsResult, 0), " ");
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
        wxMessageDialog* dlg = new wxMessageDialog(this, "Could not open URL:\n" + urlStr);
        dlg->ShowModal();
    }
}

void forms::main::menu_help_about_click(wxCommandEvent& e)
{
    wxMessageBox("Minesweeper " + version.toString());
}

void forms::main::buttonReset_click(wxCommandEvent& e)
{
    mineField->resetGame();
}

void forms::main::mineField_finnished(wxEvent& e)
{
}

void forms::main::mineField_mineExploded(wxEvent& e)
{
}
