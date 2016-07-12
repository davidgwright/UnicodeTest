// UnicodeTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UnicodeTest.h"
#include "UnicodeTestDlg.h"
#include "StudioFile.h"
//#include "UTF8toUTF16.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CStringA UTF16toUTF8(const CStringW& utf16)
{
  LPSTR pszUtf8 = NULL;
  CStringA utf8("");

  if (utf16.IsEmpty()) 
    return utf8; //empty imput string

  size_t nLen16 = utf16.GetLength();
  size_t nLen8 = 0;

  if ((nLen8 = WideCharToMultiByte (CP_UTF8, 0, utf16, nLen16, 
                                    NULL, 0, 0, 0) + 2) == 2)
    return utf8; //conversion error!

  pszUtf8 = new char [nLen8];
  if (pszUtf8)
  {
    memset (pszUtf8, 0x00, nLen8);
    WideCharToMultiByte(CP_UTF8, 0, utf16, nLen16, pszUtf8, nLen8, 0, 0);
    utf8 = CStringA(pszUtf8);
  }

  delete [] pszUtf8;
  return utf8; //utf8 encoded string
}

CStringW UTF8toUTF16(const CStringA& utf8)
{
  LPWSTR pszUtf16 = NULL;
  CStringW utf16("");
  
  if (utf8.IsEmpty()) 
    return utf16; //empty imput string

  size_t nLen8 = utf8.GetLength();
  size_t nLen16 = 0;

  if ((nLen16 = MultiByteToWideChar (CP_UTF8, 0, utf8, nLen8, NULL, 0)) == 0)
    return utf16; //conversion error!

  pszUtf16 = new wchar_t[nLen16];
  if (pszUtf16)
  {
    wmemset (pszUtf16, 0x00, nLen16);
    MultiByteToWideChar (CP_UTF8, 0, utf8, nLen8, pszUtf16, nLen16);
    utf16 = CStringW(pszUtf16);
  }

  delete [] pszUtf16;
  return utf16; //utf16 encoded string
}
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

	return;
	CString fileLocation( GetProgramFolder( ) + L"\\Greek.txt" );
	CString fileLocation16Be( GetProgramFolder( ) + L"\\Greekutf16be.txt" );
	CString fileLocation16le( GetProgramFolder( ) + L"\\Greekutf16le.txt" );
	CString fileLocation16( GetProgramFolder( ) + L"\\Greekutf16.txt" );
	CString fileLocationOut( GetProgramFolder( ) + L"\\OutGreek.txt" );

    //MessageBox( L"αὐτοὶ πρότερον", L"παρίσταταί", MB_OK );
	CStringW debug( L"παρίσταταίε" );//λληνική" );
	::OutputDebugString( L" Compiled in [" );
	::OutputDebugString( debug );
	::OutputDebugString( L"]" );
	::OutputDebugString( L"\n" );

	MessageBox( (PCWSTR)debug, L"Is this Greek?", MB_OK);

	//TRACE( debug );
	//AfxTrace( debug );
	{
		CFile utf8( fileLocation, CFile::modeRead );
		//int fileSize = ( int )utf16le.GetLength( );
		CStringA fileText;
		utf8.Read( fileText.GetBuffer( 200 ), 200 );
		fileText.ReleaseBuffer( ); // What does this do?
		CStringW stringW( CA2W( fileText, CP_UTF8 ) );
		stringW.Append(0);
		::OutputDebugString( L" CA2W [" );
		::OutputDebugString( stringW );
		::OutputDebugString( L"]" );
		::OutputDebugString( L"\n" );
		MessageBox( stringW, L"Is this Greek?", MB_OK);
		return;
	}
	{
		std::ifstream fs;
		fs.open(fileLocation16, std::ios::in | std::ios::binary);
		//fs.seekg(2);		

		//std::locale utf8_locale(std::locale(), new utf8cvt<false>);
		//fs.imbue(utf8_locale);
		wchar_t line[ 300 ];
		fs.read( (char*)line, 299 );
		fs.close( );
		CStringA result = UTF16toUTF8( CStringW( line ) );

		//::OutputDebugString( L"non wide - [" );
		//::OutputDebugString( result );
		//::OutputDebugString( L"]" );
		//::OutputDebugString( L"\n" );
		::OutputDebugString( L"Reading utf16 - [" );
		::OutputDebugString( line );
		::OutputDebugString( L"]" );
		::OutputDebugString( L"\n" );
		MessageBox( line, L"Is this greek?", MB_OK );
	}

	{
		std::wifstream fs;
		//fs.open(fileLocation16Be, std::ios::in | std::ios::binary);
		fs.open(fileLocation16, std::ios::in | std::ios::binary);
		//fs.seekg(2);		

		//std::locale utf8_locale(std::locale(), new utf8cvt<false>);
		//fs.imbue(utf8_locale);
		wchar_t line[ 300 ];
		fs.read( line, 299 );
		fs.close( );
		::OutputDebugString( L"Reading utf16be - [" );
		::OutputDebugString( line );
		::OutputDebugString( L"]" );
		::OutputDebugString( L"\n" );
	}

	{
		std::wifstream fs;
		fs.open(fileLocation16le, std::ios::in | std::ios::binary);
		fs.seekg(2);		
		//std::locale utf8_locale(std::locale(), new utf8cvt<false>);
		//fs.imbue(utf8_locale);
		wchar_t line[ 300 ];
		fs.read( line, 299 );
		fs.close( );
		::OutputDebugString( L"Reading utf16le - [" );
		::OutputDebugString( line );
		::OutputDebugString( L"]" );
		::OutputDebugString( L"\n" );
	}


	{
		std::wifstream fs;
		fs.open(fileLocation, std::ios::in | std::ios::binary);

		//std::locale utf8_locale(std::locale(), new utf8cvt<false>);
		//fs.imbue(utf8_locale);
		wchar_t line[ 300 ];
		fs.read( line, 299 );
		fs.close( );
		::OutputDebugString( L"Setting Locale [" );
		::OutputDebugString( line );
		::OutputDebugString( L"]" );
		::OutputDebugString( L"\n" );
	}
	//CStudioFile file;
	{
		CFile file;
		file.Open( fileLocation, CFile::modeRead );

		//int fd = _open_osfhandle((long)file.m_hFile, 0x0000 );//O_RDONLY);
		//
		//::_setmode(fd, 0x40000);//_O_U8TEXT);
		wchar_t line[ 300 ];
		//file.ReadString( line, true );
		CArchive archive( &file, CArchive::load | CArchive::bNoByteSwap, 256, 0 );
		archive.ReadString( line, 299 );
		::OutputDebugString( L"Archive [" );
		::OutputDebugString( line );
		::OutputDebugString( L"]" );
		::OutputDebugString( L"\n" );
		//MessageBox( line, line, MB_OK );
	}
	{
		std::ifstream file; 
		file.open(fileLocation, std::ifstream::in|std::ifstream::binary);
		wchar_t buffer[2048]; 
		//file.seekg(2);
		file.read((char*)buffer, 2047);
		{
			std::ofstream file2;
			file2.open( fileLocationOut );
			file2.write((char*)buffer, wcslen( buffer ) * sizeof( wchar_t ) );
			file2.close( );
		}

		//CStringA resultA = UTF8Util::ConvertUTF16ToUTF8( buffer );
		/*
		CStringW resultW = UTF8Util::ConvertUTF8ToUTF16( ( char*)buffer );

		::OutputDebugString( L" Conversion [" );
		::OutputDebugString( resultW );
		::OutputDebugString( L"]" );
		::OutputDebugString( L"\n" );
		*/
		//wcscpy( buffer, L"παρίσταταί" );
		::OutputDebugString( L" ifstream [" );
		::OutputDebugString( buffer );
		::OutputDebugString( L"]" );
		::OutputDebugString( L"\n" );
		VARIANT vBuf;
		vBuf.vt = VT_BSTR;
		vBuf.bstrVal = CComBSTR( buffer ).Detach( );
		CStringW test( vBuf );
		::OutputDebugString( L" BSTR [" );
		::OutputDebugString( test );
		::OutputDebugString( L"]" );
		::OutputDebugString( L"\n" );
		//MessageBox( test, L"Is it Greek?", MB_OK );
		file.close();
	}
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
		CString fileLocation( GetProgramFolder( ) + L"\\Greek.txt" );

		CFile utf8( fileLocation, CFile::modeRead );
		//int fileSize = ( int )utf16le.GetLength( );
		CStringA fileText;
		utf8.Read( fileText.GetBuffer( 100 ), 100 );
		fileText.ReleaseBuffer( ); // What does this do?
		CStringW stringW( CA2W( fileText, CP_UTF8 ) );
		stringW.Append(0);
		TheButton.SetWindowText( stringW );

		::MessageBox(*this, 
				L"παρίσταταίε",
				L"Is this greek?", MB_YESNO | MB_ICONHAND );

		XMessageBox( *this, 
				L"παρίσταταίε",
				L"Is this greek?", MB_YESNO | MB_ICONHAND );

		//::AfxMessageBox( stringW );
		//TheButton.SetWindowText( L"παρίσταταί" );
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

