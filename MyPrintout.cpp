#include "MyPrintout.h"


void MyPrintout::OnPreparePrinting()
{
    wxDC* dc = GetDC();
    
    if(!m_frame->m_myPanel->m_vector.empty())
    {
        m_numPages = (m_frame->m_myPanel->m_vector.size() - 1) / 30 + 1;
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
        
        if(!m_frame->m_myPanel->m_vector.empty())
        {
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

            if (page == m_numPages)
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
