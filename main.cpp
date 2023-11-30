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
#include <wx/datetime.h>
#include <wx/textfile.h>
#include "res.h"
#endif

// Global print data, to remember settings during the session
wxPrintData* g_printData = nullptr;

// Global page setup data
wxPageSetupDialogData* g_pageSetupData = nullptr;


class MyApp : public wxApp
{
public:
    virtual bool OnInit() override;
    virtual int OnExit() override;
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
    wxButton* buttonOk;
    wxButton* buttonCancel;
};

class MyPanel : public wxPanel
{
public:
    MyPanel(wxPanel* parent);
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
    wxString m_nameColumn1 = "#";
    wxString m_nameColumn2 = "name of product";
    wxString m_nameColumn3 = "price";
    wxString m_nameColumn4 = "quantity";
    wxString m_nameColumn5 = "total";
    wxString m_nameColumn6 = "total cost";
   
private:
    wxPanel* childPanel;
    wxPanel* childPanel1;  
    wxTextCtrl* textctrl1;
    wxTextCtrl* textctrl2;
    wxTextCtrl* textctrl3;
    wxStaticText* text4;
    static unsigned int count;
    static unsigned int countDelete;
    float* m_value1 = 0;
    float* m_value2 = 0; 
};

unsigned int MyPanel::count = 0;
unsigned int MyPanel::countDelete = 0;

class MyFrame : public wxFrame
{
public:
    MyFrame();
    MyPanel *myPanel;
    myDialog* dialogInFrame;

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnPageSetup(wxCommandEvent& event);
    void OnPreview(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
};


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


enum
{
    ID_Create = 1, ID_Panel, ID_Panel1, ID_Panel2, ID_Spin, ID_Dialog, ID_buttonOk, ID_MyPanel
};

 
wxIMPLEMENT_APP(MyApp);

 
bool MyApp::OnInit()
{
    g_printData = new wxPrintData;
    g_pageSetupData = new wxPageSetupDialogData;
    (*g_pageSetupData) = *g_printData;

    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

int MyApp::OnExit()
{
    delete g_printData;
    delete g_pageSetupData;

    return wxApp::OnExit();
}

MyPanel::MyPanel(wxPanel* parent) : wxPanel (parent, wxID_ANY, wxDefaultPosition, wxSize (710, 340), wxBORDER_SUNKEN)
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

    wxStaticText* text4 = new wxStaticText(childPanel, wxID_ANY, "Select list number", wxPoint (20, 20), wxSize (160, 20), wxALIGN_CENTRE_HORIZONTAL);  

    wxButton* button3 = new wxButton (childPanel, wxID_ANY, "Edit", wxPoint (20, 90), wxSize (50, 20)); 
    wxButton* button4 = new wxButton (childPanel, wxID_ANY, "Delete", wxPoint (75, 90), wxSize (50, 20)); 
    wxButton* button5 = new wxButton (childPanel, wxID_ANY, "Cancel", wxPoint (130, 90), wxSize (50, 20));
    
    spinctrl = new wxSpinCtrl(childPanel, ID_Spin, wxEmptyString, wxPoint (70, 50), wxSize (60, 20), wxSP_ARROW_KEYS | wxALIGN_CENTRE_HORIZONTAL, 1);
    wxStaticText* text6 = new wxStaticText(this, wxID_ANY, "andrew", wxPoint (400, 310), wxSize (100, 20), wxALIGN_CENTRE_HORIZONTAL);

    listCtrl = new wxListCtrl (this, wxID_ANY, wxPoint (200,0), wxSize (510, 300), wxLC_REPORT);
    listCtrl->AppendColumn (m_nameColumn1, wxLIST_FORMAT_CENTER, 30);
    listCtrl->AppendColumn (m_nameColumn2, wxLIST_FORMAT_CENTER, 150);
    listCtrl->AppendColumn (m_nameColumn3, wxLIST_FORMAT_CENTER, 110);
    listCtrl->AppendColumn (m_nameColumn4, wxLIST_FORMAT_CENTER, 110);
    listCtrl->AppendColumn (m_nameColumn5, wxLIST_FORMAT_CENTER, 110);

    listCtrltotal = new wxListCtrl (this, wxID_ANY, wxPoint (600,300), wxSize (110, 40), wxLC_REPORT);
    listCtrltotal->AppendColumn (m_nameColumn6, wxLIST_FORMAT_CENTER, 110);
    listCtrltotal->InsertItem (0, "0");

    button1->Bind(wxEVT_BUTTON, &MyPanel::Adding, this);
    button2->Bind(wxEVT_BUTTON, &MyPanel::EditDelete, this);
    button3->Bind(wxEVT_BUTTON, &MyPanel::Editing, this);
    button4->Bind(wxEVT_BUTTON, &MyPanel::DeletingOne, this);
    button5->Bind(wxEVT_BUTTON, &MyPanel::Canceling, this);

    button9->Bind(wxEVT_BUTTON, &MyPanel::Deleting, this);
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
    buttonOk->Bind(wxEVT_BUTTON, &myDialog::OkDialog, this);
    buttonCancel->Bind(wxEVT_BUTTON, &myDialog::CancelDialog, this);

}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "ListOP")
{
    SetIcon (wxICON(icon_frame));

    wxMenu* menuFile = new wxMenu;

    menuFile->Append(wxID_SAVE);
    
    menuFile->AppendSeparator();
    
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

    myPanel = new MyPanel(panel);

    dialogInFrame = new myDialog(panel);

    CreateStatusBar();
    SetStatusText("Welcome to ListOP!");

    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnPrint, this, wxID_PRINT);
    Bind(wxEVT_MENU, &MyFrame::OnPageSetup, this, wxID_PAGE_SETUP);
    Bind(wxEVT_MENU, &MyFrame::OnPreview, this, wxID_PREVIEW);
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, wxID_SAVE);
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
    wxPrintDialogData printDialogData(* g_printData);
    printDialogData.EnableSelection(true);
    printDialogData.EnablePageNumbers(true);
    wxPrinter printer(&printDialogData);
    MyPrintout printout(this, &printer.GetPrintDialogData(), "My printout"); 
    printDialogData.SetMinPage(1);
    printDialogData.SetMaxPage(printout.m_numPages);
    printDialogData.SetFromPage(1);
    printDialogData.SetToPage(printout.m_numPages);
    printDialogData.SetAllPages(true);

    SetStatusText(""); // clear previous "cancelled" message, if any

    if (!printer.Print(this, &printout, true))
    {
        if (wxPrinter::GetLastError() == wxPRINTER_ERROR)
        {
            wxLogError("There was a problem printing. Perhaps your current printer is not set correctly?");
        }
        else
        {
            wxLogStatus("You canceled printing");
        }
    }
    else
    {
        (*g_printData) = printer.GetPrintDialogData().GetPrintData();
    }
}


