
// image1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// Cimage1Dlg �Ի���
class Cimage1Dlg : public CDialogEx
{
// ����
public:
	Cimage1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	void Display(int HWND,BITMAPINFO* pDisBmpInfo,BYTE* pDisBmpData);

// �Ի�������
	enum { IDD = IDD_IMAGE1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	CWinThread* pThread1;
	CWinThread* pThread2;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnStnClickedNote1();
	afx_msg void OnBnClickedFix1();
	afx_msg void OnBnClickedFix2();

	
	CProgressCtrl m_process1;
	CProgressCtrl m_process2;
};

UINT ThreadFunc1(LPVOID lpParam);
UINT ThreadFunc2(LPVOID lpParam);

