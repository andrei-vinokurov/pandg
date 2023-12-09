#ifndef MYPANEL_H
#define MYPANEL_H

#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/spinCtrl.h>
#include <wx/stattext.h>
#include "MyDialog.h"


class MyPanel : public wxPanel
{
public:
    MyPanel(wxPanel* parent);
    wxPanel* m_parentPanel;
    wxListCtrl* m_listCtrl;
    wxSpinCtrl* m_spinCtrl; 
    wxVector<float*> m_vector;
    wxListCtrl* m_listCtrlTotal;
    void Adding(wxCommandEvent& event);
    void EditDelete(wxCommandEvent& event);
    void DeletingOne(wxCommandEvent& event);
    void Editing(wxCommandEvent& event);
    void Canceling(wxCommandEvent& event);
    void Deleting(wxCommandEvent& event);
    static unsigned int TotalCount();
    float TotalCost();
    wxString m_nameColumn1 = "#";
    wxString m_nameColumn2 = "name of product";
    wxString m_nameColumn3 = "price";
    wxString m_nameColumn4 = "quantity";
    wxString m_nameColumn5 = "total";
    wxString m_nameColumn6 = "total cost";
   
private:
    wxPanel* m_childPanel1;
    wxPanel* m_childPanel2;  
    wxTextCtrl* m_textCtrl1;
    wxTextCtrl* m_textCtrl2;
    wxTextCtrl* m_textCtrl3;
    wxStaticText* m_text;
    static unsigned int s_count;
    static unsigned int s_countDelete;
    float* m_value1 = 0;
    float* m_value2 = 0; 
};


enum
{
    ID_Panel, ID_Panel1, ID_Panel2
};

#endif