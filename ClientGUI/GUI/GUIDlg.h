
// GUIDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <json/json.h>
#include <afxinet.h>

// CGUIDlg �Ի���
class CGUIDlg : public CDialogEx
{
// ����
public:
	CGUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPasswordChangeEdit();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnUsernameChangeEdit();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void onLoginClicked();
	CComboBox mCombo;

};
