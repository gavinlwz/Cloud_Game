#pragma once



// PortalWindow

class PortalWindow : public CWinApp
{
	DECLARE_DYNCREATE(PortalWindow)

protected:
	PortalWindow();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~PortalWindow();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


