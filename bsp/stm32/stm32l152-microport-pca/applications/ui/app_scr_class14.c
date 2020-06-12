/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
***********************************************************************/

#include "DIALOG.h"
#include "GUI.h"
//#include "ui_common.h"
#include "image_data.h"
#include "string_data.h"
#include "font_data.h"
#include <stdbool.h>
#include "app_scr_class14.h"
#include <stdio.h>
#include "ssz_common.h"
#include "widget_text.h"
#include "widget_image.h"


/*********************************************************************
*
*       Defines
*
***********************************************************************/
#define ID_WINDOW_0     (GUI_ID_USER + 0x00)

#define MessageID1	(GUI_ID_USER + 0x01)
#define MessageID2	(GUI_ID_USER + 0x02)
#define MessageID3	(GUI_ID_USER + 0x03)


/*********************************************************************
*
*       Static data
*
***********************************************************************/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  {WINDOW_CreateIndirect, "app_scr_class14", ID_WINDOW_0, 0, 0, 256, 64, 0, 0x0, 0},
  
};
/*********************************************************************
*
*       Static code
*
***********************************************************************/

static void put_message(uint8_t UIID , uint8_t hour ,uint8_t min,uint8_t seriesID ,uint8_t seriesIDall  ,uint8_t cursor)
{		
	char p[30];
    const char *ptr;
    WM_HWIN hWin;

	hWin = WM_GetDialogItem(ui_get_current_hwin(), MessageID1);
	switch(UIID)
	{
		case 0:
			ptr = get_string(kStreffectivetime);
			break;
		case 1:
			ptr = get_string(kStrworktime);
			break;
		case 2:
			ptr = get_string(kStrbreaktime);
			break;
		case 3:
			ptr = get_string(kStrinternaltime);
			break;
		default:

			break;
	}
	TEXT_SetText(hWin, ptr);
	
    hWin = WM_GetDialogItem(ui_get_current_hwin(), MessageID2);
	sprintf(p, "%d/%d", seriesID,seriesIDall);	
	TEXT_SetText(hWin, p);	

    hWin = WM_GetDialogItem(ui_get_current_hwin(), MessageID3);
    sprintf(p, "%2dhr %2dmin ", hour,min);
	      
    if(cursor == 1)
    {
        TEXT_SetBkColor(hWin,GUI_WHITE);
        TEXT_SetTextColor(hWin,GUI_BLACK);
    }
    else
    {
        TEXT_SetBkColor(hWin,GUI_BLACK);
        TEXT_SetTextColor(hWin,GUI_WHITE);
    }

    TEXT_SetText(hWin, p);
  

}

static void _cbDialog(WM_MESSAGE * pMsg)
{
	GUI_RECT rect;
	WM_HWIN hWin;
	int len;
	const char *ptr;
        char *p;
        uint8_t strlen;
        
	switch (pMsg->MsgId) 
	{
		case WM_CREATE:
			
			break;
			
		case WM_INIT_DIALOG:
			WINDOW_SetBkColor(pMsg->hWin, GUI_BLACK);
                                               
			hWin = TEXT_CreateEx(2, 2, 100, 14, pMsg->hWin, 
				                 WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_LEFT, MessageID1, 0);
			TEXT_SetFont(hWin, get_font(14));
			TEXT_SetBkColor(hWin,GUI_BLACK );
			TEXT_SetTextColor(hWin, GUI_WHITE);
			WM_BringToTop(hWin);
		
			strlen = GUI_GetStringDistX("1/3 ");                                               
			hWin = TEXT_CreateEx(220, 6, strlen, 14, pMsg->hWin, 
				                 WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_HCENTER, MessageID2, 0);
			TEXT_SetFont(hWin, get_font(14));
			TEXT_SetBkColor(hWin,GUI_BLACK );
			TEXT_SetTextColor(hWin, GUI_WHITE);
			WM_BringToTop(hWin);


			strlen = GUI_GetStringDistX("1251.2 mcg/mL");                                               
			hWin = TEXT_CreateEx(89, 25, strlen, 14, pMsg->hWin, 
				                 WM_CF_SHOW, GUI_TA_VCENTER|GUI_TA_HCENTER, MessageID3, 0);
			TEXT_SetFont(hWin, get_font(14));
			TEXT_SetBkColor(hWin,GUI_BLACK );
			TEXT_SetTextColor(hWin, GUI_WHITE);
			WM_BringToTop(hWin);

			break;
	
		case WM_PAINT:
			GUI_SetColor(GUI_WHITE);
			GUI_SetFont(get_font(14));
		
			ptr = get_string(kStrReturn);
			strlen = GUI_GetStringDistX(ptr);
			ui_rect_init_by_size(rect, 2, 46, strlen, 14);
			GUI_DispStringInRect(ptr, &rect, GUI_TA_LEFT|GUI_TA_VCENTER);

			ptr = get_string(kStredit);
			strlen = GUI_GetStringDistX(ptr);
			ui_rect_init_by_size(rect, 220, 46, strlen, 14);
			GUI_DispStringInRect(ptr, &rect, GUI_TA_LEFT|GUI_TA_VCENTER);
			            
			break; 
		
		default:
			  WM_DefaultProc(pMsg);
			  break;
	}
}

/*********************************************************************
*
*       Public code
*
***********************************************************************/
WM_HWIN app_scr_class14_create(type_MsgBody4UICtrlMsg *msg) 
{
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	
	return hWin;
}


int app_scr_class14_update(WM_HWIN hwin, type_MsgBody4UICtrlMsg *msg)
{
	uint8_t hour,min;

	hour = msg->ditem.DataValArray[1] * 10 + msg->ditem.DataValArray[2] ;
	min  = msg->ditem.DataValArray[3] * 10 + msg->ditem.DataValArray[4] ;
	
    put_message(msg->SItem.DataValArray[1],
                hour,
                min ,
                msg->SItem.DataValArray[2],
                msg->SItem.DataValArray[3], 
                msg->CursorIndex.CursorType);

 	return 0;	
}

void app_scr_class14_destroy(WM_HWIN win_id) 
{
	GUI_EndDialog(win_id, 0);
}

/*************************** End of file ****************************/

