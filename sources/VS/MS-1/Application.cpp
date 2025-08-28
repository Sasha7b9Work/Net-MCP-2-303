// 2022/04/27 11:10:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Application.h"
#include "Frame.h"


wxIMPLEMENT_APP(Application);


Application *Application::self = nullptr;


bool Application::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // we use a PNG image in our HTML page
    wxImage::AddHandler(new wxPNGHandler);

    // create and show the main application window
    Frame *frame = new Frame(_("ля-1"));
    frame->Show();

    Init();

    self = this;

    return true;
}
