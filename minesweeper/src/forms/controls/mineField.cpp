/*!

\author         Oliver Blaser

\date           29.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#include "mineField.h"

#include "wx/dcclient.h"
#include "wx/dcbuffer.h"
#include "wx/dcmemory.h"

#if _DEBUG
#define DISCOVERFIELD_DISPLAY_STATUS 0
#endif


wxBEGIN_EVENT_TABLE(forms::controls::mineField, wxHVScrolledWindow)
EVT_LEFT_UP(forms::controls::mineField::OnMouseLeftClick)
EVT_PAINT(forms::controls::mineField::OnPaint)
wxEND_EVENT_TABLE()



forms::controls::mineField::mineField(wxWindow* parent, wxWindowID id,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name) :
    wxHVScrolledWindow(parent, id, pos, size, style, name), tileSize(20)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    colorBG = 0xababab;
    colorTileOpen = 0xe8e8e8;
    colorTileCovered = 0x909090;
    colorGrid = 0xa0a0a0;
    colorMine = 0x042133;
    colorMineExpl = 0x000096;
    colorMineFound = 0x005000;

    // https://colordesigner.io/gradient-generator
    colorNumbers[0] = 0xa33400;
    colorNumbers[1] = 0x00008b;
    colorNumbers[2] = 0x0000c3;
    colorNumbers[3] = 0x0000ff;
    colorNumbers[4] = 0x0000ff;
    colorNumbers[5] = 0x0000ff;
    colorNumbers[6] = 0x0000ff;
    colorNumbers[7] = 0x0000ff;

    SetBackgroundColour(wxColour(colorBG));

    srand(time(0));

    Bind(wxEVT_SIZE, &forms::controls::mineField::OnSize, this);

    setFieldParams(10, 10, 0.15f);
}

forms::controls::mineField::~mineField()
{
    delete[] field;
    delete[] mines;
}

int forms::controls::mineField::getFieldHeight() const
{
    return fieldHeight;
}

int forms::controls::mineField::getFieldWidth() const
{
    return fieldWidth;
}

wxSize forms::controls::mineField::getPaintedFieldSize() const
{
    return wxSize((fieldWidth * tileSize), (fieldHeight * tileSize));
}

int forms::controls::mineField::getTileSize() const
{
    return 0;
}

void forms::controls::mineField::resetGame()
{
    delete[] field;
    delete[] mines;

    field = new int[fieldWidth * fieldHeight];
    mines = new int[fieldWidth * fieldHeight];

    for (int x = 0; x < fieldWidth; ++x)
    {
        for (int y = 0; y < fieldHeight; ++y)
        {
            field[y * fieldWidth + x] = -1;
            mines[y * fieldWidth + x] = 0;
        }
    }

    firstClick = true;
    finnished = false;

    Refresh();
}

int forms::controls::mineField::setFieldParams(int nCol, int nRow, float relativeNumOfMines)
{
    if ((nCol > 0) && (nRow > 0) && (relativeNumOfMines > 0.0f))
    {
        fieldWidth = nCol;
        fieldHeight = nRow;
        relNMines = relativeNumOfMines;

        SetSize(getPaintedFieldSize());
        SetMinSize(getPaintedFieldSize());

        SetRowColumnCount(fieldHeight, fieldWidth);
        wxVarHScrollHelper::RefreshAll();
        wxVarVScrollHelper::RefreshAll();
        //Refresh(); is done in resetGame()

        resetGame();

        return 0;
    }

    return 1;
}

int forms::controls::mineField::setTileSize(int size)
{
    if (size >= 0)
    {
        tileSize = size;

        SetSize(getPaintedFieldSize());
        SetMinSize(getPaintedFieldSize());
        this->Refresh();

        return 0;
    }

    return 1;
}

int forms::controls::mineField::cntMinesAround(int x, int y)
{
    int cntMines = 0;

    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            int tmpX = x + i;
            int tmpY = y + j;

            if ((tmpX >= 0) && (tmpX < fieldWidth) && (tmpY >= 0) && (tmpY < fieldHeight) && ((i != 0) || (j != 0)))
            {
                if (mines[tmpY * fieldWidth + tmpX]) ++cntMines;
            }
        }
    }

    return cntMines;
}

void forms::controls::mineField::discoverField()
{
    int cntLoops = 0;

    bool discoveringTiles;
    do
    {
        discoveringTiles = false;

        for (int x = 0; x < fieldWidth; ++x)
        {
            for (int y = 0; y < fieldHeight; ++y)
            {
                if (field[y * fieldWidth + x] == 0)
                {
                    for (int i = -1; i < 2; ++i)
                    {
                        for (int j = -1; j < 2; ++j)
                        {
                            int tmpX = x + i;
                            int tmpY = y + j;

                            if ((tmpX >= 0) && (tmpX < fieldWidth) && (tmpY >= 0) && (tmpY < fieldHeight) && (field[tmpY * fieldWidth + tmpX] < 0))
                            {
                                field[tmpY * fieldWidth + tmpX] = cntMinesAround(tmpX, tmpY);
                                discoveringTiles = true;
                            }
                        }
                    }
                }
            }
        }

        if (cntLoops >= 0) ++cntLoops;

    } while (discoveringTiles);

    MineFieldDiscoverEvent* tmpEvt = new MineFieldDiscoverEvent(cEVT_MINEFIELD_DISCOVER);
    tmpEvt->setNLoops(cntLoops);
    wxQueueEvent(this, tmpEvt);

#if DISCOVERFIELD_DISPLAY_STATUS
    if (cntLoops > 1)
    {
        char itoaBuff[30];
        wxMessageBox(wxString("discoverField cntLoops: ") + wxString(_itoa(cntLoops, itoaBuff, 10)), " ");
    }
#endif
}

bool forms::controls::mineField::allMinesFound()
{
    bool won = true;

    for (int i = 0; i < fieldWidth; ++i)
    {
        for (int j = 0; j < fieldHeight; ++j)
        {
            if ((field[j * fieldWidth + i] < 0) && (mines[j * fieldWidth + i] == 0))
            {
                won = false;
                i = fieldWidth;
                j = fieldHeight;
            }
        }
    }

    return won;
}

void forms::controls::mineField::OnDraw(wxDC& dc)
{
    dc.Clear();

    wxPosition visBeg = GetVisibleBegin();
    wxPosition visEnd = GetVisibleEnd();

    wxBrush brush = dc.GetBrush();
    wxPen pen = dc.GetPen();
    wxFont font = dc.GetFont();

    pen.SetColour(colorGrid);
    pen.SetStyle(wxPENSTYLE_SOLID);
    pen.SetWidth(1);
    dc.SetPen(pen);
    //dc.SetPen(*wxTRANSPARENT_PEN);

    font.SetPixelSize(wxSize(tileSize * 0.5, tileSize * 0.8));
    font.SetFamily(wxFontFamily::wxFONTFAMILY_TELETYPE);
    font.SetWeight(wxFontWeight::wxFONTWEIGHT_BOLD);
    dc.SetFont(font);

    for (int x = visBeg.GetCol(); x < visEnd.GetCol(); ++x)
    {
        for (int y = visBeg.GetRow(); y < visEnd.GetRow(); ++y)
        {
            int fieldValue = field[y * fieldWidth + x];

            if (fieldValue < 0)
            {
                brush.SetStyle(wxBRUSHSTYLE_SOLID);
                brush.SetColour(colorTileCovered);
            }
            else if (fieldValue < 9)
            {
                brush.SetStyle(wxBRUSHSTYLE_SOLID);
                brush.SetColour(colorTileOpen);
            }
            else if (fieldValue == 10)
            {
                brush.SetStyle(wxBRUSHSTYLE_SOLID);
                brush.SetColour(colorMine);
            }
            else if (fieldValue == 11)
            {
                brush.SetStyle(wxBRUSHSTYLE_SOLID);
                brush.SetColour(colorMineExpl);
            }
            else if (fieldValue == 12)
            {
                brush.SetStyle(wxBRUSHSTYLE_SOLID);
                brush.SetColour(colorMineFound);
            }
            else
            {
                brush.SetStyle(wxBRUSHSTYLE_CROSSDIAG_HATCH);
                brush.SetColour(wxColour(220, 0, 0));
            }

            dc.SetBrush(brush);

            if (fieldValue >= 10)
            {
                wxBrush tmpBrush = brush;
                tmpBrush.SetColour(colorTileCovered);
                dc.SetBrush(tmpBrush);
                dc.DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize);
                dc.SetBrush(brush);
                dc.DrawCircle((x * tileSize + (tileSize * 0.5)), (y * tileSize + (tileSize * 0.5)), tileSize * 0.4);
            }
            else
            {
                dc.DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize);
            }

            if ((fieldValue > 0) && (fieldValue < 9))
            {
                dc.SetTextForeground(colorNumbers[fieldValue - 1]);
                dc.DrawText(wxString(1, (char)(fieldValue + 0x30)), (x * tileSize + (tileSize * 0.25)), (y * tileSize + (tileSize * 0.1)));
            }
        }
    }
}

float forms::controls::mineField::getRelNMines() const
{
    return relNMines;
}

void forms::controls::mineField::OnMouseLeftClick(wxMouseEvent& e)
{
    int eventRiseFlags = 0;

    wxPosition visBeg = GetVisibleBegin();
    int x = e.GetX() / tileSize + visBeg.GetCol();
    int y = e.GetY() / tileSize + visBeg.GetRow();

    if (!finnished)
    {
        if (firstClick)
        {
            firstClick = false;

            int mines = fieldWidth * fieldHeight * relNMines;

            while (mines)
            {
                int newMinePos = rand() % (fieldWidth * fieldHeight);

                if ((newMinePos != (y * fieldWidth + x)) && (this->mines[newMinePos] == 0))
                {
                    this->mines[newMinePos] = 1;
                    --mines;
                }
            }
        }

        if (mines[y * fieldWidth + x])
        {
            for (int i = 0; i < fieldWidth; ++i)
            {
                for (int j = 0; j < fieldHeight; ++j)
                {
                    if (mines[j * fieldWidth + i]) field[j * fieldWidth + i] = 10;
                }
            }

            field[y * fieldWidth + x] = 11;

            eventRiseFlags |= 0x01;
        }
        else
        {
            field[y * fieldWidth + x] = cntMinesAround(x, y);
        }

        discoverField();

        if (allMinesFound())
        {
            for (int i = 0; i < fieldWidth; ++i)
            {
                for (int j = 0; j < fieldHeight; ++j)
                {
                    if (mines[j * fieldWidth + i]) field[j * fieldWidth + i] = 12;
                }
            }

            eventRiseFlags |= 0x02;
        }

        this->Refresh(false);

        if (eventRiseFlags & 0x01)
        {
            finnished = true;

            wxCommandEvent* tmpEvt = new wxCommandEvent(cEVT_MINEFIELD_FAIL);
            wxQueueEvent(this, tmpEvt);
        }

        if (eventRiseFlags & 0x02)
        {
            finnished = true;

            wxCommandEvent* tmpEvt = new wxCommandEvent(cEVT_MINEFIELD_DONE);
            wxQueueEvent(this, tmpEvt);
        }
    }

    e.Skip();
}

void forms::controls::mineField::OnPaint(wxPaintEvent& e)
{
    wxBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    this->OnDraw(dc);
}

void forms::controls::mineField::OnSize(wxSizeEvent& e)
{
    wxSize size = GetSize();
    wxSize minSize = GetMinSize();

    if ((size.x >= minSize.x) && (size.y >= minSize.y))
    {
        // hide the scroll bars

        Unbind(wxEVT_SIZE, &forms::controls::mineField::OnSize, this);

        SetSize(GetSize() + wxSize(20, 20));
        wxVarHScrollHelper::RefreshAll();
        wxVarVScrollHelper::RefreshAll();
        Refresh();
        SetSize(GetSize() - wxSize(20, 20));

        Bind(wxEVT_SIZE, &forms::controls::mineField::OnSize, this);
    }

    e.Skip();
}

wxCoord forms::controls::mineField::OnGetRowHeight(size_t row) const
{
    return wxCoord(tileSize);
}

wxCoord forms::controls::mineField::OnGetColumnWidth(size_t col) const
{
    return wxCoord(tileSize);
}

wxDEFINE_EVENT(cEVT_MINEFIELD_DONE, wxCommandEvent);
wxDEFINE_EVENT(cEVT_MINEFIELD_FAIL, wxCommandEvent);
wxDEFINE_EVENT(cEVT_MINEFIELD_DISCOVER, forms::controls::MineFieldDiscoverEvent);
