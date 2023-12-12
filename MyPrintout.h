#ifndef MYPRINTOUT_H
#define MYPRINTOUT_H

//подключение заголовочных файлов wxWidgets и приложения, используемых в этом файле (h и cpp)
#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/cmndata.h>
#include "MyFrame.h"


//класс MyPrintout отрисовывает изображение страницы печати и предварительного просмотра
class MyPrintout : public wxPrintout
{
public:
    MyPrintout(MyFrame* frame, wxPrintDialogData* printDlgData, const wxString& title = "My printout") : wxPrintout(title)
    {
        m_frame = frame;
        m_printDlgData = printDlgData;
    }
    virtual void OnPreparePrinting () override; //определяет m_numPages
    virtual bool OnPrintPage(int page) override; //отрисовывает изображение страницы печати и предварительного просмотра
    virtual bool HasPage(int pageNum) override; //определяет есть ли страница в документе
    virtual void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo) override; //определяет мин. и макс. количество страниц
    int m_numPages; //член данных, содержащий информацию о количестве страниц печати/предварительного просмотра

private:
    MyFrame* m_frame; //член данных для связи с окном, из которого происходит вызов
    wxPrintDialogData* m_printDlgData; //член данных для связи с настройками печати
};

#endif