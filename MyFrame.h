#ifndef MYFRAME_H
#define MYFRAME_H

//подключение заголовочных файлов wxWidgets и приложения, используемых в этом файле (h и cpp)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/log.h>
#include <wx/textfile.h>
#include <wx/printdlg.h>
#include "MyPanel.h"
#include "MyDialog.h"
#include "res.h"


//основное окно приложения
class MyFrame : public wxFrame
{
public:
    MyFrame();
    MyPanel* m_myPanel; //окно класса MyPanel, где расположены основные объекты
    MyDialog* m_dialogInFrame; //диалоговое окно для редактирования
    wxPrintData m_printData; //член данных, содержащий данные для печати
    wxPageSetupDialogData m_pageSetupData; //член данных, соддержащий данные о параметрах страницы

private:
    void OnExit(wxCommandEvent& event); //выход
    void OnAbout(wxCommandEvent& event); //о программе
    void OnPrint(wxCommandEvent& event); //печать
    void OnPageSetup(wxCommandEvent& event); //параметры страницы
    void OnPreview(wxCommandEvent& event); //предварительный просмотр
    void OnSave(wxCommandEvent& event); //сохранить
};

#endif