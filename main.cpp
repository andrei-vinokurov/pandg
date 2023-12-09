#include <wx/app.h>
#include "MyFrame.h"
#include "MyPanel.h"
#include "MyDialog.h"
#include "MyPrintout.h"


class MyApp : public wxApp
{
public:
    virtual bool OnInit() override;
    virtual int OnExit() override;
};


wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}


int MyApp::OnExit()
{
    return wxApp::OnExit();
}