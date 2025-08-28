// 2022/04/27 11:11:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Frame.h"
#include "Display/Display.h"
#include "Modules/ST7735/ST7735.h"
#include "Application.h"
#include "Menu/Menu.h"
#include "wx/statline.h"


// Здесь нарисованная картинка
static wxBitmap bitmap(Display::WIDTH, Display::HEIGHT);

// Здесь будем рисовать
static wxMemoryDC memDC;

Frame *Frame::self = nullptr;

static const int IMAGE_SCALE = 2;

enum
{
    TIMER_ID = 111,
    TIMER_BUTTON_ID_1,
    TIMER_BUTTON_ID_2
};

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
EVT_MENU(wxID_ABOUT, Frame::OnAbout)
EVT_MENU(wxID_EXIT, Frame::OnQuit)
wxEND_EVENT_TABLE()


class Screen : public wxPanel
{
public:
    Screen(wxWindow *parent) : wxPanel(parent)
    {
        SetMinSize({ Display::WIDTH * IMAGE_SCALE, Display::HEIGHT * IMAGE_SCALE });
        SetDoubleBuffered(true);
        Bind(wxEVT_PAINT, &Screen::OnPaint, this);
        Bind(wxEVT_LEFT_DOWN, &Frame::OnMouseLeftDown, Frame::Self());
        Bind(wxEVT_LEFT_UP, &Frame::OnMouseLeftUp, Frame::Self());
        Bind(wxEVT_RIGHT_DOWN, &Frame::OnMouseRightDown, Frame::Self());
        Bind(wxEVT_RIGHT_UP, &Frame::OnMouseRightUp, Frame::Self());
    }

    void OnPaint(wxPaintEvent &)
    {
        wxPaintDC dc(this);

        wxImage image = bitmap.ConvertToImage().Rescale(Display::WIDTH * IMAGE_SCALE, Display::HEIGHT * IMAGE_SCALE);

        dc.DrawBitmap(wxBitmap(image), 0, 0);
    }
};


static Screen *screen = nullptr;


Frame::Frame(const wxString &title)
    : wxFrame((wxFrame *)NULL, wxID_ANY, title)
{
    SetIcon(wxICON(sample));

    wxMenu *menuFile = new wxMenu;

    menuFile->Append(wxID_ABOUT);
    menuFile->Append(wxID_EXIT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, _("&File"));

    wxFrameBase::SetMenuBar(menuBar);

    self = this;

    screen = new Screen(this);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(screen);
    SetSizer(sizer);

    Bind(wxEVT_PAINT, &Frame::OnPaint, this);
    Bind(wxEVT_TIMER, &Frame::OnTimer, this, TIMER_ID);
    Bind(wxEVT_TIMER, &Frame::OnTimerButton1, this, TIMER_BUTTON_ID_1);
    Bind(wxEVT_TIMER, &Frame::OnTimerButton2, this, TIMER_BUTTON_ID_2);

    timerButton1.SetOwner(this, TIMER_BUTTON_ID_1);
    timerButton2.SetOwner(this, TIMER_BUTTON_ID_2);
    timer.SetOwner(this, TIMER_ID);

    SetClientSize(Display::WIDTH * IMAGE_SCALE, Display::HEIGHT * IMAGE_SCALE);

    wxTopLevelWindowBase::SetMinSize(GetSize());
    wxTopLevelWindowBase::SetMaxSize(GetSize());

    const int maxWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    const int maxHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);

    int x = (maxWidth - GetSize().x) / 2;
    int y = (maxHeight - GetSize().y) / 2;

    SetPosition({ x, y });

    timer.StartOnce(25);
}


void Frame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}

void Frame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
    wxBoxSizer *topsizer;
    wxDialog dlg(this, wxID_ANY, wxString(_("About")));

    topsizer = new wxBoxSizer(wxVERTICAL);

#if wxUSE_STATLINE
    topsizer->Add(new wxStaticLine(&dlg, wxID_ANY), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
#endif // wxUSE_STATLINE

    wxButton *bu1 = new wxButton(&dlg, wxID_OK, _("OK"));
    bu1->SetDefault();

    topsizer->Add(bu1, 0, wxALL | wxALIGN_RIGHT, 15);

    dlg.SetSizer(topsizer);
    topsizer->Fit(&dlg);

    dlg.ShowModal();
}


void Frame::OnTimer(wxTimerEvent &)
{
    timer.Stop();

    Application::Self()->Update();

    timer.Start(25);
}


void Frame::BeginScene()
{
}


void Frame::EndScene()
{

}


void Frame::OnMouseLeftDown(wxMouseEvent &)
{
    meterButton1.Reset();
    timerButton1.StartOnce(500);
}


void Frame::OnMouseRightDown(wxMouseEvent &)
{
    meterButton2.Reset();
    timerButton2.StartOnce(500);
}


void Frame::OnMouseLeftUp(wxMouseEvent &)
{
    if (meterButton1.ElapsedTime() < 500)
    {
        Menu::ShortPress(Key::_1);
        timerButton1.Stop();
    }
}


void Frame::OnMouseRightUp(wxMouseEvent &)
{
    if (meterButton2.ElapsedTime() < 500)
    {
        Menu::ShortPress(Key::_2);
        timerButton2.Stop();
    }
}


void Frame::OnTimerButton1(wxTimerEvent &)
{
    Menu::LongPress(Key::_1);
}


void Frame::OnTimerButton2(wxTimerEvent &)
{
    Menu::LongPress(Key::_2);
}


static wxColour ConvertColor(Color::E e)
{
    uint16 value = Color::colors[e];

    float b = (float)BLUE_FROM_COLOR(value);
    float g = (float)GREEN_FROM_COLOR(value);
    float r = (float)RED_FROM_COLOR(value);

    uint8 blue  = (uint8)((b / 31.0f) * 255);
    uint8 green = (uint8)((g / 63.0f) * 255);
    uint8 red   = (uint8)((r / 31.0f) * 255);

    return wxColour(red, green, blue);
}


void ST7735::WritePoint(int /*x*/, int /*y*/, uint16 /*color*/)
{

}


void ST7735::WriteBuffer(int x0, int y0, int width, int height)
{
    static const wxColour colors[16] =
    {
        ConvertColor((Color::E)0),
        ConvertColor((Color::E)1),
        ConvertColor((Color::E)2),
        ConvertColor((Color::E)3),
        ConvertColor((Color::E)4),
        ConvertColor((Color::E)5),
        ConvertColor((Color::E)6),
        ConvertColor((Color::E)7),
        ConvertColor((Color::E)8),
        ConvertColor((Color::E)9)
    };

    memDC.SelectObject(bitmap);

    static wxPen pen = *wxWHITE_PEN;

    for (int y = y0; y < y0 + height; y++)
    {
        uint8 *points = Display::Buffer::GetLine(x0, y);

        uint8 value = *points;

        for (int x = x0; x < x0 + width; x += 2)
        {
            pen.SetColour(colors[value >> 4]);

            memDC.SetPen(pen);

            memDC.DrawPoint(x + 1, y);

            pen.SetColour(colors[value & 0x0f]);

            memDC.SetPen(pen);

            memDC.DrawPoint(x, y);

            value = *(++points);
        }
    }

    memDC.SelectObject(wxNullBitmap);

    screen->Refresh();
}
