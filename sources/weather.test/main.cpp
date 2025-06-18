#include "MainFrame.h"

#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MainFrame *frame = new MainFrame("Hello Everyone!", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}
