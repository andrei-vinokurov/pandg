#include "MyPanel.h"
#include "MyFrame.h"


unsigned int MyPanel::s_count = 0;
unsigned int MyPanel::s_countDelete = 0;


//конструктор класса MyPanel
MyPanel::MyPanel(wxPanel* parent) : wxPanel (parent, wxID_ANY, wxDefaultPosition, wxSize (710, 340), wxBORDER_SUNKEN)
{
    m_parentPanel = parent; //получения доступа к родительской панели
    wxPanel* m_childPanel1 = new wxPanel (this, ID_Panel1, wxPoint (200,310), wxSize (90, 20));
    wxPanel* m_childPanel2 = new wxPanel (this, ID_Panel2, wxPoint (0,190), wxSize (200, 150));
    m_childPanel2->Show(false); //дочерняя панель 2 по умолчанию скрыта   

    //поля для ввода информации
    wxStaticText* text1 = new wxStaticText(this, wxID_ANY, wxT("Введите название товара"), wxPoint (0,0), wxSize (200, 20));
    m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,20), wxSize (200, 20));
    wxStaticText* text2 = new wxStaticText(this, wxID_ANY, wxT("Укажите цену"), wxPoint (0,40), wxSize (200, 20));
    wxFloatingPointValidator<float> val1(2, m_value1, wxNUM_VAL_ZERO_AS_BLANK);
    m_textCtrl2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,60), wxSize (200, 20), 0L, val1);
    wxStaticText* text3 = new wxStaticText(this, wxID_ANY, wxT("Укажите количество"), wxPoint (0,80), wxSize (200, 20));
    wxFloatingPointValidator<float> val2(3, m_value2, wxNUM_VAL_ZERO_AS_BLANK);
    m_textCtrl3 = new wxTextCtrl(this, wxID_ANY, "", wxPoint (0,100), wxSize (200, 20), 0L, val2);

    //кнопки управления
    wxButton* button1 = new wxButton (this, wxID_ANY, wxT("Добавить"), wxPoint (25,130), wxSize (150, 20));
    wxButton* button2 = new wxButton (this, wxID_ANY, wxT("Редактировать/Удалить"), wxPoint (25,170), wxSize (150, 20)); 

    wxStaticText* m_text = new wxStaticText(m_childPanel2, wxID_ANY, wxT("Выберите номер в списке"), wxPoint (20, 20), wxSize (160, 20), wxALIGN_CENTRE_HORIZONTAL);  

    //кнопки редактирования
    wxButton* button3 = new wxButton (m_childPanel2, wxID_ANY, wxT("Редактировать"), wxPoint (5, 90), wxSize (90, 20)); 
    wxButton* button4 = new wxButton (m_childPanel2, wxID_ANY, wxT("Удалить"), wxPoint (105, 90), wxSize (90, 20)); 
    wxButton* button5 = new wxButton (m_childPanel2, wxID_ANY, wxT("Отмена"), wxPoint (50, 120), wxSize (90, 20));
    
    //поле, определяющее номер в списке покупок для редактирования
    m_spinCtrl = new wxSpinCtrl(m_childPanel2, wxID_ANY, wxEmptyString, wxPoint (70, 50), wxSize (60, 20), wxSP_ARROW_KEYS | wxALIGN_CENTRE_HORIZONTAL, 1);

    //кнопка удаления всего списка
    wxButton* button6 = new wxButton (m_childPanel1, wxID_ANY, wxT("Удалить все"), wxPoint (0,0), wxSize (90, 20));

    //создание таблицы, добавление колонок
    m_listCtrl = new wxListCtrl (this, wxID_ANY, wxPoint (200,0), wxSize (510, 300), wxLC_REPORT);
    m_listCtrl->AppendColumn (m_nameColumn1, wxLIST_FORMAT_CENTER, 30);
    m_listCtrl->AppendColumn (m_nameColumn2, wxLIST_FORMAT_CENTER, 150);
    m_listCtrl->AppendColumn (m_nameColumn3, wxLIST_FORMAT_CENTER, 110);
    m_listCtrl->AppendColumn (m_nameColumn4, wxLIST_FORMAT_CENTER, 110);
    m_listCtrl->AppendColumn (m_nameColumn5, wxLIST_FORMAT_CENTER, 110);

    //ячейки для итоговой суммы
    m_listCtrlTotal = new wxListCtrl (this, wxID_ANY, wxPoint (600,300), wxSize (110, 40), wxLC_REPORT);
    m_listCtrlTotal->AppendColumn (m_nameColumn6, wxLIST_FORMAT_CENTER, 110);
    m_listCtrlTotal->InsertItem (0, "0");

    //привязка кнопок и функций
    button1->Bind(wxEVT_BUTTON, &MyPanel::Adding, this);
    button2->Bind(wxEVT_BUTTON, &MyPanel::EditDelete, this);
    button3->Bind(wxEVT_BUTTON, &MyPanel::Editing, this);
    button4->Bind(wxEVT_BUTTON, &MyPanel::DeletingOne, this);
    button5->Bind(wxEVT_BUTTON, &MyPanel::Canceling, this);
    button6->Bind(wxEVT_BUTTON, &MyPanel::Deleting, this);
    
}