void MyFrame::OnPreview(wxCommandEvent& event)
{

// Pass two printout objects: for preview, and possible printing.
    wxPrintDialogData printDialogData(* g_printData);

    wxPrinter printer(&printDialogData);

    // wxPrinter copies printDialogData internally, so we have to pass this
    // instance in order to evaluate users inputs.

    wxPrintPreview *preview =
        new wxPrintPreview(new MyPrintout(this, &printDialogData), new MyPrintout(this, &printDialogData), &printDialogData);
    if (!preview->IsOk())
    {
        delete preview;
        wxLogError("There was a problem previewing.\nPerhaps your current printer is not set correctly?");
        return;
    }

    wxPreviewFrame *frame = new wxPreviewFrame(preview, this, "Demo Print Preview");

frame->Centre(wxBOTH);
frame->Initialize();
frame->Show(true);

}

void MyFrame::OnPageSetup(wxCommandEvent& event)
{

    (*g_pageSetupData) = *g_printData;

    wxPageSetupDialog pageSetupDialog(this, g_pageSetupData);
    pageSetupDialog.ShowModal();

    (*g_printData) = pageSetupDialog.GetPageSetupDialogData().GetPrintData();
    (*g_pageSetupData) = pageSetupDialog.GetPageSetupDialogData();

}


