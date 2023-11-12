#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/validate.h>
#include <wx/valnum.h>
#include <wx/spinctrl.h>
#include <wx/printdlg.h>
#include <wx/print.h>
#include <wx/cmndata.h>
#include "res.h"
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class myDialog : public wxDialog
{
public:
    myDialog(wxPanel* parent);
    void OkDialog(wxCommandEvent& event);
    void CancelDialog(wxCommandEvent& event);
    float* m_valueDialog1 = 0;
    float* m_valueDialog2 = 0;
    wxStaticText* textDialog1;
    wxTextCtrl* textctrlDialog1;
    wxStaticText* textDialog2;
    wxTextCtrl* textctrlDialog2;
    wxStaticText* textDialog3;
    wxTextCtrl* textctrlDialog3;
    wxPanel* parentPanelForDialog;

private:
    /*DECLARE_CLASS(myDialog)
    DECLARE_EVENT_TABLE()*/


    wxButton* buttonOk;
    wxButton* buttonCancel;
};

class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel* parent);

    wxPanel* parentPanel;
    wxListCtrl* listCtrl;
    wxSpinCtrl* spinctrl; 
    wxVector<float*> vector;
    wxListCtrl* listCtrltotal;
    void Adding(wxCommandEvent& event);
    void EditDelete(wxCommandEvent& event);
    void DeletingOne(wxCommandEvent& event);
    void Editing(wxCommandEvent& event);
    void Canceling(wxCommandEvent& event);
    void Deleting(wxCommandEvent& event);
    static unsigned int TotalCount();
    float TotalCost();

    //void OkDialog(wxCommandEvent& event);
    //void CancelDialog(wxCommandEvent& event);

    //int VS (wxVector<float*> vec);
    //void ChangeIdOfListCtrl(unsigned int k);

    //int ValueSpinCtrl();
    

private:

    wxPanel* childPanel;
    wxPanel* childPanel1;

    
    
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
    
};

unsigned int LeftPanel::count = 0;
unsigned int LeftPanel::countDelete = 0;

class MyPrintout : public wxPrintout
{
public:
    MyPrintout();
    bool OnPrintPage(int pageNum);
    bool HasPage(int pageNum);
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
    LeftPanel *leftPanel;
    myDialog* dialogInFrame;

private:
    wxPrintDialogData m_dialogData;
    wxPageSetupDialogData m_pageSetupDialogData;
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnPageSetup(wxCommandEvent& event);
    void OnPreview(wxCommandEvent& event);

};
wxPrintDialogData g_dialogData;
enum
{
    ID_Create = 1, ID_Panel, ID_Panel1, ID_Panel2, ID_Spin, ID_Dialog, ID_buttonOk, ID_MyPanel
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
    parentPanel = parent;
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
    
    spinctrl = new wxSpinCtrl(childPanel, ID_Spin, wxEmptyString, wxPoint (70, 50), wxSize (60, 20), wxSP_ARROW_KEYS | wxALIGN_CENTRE_HORIZONTAL, 1);

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

    button1->Bind(wxEVT_BUTTON, &LeftPanel::Adding, this);
    button2->Bind(wxEVT_BUTTON, &LeftPanel::EditDelete, this);
    button3->Bind(wxEVT_BUTTON, &LeftPanel::Editing, this);
    button4->Bind(wxEVT_BUTTON, &LeftPanel::DeletingOne, this);
    button5->Bind(wxEVT_BUTTON, &LeftPanel::Canceling, this);

    button9->Bind(wxEVT_BUTTON, &LeftPanel::Deleting, this);
}

