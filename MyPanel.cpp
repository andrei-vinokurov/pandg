#include "MyPanel.h"
#include "MyFrame.h"


unsigned int MyPanel::s_count = 0;
unsigned int MyPanel::s_countDelete = 0;


MyPanel::MyPanel(wxPanel* parent) : wxPanel (parent, wxID_ANY, wxDefaultPosition, wxSize (710, 340), wxBORDER_SUNKEN)
{
    m_parentPanel = parent;
    wxPanel* m_childPanel1 = new wxPanel (this, ID_Panel1, wxPoint (200,310), wxSize (70, 20));
    wxPanel* m_childPanel2 = new wxPanel (this, ID_Panel2, wxPoint (0,190), wxSize (200, 150));
    m_childPanel2->Show(false);    
   
    wxStaticText* text1 = new wxStaticText(this, wxID_ANY, "Enter a name of product", wxPoint (0,0), wxSize (200, 20));
    m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,20), wxSize (200, 20));
    wxStaticText* text2 = new wxStaticText(this, wxID_ANY, "Enter a price", wxPoint (0,40), wxSize (200, 20));
    wxFloatingPointValidator<float> val1(2, m_value1, wxNUM_VAL_ZERO_AS_BLANK);

    m_textCtrl2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,60), wxSize (200, 20), 0L, val1);
    wxStaticText* text3 = new wxStaticText(this, wxID_ANY, "Enter a quantity", wxPoint (0,80), wxSize (200, 20));
    wxFloatingPointValidator<float> val2(3, m_value2, wxNUM_VAL_ZERO_AS_BLANK);
    m_textCtrl3 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,100), wxSize (200, 20), 0L, val2);
    wxButton* button1 = new wxButton (this, wxID_ANY, "Add", wxPoint (50,130), wxSize (100, 20));
    wxButton* button2 = new wxButton (this, wxID_ANY, "Edit/Delete", wxPoint (50,170), wxSize (100, 20)); 

    wxStaticText* m_text = new wxStaticText(m_childPanel2, wxID_ANY, "Select list number", wxPoint (20, 20), wxSize (160, 20), wxALIGN_CENTRE_HORIZONTAL);  

    wxButton* button3 = new wxButton (m_childPanel2, wxID_ANY, "Edit", wxPoint (20, 90), wxSize (50, 20)); 
    wxButton* button4 = new wxButton (m_childPanel2, wxID_ANY, "Delete", wxPoint (75, 90), wxSize (50, 20)); 
    wxButton* button5 = new wxButton (m_childPanel2, wxID_ANY, "Cancel", wxPoint (130, 90), wxSize (50, 20));
    
    m_spinCtrl = new wxSpinCtrl(m_childPanel2, wxID_ANY, wxEmptyString, wxPoint (70, 50), wxSize (60, 20), wxSP_ARROW_KEYS | wxALIGN_CENTRE_HORIZONTAL, 1);

    wxButton* button6 = new wxButton (m_childPanel1, wxID_ANY, "Clear all", wxPoint (0,0), wxSize (70, 20));

    m_listCtrl = new wxListCtrl (this, wxID_ANY, wxPoint (200,0), wxSize (510, 300), wxLC_REPORT);
    m_listCtrl->AppendColumn (m_nameColumn1, wxLIST_FORMAT_CENTER, 30);
    m_listCtrl->AppendColumn (m_nameColumn2, wxLIST_FORMAT_CENTER, 150);
    m_listCtrl->AppendColumn (m_nameColumn3, wxLIST_FORMAT_CENTER, 110);
    m_listCtrl->AppendColumn (m_nameColumn4, wxLIST_FORMAT_CENTER, 110);
    m_listCtrl->AppendColumn (m_nameColumn5, wxLIST_FORMAT_CENTER, 110);

    m_listCtrlTotal = new wxListCtrl (this, wxID_ANY, wxPoint (600,300), wxSize (110, 40), wxLC_REPORT);
    m_listCtrlTotal->AppendColumn (m_nameColumn6, wxLIST_FORMAT_CENTER, 110);
    m_listCtrlTotal->InsertItem (0, "0");

    button1->Bind(wxEVT_BUTTON, &MyPanel::Adding, this);
    button2->Bind(wxEVT_BUTTON, &MyPanel::EditDelete, this);
    button3->Bind(wxEVT_BUTTON, &MyPanel::Editing, this);
    button4->Bind(wxEVT_BUTTON, &MyPanel::DeletingOne, this);
    button5->Bind(wxEVT_BUTTON, &MyPanel::Canceling, this);
    button6->Bind(wxEVT_BUTTON, &MyPanel::Deleting, this);
    
}


