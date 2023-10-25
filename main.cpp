#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/validate.h>
#include <wx/valnum.h>
#include <wx/spinctrl.h>
#include "res.h"
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel* parent);

    void Adding(wxCommandEvent& event);
    void EditDelete(wxCommandEvent& event);
    void DeletingOne(wxCommandEvent& event);
    void Editing(wxCommandEvent& event);
    void Canceling(wxCommandEvent& event);
    void Deleting(wxCommandEvent& event);
    static unsigned int TotalCount();
    float TotalCost();
    //int VS (wxVector<float*> vec);
    //void ChangeIdOfListCtrl(unsigned int k);

    //int ValueSpinCtrl();

    

private:

    wxPanel* childPanel;
    wxPanel* childPanel1;
    wxSpinCtrl* spinctrl; 
    wxListCtrl* listCtrl;
    wxListCtrl* listCtrltotal;
    wxTextCtrl* textctrl1;
    wxTextCtrl* textctrl2;
    wxTextCtrl* textctrl3;
    wxStaticText* text4;
    wxStaticText* text5;
    //wxString *str;
    
    //wxButton *button5;
    static unsigned int count;
    static unsigned int countDelete;

    float* m_value1 = 0;
    float* m_value2 = 0;
    wxVector<float*> vector;
    
    //wxDialog* myDialog;

};

unsigned int LeftPanel::count = 0;
unsigned int LeftPanel::countDelete = 0;

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    //wxPanel *panel;
    //LeftPanel *leftPanel;
    //void OnCreate(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

};

enum
{
    ID_Create = 1, ID_Panel, ID_Panel1, ID_Panel2, ID_Spin, ID_Dialog
};
 
wxIMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

LeftPanel::LeftPanel(wxPanel* parent) : wxPanel (parent, wxID_ANY, wxDefaultPosition, wxSize (710, 340), wxBORDER_SUNKEN)
{
    wxPanel* childPanel1 = new wxPanel (this, ID_Panel1, wxPoint (200,310), wxSize (70, 20));
    wxPanel* childPanel = new wxPanel (this, ID_Panel2, wxPoint (0,190), wxSize (200, 150));
    childPanel->Show(false);    
   
    wxStaticText* text1 = new wxStaticText(this, wxID_ANY, "Enter a name of product", wxPoint (0,0), wxSize (200, 20));
    textctrl1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,20), wxSize (200, 20));
    wxStaticText* text2 = new wxStaticText(this, wxID_ANY, "Enter a price", wxPoint (0,40), wxSize (200, 20));
    wxFloatingPointValidator<float> val1(2, m_value1, wxNUM_VAL_ZERO_AS_BLANK);

    textctrl2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,60), wxSize (200, 20), 0L, val1);
    wxStaticText* text3 = new wxStaticText(this, wxID_ANY, "Enter a quantity", wxPoint (0,80), wxSize (200, 20));
    wxFloatingPointValidator<float> val2(3, m_value2, wxNUM_VAL_ZERO_AS_BLANK);
    textctrl3 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,100), wxSize (200, 20), 0L, val2);
    wxButton* button1 = new wxButton (this, wxID_ANY, "Add", wxPoint (50,130), wxSize (100, 20));
    wxButton* button2 = new wxButton (this, wxID_ANY, "Edit/Delete", wxPoint (50,170), wxSize (100, 20)); 


    wxButton* button9 = new wxButton (childPanel1, wxID_ANY, "Clear all", wxPoint (0,0), wxSize (70, 20));

    wxStaticText* text4 = new wxStaticText(childPanel, wxID_ANY, "Select list number", wxPoint (20, 20), wxSize (160, 20), wxALIGN_CENTRE_HORIZONTAL);  //wxPoint (20,210), wxSize (160, 20)


    wxButton* button3 = new wxButton (childPanel, wxID_ANY, "Edit", wxPoint (20, 90), wxSize (50, 20));  //wxPoint (65,250), wxSize (70, 20)
    wxButton* button4 = new wxButton (childPanel, wxID_ANY, "Delete", wxPoint (75, 90), wxSize (50, 20)); 
    wxButton* button5 = new wxButton (childPanel, wxID_ANY, "Cancel", wxPoint (130, 90), wxSize (50, 20));  //wxPoint (65,250), wxSize (70, 20)
    
    wxSpinCtrl* spinctrl = new wxSpinCtrl(childPanel, ID_Spin, wxEmptyString, wxPoint (70, 50), wxSize (60, 20), wxSP_ARROW_KEYS | wxALIGN_CENTRE_HORIZONTAL, 1);

    //wxStaticText *text5 = new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%d"), ValueSpinCtrl()), wxPoint (300, 310), wxSize (100, 20), wxALIGN_CENTRE_HORIZONTAL);
    wxStaticText* text6 = new wxStaticText(this, wxID_ANY, "andrew", wxPoint (400, 310), wxSize (100, 20), wxALIGN_CENTRE_HORIZONTAL);

    listCtrl = new wxListCtrl (this, wxID_ANY, wxPoint (200,0), wxSize (510, 300), wxLC_REPORT);
    listCtrl->AppendColumn ("#", wxLIST_FORMAT_CENTER, 30);
    listCtrl->AppendColumn ("name of product", wxLIST_FORMAT_CENTER, 150);
    listCtrl->AppendColumn ("price", wxLIST_FORMAT_CENTER, 110);
    listCtrl->AppendColumn ("quantity", wxLIST_FORMAT_CENTER, 110);
    listCtrl->AppendColumn ("total", wxLIST_FORMAT_CENTER, 110);

    listCtrltotal = new wxListCtrl (this, wxID_ANY, wxPoint (600,300), wxSize (110, 40), wxLC_REPORT);
    listCtrltotal->AppendColumn ("total cost", wxLIST_FORMAT_CENTER, 110);
    listCtrltotal->InsertItem (0, "0");

    //wxDialog* myDialog = new wxDialog (childPanel, ID_Dialog, "Product editing", wxDefaultPosition, wxSize (400, 300), wxDEFAULT_DIALOG_STYLE);
    //myDialog->Show(1);
    button1->Bind(wxEVT_BUTTON, &LeftPanel::Adding, this);
    button2->Bind(wxEVT_BUTTON, &LeftPanel::EditDelete, this);
    button3->Bind(wxEVT_BUTTON, &LeftPanel::Editing, this);
    button4->Bind(wxEVT_BUTTON, &LeftPanel::DeletingOne, this);
    button5->Bind(wxEVT_BUTTON, &LeftPanel::Canceling, this);

    button9->Bind(wxEVT_BUTTON, &LeftPanel::Deleting, this);
}


MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "ListOP")
{
    SetIcon (wxICON(icon_frame));

    wxMenu* menuFile = new wxMenu;
    /*menuFile->Append(ID_Create, "&Create...\tCtrl-H",
                     "Create a new list");
    menuFile->AppendSeparator();*/

    menuFile->Append(wxID_EXIT);
 
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar( menuBar );

    wxPanel* panel = new wxPanel(this, ID_Panel, wxPoint (0,0), wxSize (0,0));

    LeftPanel* leftPanel = new LeftPanel (panel);

    CreateStatusBar();
    SetStatusText("Welcome to ListOP!");

    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}


void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This program helps to make a shopping list.",
                 "About Program", wxOK | wxICON_INFORMATION);
}
 

void LeftPanel::Adding (wxCommandEvent& event)
{
    if (!textctrl1->IsEmpty() && !textctrl2->IsEmpty() && !textctrl3->IsEmpty()){      
    listCtrl->InsertItem (TotalCount(), "");
    listCtrl->SetItem (TotalCount(), 0, wxString::Format(wxT("%d"), TotalCount()+1), -1);
    listCtrl->SetItem (TotalCount(), 1, textctrl1->GetValue(), -1);
    listCtrl->SetItem (TotalCount(), 2, textctrl2->GetValue(), -1);
    double price;
    textctrl2->GetValue().ToDouble(&price);
    listCtrl->SetItem (TotalCount(), 3, textctrl3->GetValue(), -1);
    double quantity;
    textctrl3->GetValue().ToDouble(&quantity);
    listCtrl->SetItem (TotalCount(), 4, wxString::Format(wxT("%.2f"), price*quantity), -1);
    float* total = new float (price*quantity); //память!!!!!!!!!!!!!!!!!!
    vector.push_back(total);
    listCtrltotal->SetItemText (0, wxString::Format(wxT("%.2f"), TotalCost()));

    //*str = wxString::Format(wxT("%.2f"), TotalCost());

    //!!!!!!!!!!wxStaticText *text6 = new wxStaticText(this, wxID_ANY, text5->GetLabelText(), wxPoint (500, 310), wxSize (160, 20), wxALIGN_CENTRE_HORIZONTAL);
    textctrl1->SetValue("");
    textctrl2->SetValue("");
    textctrl3->SetValue("");
    count++;
    }
    else
    {
        wxMessageBox("The name of product, price or quantity is not correct.",
                 "Error", wxOK | wxICON_INFORMATION);
    }
}

unsigned int LeftPanel::TotalCount()
{
    return (count-countDelete);
}

float LeftPanel::TotalCost()
{
    float cost = 0;
    for(unsigned int i = 0; i < vector.size(); ++i)
    {
        cost += *vector[i];
    }
    return cost;
}


