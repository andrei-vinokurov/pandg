#include "MyFrame.h"
#include "MyPrintout.h"


//конструктор основного окна
MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, wxT("Список покупок"))
{
    SetIcon (wxICON(icon_frame));  //подключаем логотип через файл res.h
    SetSize(730, 425);
    wxMenu* menuFile = new wxMenu; //меню "Файл"
    menuFile->Append(wxID_SAVE, wxT("Сохранить"), wxT("Сохранить созданный список покупок")); 
    menuFile->AppendSeparator();
    menuFile->Append(wxID_PRINT, wxT("Печать"));
    menuFile->AppendSeparator();
    menuFile->Append(wxID_PAGE_SETUP, wxT("Параметры страницы"));
    menuFile->AppendSeparator();
    menuFile->Append(wxID_PREVIEW, wxT("Предварительный просмотр"));
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, wxT("Выход"), wxT("Выйти из программы"));
    wxMenu* menuHelp = new wxMenu; //меню "Помощь"
    menuHelp->Append(wxID_ABOUT, wxT("О программе"), wxT("Краткая информация о работе программы"));
    wxMenuBar* menuBar = new wxMenuBar; //создание панели Меню
    menuBar->Append(menuFile, wxT("Файл")); //добавление пункта в панель Меню
    menuBar->Append(menuHelp, wxT("Помощь")); //добавление пункта в панель Меню
    SetMenuBar( menuBar ); //установка панели Меню в окно
    wxPanel* panel = new wxPanel(this, ID_Panel, wxPoint (0,0), wxSize (0,0));
    m_myPanel = new MyPanel(panel);
    m_dialogInFrame = new MyDialog(panel);
    CreateStatusBar(); //информационная панель
    SetStatusText(wxT("Добро пожаловать в Список покупок!")); //сообщение в информационной панели
    //привязка функций к пунктам меню
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnPrint, this, wxID_PRINT);
    Bind(wxEVT_MENU, &MyFrame::OnPageSetup, this, wxID_PAGE_SETUP);
    Bind(wxEVT_MENU, &MyFrame::OnPreview, this, wxID_PREVIEW);
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, wxID_SAVE);
}


//выход
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 

//о программе
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(wxT("Эта программа помогает составить список покупок и расчитать примерный бюджет. После составления списка вы можете его сохранить и/или распечатать."),
                 wxT("О программе"), wxOK | wxICON_INFORMATION);
}


//печать
void MyFrame::OnPrint(wxCommandEvent& event)
{
    wxPrintDialogData printDialogData(m_printData);
    printDialogData.EnableSelection(true);
    printDialogData.EnablePageNumbers(true);
    wxPrinter printer(&printDialogData);
    MyPrintout printout(this, &printer.GetPrintDialogData(), "My printout"); 
    printDialogData.SetMinPage(1);
    printDialogData.SetMaxPage(printout.m_numPages);
    printDialogData.SetFromPage(1);
    printDialogData.SetToPage(printout.m_numPages);
    printDialogData.SetAllPages(true);

    SetStatusText("");

    if (!printer.Print(this, &printout, true))
    {
        if (wxPrinter::GetLastError() == wxPRINTER_ERROR)
        {
            wxLogError(wxT("Проблемы печати. Проверьте, вы правильно настроили принтер?"));
        }
        else
        {
            wxLogStatus(wxT("Вы отменили печать"));
        }
    }
    else
    {
        m_printData = printer.GetPrintDialogData().GetPrintData();
    }
}


//предварительный просмотр
void MyFrame::OnPreview(wxCommandEvent& event)
{

    wxPrintDialogData printDialogData(m_printData);

    wxPrinter printer(&printDialogData);

    wxPrintPreview *preview =
        new wxPrintPreview(new MyPrintout(this, &printDialogData), new MyPrintout(this, &printDialogData), &printDialogData);
    if (!preview->IsOk())
    {
        delete preview;
        wxLogError(wxT("Проблемы печати. Проверьте, вы правильно настроили принтер?"));
        return;
    }

    wxPreviewFrame *frame = new wxPreviewFrame(preview, this, wxT("Предварительный просмотр печати"));

frame->Centre(wxBOTH);
frame->Initialize();
frame->Show(true);
}


//параметры страницы
void MyFrame::OnPageSetup(wxCommandEvent& event)
{

    m_pageSetupData = m_printData;

    wxPageSetupDialog pageSetupDialog(this, &m_pageSetupData);
    pageSetupDialog.ShowModal();

    m_printData = pageSetupDialog.GetPageSetupDialogData().GetPrintData();
    m_pageSetupData = pageSetupDialog.GetPageSetupDialogData();
}