void MyPanel::Adding (wxCommandEvent& event)
{
    if (!m_textCtrl1->IsEmpty() && !m_textCtrl2->IsEmpty() && !m_textCtrl3->IsEmpty()){      
    m_listCtrl->InsertItem (TotalCount(), "");
    m_listCtrl->SetItem (TotalCount(), 0, wxString::Format(wxT("%d"), TotalCount()+1), -1);
    m_listCtrl->SetItem (TotalCount(), 1, m_textCtrl1->GetValue(), -1);
    m_listCtrl->SetItem (TotalCount(), 2, m_textCtrl2->GetValue(), -1);
    double price;
    m_textCtrl2->GetValue().ToDouble(&price);
    m_listCtrl->SetItem (TotalCount(), 3, m_textCtrl3->GetValue(), -1);
    double quantity;
    m_textCtrl3->GetValue().ToDouble(&quantity);
    float* total = new float (price*quantity);
    m_listCtrl->SetItem (TotalCount(), 4, wxString::Format(wxT("%.2f"), *total), -1);
    m_vector.push_back(total);
    m_listCtrlTotal->SetItemText (0, wxString::Format(wxT("%.2f"), TotalCost()));
    m_textCtrl1->SetValue("");
    m_textCtrl2->SetValue("");
    m_textCtrl3->SetValue("");
    s_count++;
    }
    else
    {
        wxMessageBox("The name of product, price or quantity is not correct.",
                 "Error", wxOK | wxICON_INFORMATION);
    }
}


unsigned int MyPanel::TotalCount()
{
    return (s_count-s_countDelete);
}


float MyPanel::TotalCost()
{
    float cost = 0;
    for(unsigned int i = 0; i < m_vector.size(); ++i)
    {
        cost += *m_vector[i];
    }
    return cost;
}


void MyPanel::EditDelete(wxCommandEvent& event)
{
    if(m_vector.empty())
    {
        wxMessageBox("The list of product is empty.",
                 "Empty list", wxOK | wxICON_INFORMATION);
    }
    else
    {
        FindWindow (ID_Panel2)->Show(true);
        FindWindow (ID_Panel1)->Show(false);
        
    }
}


void MyPanel::Editing(wxCommandEvent& event)
{
    if (m_vector.size() > (m_spinCtrl->GetValue()-1))
    {

            MyFrame* frameFromDialog = (MyFrame*) m_parentPanel->GetParent();
            MyDialog* dlg = frameFromDialog->m_dialogInFrame;
            dlg->m_textctrlDialog1->SetValue(m_listCtrl->GetItemText((m_spinCtrl->GetValue()-1), 1));
            dlg->m_textctrlDialog2->SetValue(m_listCtrl->GetItemText((m_spinCtrl->GetValue()-1), 2));
            dlg->m_textctrlDialog3->SetValue(m_listCtrl->GetItemText((m_spinCtrl->GetValue()-1), 3));

            dlg->ShowModal();

    }
    else
    {
            wxMessageBox("This name is not in the list.",
                 "Name missing", wxOK | wxICON_INFORMATION);
            
    }
    FindWindow(ID_Panel2)->Show(false);
    FindWindow(ID_Panel1)->Show(true);
}


void MyPanel::DeletingOne(wxCommandEvent& event)
{
    if (m_vector.size() > (m_spinCtrl->GetValue()-1))
    {
            m_listCtrl->DeleteItem(m_spinCtrl->GetValue()-1);
            s_countDelete++;
            for (unsigned int i = (m_spinCtrl->GetValue()-1); i < TotalCount(); i++)
            {
                m_listCtrl->SetItem (i, 0, wxString::Format(wxT("%d"), i+1), -1);
            }
            m_listCtrlTotal->SetItemText (0, wxString::Format(wxT("%.2f"), (TotalCost()-*m_vector[m_spinCtrl->GetValue()-1])));
            delete m_vector[m_spinCtrl->GetValue()-1];
            m_vector[m_spinCtrl->GetValue()-1] = 0;
            m_vector.erase(m_vector.begin()+m_spinCtrl->GetValue()-1);
    }
    else
    {
            wxMessageBox("This name is not in the list.",
                 "Name missing", wxOK | wxICON_INFORMATION);
            
    }
    FindWindow(ID_Panel2)->Show(false);
    FindWindow(ID_Panel1)->Show(true);
}


void MyPanel::Canceling(wxCommandEvent& event)
{
    FindWindow(ID_Panel2)->Show(false);
    FindWindow(ID_Panel1)->Show(true);
}


void MyPanel::Deleting (wxCommandEvent& event)
{
    m_listCtrl->DeleteAllItems ();
    for(unsigned int i = 0; i < m_vector.size(); ++i)
    {
        delete m_vector[i];
        m_vector[i] = 0;
    }
    m_vector.clear();
    s_count = 0;
    s_countDelete = 0;
    m_listCtrlTotal->SetItemText (0, "0");
}