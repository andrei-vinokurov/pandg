#include "MyDialog.h"
#include "MyFrame.h"


MyDialog::MyDialog(wxPanel* parent) : wxDialog(parent, wxID_ANY, wxT("Редактирование"), wxDefaultPosition, wxSize (205, 200), wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP)
{
    m_parentPanelForDialog = parent;
    wxStaticText* m_textDialog1 = new wxStaticText(this, wxID_ANY, wxT("Введите название товара"), wxPoint (0,0), wxSize (200, 20));
    m_textctrlDialog1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,20), wxSize (200, 20));
    wxStaticText* m_textDialog2 = new wxStaticText(this, wxID_ANY, wxT("Укажите цену"), wxPoint (0,40), wxSize (200, 20));
    wxFloatingPointValidator<float> valDialog1(2, m_valueDialog1, wxNUM_VAL_ZERO_AS_BLANK);
    m_textctrlDialog2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,60), wxSize (200, 20), 0L, valDialog1);
    wxStaticText* m_textDialog3 = new wxStaticText(this, wxID_ANY, wxT("Укажите количество"), wxPoint (0,80), wxSize (200, 20));
    wxFloatingPointValidator<float> valDialog2(3, m_valueDialog2, wxNUM_VAL_ZERO_AS_BLANK);
    m_textctrlDialog3 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,100), wxSize (200, 20), 0L, valDialog2);
    wxButton* m_buttonOk = new wxButton (this, wxID_ANY, wxT("Ок"), wxPoint (35, 135), wxSize (50, 20));  
    wxButton* m_buttonCancel = new wxButton (this, wxID_ANY, wxT("Отмена"), wxPoint (115, 135), wxSize (50, 20)); 
    m_buttonOk->Bind(wxEVT_BUTTON, &MyDialog::OkDialog, this);
    m_buttonCancel->Bind(wxEVT_BUTTON, &MyDialog::CancelDialog, this);

}


void MyDialog::OkDialog(wxCommandEvent& event)
{
    MyFrame* frameFromFunc = (MyFrame*)m_parentPanelForDialog->GetParent();

    if (frameFromFunc->m_myPanel->m_listCtrl->GetItemText((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 1)==m_textctrlDialog1->GetValue() &&
    frameFromFunc->m_myPanel->m_listCtrl->GetItemText((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 2)==m_textctrlDialog2->GetValue() &&
    frameFromFunc->m_myPanel->m_listCtrl->GetItemText((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 3)==m_textctrlDialog3->GetValue())
    {
        wxMessageBox(wxT("Вы ничего не изменили"),
                 wxT("Нет изменений"), wxOK | wxICON_INFORMATION);
    }
    
    else
    {
        if(frameFromFunc->m_myPanel->m_listCtrl->GetItemText((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 1)!=m_textctrlDialog1->GetValue())
        {
            frameFromFunc->m_myPanel->m_listCtrl->SetItem ((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 1, m_textctrlDialog1->GetValue(), -1);
        }
        if(frameFromFunc->m_myPanel->m_listCtrl->GetItemText((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 2)!=m_textctrlDialog2->GetValue())
        {
            frameFromFunc->m_myPanel->m_listCtrl->SetItem ((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 2, m_textctrlDialog2->GetValue(), -1);
        }
        if(frameFromFunc->m_myPanel->m_listCtrl->GetItemText((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 3)!=m_textctrlDialog3->GetValue())
        {
            frameFromFunc->m_myPanel->m_listCtrl->SetItem ((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 3, m_textctrlDialog3->GetValue(), -1);
        }
        double priceInDialog;
        double quantityInDialog;
        m_textctrlDialog2->GetValue().ToDouble(&priceInDialog);
        m_textctrlDialog3->GetValue().ToDouble(&quantityInDialog);
        frameFromFunc->m_myPanel->m_listCtrlTotal->SetItemText (0, wxString::Format(wxT("%.2f"), (frameFromFunc->m_myPanel->TotalCost() - 
            (*(frameFromFunc->m_myPanel->m_vector[frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1])) + priceInDialog * quantityInDialog)));
        
        *(frameFromFunc->m_myPanel->m_vector[frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1]) = priceInDialog * quantityInDialog;
        
        frameFromFunc->m_myPanel->m_listCtrl->SetItem ((frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1), 4, wxString::Format(wxT("%.2f"), 
            *(frameFromFunc->m_myPanel->m_vector[frameFromFunc->m_myPanel->m_spinCtrl->GetValue()-1])), -1);

        Close();
    }
}


void MyDialog::CancelDialog(wxCommandEvent& event)
{
    Close();
}