//сохранить. Функция сохраняет в txt файл, присваивая имя, включающее текущую дату. 
//Заполнение разделителей с помощью '-' и "|" позволяет создать подобие таблицы
void MyFrame::OnSave(wxCommandEvent& event)
{
    
    if(!m_myPanel->m_vector.empty())

    {

    wxString filename = wxT("Список_покупок_") + wxDateTime::Today().FormatISODate() + ".txt";  //имя файла

    wxTextFile file (filename); //создание файла с именем, созданым в предыдущей строке
    if (!file.Exists())  //если файл не существует
    {
        file.Create(); //создать файл
    }

    if (file.Open()) //открыть файл
    {
    file.Clear(); //очистить файл (актуально, если он был заполнен ранее)
    char fill1 = '-';
    char fill2 = ' ';
    wxString fill3 = "|";

    //определение соответствия названий колонок, заранее определенному количеству символов
    wxString nameColumn1 = m_myPanel->m_nameColumn1;
    if (nameColumn1.size()>3)
    {
        nameColumn1.Remove(3);
    }
    wxString nameColumn2 = m_myPanel->m_nameColumn2;
    if (nameColumn2.size()>25)
    {
        nameColumn2.Remove(25);
    }
    wxString nameColumn3 = m_myPanel->m_nameColumn3;
    if (nameColumn3.size()>12)
    {
        nameColumn3.Remove(12);
    }
    wxString nameColumn4 = m_myPanel->m_nameColumn4;
    if (nameColumn4.size()>10)
    {
        nameColumn4.Remove(10);
    }
    wxString nameColumn5 = m_myPanel->m_nameColumn5;
    if (nameColumn5.size()>24)
    {
        nameColumn5.Remove(24);
    }

    file.AddLine(wxT("Список_покупок_") + wxDateTime::Today().FormatISODate()); //название таблицы (соответствует названию файла)
    file.AddLine (""); //пустая строка

    //шапка таблицы
    file.AddLine (wxString(fill1, 80));
    file.AddLine(fill3 + nameColumn1 + wxString(fill2, (3 - nameColumn1.size())) + fill3 + 
    nameColumn2 + wxString(fill2, (25 - nameColumn2.size())) + fill3 + 
    nameColumn3 + wxString(fill2, (12 - nameColumn3.size())) + fill3 + 
    nameColumn4 + wxString(fill2, (10 - nameColumn4.size())) + fill3 + 
    nameColumn5 + wxString(fill2, (24 - nameColumn5.size())) + fill3);
    file.AddLine (wxString(fill1, 80));

    //заполнение таблицы списком покупок
    for (unsigned int i = 0; i < m_myPanel->m_vector.size(); ++i)
    {
        //определение соответствия содержания элементов, заранее определенному количеству символов
        wxString nameItem1 = m_myPanel->m_listCtrl->GetItemText(i, 0);
        if (nameItem1.size()>3)
        {
            nameItem1.Remove(3);
        }
        wxString nameItem2 = m_myPanel->m_listCtrl->GetItemText(i, 1);
        if (nameItem2.size()>25)
        {
            nameItem2.Remove(25);
        }
        wxString nameItem3 = m_myPanel->m_listCtrl->GetItemText(i, 2);
        if (nameItem3.size()>12)
        {
            nameItem3.Remove(12);
        }
        wxString nameItem4 = m_myPanel->m_listCtrl->GetItemText(i, 3);
        if (nameItem4.size()>10)
        {
            nameItem4.Remove(10);
        }
        wxString nameItem5 = m_myPanel->m_listCtrl->GetItemText(i, 4);
        if (nameItem5.size()>24)
        {
            nameItem5.Remove(24);
        }
        //заполнение строчки
        file.AddLine(fill3 + nameItem1 + wxString(fill2, (3 - nameItem1.size())) + fill3 + 
        nameItem2 + wxString(fill2, (25 - nameItem2.size())) + fill3 + 
        nameItem3 + wxString(fill2, (12 - nameItem3.size())) + fill3 + 
        nameItem4 + wxString(fill2, (10 - nameItem4.size())) + fill3 + 
        nameItem5 + wxString(fill2, (24 - nameItem5.size())) + fill3);
        file.AddLine (wxString(fill1, 80));        
    }

    //значение ИТОГО
    file.AddLine (wxString(fill2, 55) + m_myPanel->m_nameColumn6);
    file.AddLine (wxString(fill2, 55) + m_myPanel->m_listCtrlTotal->GetItemText(0, 0));


    file.Write(wxTextFileType_None); //записать файл

    }

    }

    else
    {
        wxMessageBox(wxT("Список покупок пуст"),
                 wxT("Пустой список"), wxOK | wxICON_INFORMATION);
    }
    
}