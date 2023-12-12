#ifndef MYPANEL_H
#define MYPANEL_H

//подключение заголовочных файлов wxWidgets и приложения, используемых в этом файле (h и cpp)
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/spinCtrl.h>
#include <wx/stattext.h>
#include "MyDialog.h"


//класс MyPanel для размещения основных объектов приложения
class MyPanel : public wxPanel
{
public:
    MyPanel(wxPanel* parent);
    wxPanel* m_parentPanel; //член данных, для получения доступа к родительской панели
    wxListCtrl* m_listCtrl; //таблица со списком
    wxSpinCtrl* m_spinCtrl; //указатель порядкового номера в списке для редактирования/удаления
    wxVector<float*> m_vector; //вектор стоимостей по товарам списка покупок
    wxListCtrl* m_listCtrlTotal; //для итогового значения
    void Adding(wxCommandEvent& event); //добавить
    void EditDelete(wxCommandEvent& event); //редактировать/удалить
    void DeletingOne(wxCommandEvent& event); //удалить один товар из списка
    void Editing(wxCommandEvent& event); //редактировать
    void Canceling(wxCommandEvent& event); //отмена редактирования
    void Deleting(wxCommandEvent& event); //удалить все
    static unsigned int TotalCount(); //подсчет количества наименований в списке
    float TotalCost(); //подсчет общей суммы
    //названия колонок в таблице
    wxString m_nameColumn1 = wxT("№");
    wxString m_nameColumn2 = wxT("Наименование товара");
    wxString m_nameColumn3 = wxT("Цена");
    wxString m_nameColumn4 = wxT("Количество");
    wxString m_nameColumn5 = wxT("Стоимость");
    wxString m_nameColumn6 = wxT("ИТОГО");
   
private:
    wxPanel* m_childPanel1; //дочерняя панель 1
    wxPanel* m_childPanel2;  //дочерняя панель 2
    wxTextCtrl* m_textCtrl1; //текстовое поле для ввода наименования
    wxTextCtrl* m_textCtrl2; //текстовое поле для ввода цены
    wxTextCtrl* m_textCtrl3; //текстовое поле для ввода количества
    wxStaticText* m_text; //текстовое поле с пояснением для пользователя
    static unsigned int s_count; //учет количества добавленных наименований
    static unsigned int s_countDelete;  //учет количества удаленных наименований
    float* m_value1 = 0;
    float* m_value2 = 0; 
};


//идентификаторы некоторых элементов приложения
enum
{
    ID_Panel, ID_Panel1, ID_Panel2
};

#endif