void MyFrame::OnSave(wxCommandEvent& event)
{
    
    if(!myPanel->vector.empty())

    {

    wxString filename = "file_" + wxDateTime::Today().FormatISODate() + ".txt";


    wxTextFile file (filename);
    if (!file.Exists())
    {
        file.Create();
    }

    if (file.Open())
    {
    file.Clear();
    char fill1 = '-';
    char fill2 = ' ';
    wxString fill3 = "|";

    wxString nameColumn1 = myPanel->m_nameColumn1;
    if (nameColumn1.size()>3)
    {
        nameColumn1.Remove(3);
    }
    wxString nameColumn2 = myPanel->m_nameColumn2;
    if (nameColumn2.size()>25)
    {
        nameColumn2.Remove(25);
    }
    wxString nameColumn3 = myPanel->m_nameColumn3;
    if (nameColumn3.size()>12)
    {
        nameColumn3.Remove(12);
    }
    wxString nameColumn4 = myPanel->m_nameColumn4;
    if (nameColumn4.size()>10)
    {
        nameColumn4.Remove(10);
    }
    wxString nameColumn5 = myPanel->m_nameColumn5;
    if (nameColumn5.size()>24)
    {
        nameColumn5.Remove(24);
    }

    file.AddLine("List of products " + wxDateTime::Today().FormatISODate());
    file.AddLine ("");
    file.AddLine (wxString(fill1, 80));
    file.AddLine(fill3 + nameColumn1 + wxString(fill2, (3 - nameColumn1.size())) + fill3 + 
    nameColumn2 + wxString(fill2, (25 - nameColumn2.size())) + fill3 + 
    nameColumn3 + wxString(fill2, (12 - nameColumn3.size())) + fill3 + 
    nameColumn4 + wxString(fill2, (10 - nameColumn4.size())) + fill3 + 
    nameColumn5 + wxString(fill2, (24 - nameColumn5.size())) + fill3);
    file.AddLine (wxString(fill1, 80));

    for (unsigned int i = 0; i < myPanel->vector.size(); ++i)
    {
        wxString nameItem1 = myPanel->listCtrl->GetItemText(i, 0);
        if (nameItem1.size()>3)
        {
            nameItem1.Remove(3);
        }
        wxString nameItem2 = myPanel->listCtrl->GetItemText(i, 1);
        if (nameItem2.size()>25)
        {
            nameItem2.Remove(25);
        }
        wxString nameItem3 = myPanel->listCtrl->GetItemText(i, 2);
        if (nameItem3.size()>12)
        {
            nameItem3.Remove(12);
        }
        wxString nameItem4 = myPanel->listCtrl->GetItemText(i, 3);
        if (nameItem4.size()>10)
        {
            nameItem4.Remove(10);
        }
        wxString nameItem5 = myPanel->listCtrl->GetItemText(i, 4);
        if (nameItem5.size()>24)
        {
            nameItem5.Remove(24);
        }
        file.AddLine(fill3 + nameItem1 + wxString(fill2, (3 - nameItem1.size())) + fill3 + 
        nameItem2 + wxString(fill2, (25 - nameItem2.size())) + fill3 + 
        nameItem3 + wxString(fill2, (12 - nameItem3.size())) + fill3 + 
        nameItem4 + wxString(fill2, (10 - nameItem4.size())) + fill3 + 
        nameItem5 + wxString(fill2, (24 - nameItem5.size())) + fill3);
        file.AddLine (wxString(fill1, 80));        
    }

    file.AddLine (wxString(fill2, 55) + myPanel->m_nameColumn6);
    file.AddLine (wxString(fill2, 55) + myPanel->listCtrltotal->GetItemText(0, 0));


    file.Write(wxTextFileType_None);

    }

    }

    else
    {
        wxMessageBox("The list of product is empty.",
                 "Empty list", wxOK | wxICON_INFORMATION);
    }
    
}


void MyPanel::Adding (wxCommandEvent& event)
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
    vector.push_back(total);
    listCtrltotal->SetItemText (0, wxString::Format(wxT("%.2f"), TotalCost()));
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

unsigned int MyPanel::TotalCount()
{
    return (count-countDelete);
}

float MyPanel::TotalCost()
{
    float cost = 0;
    for(unsigned int i = 0; i < vector.size(); ++i)
    {
        cost += *vector[i];
    }
    return cost;
}


