
// GUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGUIDlg �Ի���




CGUIDlg::CGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lpvMem = NULL;
	hMapObject = NULL;
	badMemory=false;
	lastRecordTime=0;
}

void CGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mCombo);
	DDX_Control(pDX, IDC_COMBO2, gameCombo);
	DDX_Control(pDX, IDC_EDIT1, gameIntroduction);
	DDX_Control(pDX, IDC_GAMEPHOTO, gamePhoto);
}

BEGIN_MESSAGE_MAP(CGUIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_PASSWORDEDIT, &CGUIDlg::OnPasswordChangeEdit)
	ON_BN_CLICKED(IDCANCEL, &CGUIDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK,&CGUIDlg::onLoginClicked)
	ON_EN_CHANGE(IDC_USERNAMEEDIT, &CGUIDlg::OnUsernameChangeEdit)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CGUIDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CGUIDlg ��Ϣ�������
void CGUIDlg::onLoginClicked()
{
	CInternetSession session;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
	session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
	CString szHeaders = L"Accept: audio/x-aiff, audio/basic, audio/midi,\
						 audio/mpeg, audio/wav, image/jpeg, image/gif, image/jpg, image/png,\
						 image/mng, image/bmp, text/plain, text/html, text/htm\r\n";
	CString szHeaders2   = L"Content-Type: application/x-www-form-urlencoded;charset=UTF-8";
	CString url;
	int quality=mCombo.GetCurSel()+1;
	int program=gameCombo.GetCurSel()+1;
	url.Format(L"/play?quality=%d&programId=%d",quality,program);
	CHttpConnection* pConnection = session.GetHttpConnection(TEXT("222.200.182.75"),(INTERNET_PORT)8090);
	CHttpFile* pFile = pConnection->OpenRequest( CHttpConnection::HTTP_VERB_GET,
												 url);



	pFile->AddRequestHeaders(szHeaders);
	pFile->AddRequestHeaders(szHeaders2);
	pFile->SendRequest();

	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);

	if(dwRet != HTTP_STATUS_OK)
	{
		CString errText;
		errText.Format(L"������������룺%d", dwRet);
		AfxMessageBox(errText);
		exit(-1);
	}
	else
	{
		int len = pFile->GetLength();
		char buf[2000];
		int numread;
		
		std::string jsonString;
		while ((numread = pFile->Read(buf,sizeof(buf)-1)) > 0)
		{
			//Write to a string
			
			jsonString.append(buf);
			
		}
		  Json::Reader reader;
		  Json::Value root;
		  if (!reader.parse(jsonString, root))
		  {
			  AfxMessageBox(TEXT("�޷��������������صĽ��"));
			  exit(-1);
		  }
		 bool isSuccessful= root["successful"].asBool();
		 if(isSuccessful)
		 {
			 CString program;
			 char *serverAddr=(char *)root["serverIp"].asCString();
			
			 program.Format(TEXT("client.exe -a %s -q %d -p %d"),CString(serverAddr),quality,root["port"].asInt());
			 PROCESS_INFORMATION pi;  	
			STARTUPINFO si; 	
			si.cb = sizeof(STARTUPINFO); 
			si.lpReserved = NULL;   
			si.lpDesktop = NULL;   
			si.lpTitle = NULL;   
			si.dwFlags = 0;   
			si.cbReserved2 = 0;   
			si.lpReserved2 = NULL; 
			CreateProcess(NULL, (LPWSTR)(LPCTSTR)program, NULL, NULL, false, 
                            HIGH_PRIORITY_CLASS, NULL, NULL, &si, &pi);
			exit(0);
			 //AfxMessageBox(program);
			 //system(strbuf.c_str());
		 }
		 else
		 {
			 AfxMessageBox(TEXT("��û��׼���ã�������"));
			 exit(-1);
		 }
	}

	session.Close();
	pFile->Close(); 
	delete pFile;
	
}
BOOL CGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	mCombo.SetCurSel(0);
	gameCombo.SetCurSel(0);
	gameIntroduction.SetReadOnly(true);
	gameIntroduction.SetWindowTextW(TEXT("Dota ��һ�ʱ������Ϸ"));
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDC *pdc=GetDC();
		int Width = pDC->GetDeviceCaps(HORZRES);//��ȡ��ǰ������Ļ�Ŀ�
		int Height = pDC->GetDeviceCaps(VERTRES);//��ȡ��ǰ������Ļ�ĸ�
		CDC memDC;//�ڴ�DC
		memDC.CreateCompatibleDC(pDC);
		ReleaseDC(pdc);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGUIDlg::OnPasswordChangeEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CGUIDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CGUIDlg::OnUsernameChangeEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CGUIDlg::OnCbnSelchangeCombo1()
{
	
	int sel=gameCombo.GetCurSel();
	if(sel==0)
	{
		gameIntroduction.SetWindowTextW(TEXT("Dota ��һ�ʱ������Ϸ"));
		CBitmap bitmap;  // CBitmap�������ڼ���λͼ   
		 HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   
  
		bitmap.LoadBitmap(IDB_BITMAP1);  // ��λͼIDB_BITMAP1���ص�bitmap   
		hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��   
		gamePhoto.SetBitmap(hBmp);    // ����
	}
	else
	{
		gameIntroduction.SetWindowTextW(TEXT("GTA ��һ��ʵʱս����Ϸ"));
		CBitmap bitmap;  // CBitmap�������ڼ���λͼ   
		 HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   
  
		bitmap.LoadBitmap(IDB_BITMAP2);  // ��λͼIDB_BITMAP1���ص�bitmap   
		hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��   
		gamePhoto.SetBitmap(hBmp);    // ����
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
bool CGUIDlg::setupSharedMemory()
{
		hMapObject = CreateFileMapping( 
                INVALID_HANDLE_VALUE,   // use paging file
                NULL,                   // default security attributes
                PAGE_READWRITE,         // read/write access
                0,                      // size: high 32-bits
                SHAREDMEMSIZE,              // size: low 32-bits
                TEXT("ded9dllmemfilemap")); // name of map object
        if (hMapObject == NULL) 
            return FALSE; 
		bool fInit = (GetLastError() != ERROR_ALREADY_EXISTS); 
		lpvMem = (BYTE*)MapViewOfFile( 
                hMapObject,     // object to map view of
                FILE_MAP_WRITE, // read/write access
                0,              // high offset:  map from
                0,              // low offset:   beginning
                0);             // default: map entire file
		if (lpvMem == NULL) 
           return FALSE; 
		if (fInit) 
           memset(lpvMem, '\0', SHAREDMEMSIZE);
		
		return TRUE;
}
void CGUIDlg::uninstallSharedMemory()
{
	if(lpvMem!=NULL)
	UnmapViewOfFile(lpvMem);
	lpvMem=NULL;
	if(hMapObject!=NULL)
	CloseHandle(hMapObject);
	hMapObject=NULL;
	badMemory=false;
	
}