//добавить наименование в список
void MyPanel::Adding (wxCommandEvent& event)
{
    if (!m_textCtrl1->IsEmpty() && !m_textCtrl2->IsEmpty() && !m_textCtrl3->IsEmpty()){    //проверка, чтобы все поля ввода были заполнены  
    m_listCtrl->InsertItem (TotalCount(), ""); //добавляет элемент
    m_listCtrl->SetItem (TotalCount(), 0, wxString::Format(wxT("%d"), TotalCount()+1), -1); //номер по порядку в таблице
    m_listCtrl->SetItem (TotalCount(), 1, m_textCtrl1->GetValue(), -1); //передача наименования товара и из поля ввода
    m_listCtrl->SetItem (TotalCount(), 2, m_textCtrl2->GetValue(), -1); //передача стоимости из поля ввода
    double price;
    m_textCtrl2->GetValue().ToDouble(&price); //преобразование данных из поля ввода типа wxString в тип double
    m_listCtrl->SetItem (TotalCount(), 3, m_textCtrl3->GetValue(), -1); //передача количества из поля ввода
    double quantity;
    m_textCtrl3->GetValue().ToDouble(&quantity); //преобразование данных из поля ввода типа wxString в тип double
    float* total = new float (price*quantity); //получение стоимости по определенному товару
    m_listCtrl->SetItem (TotalCount(), 4, wxString::Format(wxT("%.2f"), *total), -1); //передача стоимости по определенному товару в таблицу
    m_vector.push_back(total); //занесение стоимости в вектор стоимостей
    m_listCtrlTotal->SetItemText (0, wxString::Format(wxT("%.2f"), TotalCost())); //обновление итоговой суммы
    
    //очистить поля ввода
    m_textCtrl1->SetValue("");
    m_textCtrl2->SetValue("");
    m_textCtrl3->SetValue("");

    s_count++; //увеличивает количество добавленных наименований на 1
    }
    else
    {
        wxMessageBox(wxT("Наименование товара, цена или количество указаны некорректно"),
                 wxT("Ошибка"), wxOK | wxICON_INFORMATION);
    }
}


//подсчет количества наименований в списке
unsigned int MyPanel::TotalCount()
{
    return (s_count-s_countDelete);
}


//подсчет итоговой суммы
float MyPanel::TotalCost()
{
    float cost = 0;
    for(unsigned int i = 0; i < m_vector.size(); ++i)
    {
        cost += *m_vector[i];
    }
    return cost;
}


//редактировать список или удалить товар из него
void MyPanel::EditDelete(wxCommandEvent& event)
{
    if(m_vector.empty())
    {
        wxMessageBox(wxT("Список покупок пуст"),
                 wxT("Пустой список"), wxOK | wxICON_INFORMATION);
    }
    else
    {
        FindWindow (ID_Panel2)->Show(true); //показывает элементы управления для редактирования
        FindWindow (ID_Panel1)->Show(false); //скрывает кнопку "удалить все"
        
    }
}


