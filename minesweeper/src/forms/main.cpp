/*!

\author         Oliver Blaser

\date           26.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#include "main.h"

#include "wx/dcclient.h"
#include "wx/dcbuffer.h"
#include "wx/dcmemory.h"

namespace
{
    enum id
    {
        buttonReset = wxHelper::idStart,
        mineField
    };
}



wxBEGIN_EVENT_TABLE(forms::main, wxFrame)
EVT_BUTTON(id::buttonReset, forms::main::buttonReset_click)
wxEND_EVENT_TABLE()



forms::main::main(int x, int y, int w, int h) : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(x, y), wxSize(w, h))
{
    SetMinSize(wxSize(270, 250));

    initControls();
}

forms::main::~main()
{
    
}

void forms::main::initControls()
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* ss1 = new wxBoxSizer(wxVERTICAL);
    buttonReset = new wxButton(panel, id::buttonReset, "reset");
    labelStatus = new wxStaticText(panel, wxID_ANY, "status");
    ss1->Add(buttonReset, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    ss1->Add(labelStatus, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
    vSizer->Add(ss1, 0, wxALIGN_CENTER);

    wxBoxSizer* ss2 = new wxBoxSizer(wxHORIZONTAL);
    mineField = new controls::mineField(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    mineField->setFieldParams(30, 20, 0.16f);
    ss2->Add(mineField, 0, wxALIGN_CENTER | wxALL, 5);
    vSizer->Add(ss2, 1, wxALIGN_CENTER);

    panel->SetSizer(vSizer);
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
