/*!

\author         Oliver Blaser

\date           27.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#ifndef _FORMS_SETTINGSDIALOG_H_
#define _FORMS_SETTINGSDIALOG_H_

#include "wxHelper.h"

#include "application/settings.h"

namespace forms
{
    class settingsDialog : public wxDialog
    {
    public:
        settingsDialog(wxWindow* parent, wxWindowID id,
            const wxString& title = "Settings",
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_DIALOG_STYLE,
            const wxString& name = wxDialogNameStr);
        ~settingsDialog();

        application::Settings getSettings() const;

        void setSettings(const application::Settings& settings);

    private:
        wxSpinCtrl* spnCtl_width;
        wxSpinCtrl* spnCtl_height;
        wxSpinCtrl* spnCtl_relNMines;
        wxButton* btn_ok;
        wxButton* btn_cancel;

        application::Settings settings;

        void initControls();
        void updateGUI();

        void btn_ok_click(wxCommandEvent& e);
        void btn_cancel_click(wxCommandEvent& e);
    };
}

#endif // _FORMS_SETTINGSDIALOG_H_