//редактировать данные по товару в списке
void MyPanel::Editing(wxCommandEvent& event)
{
    if (m_vector.size() > (m_spinCtrl->GetValue()-1)) //проверка, есть ли такой порядковый номер в списке
    {
            //получение доступа к диалогу через родительскую панель m_parentPanel
            MyFrame* frameFromDialog = (MyFrame*) m_parentPanel->GetParent();
            MyDialog* dlg = frameFromDialog->m_dialogInFrame;
            //передача в диалог редактируемых значений
            dlg->m_textctrlDialog1->SetValue(m_listCtrl->GetItemText((m_spinCtrl->GetValue()-1), 1));
            dlg->m_textctrlDialog2->SetValue(m_listCtrl->GetItemText((m_spinCtrl->GetValue()-1), 2));
            dlg->m_textctrlDialog3->SetValue(m_listCtrl->GetItemText((m_spinCtrl->GetValue()-1), 3));

            dlg->ShowModal(); //модальное отображение диалога

    }
    else
    {
            wxMessageBox(wxT("В списке нет такого порядкового номера"),
                 wxT("Товар не найден"), wxOK | wxICON_INFORMATION);
            
    }
    FindWindow(ID_Panel2)->Show(false); //скрывает элементы управления для редактирования
    FindWindow(ID_Panel1)->Show(true); //показывает кнопку "удалить все"
}


//удалить один товар в списке
void MyPanel::DeletingOne(wxCommandEvent& event)
{
    if (m_vector.size() > (m_spinCtrl->GetValue()-1)) //проверка, есть ли такой порядковый номер в списке
    {
            m_listCtrl->DeleteItem(m_spinCtrl->GetValue()-1); //удаляет элемент
            s_countDelete++; //увеличивает количество удаленных наименований на 1
            
            //обновление порядковых номеров в списке
            for (unsigned int i = (m_spinCtrl->GetValue()-1); i < TotalCount(); i++)
            {
                m_listCtrl->SetItem (i, 0, wxString::Format(wxT("%d"), i+1), -1);
            }

            m_listCtrlTotal->SetItemText (0, wxString::Format(wxT("%.2f"), (TotalCost()-*m_vector[m_spinCtrl->GetValue()-1]))); //пересчет итоговой суммы

            delete m_vector[m_spinCtrl->GetValue()-1]; //удаление памяти под элемент вектора стоимостей из кучи
            m_vector[m_spinCtrl->GetValue()-1] = 0;  //нулевой указатель
            m_vector.erase(m_vector.begin()+m_spinCtrl->GetValue()-1); //удаление элемента вектора стоимостей
    }
    else
    {
            wxMessageBox(wxT("В списке нет такого порядкового номера"),
                 wxT("Товар не найден"), wxOK | wxICON_INFORMATION);
            
    }
    FindWindow(ID_Panel2)->Show(false); //скрывает элементы управления для редактирования
    FindWindow(ID_Panel1)->Show(true); //показывает кнопку "удалить все"
}


//отмена редактирования или удаления
void MyPanel::Canceling(wxCommandEvent& event)
{
    FindWindow(ID_Panel2)->Show(false); //скрывает элементы управления для редактирования
    FindWindow(ID_Panel1)->Show(true); //показывает кнопку "удалить все"
}


//удалить все
void MyPanel::Deleting (wxCommandEvent& event)
{
    m_listCtrl->DeleteAllItems(); //удаление всех элементов

    //освобождение динамической памяти
    for(unsigned int i = 0; i < m_vector.size(); ++i)
    {
        delete m_vector[i];
        m_vector[i] = 0;
    }

    m_vector.clear(); //удаление элементов вектора стоимостей
    s_count = 0; //обнуление количества добавленных наименований
    s_countDelete = 0; //обнуление количества удаленных наименований
    m_listCtrlTotal->SetItemText (0, "0"); //обнуление итоговой суммы
}