/*!

\author         Oliver Blaser

\date           28.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#include "settingsDialog.h"

#include "wx/spinctrl.h"

using namespace wxHelper;

namespace
{
    enum
    {
        _begin = idBeginLocalCustom,

        // controls
        id_spnCtl_width,
        id_spnCtl_height,
        id_spnCtl_relNMines,
        
        _end
    };
}



forms::settingsDialog::settingsDialog(wxWindow* parent, wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name)
    : wxDialog(parent, id, title, pos, size, style, name)
{
    initControls();

    btn_ok->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &forms::settingsDialog::btn_ok_click, this);
    btn_cancel->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &forms::settingsDialog::btn_cancel_click, this);
}

forms::settingsDialog::~settingsDialog()
{
    
}

application::Settings forms::settingsDialog::getSettings() const
{
    application::Settings tmpSet;

    tmpSet.setFieldWidth(spnCtl_width->GetValue());
    tmpSet.setFieldHeight(spnCtl_height->GetValue());
    tmpSet.setRelNMines(spnCtl_relNMines->GetValue() / 1000.0f);

    return tmpSet;
}

void forms::settingsDialog::setSettings(const application::Settings& settings)
{
    this->settings = settings;

    updateGUI();
}

void forms::settingsDialog::initControls()
{
    wxPanel* panel = new wxPanel(this, idAny);
    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);


    wxFlexGridSizer* ss1 = new wxFlexGridSizer(3, 2, 5, 10);
    ss1->Add(new wxStaticText(panel, idAny, "Field width"));
    spnCtl_width = new wxSpinCtrl(panel, id_spnCtl_width, "", wxDefaultPosition, wxHelper::defaultSize::textBox, wxSP_ARROW_KEYS, 5, 10000, 10);
    ss1->Add(spnCtl_width, 1, wxEXPAND);

    ss1->Add(new wxStaticText(panel, idAny, "Field height"));
    spnCtl_height = new wxSpinCtrl(panel, id_spnCtl_height, "", wxDefaultPosition, wxHelper::defaultSize::textBox, wxSP_ARROW_KEYS, 5, 10000, 10);
    ss1->Add(spnCtl_height, 1, wxEXPAND);

    ss1->Add(new wxStaticText(panel, idAny, "Number of mines [\u2030]"));
    spnCtl_relNMines = new wxSpinCtrl(panel, id_spnCtl_relNMines, "", wxDefaultPosition, wxHelper::defaultSize::textBox, wxSP_ARROW_KEYS, 1, 500, 100);
    ss1->Add(spnCtl_relNMines, 1, wxEXPAND);
    vSizer->Add(ss1, 1, wxALIGN_CENTER | wxALL, 5);


    wxBoxSizer* ss2 = new wxBoxSizer(wxHORIZONTAL);
    btn_ok = new wxButton(panel, idOK, "OK", wxDefaultPosition, wxHelper::defaultSize::button);
    ss2->Add(btn_ok, 0);
    btn_cancel = new wxButton(panel, idCancel, "Cancel", wxDefaultPosition, wxHelper::defaultSize::button);
    ss2->Add(btn_cancel, 0);
    vSizer->Add(ss2, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT | wxBOTTOM, 5);


    panel->SetSizer(vSizer);
}

void forms::settingsDialog::updateGUI()
{
    spnCtl_width->SetValue(settings.getFieldWidth());
    spnCtl_height->SetValue(settings.getFieldHeight());
    spnCtl_relNMines->SetValue(settings.getRelNMines() * 1000);
}

void forms::settingsDialog::btn_ok_click(wxCommandEvent& e)
{
    EndModal(idOK);
}

void forms::settingsDialog::btn_cancel_click(wxCommandEvent& e)
{
    EndModal(idCancel);
}
