// UnicodeTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UnicodeTest.h"
#include "UnicodeTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CUnicodeTestDlg dialog

CString GetProgramFilePath( )
{
	CString strFileName;
	TCHAR lpFileName[MAX_PATH+1];
	GetModuleFileName(NULL, lpFileName, MAX_PATH);
	strFileName = lpFileName;
	return strFileName;
}

CString GetProgramFolder( )
{
	CString strFilePath = GetProgramFilePath( );
	int nLastIndex = strFilePath.ReverseFind('\\');
	if (nLastIndex!=-1) {
		return strFilePath.Left(nLastIndex);
	} else {
		return _T("\\");
	}
}

#include <fstream>
//#include <io.h>
//#include <fcntl.h>
//#include <locale>
#include <windows.h>

CUnicodeTestDlg::CUnicodeTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnicodeTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUnicodeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

   DDX_Control( pDX, IDC_BUTTON_MESSAGEBOX, TheButton );
}

BEGIN_MESSAGE_MAP(CUnicodeTestDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CUnicodeTestDlg message handlers

#include "XMessageBox.h"

BOOL CUnicodeTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	{
		/*
		CString fileLocation( GetProgramFolder( ) + L"\\Greek.txt" );

		CFile utf8( fileLocation, CFile::modeRead );
		//int fileSize = ( int )utf16le.GetLength( );
		CStringA fileText;
		utf8.Read( fileText.GetBuffer( 30 ), 30 );
		fileText.ReleaseBuffer( ); // What does this do?
		CStringW stringW( CA2W( fileText, CP_UTF8 ) );
		stringW.Append(0);
		*/

		CStringW greekText( L"παρίσταταί" );

		TheButton.SetWindowText( greekText  );

		::MessageBox(*this, 
				greekText,
				L"Is this greek?", MB_YESNO | MB_ICONHAND );

		XMessageBox( *this, 
				greekText,
				L"Is this greek?", MB_YESNO | MB_ICONHAND );

		//TheButton.SetWindowText(  );
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CUnicodeTestDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_UNICODETEST_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_UNICODETEST_DIALOG));
	}
}
#endif