void MyPanel::EditDelete(wxCommandEvent& event)
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

void MyPanel::Editing(wxCommandEvent& event)
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

void MyPanel::DeletingOne(wxCommandEvent& event)
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

void MyPanel::Canceling(wxCommandEvent& event)
{
    FindWindow(ID_Panel2)->Show(false);
    FindWindow(ID_Panel1)->Show(true);
}

void MyPanel::Deleting (wxCommandEvent& event)
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

    if (frameFromFunc->myPanel->listCtrl->GetItemText((frameFromFunc->myPanel->spinctrl->GetValue()-1), 1)==textctrlDialog1->GetValue() &&
    frameFromFunc->myPanel->listCtrl->GetItemText((frameFromFunc->myPanel->spinctrl->GetValue()-1), 2)==textctrlDialog2->GetValue() &&
    frameFromFunc->myPanel->listCtrl->GetItemText((frameFromFunc->myPanel->spinctrl->GetValue()-1), 3)==textctrlDialog3->GetValue())
    {
        wxMessageBox("You haven't made any changes",
                 "No changes", wxOK | wxICON_INFORMATION);
    }
    
    else
    {
        if(frameFromFunc->myPanel->listCtrl->GetItemText((frameFromFunc->myPanel->spinctrl->GetValue()-1), 1)!=textctrlDialog1->GetValue())
        {
            frameFromFunc->myPanel->listCtrl->SetItem ((frameFromFunc->myPanel->spinctrl->GetValue()-1), 1, textctrlDialog1->GetValue(), -1);
        }
        if(frameFromFunc->myPanel->listCtrl->GetItemText((frameFromFunc->myPanel->spinctrl->GetValue()-1), 2)!=textctrlDialog2->GetValue())
        {
            frameFromFunc->myPanel->listCtrl->SetItem ((frameFromFunc->myPanel->spinctrl->GetValue()-1), 2, textctrlDialog2->GetValue(), -1);
        }
        if(frameFromFunc->myPanel->listCtrl->GetItemText((frameFromFunc->myPanel->spinctrl->GetValue()-1), 3)!=textctrlDialog3->GetValue())
        {
            frameFromFunc->myPanel->listCtrl->SetItem ((frameFromFunc->myPanel->spinctrl->GetValue()-1), 3, textctrlDialog3->GetValue(), -1);
        }
        double priceInDialog;
        double quantityInDialog;
        textctrlDialog2->GetValue().ToDouble(&priceInDialog);
        textctrlDialog3->GetValue().ToDouble(&quantityInDialog);
        frameFromFunc->myPanel->listCtrltotal->SetItemText (0, wxString::Format(wxT("%.2f"), (frameFromFunc->myPanel->TotalCost() - 
            (*(frameFromFunc->myPanel->vector[frameFromFunc->myPanel->spinctrl->GetValue()-1])) + priceInDialog * quantityInDialog)));
        
        *(frameFromFunc->myPanel->vector[frameFromFunc->myPanel->spinctrl->GetValue()-1]) = priceInDialog * quantityInDialog;
        
        frameFromFunc->myPanel->listCtrl->SetItem ((frameFromFunc->myPanel->spinctrl->GetValue()-1), 4, wxString::Format(wxT("%.2f"), 
            *(frameFromFunc->myPanel->vector[frameFromFunc->myPanel->spinctrl->GetValue()-1])), -1);

        Close();
    }
}

void myDialog::CancelDialog(wxCommandEvent& event)
{
    Close();
}

// ----------------------------------------------------------------------------
// MyPrintout
// ----------------------------------------------------------------------------

void MyPrintout::OnPreparePrinting()
{
    wxDC* dc = GetDC();
    
    if(!m_frame->myPanel->vector.empty())
    {
        m_numPages = (m_frame->myPanel->vector.size() - 1) / 30 + 1;
    }
    else
    {
        m_numPages = 1;
    }

}

