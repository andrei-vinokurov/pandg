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
//#include <wx/gdicmn.h>
//#include <memory>
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
/*void Draw(wxDC& dc);
    void IncrementAngle()
        { m_angle += 5; }
    void DecrementAngle()
        { m_angle -= 5; }

    wxFont& GetTestFont()
        { return m_testFont; }

private:
    int       m_angle;
    wxBitmap  m_bitmap;
    wxFont    m_testFont;*/
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

    wxString m_nameColumn1 = "#";
    wxString m_nameColumn2 = "name of product";
    wxString m_nameColumn3 = "price";
    wxString m_nameColumn4 = "quantity";
    wxString m_nameColumn5 = "total";
    wxString m_nameColumn6 = "total cost";

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

class MyFrame : public wxFrame
{

public:
    MyFrame();
    LeftPanel *leftPanel;
    myDialog* dialogInFrame;
    //wxPrintDialogData m_dialogData;
    //wxPageSetupDialogData m_pageSetupDialogData;

private:
    
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnPageSetup(wxCommandEvent& event);
    void OnPreview(wxCommandEvent& event);

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
    virtual bool OnBeginDocument(int startPage, int endPage) override;
    virtual void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo) override;
    //bool IsPageSelected(int pageNum);
    

    //void DrawPageOne();
    //void DrawPageTwo();

    // Writes a header on a page. Margin units are in millimetres.
    bool WritePageHeader(wxPrintout *printout, wxDC *dc, const wxString& text, double mmToLogical);


private:
    MyFrame* m_frame;
    wxPrintDialogData* m_printDlgData;
    int m_numPages;

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
    listCtrl->AppendColumn (m_nameColumn1, wxLIST_FORMAT_CENTER, 30);
    listCtrl->AppendColumn (m_nameColumn2, wxLIST_FORMAT_CENTER, 150);
    listCtrl->AppendColumn (m_nameColumn3, wxLIST_FORMAT_CENTER, 110);
    listCtrl->AppendColumn (m_nameColumn4, wxLIST_FORMAT_CENTER, 110);
    listCtrl->AppendColumn (m_nameColumn5, wxLIST_FORMAT_CENTER, 110);

    listCtrltotal = new wxListCtrl (this, wxID_ANY, wxPoint (600,300), wxSize (110, 40), wxLC_REPORT);
    listCtrltotal->AppendColumn (m_nameColumn6, wxLIST_FORMAT_CENTER, 110);
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

    //wxStaticText* staticText = new wxStaticText (this, wxID_ANY, "Text", wxPoint (300, 210), wxSize (100, 20), wxALIGN_CENTRE_HORIZONTAL);

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
    wxPrintDialogData printDialogData(* g_printData);
    printDialogData.EnableSelection(true);
    printDialogData.EnablePageNumbers(true);
    //printDialogData.EnableCurrentPage(true);
    printDialogData.SetMinPage(1);
    printDialogData.SetMaxPage(2);
    printDialogData.SetFromPage(1);
    printDialogData.SetToPage(2);
    printDialogData.SetAllPages(true);

    wxPrinter printer(&printDialogData);

    // wxPrinter copies printDialogData internally, so we have to pass this
    // instance in order to evaluate users inputs.
    MyPrintout printout(this, &printer.GetPrintDialogData(), "My printout");

    SetStatusText(""); // clear previous "cancelled" message, if any

    if (!printer.Print(this, &printout, true /*prompt*/))
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


    /*wxPrinter printer(& g_printDialogData);
    MyPrintout printout(wxT("My printout"));  //wxT("My printout")

    if (!printer.Print(this, &printout, true))
    {
        if (wxPrinter::GetLastError() == wxPRINTER_ERROR)
        wxMessageBox(wxT("There was a problem printing.\nPerhaps your current printer is not set correctly?"), wxT("Printing"), wxOK);
        else
        wxMessageBox(wxT("You cancelled printing"), wxT("Printing"), wxOK);
    }
    else
    {
        g_printDialogData = printer.GetPrintDialogData();
    }*/


/*wxPrintDialogData dialogData;
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

}*/

}


