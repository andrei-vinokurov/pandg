#ifndef MYFRAME_H
#define MYFRAME_H

#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/log.h>
#include <wx/textfile.h>
#include <wx/printdlg.h>
#include "MyPanel.h"
#include "MyDialog.h"
#include "res.h"


class MyFrame : public wxFrame
{
public:
    MyFrame();
    MyPanel* m_myPanel;
    MyDialog* m_dialogInFrame;
    wxPrintData m_printData;
    wxPageSetupDialogData m_pageSetupData;

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnPageSetup(wxCommandEvent& event);
    void OnPreview(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
};

#endif