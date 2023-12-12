#ifndef MYDIALOG_H
#define MYDIALOG_H

//подключение заголовочных файлов wxWidgets, используемых в этом файле (h и cpp)
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/validate.h>
#include <wx/valnum.h>
#include <wx/button.h>
#include <wx/msgdlg.h>


//Класс MyDialog для редактирования ранее введенных пользователем данных
class MyDialog : public wxDialog
{
public:
    MyDialog(wxPanel* parent);
    void OkDialog(wxCommandEvent& event);
    void CancelDialog(wxCommandEvent& event);
    float* m_valueDialog1 = 0;
    float* m_valueDialog2 = 0;
    wxStaticText* m_textDialog1;
    wxTextCtrl* m_textctrlDialog1;
    wxStaticText* m_textDialog2;
    wxTextCtrl* m_textctrlDialog2;
    wxStaticText* m_textDialog3;
    wxTextCtrl* m_textctrlDialog3;
    wxPanel* m_parentPanelForDialog;

private:
    wxButton* m_buttonOk;
    wxButton* m_buttonCancel;
};

#endif