void MyFrame::OnPreview(wxCommandEvent& event)
{

// Pass two printout objects: for preview, and possible printing.
    wxPrintDialogData printDialogData(* g_printData);

    wxPrinter printer(&printDialogData);

    // wxPrinter copies printDialogData internally, so we have to pass this
    // instance in order to evaluate users inputs.

    wxPrintPreview *preview =
        new wxPrintPreview(new MyPrintout(this, &printDialogData), new MyPrintout(this, &printDialogData), &printDialogData);   //new MyPrintout(this, &printDialogData), new MyPrintout(this, &printDialogData), &printDialogData
    if (!preview->IsOk())
    {
        delete preview;
        wxLogError("There was a problem previewing.\nPerhaps your current printer is not set correctly?");
        return;
    }

    wxPreviewFrame *frame = new wxPreviewFrame(preview, this, "Demo Print Preview");


/*wxPrintPreview *preview = new wxPrintPreview(new MyPrintout, new MyPrintout, & m_dialogData);   //
if (!preview->Ok())
{
delete preview;
wxMessageBox(wxT("There was a problem previewing.\nPerhaps your current printer is not set correctly?"), wxT("Previewing"), wxOK);
return;
}    

wxPreviewFrame *frame = new wxPreviewFrame(preview, this, wxT("Demo Print Preview"), wxPoint(0, 0), wxSize (710, 340)); */
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

/*wxPageSetupDialog pageSetupDialog(this, & m_pageSetupDialogData);    //& m_pageSetupDialogData
if (pageSetupDialog.ShowModal() == wxID_OK)    
m_pageSetupDialogData = pageSetupDialog.GetPageSetupData();*/
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

// ----------------------------------------------------------------------------
// MyPrintout
// ----------------------------------------------------------------------------

void MyPrintout::OnPreparePrinting()
{
    wxDC* dc = GetDC();
    long x = 100, y= 100;

    int dcHeight;
    if(!m_frame->leftPanel->vector.empty())
    {
        dcHeight = 30*(m_frame->leftPanel->vector.size()+2);
    }
    else
    {
        dcHeight = 500;
    }
    dc->SetClippingRegion (0, 0, 700, dcHeight);

    /*int ppiScreenX, ppiScreenY;
    GetPPIScreen(&ppiScreenX, &ppiScreenY);
    int ppiPrinterX, ppiPrinterY;
    GetPPIPrinter(&ppiPrinterX, &ppiPrinterY);

    double scale = double(ppiPrinterY) / ppiScreenY; */
    int pageWidth, pageHeight;
    int w, h;
    dc->GetSize(&w, &h);
    GetPageSizePixels(&pageWidth, &pageHeight);
    
    m_numPages =  h / pageHeight + 1;   //scale *
}

bool MyPrintout::OnPrintPage(int page)
{
    wxDC* dc = GetDC();
    if (dc)
    {
        /*if (page == 1)
            DrawPageOne();
        else if (page == 2)
            DrawPageTwo();*/

        // Draw page numbers at top left corner of printable area, sized so that
        // screen size of text matches paper size.
        MapScreenSizeToPage();

        dc->DrawIcon(wxICON(icon_frame), 5, 5);

        dc->DrawText(wxString::Format("PAGE %d", page), 50, 0);

        dc->DrawText("This program was developed by Andrey Vinokurov", 200, 0);

        long x = 100, y= 100;
        //wxCoord wordWidth, wordHeight;
        //dc->DrawRectangle(300, 300, 100, 100);
        //dc->DrawText ("andrew", 200, 200);

        dc->DrawText("List of products " + wxDateTime::Now().Format(), x-10, y-60);    

        dc->DrawText(wxString::Format(wxT("%d"), m_numPages), x-10, y+600);
        
        //dc->DrawText(wxString::Format(wxT("%d"), dc->GetSize().GetHeight()), x-10, y+600);
        //dc->DrawText(wxString::Format(wxT("%d"), GetLogicalPaperRect().GetSize().GetHeight()), x-10, y+650);

        
        if(!m_frame->leftPanel->vector.empty())
        {
            dc->DrawLine(x-10, y-30, x+500, y-30);
            dc->DrawLine(x-10, y-30, x-10, y);
            dc->DrawLine(x+40, y-30, x+40, y);
            dc->DrawLine(x+190, y-30, x+190, y);
            dc->DrawLine(x+290, y-30, x+290, y);
            dc->DrawLine(x+390, y-30, x+390, y);
            dc->DrawLine(x+500, y-30, x+500, y);
            dc->DrawText(m_frame->leftPanel->m_nameColumn1, x, y-30);
            dc->DrawText(m_frame->leftPanel->m_nameColumn2, x+50, y-30);
            dc->DrawText(m_frame->leftPanel->m_nameColumn3, x+200, y-30);
            dc->DrawText(m_frame->leftPanel->m_nameColumn4, x+300, y-30);
            dc->DrawText(m_frame->leftPanel->m_nameColumn5, x+400, y-30);
            for (unsigned int i = 0; i < m_frame->leftPanel->vector.size(); ++i)
            {
            //    wxString word = m_frame->leftPanel->listCtrl->GetItemText(0,1);
        //word.Remove( word.Len()-1, 1 );
        //dc->GetTextExtent(word, &wordWidth, &wordHeight);
        //dc->DrawRectangle(x, y, wordWidth, wordHeight);
        //dc->GetTextExtent(words[i], &wordWidth, &wordHeight);
                dc->DrawLine(x-10, y+30*i, x+500, y+30*i);
                dc->DrawLine(x-10, y+30*i, x-10, y+30*(i+1));
                dc->DrawLine(x+40, y+30*i, x+40, y+30*(i+1));
                dc->DrawLine(x+190, y+30*i, x+190, y+30*(i+1));
                dc->DrawLine(x+290, y+30*i, x+290, y+30*(i+1));
                dc->DrawLine(x+390, y+30*i, x+390, y+30*(i+1));
                dc->DrawLine(x+500, y+30*i, x+500, y+30*(i+1));
                dc->DrawText(m_frame->leftPanel->listCtrl->GetItemText(i, 0), x, y+30*i);
                dc->DrawText(m_frame->leftPanel->listCtrl->GetItemText(i, 1), x+50, y+30*i);
                dc->DrawText(m_frame->leftPanel->listCtrl->GetItemText(i, 2), x+200, y+30*i);
                dc->DrawText(m_frame->leftPanel->listCtrl->GetItemText(i, 3), x+300, y+30*i);
                dc->DrawText(m_frame->leftPanel->listCtrl->GetItemText(i, 4), x+400, y+30*i);
            }
            dc->DrawLine(x-10, y+30*(m_frame->leftPanel->vector.size()), x+500, y+30*(m_frame->leftPanel->vector.size()));
            dc->DrawText(m_frame->leftPanel->m_nameColumn6, x + 400, y + 30*(m_frame->leftPanel->vector.size()+1));
            dc->DrawText(m_frame->leftPanel->listCtrltotal->GetItemText(0, 0), x + 400, y + 30*(m_frame->leftPanel->vector.size()+2));
            
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool MyPrintout::OnBeginDocument(int startPage, int endPage)
{
    if (!wxPrintout::OnBeginDocument(startPage, endPage))
        return false;

    return true;
}

void MyPrintout::GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo)
{
    *minPage = 1;
    *maxPage = m_numPages;
    *selPageFrom = 1;
    *selPageTo = m_numPages;

    // check if the user just wants to print the current page and if so,
    // we say, that page 1 is the current page in this example.
    /*if (m_printDlgData->GetCurrentPage())
    {
        *selPageFrom = 1;
        *selPageTo = 1;
    }
    else if (m_printDlgData->GetSelection())
    {
        // if the user wants to print the selection, we could set the range via
        // selPageFrom and selPageTo, but if the pages are not consecutive, we
        // set selPageFrom and selPageTo to the maximum range and we use
        // IsPageSelected() to tell the printing system which page is selected.

        // in our example below, only page 2 is selected.
    }*/
}

bool MyPrintout::HasPage(int pageNum)
{
    return (pageNum >= 1 && pageNum <= m_numPages);
}

/*bool MyPrintout::IsPageSelected(int pageNum)
{
    // to demonstrate selection, we just simulate selection of page 2
    return pageNum == 2;
}*/

/*void MyPrintout::DrawPageOne()
{
    wxDC* dc = GetDC();

 // Get the logical pixels per inch of screen and printer
    int ppiScreenX, ppiScreenY;
    GetPPIScreen(&ppiScreenX, &ppiScreenY);
    int ppiPrinterX, ppiPrinterY;
    GetPPIPrinter(&ppiPrinterX, &ppiPrinterY);

    // This scales the DC so that the printout roughly represents the screen
    // scaling. The text point size _should_ be the right size but in fact is
    // too small for some reason. This is a detail that will need to be
    // addressed at some point but can be fudged for the moment.
    double scale = double(ppiPrinterX) / ppiScreenX;

    // Now we have to check in case our real page size is reduced (e.g. because
    // we're drawing to a print preview memory DC)
    int pageWidth, pageHeight;
    int w, h;
    dc->GetSize(&w, &h);
    GetPageSizePixels(&pageWidth, &pageHeight);

    // If printer pageWidth == current DC width, then this doesn't change. But w
    // might be the preview bitmap width, so scale down.
    double overallScale = scale * w / pageWidth;
    dc->SetUserScale(overallScale, overallScale);

     // Draw 50 mm by 50 mm L shape
    double logUnitsFactor = ppiPrinterX / (scale * 25.4);
    int logUnits = int(50 * logUnitsFactor);
    dc->SetPen(* wxBLACK_PEN);
    dc->DrawLine(50, 250, 50 + logUnits, 250);
    dc->DrawLine(50, 250, 50, 250 + logUnits);

    long x = 200, y= 250;

    dc->SetFont(wxFontInfo(15).Family(wxFONTFAMILY_SWISS));

    wxCoord maxX = GetDC()->FromDIP(710);
    wxCoord maxY = GetDC()->FromDIP(340);

    FitThisSizeToPageMargins(wxSize(maxX, maxY), *g_pageSetupData);
    wxRect fitRect = GetLogicalPageMarginsRect(*g_pageSetupData);

    dc->SetBackgroundMode(wxBRUSHSTYLE_TRANSPARENT);
    dc->SetBrush(*wxTRANSPARENT_BRUSH);


    wxCoord wordWidth, wordHeight;
    wxString word = m_frame->leftPanel->listCtrl->GetItemText(0,1);
    word.Remove( word.Len()-1, 1 );
            dc->GetTextExtent(word, &wordWidth, &wordHeight);
            dc->DrawRectangle(x, y, wordWidth, wordHeight);
            //dc->GetTextExtent(words[i], &wordWidth, &wordHeight);
            dc->DrawText(word, x, y);

*/
    //dc->GetTextExtent(m_frame->leftPanel->listCtrl->GetItemText(0,1));
    //dc->DrawText(m_frame->leftPanel->listCtrl->GetItemText(0,1), wxPoint(0,0));
    //wxMemoryDC mdc(dc);
/*
    // You might use THIS code if you were scaling graphics of known size to fit
    // on the page. The commented-out code illustrates different ways of scaling
    // the graphics.

    // We know the graphic is 230x350. If we didn't know this, we'd need to
    // calculate it.
    wxCoord maxX = GetDC()->FromDIP(230);
    wxCoord maxY = GetDC()->FromDIP(350);

    // This sets the user scale and origin of the DC so that the image fits
    // within the paper rectangle (but the edges could be cut off by printers
    // that can't print to the edges of the paper -- which is most of them. Use
    // this if your image already has its own margins.
//    FitThisSizeToPaper(wxSize(maxX, maxY));
//    wxRect fitRect = GetLogicalPaperRect();

    // This sets the user scale and origin of the DC so that the image fits
    // within the page rectangle, which is the printable area on Mac and MSW
    // and is the entire page on other platforms.
//    FitThisSizeToPage(wxSize(maxX, maxY));
//    wxRect fitRect = GetLogicalPageRect();

    // This sets the user scale and origin of the DC so that the image fits
    // within the page margins as specified by g_PageSetupData, which you can
    // change (on some platforms, at least) in the Page Setup dialog. Note that
    // on Mac, the native Page Setup dialog doesn't let you change the margins
    // of a wxPageSetupDialogData object, so you'll have to write your own dialog or
    // use the Mac-only wxMacPageMarginsDialog, as we do in this program.
    FitThisSizeToPageMargins(wxSize(maxX, maxY), *g_pageSetupData);
    wxRect fitRect = GetLogicalPageMarginsRect(*g_pageSetupData);

    // This sets the user scale and origin of the DC so that the image appears
    // on the paper at the same size that it appears on screen (i.e., 10-point
    // type on screen is 10-point on the printed page) and is positioned in the
    // top left corner of the page rectangle (just as the screen image appears
    // in the top left corner of the window).
//    MapScreenSizeToPage();
//    wxRect fitRect = GetLogicalPageRect();

    // You could also map the screen image to the entire paper at the same size
    // as it appears on screen.
//    MapScreenSizeToPaper();
//    wxRect fitRect = GetLogicalPaperRect();

    // You might also wish to do you own scaling in order to draw objects at
    // full native device resolution. In this case, you should do the following.
    // Note that you can use the GetLogicalXXXRect() commands to obtain the
    // appropriate rect to scale to.
//    MapScreenSizeToDevice();
//    wxRect fitRect = GetLogicalPageRect();

    // Each of the preceding Fit or Map routines positions the origin so that
    // the drawn image is positioned at the top left corner of the reference
    // rectangle. You can easily center or right- or bottom-justify the image as
    // follows.

    // This offsets the image so that it is centered within the reference
    // rectangle defined above.
    wxCoord xoff = (fitRect.width - maxX) / 2;
    wxCoord yoff = (fitRect.height - maxY) / 2;
    OffsetLogicalOrigin(xoff, yoff);

    // This offsets the image so that it is positioned at the bottom right of
    // the reference rectangle defined above.
//    wxCoord xoff = (fitRect.width - maxX);
//    wxCoord yoff = (fitRect.height - maxY);
//    OffsetLogicalOrigin(xoff, yoff);*/

//   wxGetApp().Draw(*GetDC());
//}

//void MyPrintout::DrawPageTwo()
//{
 /*   // You might use THIS code to set the printer DC to ROUGHLY reflect
    // the screen text size. This page also draws lines of actual length
    // 5cm on the page.

    // Compare this to DrawPageOne(), which uses the really convenient routines
    // from wxPrintout to fit the screen image onto the printed page. This page
    // illustrates how to do all the scaling calculations yourself, if you're so
    // inclined.

    wxDC *dc = GetDC();

    // Get the logical pixels per inch of screen and printer
    int ppiScreenX, ppiScreenY;
    GetPPIScreen(&ppiScreenX, &ppiScreenY);
    int ppiPrinterX, ppiPrinterY;
    GetPPIPrinter(&ppiPrinterX, &ppiPrinterY);

    // This scales the DC so that the printout roughly represents the screen
    // scaling. The text point size _should_ be the right size but in fact is
    // too small for some reason. This is a detail that will need to be
    // addressed at some point but can be fudged for the moment.
    double scale = double(ppiPrinterX) / ppiScreenX;

    // Now we have to check in case our real page size is reduced (e.g. because
    // we're drawing to a print preview memory DC)
    int pageWidth, pageHeight;
    int w, h;
    dc->GetSize(&w, &h);
    GetPageSizePixels(&pageWidth, &pageHeight);

    // If printer pageWidth == current DC width, then this doesn't change. But w
    // might be the preview bitmap width, so scale down.
    double overallScale = scale * w / pageWidth;
    dc->SetUserScale(overallScale, overallScale);

    // Calculate conversion factor for converting millimetres into logical
    // units. There are approx. 25.4 mm to the inch. There are ppi device units
    // to the inch. Therefore 1 mm corresponds to ppi/25.4 device units. We also
    // divide by the screen-to-printer scaling factor, because we need to
    // unscale to pass logical units to DrawLine.

    // Draw 50 mm by 50 mm L shape
    double logUnitsFactor = ppiPrinterX / (scale * 25.4);
    int logUnits = int(50 * logUnitsFactor);
    dc->SetPen(* wxBLACK_PEN);
    dc->DrawLine(50, 250, 50 + logUnits, 250);
    dc->DrawLine(50, 250, 50, 250 + logUnits);

    dc->SetBackgroundMode(wxBRUSHSTYLE_TRANSPARENT);
    dc->SetBrush(*wxTRANSPARENT_BRUSH);

    {  //GetTextExtent demo:
        wxString words[7] = { "This ", "is ", "GetTextExtent ",
                             "testing ", "string. ", "Enjoy ", "it!" };
        long x = 200, y= 250;

        dc->SetFont(wxFontInfo(15).Family(wxFONTFAMILY_SWISS));

        for (int i = 0; i < 7; i++)
        {
            wxCoord wordWidth, wordHeight;
            wxString word = words[i];
            word.Remove( word.Len()-1, 1 );
            dc->GetTextExtent(word, &wordWidth, &wordHeight);
            dc->DrawRectangle(x, y, wordWidth, wordHeight);
            dc->GetTextExtent(words[i], &wordWidth, &wordHeight);
            dc->DrawText(words[i], x, y);
            x += wordWidth;
        }

    }

    //dc->SetFont(wxGetApp().GetTestFont());

    dc->DrawText("Some test text", 200, 300 );

    // TESTING

    int leftMargin = 20;
    int rightMargin = 20;
    int topMargin = 20;
    int bottomMargin = 20;

    int pageWidthMM, pageHeightMM;
    GetPageSizeMM(&pageWidthMM, &pageHeightMM);

    int leftMarginLogical = int(logUnitsFactor * leftMargin);
    int topMarginLogical = int(logUnitsFactor * topMargin);
    int bottomMarginLogical = int(logUnitsFactor * (pageHeightMM - bottomMargin));
    int rightMarginLogical = int(logUnitsFactor * (pageWidthMM - rightMargin));

    dc->SetPen(* wxRED_PEN);
    dc->DrawLine(leftMarginLogical, topMarginLogical,
        rightMarginLogical, topMarginLogical);
    dc->DrawLine(leftMarginLogical, bottomMarginLogical,
        rightMarginLogical, bottomMarginLogical);

    WritePageHeader(this, dc, "A header", logUnitsFactor);*/
//}

// Writes a header on a page. Margin units are in millimetres.
bool MyPrintout::WritePageHeader(wxPrintout *printout, wxDC *dc, const wxString&text, double mmToLogical)
{
    int pageWidthMM, pageHeightMM;

    printout->GetPageSizeMM(&pageWidthMM, &pageHeightMM);
    wxUnusedVar(pageHeightMM);

    int leftMargin = 10;
    int topMargin = 10;
    int rightMargin = 10;

    int leftMarginLogical = int(mmToLogical * leftMargin);
    int topMarginLogical = int(mmToLogical * topMargin);
    int rightMarginLogical = int(mmToLogical * (pageWidthMM - rightMargin));

    wxCoord xExtent, yExtent;
    dc->GetTextExtent(text, &xExtent, &yExtent);

    int xPos = int(((((pageWidthMM - leftMargin - rightMargin) / 2.0) + leftMargin) * mmToLogical) - (xExtent / 2.0));
    dc->DrawText(text, xPos, topMarginLogical);

    dc->SetPen(* wxBLACK_PEN);
    dc->DrawLine(leftMarginLogical, topMarginLogical + yExtent,
                 rightMarginLogical, topMarginLogical + yExtent);

    return true;
}

/*void MyApp::Draw(wxDC&dc)
{
    // This routine just draws a bunch of random stuff on the screen so that we
    // can check that different types of object are being drawn consistently
    // between the screen image, the print preview image (at various zoom
    // levels), and the printed page.
    dc.SetBackground(*wxWHITE_BRUSH);
    // dc.Clear();
    dc.SetFont(m_testFont);

    // dc.SetBackgroundMode(wxBRUSHSTYLE_TRANSPARENT);

    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxLIGHT_GREY_BRUSH);

    dc.DrawRectangle(0, 0, dc.FromDIP(230), dc.FromDIP(350));
    dc.DrawLine(0, 0, dc.FromDIP(229), dc.FromDIP(349));
    dc.DrawLine(dc.FromDIP(229), 0, 0, dc.FromDIP(349));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    dc.SetBrush(*wxCYAN_BRUSH);
    dc.SetPen(*wxRED_PEN);

    dc.DrawRoundedRectangle(0, dc.FromDIP(20), dc.FromDIP(200), dc.FromDIP(80), 20);

    dc.DrawText( "Rectangle 200 by 80", dc.FromDIP(40), dc.FromDIP(40));

    dc.SetPen( wxPen(*wxBLACK, 0, wxPENSTYLE_DOT_DASH) );
    dc.DrawEllipse(dc.FromDIP(50), dc.FromDIP(140), dc.FromDIP(100), dc.FromDIP(50));
    dc.SetPen(*wxRED_PEN);

    dc.DrawText( "Test message: this is in 10 point text", dc.FromDIP(10), dc.FromDIP(180));

    dc.DrawRotatedText( "This\nis\na multi-line\ntext", dc.FromDIP(170), dc.FromDIP(100), -m_angle/1.5);

    const char *test = "Hebrew    שלום -- Japanese (日本語)";
    wxString tmp = wxConvUTF8.cMB2WC( test );
    dc.DrawText( tmp, dc.FromDIP(10), dc.FromDIP(200) );

    wxPoint points[5];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = dc.FromDIP(20);
    points[1].y = 0;
    points[2].x = dc.FromDIP(20);
    points[2].y = dc.FromDIP(20);
    points[3].x = dc.FromDIP(10);
    points[3].y = dc.FromDIP(20);
    points[4].x = dc.FromDIP(10);
    points[4].y = dc.FromDIP(-20);
    dc.DrawPolygon( 5, points, dc.FromDIP(20), dc.FromDIP(250), wxODDEVEN_RULE );
    dc.DrawPolygon( 5, points, dc.FromDIP(50), dc.FromDIP(250), wxWINDING_RULE );

    dc.DrawArc( dc.FromDIP(20), dc.FromDIP(330), dc.FromDIP(40), dc.FromDIP(300), dc.FromDIP(20), dc.FromDIP(300) );
    {
        wxDCBrushChanger changeBrush(dc, *wxTRANSPARENT_BRUSH);
        dc.DrawArc( dc.FromDIP(60), dc.FromDIP(330), dc.FromDIP(80), dc.FromDIP(300), dc.FromDIP(60), dc.FromDIP(300) );
    }


    dc.DrawEllipticArc( dc.FromDIP(80), dc.FromDIP(250), dc.FromDIP(60), dc.FromDIP(30), 0.0, 270.0 );

    points[0].x = dc.FromDIP(150);
    points[0].y = dc.FromDIP(250);
    points[1].x = dc.FromDIP(180);
    points[1].y = dc.FromDIP(250);
    points[2].x = dc.FromDIP(180);
    points[2].y = dc.FromDIP(220);
    points[3].x = dc.FromDIP(200);
    points[3].y = dc.FromDIP(220);
    dc.DrawSpline( 4, points );

    wxString str;
    int i = 0;
    str.Printf( "---- Text at angle %d ----", i );
    dc.DrawRotatedText( str, dc.FromDIP(100), dc.FromDIP(300), i );

    i = m_angle;
    str.Printf( "---- Text at angle %d ----", i );
    dc.DrawRotatedText( str, dc.FromDIP(100), dc.FromDIP(300), i );

    wxIcon my_icon = wxICON(sample);

    dc.DrawIcon( my_icon, dc.FromDIP(100), dc.FromDIP(100));

    if (m_bitmap.IsOk())
        dc.DrawBitmap( m_bitmap, dc.FromDIP(10), dc.FromDIP(10) );

#if wxUSE_GRAPHICS_CONTEXT
    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::CreateFromUnknownDC(dc));

    if (gc)
    {
        // make a path that contains a circle and some lines, centered at 100,100
        gc->SetPen( *wxRED_PEN );

        wxGraphicsPath path = gc->CreatePath();
        path.AddCircle( gc->FromDIP(50.0), gc->FromDIP(50.0), gc->FromDIP(50.0) );
        path.MoveToPoint(gc->FromDIP(0.0), gc->FromDIP(50.0));
        path.AddLineToPoint(gc->FromDIP(100.0), gc->FromDIP(50.0));
        path.MoveToPoint(gc->FromDIP(50.0), gc->FromDIP(0.0));
        path.AddLineToPoint(gc->FromDIP(50.0), gc->FromDIP(100.0) );
        path.CloseSubpath();
        path.AddRectangle(gc->FromDIP(25.0), gc->FromDIP(25.0), gc->FromDIP(50.0), gc->FromDIP(50.0));

        gc->StrokePath(path);

        // draw some text
        wxString text("Text by wxGraphicsContext");
        gc->SetFont( m_testFont, *wxBLACK );
        gc->DrawText(text, gc->FromDIP(25.0), gc->FromDIP(60.0));

        // draw rectangle around the text
        double w, h;
        gc->GetTextExtent(text, &w, &h);
        gc->SetPen( *wxBLACK_PEN );
        gc->DrawRectangle(gc->FromDIP(25.0), gc->FromDIP(60.0), w, h);
    }
#endif

}*/