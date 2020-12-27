/*!

\author         Oliver Blaser

\date           26.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#ifndef _MINEFIELD_H_
#define _MINEFIELD_H_

#include "../wxHelper.h"

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
                long style = 0,
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
            int* mines = nullptr;
            int* field = nullptr;

            int cntMinesAround(int x, int y);
            void discoverField();
            bool allMinesFound();

            void OnDraw(wxDC& dc);
            void OnMouseLeftClick(wxMouseEvent& e);
            void OnPaint(wxPaintEvent& e);
            void OnSize(wxSizeEvent& e);

            wxCoord OnGetRowHeight(size_t row) const;
            wxCoord OnGetColumnWidth(size_t col) const;

            wxDECLARE_EVENT_TABLE();
        };
    }
}

#endif // _MINEFIELD_H_
