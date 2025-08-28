// 2022/04/27 11:12:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/Timer.h"
#define WIN32_LEAN_AND_MEAN
#include "wx/wx.h"


class Frame : public wxFrame
{
public:
    Frame(const wxString &title);

    static Frame *Self() { return self; };

    void OnQuit(wxCommandEvent &);
    void OnAbout(wxCommandEvent &);
    void OnTimer(wxTimerEvent &);
    void OnTimerButton1(wxTimerEvent &);
    void OnTimerButton2(wxTimerEvent &);

    void OnMouseLeftDown(wxMouseEvent &);
    void OnMouseLeftUp(wxMouseEvent &);
    void OnMouseRightDown(wxMouseEvent &);
    void OnMouseRightUp(wxMouseEvent &);

    void BeginScene();

    void EndScene();

private:
    wxDECLARE_EVENT_TABLE();

    wxTimer timer;
    static Frame *self;

    TimeMeterMS meterButton1;       // Для кнопки 1
    TimeMeterMS meterButton2;       // Для кнопки 2
    wxTimer timerButton1;
    wxTimer timerButton2;
};
