#ifndef MYPRINTOUT_H
#define MYPRINTOUT_H

//подключение заголовочных файлов wxWidgets и приложения, используемых в этом файле (h и cpp)
#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/cmndata.h>
#include "MyFrame.h"


class MyPrintout : public wxPrintout
{
public:
    MyPrintout(MyFrame* frame, wxPrintDialogData* printDlgData, const wxString& title = "My printout") : wxPrintout(title)
    {
        m_frame = frame;
        m_printDlgData = printDlgData;
    }
    virtual void OnPreparePrinting () override;
    virtual bool OnPrintPage(int page) override;
    virtual bool HasPage(int pageNum) override;
    virtual void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo) override;
    int m_numPages;

private:
    MyFrame* m_frame;
    wxPrintDialogData* m_printDlgData;
};

#endif