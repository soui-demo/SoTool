// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "MainDlg.h"
#include "import_table_adapter.h"
#include "export_table_adapter.h"
#include "DragDrop.h"


CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:dlg_main"))
{
}

CMainDlg::~CMainDlg()
{
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	//HRESULT hr = ;
	::RegisterDragDrop(m_hWnd, GetDropTarget());

    m_imgMergerHandler.OnInit(this);
    m_codeLineCounter.OnInit(this);
    m_2UnicodeHandler.OnInit(this);
    m_folderScanHandler.OnInit(this);
    m_calcMd5Handler.OnInit(this);

	STreeView * pTreeView1 = FindChildByName2<STreeView>("import_table_treeview");
	STreeView *pTreeView2 = FindChildByName2<STreeView>("export_table_treeview");

	if (pTreeView1&&pTreeView2)
	{
		CImportTableTreeViewAdapter *pImportTableTreeViewAdapter = new CImportTableTreeViewAdapter();
		pTreeView1->SetAdapter(pImportTableTreeViewAdapter);
		pImportTableTreeViewAdapter->Release(); 
		
		CExportTableTreeViewAdapter *pExportTableTreeViewAdapter = new CExportTableTreeViewAdapter();
		pTreeView2->SetAdapter(pExportTableTreeViewAdapter);
		pExportTableTreeViewAdapter->Release();
		RegisterDragDrop(pTreeView1->GetSwnd(), new CTreeViewDropTarget(pTreeView1, pTreeView2));
		RegisterDragDrop(pTreeView2->GetSwnd(), new CTreeViewDropTarget(pTreeView1, pTreeView2));
	}
	return 0;
}


//TODO:消息映射
void CMainDlg::OnClose()
{
	DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