myDialog::myDialog(wxPanel* parent) : wxDialog(parent, ID_Dialog, "Product editing", wxDefaultPosition, wxSize (205, 200), wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP)
{
    parentPanelForDialog = parent;
    wxStaticText* textDialog1 = new wxStaticText(this, wxID_ANY, "Enter a name of product", wxPoint (0,0), wxSize (200, 20));
    textctrlDialog1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,20), wxSize (200, 20));
    wxStaticText* textDialog2 = new wxStaticText(this, wxID_ANY, "Enter a price", wxPoint (0,40), wxSize (200, 20));
    wxFloatingPointValidator<float> valDialog1(2, m_valueDialog1, wxNUM_VAL_ZERO_AS_BLANK);
    textctrlDialog2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,60), wxSize (200, 20), 0L, valDialog1);
    wxStaticText* textDialog3 = new wxStaticText(this, wxID_ANY, "Enter a quantity", wxPoint (0,80), wxSize (200, 20));
    wxFloatingPointValidator<float> valDialog2(3, m_valueDialog2, wxNUM_VAL_ZERO_AS_BLANK);
    textctrlDialog3 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,100), wxSize (200, 20), 0L, valDialog2);

    wxButton* buttonOk = new wxButton (this, ID_buttonOk, "Ok", wxPoint (35, 135), wxSize (50, 20));  
    wxButton* buttonCancel = new wxButton (this, wxID_ANY, "Cancel", wxPoint (115, 135), wxSize (50, 20)); 
    //myDialog->Connect(ID_buttonOk, wxEVT_BUTTON, wxButtonEventHandler(myDialog::OkDialog()));
    
    /*BEGIN_EVENT_TABLE(myDialog, wxDialog)
    EVT_BUTTON(ID_buttonOk, myDialog::OkDialog)
    END_EVENT_TABLE()*/
    buttonOk->Bind(wxEVT_BUTTON, &myDialog::OkDialog, this);
    buttonCancel->Bind(wxEVT_BUTTON, &myDialog::CancelDialog, this);

}

MyPrintout::MyPrintout() : wxPrintout()
{
    //wxSize imageSize = wxSize(500,300);
    //void FitThisSizeToPage	(const wxSize &imageSize);	//const wxSize & 	imageSize


    //SetLogicalOrigin(200,0);
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "ListOP")
{
    SetIcon (wxICON(icon_frame));

    wxMenu* menuFile = new wxMenu;
    /*menuFile->Append(ID_Create, "&Create...\tCtrl-H",
                     "Create a new list");
    menuFile->AppendSeparator();*/

    menuFile->Append(wxID_PRINT);
    
    menuFile->AppendSeparator();

    menuFile->Append(wxID_PAGE_SETUP, "&PageSetup");
    
    menuFile->AppendSeparator();

    menuFile->Append(wxID_PREVIEW, "&Preview");
    
    menuFile->AppendSeparator();

    menuFile->Append(wxID_EXIT);
 
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar( menuBar );

    wxPanel* panel = new wxPanel(this, ID_Panel, wxPoint (0,0), wxSize (0,0));

    leftPanel = new LeftPanel(panel);

    dialogInFrame = new myDialog(panel);

    CreateStatusBar();
    SetStatusText("Welcome to ListOP!");

    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnPrint, this, wxID_PRINT);
    Bind(wxEVT_MENU, &MyFrame::OnPageSetup, this, wxID_PAGE_SETUP);
    Bind(wxEVT_MENU, &MyFrame::OnPreview, this, wxID_PREVIEW);
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

void MyFrame::OnPrint(wxCommandEvent& event)
{
wxPrintDialogData dialogData;
dialogData.SetFromPage(0);
dialogData.SetToPage(10);

wxPrintDialog printDialog(this, &m_dialogData);     //& m_dialogData
if (printDialog.ShowModal() == wxID_OK)
{
// After calling GetPrintDC(), the application
// owns the DC
wxDC* dc = printDialog.GetPrintDC();

// Draw on the device context
//...
//dc->SetLogicalOrigin(200, 0);

// Destroy it
delete dc;
//delete dialogData;

}

}


void MyFrame::OnPreview(wxCommandEvent& event)
{
wxPrintPreview *preview = new wxPrintPreview(new MyPrintout, new MyPrintout, & m_dialogData);   //
if (!preview->Ok())
{
delete preview;
wxMessageBox(wxT("There was a problem previewing.\nPerhaps your current printer is not set correctly?"), wxT("Previewing"), wxOK);
return;
}    

wxPreviewFrame *frame = new wxPreviewFrame(preview, this, wxT("Demo Print Preview"), wxPoint(0, 0), wxSize (710, 340));
frame->Centre(wxBOTH);
frame->Initialize();
frame->Show(true);

}