void LeftPanel::EditDelete(wxCommandEvent& event)
{
    if(vector.empty())
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

void LeftPanel::Editing(wxCommandEvent& event)
{
    if(vector.empty())
    {
        wxMessageBox("The list of product is empty.",
                 "Empty list", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxSpinCtrl* spinCtrlInFunc = (wxSpinCtrl*)FindWindow(ID_Spin);
        //wxDialog* dialogInFunc = (wxDialog*)FindWindow(ID_Dialog);
        if (vector.size() > (spinCtrlInFunc->GetValue()-1))
        {
            wxDialog* dialogInFunc = new wxDialog(childPanel, ID_Dialog, "Product editing", wxDefaultPosition, wxSize (400, 300), wxDEFAULT_DIALOG_STYLE);
            dialogInFunc->ShowModal();
            /*wxStaticText* text1 = new wxStaticText(FindWindow(ID_Dialog), wxID_ANY, "Enter a name of product", wxPoint (0,0), wxSize (200, 20));
            textctrl1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,20), wxSize (200, 20));
            wxStaticText* text2 = new wxStaticText(this, wxID_ANY, "Enter a price", wxPoint (0,40), wxSize (200, 20));
            wxFloatingPointValidator<float> val1(2, m_value1, wxNUM_VAL_ZERO_AS_BLANK);
            textctrl2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,60), wxSize (200, 20), 0L, val1);
            wxStaticText* text3 = new wxStaticText(this, wxID_ANY, "Enter a quantity", wxPoint (0,80), wxSize (200, 20));
            wxFloatingPointValidator<float> val2(3, m_value2, wxNUM_VAL_ZERO_AS_BLANK);
            textctrl3 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,100), wxSize (200, 20), 0L, val2);*/

            dialogInFunc->Destroy();
            //myDialog->Show(1);
            //listCtrl->SetItem ((spinCtrlInFunc->GetValue()-1), 1, "andrew", -1);
            //FindWindow(ID_Dialog)->Show(true);
            /*listCtrl->DeleteItem(spinCtrlInFunc->GetValue()-1);
            countDelete++;
            for (unsigned int i = (spinCtrlInFunc->GetValue()-1); i < TotalCount(); i++)
            {
                listCtrl->SetItem (i, 0, wxString::Format(wxT("%d"), i+1), -1);
            }
            listCtrltotal->SetItemText (0, wxString::Format(wxT("%.2f"), (TotalCost()-*vector[spinCtrlInFunc->GetValue()-1])));
            delete vector[spinCtrlInFunc->GetValue()-1];
            vector[spinCtrlInFunc->GetValue()-1] = 0;
            vector.erase(vector.begin()+spinCtrlInFunc->GetValue()-1);*/
        }
        else
        {
            wxMessageBox("This name is not in the list.",
                 "Name missing", wxOK | wxICON_INFORMATION);
            
        }
    }

}

void LeftPanel::DeletingOne(wxCommandEvent& event)
{
    if(vector.empty())
    {
        wxMessageBox("The list of product is empty.",
                 "Empty list", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxSpinCtrl* spinCtrlInFunc = (wxSpinCtrl*)FindWindow(ID_Spin);
        if (vector.size() > (spinCtrlInFunc->GetValue()-1))
        {
            listCtrl->DeleteItem(spinCtrlInFunc->GetValue()-1);
            countDelete++;
            for (unsigned int i = (spinCtrlInFunc->GetValue()-1); i < TotalCount(); i++)
            {
                listCtrl->SetItem (i, 0, wxString::Format(wxT("%d"), i+1), -1);
            }
            listCtrltotal->SetItemText (0, wxString::Format(wxT("%.2f"), (TotalCost()-*vector[spinCtrlInFunc->GetValue()-1])));
            delete vector[spinCtrlInFunc->GetValue()-1];
            vector[spinCtrlInFunc->GetValue()-1] = 0;
            vector.erase(vector.begin()+spinCtrlInFunc->GetValue()-1);
        }
        else
        {
            wxMessageBox("This name is not in the list.",
                 "Name missing", wxOK | wxICON_INFORMATION);
            
        }
    }

}

void LeftPanel::Canceling(wxCommandEvent& event)
{
    FindWindow (ID_Panel2)->Show(false);
    FindWindow (ID_Panel1)->Show(true);
}

void LeftPanel::Deleting (wxCommandEvent& event)
{
    listCtrl->DeleteAllItems ();
    for(unsigned int i = 0; i < vector.size(); ++i)
    {
        delete vector[i];
        vector[i] = 0;
    }
    vector.clear();
    count = 0;
    countDelete = 0;
    listCtrltotal->SetItemText (0, "0");
}

/*int LeftPanel::ValueSpinCtrl()
{
    return spinctrl->GetValue();
}*/

/*int LeftPanel::VS (wxVector<float*> vec)
{
    return vec.size();
}*/

/*void LeftPanel::ChangeIdOfListCtrl(unsigned int k)
{
    for (unsigned int i = k; i < listCtrl->GetItemCount(); i++)
    {
        listCtrl->GetId();
    }
}*/