/*!

\author         Oliver Blaser

\date           02.07.2021

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#ifndef _FORMS_CONTROLS_MINEFIELD_H_
#define _FORMS_CONTROLS_MINEFIELD_H_

#include "forms/wxHelper.h"

#include "wx/vscroll.h"

namespace forms
{
    namespace controls
    {
        class mineField : public wxHVScrolledWindow
        {
        public:
            mineField(wxWindow* parent, wxWindowID id,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxNO_BORDER,
                const wxString& name = wxPanelNameStr);
            ~mineField();

            int getFieldHeight() const;
            int getFieldWidth() const;
            wxSize getPaintedFieldSize() const;
            float getRelNMines() const;
            int getTileSize() const;

            int setFieldParams(int nCol, int nRow, float relativeNumOfMines);
            int setTileSize(int size);

            void resetGame();

        private:
            int fieldWidth;
            int fieldHeight;
            int tileSize;
            float relNMines;

            // one could think about getters/setters for the colors
            int colorBG;
            int colorGrid;
            int colorTileOpen;
            int colorTileCovered;
            int colorMine;
            int colorMineExpl;
            int colorMineFound;
            int colorNumbers[8];

            bool firstClick = true;
            bool finnished = false;
            int* mines = nullptr;
            int* field = nullptr;

            wxPoint mouseLeftDownCoord;

            int cntMinesAround(int x, int y);
            void discoverField();
            bool allMinesFound();

            void OnDraw(wxDC& dc);
            void OnMouseLeftDown(wxMouseEvent& e);
            void OnMouseLeftUp(wxMouseEvent& e);
            void OnPaint(wxPaintEvent& e);
            void OnSize(wxSizeEvent& e);

            wxCoord OnGetRowHeight(size_t row) const;
            wxCoord OnGetColumnWidth(size_t col) const;

            wxDECLARE_EVENT_TABLE();
        };

        class MineFieldDiscoverEvent : public wxEvent
        {
        public:
            MineFieldDiscoverEvent(wxEventType eventType, int winid = 0) : wxEvent(winid, eventType), nLoops(0) {}

            int getNLoops() const { return nLoops; }
            void setNLoops(int value) { nLoops = value; }

            // see https://docs.wxwidgets.org/3.0/overview_events.html#overview_events_custom_ownclass
            virtual wxEvent* Clone() const { return new MineFieldDiscoverEvent(*this); }

        private:
            int nLoops;
        };
    }
}

wxDECLARE_EVENT(cEVT_MINEFIELD_DONE, wxCommandEvent);
wxDECLARE_EVENT(cEVT_MINEFIELD_FAIL, wxCommandEvent);
wxDECLARE_EVENT(cEVT_MINEFIELD_DISCOVER, forms::controls::MineFieldDiscoverEvent);

#endif // _FORMS_CONTROLS_MINEFIELD_H_