void MyFrame::OnPageSetup(wxCommandEvent& event)
{
wxPageSetupDialog pageSetupDialog(this, & m_pageSetupDialogData);    //& m_pageSetupDialogData
if (pageSetupDialog.ShowModal() == wxID_OK)    
m_pageSetupDialogData = pageSetupDialog.GetPageSetupData();
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
    float* total = new float (price*quantity);
    listCtrl->SetItem (TotalCount(), 4, wxString::Format(wxT("%.2f"), *total), -1);
    //float* total = new float (price*quantity); //память!!!!!!!!!!!!!!!!!!
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

        if (vector.size() > (spinctrl->GetValue()-1))
        {

            MyFrame* frameFromDialog = (MyFrame*) parentPanel->GetParent();
            myDialog* dlg = frameFromDialog->dialogInFrame;
            dlg->textctrlDialog1->SetValue(listCtrl->GetItemText((spinctrl->GetValue()-1), 1));
            dlg->textctrlDialog2->SetValue(listCtrl->GetItemText((spinctrl->GetValue()-1), 2));
            dlg->textctrlDialog3->SetValue(listCtrl->GetItemText((spinctrl->GetValue()-1), 3));

            dlg->ShowModal();

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

        if (vector.size() > (spinctrl->GetValue()-1))
        {
            listCtrl->DeleteItem(spinctrl->GetValue()-1);
            countDelete++;
            for (unsigned int i = (spinctrl->GetValue()-1); i < TotalCount(); i++)
            {
                listCtrl->SetItem (i, 0, wxString::Format(wxT("%d"), i+1), -1);
            }
            listCtrltotal->SetItemText (0, wxString::Format(wxT("%.2f"), (TotalCost()-*vector[spinctrl->GetValue()-1])));
            delete vector[spinctrl->GetValue()-1];
            vector[spinctrl->GetValue()-1] = 0;
            vector.erase(vector.begin()+spinctrl->GetValue()-1);
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
    FindWindow(ID_Panel2)->Show(false);
    FindWindow(ID_Panel1)->Show(true);
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

void myDialog::OkDialog(wxCommandEvent& event)
{

    MyFrame* frameFromFunc = (MyFrame*)parentPanelForDialog->GetParent();

    if (frameFromFunc->leftPanel->listCtrl->GetItemText((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 1)==textctrlDialog1->GetValue() &&
    frameFromFunc->leftPanel->listCtrl->GetItemText((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 2)==textctrlDialog2->GetValue() &&
    frameFromFunc->leftPanel->listCtrl->GetItemText((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 3)==textctrlDialog3->GetValue())
    {
        wxMessageBox("You haven't made any changes",
                 "No changes", wxOK | wxICON_INFORMATION);
    }
    
    else
    {
        if(frameFromFunc->leftPanel->listCtrl->GetItemText((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 1)!=textctrlDialog1->GetValue())
        {
            frameFromFunc->leftPanel->listCtrl->SetItem ((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 1, textctrlDialog1->GetValue(), -1);
        }
        if(frameFromFunc->leftPanel->listCtrl->GetItemText((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 2)!=textctrlDialog2->GetValue())
        {
            frameFromFunc->leftPanel->listCtrl->SetItem ((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 2, textctrlDialog2->GetValue(), -1);
        }
        if(frameFromFunc->leftPanel->listCtrl->GetItemText((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 3)!=textctrlDialog3->GetValue())
        {
            frameFromFunc->leftPanel->listCtrl->SetItem ((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 3, textctrlDialog3->GetValue(), -1);
        }
        double priceInDialog;
        double quantityInDialog;
        textctrlDialog2->GetValue().ToDouble(&priceInDialog);
        textctrlDialog3->GetValue().ToDouble(&quantityInDialog);
        frameFromFunc->leftPanel->listCtrltotal->SetItemText (0, wxString::Format(wxT("%.2f"), (frameFromFunc->leftPanel->TotalCost() - 
            (*(frameFromFunc->leftPanel->vector[frameFromFunc->leftPanel->spinctrl->GetValue()-1])) + priceInDialog * quantityInDialog)));
        
        *(frameFromFunc->leftPanel->vector[frameFromFunc->leftPanel->spinctrl->GetValue()-1]) = priceInDialog * quantityInDialog;
        
        frameFromFunc->leftPanel->listCtrl->SetItem ((frameFromFunc->leftPanel->spinctrl->GetValue()-1), 4, wxString::Format(wxT("%.2f"), 
            *(frameFromFunc->leftPanel->vector[frameFromFunc->leftPanel->spinctrl->GetValue()-1])), -1);

        Close();
    }
}

void myDialog::CancelDialog(wxCommandEvent& event)
{
    Close();
}

bool MyPrintout::OnPrintPage(int pageNum)
{
    wxDC *ptr = GetDC();
    if(ptr == NULL || !ptr->IsOk())
    {
        return false;
    }
    wxDC &dc = *ptr;
    dc.Clear();
    dc.SetMapMode(wxMM_POINTS);
    return true;
}

bool MyPrintout::HasPage(int pageNum)
{
    return true;
}