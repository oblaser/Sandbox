/*!

\author         Oliver Blaser

\date           28.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#ifndef _FORMS_MAIN_H_
#define _FORMS_MAIN_H_

#include "wxHelper.h"
#include "controls/mineField.h"
#include "application/settings.h"
#include "middleware/version.h"

namespace forms
{
    class main : public wxFrame
    {
    public:
        main(int x, int y, int w, int h);
        ~main();

    private:
        const util::Version version = util::Version(0, 1, 1000);

        application::Settings settings;

        wxBoxSizer* mainSizer = nullptr;
        wxButton* btn_reset = nullptr;
        wxStaticText* st_status = nullptr;
        controls::mineField* mineField = nullptr;

        void initControls();
        void initMenuBar();

        void menu_file_exit_click(wxCommandEvent& e);
        void menu_options_settings_click(wxCommandEvent& e);
        void mwnu_help_gitHubPage_click(wxCommandEvent& e);
        void menu_help_about_click(wxCommandEvent& e);

        void buttonReset_click(wxCommandEvent& e);
        void mineField_finnished(wxEvent& e);
        void mineField_mineExploded(wxEvent& e);

        void OnClose(wxCloseEvent& e);
        void OnKeyDown(wxKeyEvent& e);

        wxDECLARE_EVENT_TABLE();
    };
}

#endif // _FORMS_MAIN_H_
