/*!

\author         Oliver Blaser

\date           26.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#ifndef _FORMS_MAIN_H_
#define _FORMS_MAIN_H_

#include "wxHelper.h"

#include "controls/mineField.h"

namespace forms
{
    class main : public wxFrame
    {
    public:
        main(int x, int y, int w, int h);
        ~main();

    private:
        wxButton* buttonReset = nullptr;
        wxStaticText* labelStatus = nullptr;
        controls::mineField* mineField = nullptr;

        void initControls();

        void buttonReset_click(wxCommandEvent& e);
        void mineField_finnished(wxEvent& e);
        void mineField_mineExploded(wxEvent& e);

        wxDECLARE_EVENT_TABLE();
    };
}

#endif // _FORMS_MAIN_H_