bool MyPrintout::OnPrintPage(int page)
{
    wxDC* dc = GetDC();
    if (dc)
    {

        MapScreenSizeToPage();

        dc->DrawIcon(wxICON(icon_frame), 5, 5);

        dc->DrawText(wxString::Format("PAGE %d", page), 50, 0);

        dc->DrawText("This program was developed by Andrey Vinokurov", 200, 0);

        long x = 100, y= 100;

        dc->DrawText("List of products " + wxDateTime::Today().FormatISODate(), x-10, y-60);    
        
        if(!m_frame->myPanel->vector.empty())
        {
            dc->DrawLine(x-10, y-30, x+500, y-30);
            dc->DrawLine(x-10, y-30, x-10, y);
            dc->DrawLine(x+40, y-30, x+40, y);
            dc->DrawLine(x+190, y-30, x+190, y);
            dc->DrawLine(x+290, y-30, x+290, y);
            dc->DrawLine(x+390, y-30, x+390, y);
            dc->DrawLine(x+500, y-30, x+500, y);
            dc->DrawText(m_frame->myPanel->m_nameColumn1, x, y-30);
            dc->DrawText(m_frame->myPanel->m_nameColumn2, x+50, y-30);
            dc->DrawText(m_frame->myPanel->m_nameColumn3, x+200, y-30);
            dc->DrawText(m_frame->myPanel->m_nameColumn4, x+300, y-30);
            dc->DrawText(m_frame->myPanel->m_nameColumn5, x+400, y-30); 

            if (page == m_numPages)
            {
                for (unsigned int j = 30*(page-1); j < m_frame->myPanel->vector.size(); ++j)
                {
                    unsigned int i = j - 30*(page-1);
                    dc->DrawLine(x-10, y+30*i, x+500, y+30*i);
                    dc->DrawLine(x-10, y+30*i, x-10, y+30*(i+1));
                    dc->DrawLine(x+40, y+30*i, x+40, y+30*(i+1));
                    dc->DrawLine(x+190, y+30*i, x+190, y+30*(i+1));
                    dc->DrawLine(x+290, y+30*i, x+290, y+30*(i+1));
                    dc->DrawLine(x+390, y+30*i, x+390, y+30*(i+1));
                    dc->DrawLine(x+500, y+30*i, x+500, y+30*(i+1));
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 0), x, y+30*i);
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 1), x+50, y+30*i);
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 2), x+200, y+30*i);
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 3), x+300, y+30*i);
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 4), x+400, y+30*i);
                }
                dc->DrawLine(x-10, y+30*(m_frame->myPanel->vector.size() - 30*(page-1)), x+500, y+30*(m_frame->myPanel->vector.size() - 30*(page-1)));
                dc->DrawText(m_frame->myPanel->m_nameColumn6, x + 400, y + 30*(m_frame->myPanel->vector.size()+1 - 30*(page-1)));
                dc->DrawText(m_frame->myPanel->listCtrltotal->GetItemText(0, 0), x + 400, y + 30*(m_frame->myPanel->vector.size()+2 - 30*(page-1)));
            }
            else
            {   
                for (unsigned int j = 30*(page-1); j < 30*page; ++j)
                {
                    unsigned int i = j - 30*(page-1);
                    dc->DrawLine(x-10, y+30*i, x+500, y+30*i);
                    dc->DrawLine(x-10, y+30*i, x-10, y+30*(i+1));
                    dc->DrawLine(x+40, y+30*i, x+40, y+30*(i+1));
                    dc->DrawLine(x+190, y+30*i, x+190, y+30*(i+1));
                    dc->DrawLine(x+290, y+30*i, x+290, y+30*(i+1));
                    dc->DrawLine(x+390, y+30*i, x+390, y+30*(i+1));
                    dc->DrawLine(x+500, y+30*i, x+500, y+30*(i+1));
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 0), x, y+30*i);
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 1), x+50, y+30*i);
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 2), x+200, y+30*i);
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 3), x+300, y+30*i);
                    dc->DrawText(m_frame->myPanel->listCtrl->GetItemText(j, 4), x+400, y+30*i);
                }
                dc->DrawLine(x-10, 1000, x+500, 1000);
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}


void MyPrintout::GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo)
{
    *minPage = 1;
    *maxPage = m_numPages;
    *selPageFrom = 1;
    *selPageTo = m_numPages;

}

bool MyPrintout::HasPage(int pageNum)
{
    return (pageNum >= 1 && pageNum <= m_numPages);
}
