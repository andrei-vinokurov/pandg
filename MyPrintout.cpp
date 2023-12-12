#include "MyPrintout.h"


//определяет количество страниц, исходя из 30 наименований на 1 страницу
void MyPrintout::OnPreparePrinting()
{
    wxDC* dc = GetDC(); //получаем контекст устройства
    
    if(!m_frame->m_myPanel->m_vector.empty()) //проверяем есть ли в списке товары
    {
        m_numPages = (m_frame->m_myPanel->m_vector.size() - 1) / 30 + 1;
    }
    else
    {
        m_numPages = 1;
    }

}


//отрисовывает изображение страницы печати и предварительного просмотра
bool MyPrintout::OnPrintPage(int page)
{
    wxDC* dc = GetDC(); //получаем контекст устройства
    if (dc)
    {

        MapScreenSizeToPage(); //устанавлявает масштаб контекста устройства с началом координат в верхним левом углу страницы

        dc->DrawIcon(wxICON(icon_frame), 5, 5); //вывод логотипа на страницу

        dc->DrawText(wxString::Format(wxT("Страница %d"), page), 50, 0); //номер страницы

        dc->DrawText(wxT("Эту программу разработал Андрей Винокуров"), 200, 0); //автор

        long x = 100, y= 100; //переменные для задания координат

        dc->DrawText(wxT("Список покупок ") + wxDateTime::Today().FormatISODate(), x-10, y-60); //вывод заголовка   
        
        //отрисовка
        if(!m_frame->m_myPanel->m_vector.empty()) //проверяем есть ли в списке товары
        {
            //шапка таблицы
            dc->DrawLine(x-10, y-30, x+500, y-30);
            dc->DrawLine(x-10, y-30, x-10, y);
            dc->DrawLine(x+40, y-30, x+40, y);
            dc->DrawLine(x+190, y-30, x+190, y);
            dc->DrawLine(x+290, y-30, x+290, y);
            dc->DrawLine(x+390, y-30, x+390, y);
            dc->DrawLine(x+500, y-30, x+500, y);
            dc->DrawText(m_frame->m_myPanel->m_nameColumn1, x, y-30);
            dc->DrawText(m_frame->m_myPanel->m_nameColumn2, x+50, y-30);
            dc->DrawText(m_frame->m_myPanel->m_nameColumn3, x+200, y-30);
            dc->DrawText(m_frame->m_myPanel->m_nameColumn4, x+300, y-30);
            dc->DrawText(m_frame->m_myPanel->m_nameColumn5, x+400, y-30); 

            //содержимое таблицы
            if (page == m_numPages) //если страница является последней
            {
                for (unsigned int j = 30*(page-1); j < m_frame->m_myPanel->m_vector.size(); ++j)
                {
                    unsigned int i = j - 30*(page-1);
                    dc->DrawLine(x-10, y+30*i, x+500, y+30*i);
                    dc->DrawLine(x-10, y+30*i, x-10, y+30*(i+1));
                    dc->DrawLine(x+40, y+30*i, x+40, y+30*(i+1));
                    dc->DrawLine(x+190, y+30*i, x+190, y+30*(i+1));
                    dc->DrawLine(x+290, y+30*i, x+290, y+30*(i+1));
                    dc->DrawLine(x+390, y+30*i, x+390, y+30*(i+1));
                    dc->DrawLine(x+500, y+30*i, x+500, y+30*(i+1));
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 0), x, y+30*i);
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 1), x+50, y+30*i);
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 2), x+200, y+30*i);
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 3), x+300, y+30*i);
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 4), x+400, y+30*i);
                }
                dc->DrawLine(x-10, y+30*(m_frame->m_myPanel->m_vector.size() - 30*(page-1)), x+500, y+30*(m_frame->m_myPanel->m_vector.size() - 30*(page-1)));
                dc->DrawText(m_frame->m_myPanel->m_nameColumn6, x + 400, y + 30*(m_frame->m_myPanel->m_vector.size()+1 - 30*(page-1)));
                dc->DrawText(m_frame->m_myPanel->m_listCtrlTotal->GetItemText(0, 0), x + 400, y + 30*(m_frame->m_myPanel->m_vector.size()+2 - 30*(page-1)));
            }
            else //если страница не является последней
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
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 0), x, y+30*i);
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 1), x+50, y+30*i);
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 2), x+200, y+30*i);
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 3), x+300, y+30*i);
                    dc->DrawText(m_frame->m_myPanel->m_listCtrl->GetItemText(j, 4), x+400, y+30*i);
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


//определяет мин. и макс. количество страниц
void MyPrintout::GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo)
{
    *minPage = 1;
    *maxPage = m_numPages;
    *selPageFrom = 1;
    *selPageTo = m_numPages;

}


//определяет есть ли страница в документе
bool MyPrintout::HasPage(int pageNum)
{
    return (pageNum >= 1 && pageNum <= m_numPages);
}
