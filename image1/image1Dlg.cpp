
// image1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "image1.h"
#include "image1Dlg.h"
#include "afxdialogex.h"
#include "function.h"
#include "filter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cimage1Dlg �Ի���

Cimage1Dlg::Cimage1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cimage1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cimage1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_process1);
	DDX_Control(pDX, IDC_PROGRESS2, m_process2);
}

BEGIN_MESSAGE_MAP(Cimage1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_OPEN, &Cimage1Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_FIX1, &Cimage1Dlg::OnBnClickedFix1)
	ON_BN_CLICKED(IDC_FIX2, &Cimage1Dlg::OnBnClickedFix2)
END_MESSAGE_MAP()


// Cimage1Dlg ��Ϣ�������

BOOL Cimage1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	GetDlgItem(IDC_FIX1)->EnableWindow(FALSE);
	GetDlgItem(IDC_FIX2)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cimage1Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cimage1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cimage1Dlg::Display(int HWND,BITMAPINFO* pDisBmpInfo,BYTE* pDisBmpData)
{
	//���pictrue�ؼ����ڵľ��
	CWnd *pWnd;
	pWnd=GetDlgItem(HWND);
	//��ȡ����
	CRect rect;
	pWnd->GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
	//��ȡDC(�豸�������������й�)
	CDC *pDC;
	pDC = pWnd->GetDC();//���pictrue�ؼ���DC
	pDC->SetStretchBltMode(COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(),0,0,rect.Width(),rect.Height(),0,0,  pDisBmpInfo->bmiHeader.biWidth,pDisBmpInfo->bmiHeader.biHeight,pDisBmpData,pDisBmpInfo,DIB_RGB_COLORS,SRCCOPY);
	
}

//ȫ��ͼ��ָ��

BITMAPINFO* pBmpInfo = NULL;     //��¼ͼ��ϸ��
BYTE* pBmpData = NULL;           //ͼ������
DWORD dataBytes;				 //ͼ���ֽ���

//���ļ���ť
int button_flag = 0;	//0:��ʾΪ��ͼƬ��1����ʾΪ�ر�ͼƬ
void Cimage1Dlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

//	ID_OPEN

	if(button_flag == 0)
	{
		//��ͼƬ��ť����

		//��¼ѡ���ļ�·��
		CString strFileName;	

		//��¼���ļ�
		CFile bmpFile;			

		BITMAPFILEHEADER bmpHeader;	//�ļ�ͷ
		BITMAPINFOHEADER bmpInfo;	//��Ϣͷ

		//���ļ�
		//CFileDialogΪVC�д��ļ��Ի�����
		CFileDialog dlg(TRUE, "*.BMP", NULL, NULL,"λͼ�ļ�(*.BMP)|*.bmp;*.BMP|",this);	
		if (!dlg.DoModal() == IDOK)
			return;	

		//��ȡ�ļ�·��
		strFileName = dlg.GetPathName();	

		//��ֻ���ķ�ʽ���ļ�

		//���ļ���bmpFile
		if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary))	
			return;

		//��ȡ�ļ�ͷ
		if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))	
		{
			AfxMessageBox("read bmp header failed!");
			return;
		}

		//����ļ������Ƿ�ΪBMP
		//0x424D = "BM"
		if (bmpHeader.bfType != 0x4d42) 
		{
			AfxMessageBox("invalid file type!");
			return;
		}

		//��ȡ��Ϣͷ
		if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		{
			AfxMessageBox("read bmp infor header failed!");
			return;
		}

		//����Ƿ���24λ���ͼ
		if (bmpInfo.biBitCount != 24)
		{
			AfxMessageBox("File is not 24 bit.Application doesn't support this kind of file!");
			return;
		}

		//========================================================================

		//��̬�����ڴ�ռ䣬�����ϢͷbmpInfo
		pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];	
		if (!pBmpInfo)
		{
			AfxMessageBox("memory error!");
			return;
		}

		//��bmpInfo�е���Ϣ������pBmpInfo��ָ��Ŀռ���
		memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));		

		//����ͼ�������ֽ���
		dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;

		//��̬�����ڴ�ռ䣬���ͼ������
		pBmpData = (BYTE*)new char[dataBytes];
		if (!pBmpData)
		{
			AfxMessageBox("memory error!");
			delete pBmpData;
			return;
		}

		//��bmpFile������ݶ�ȡ��д��*pBmpData
		if (bmpFile.Read(pBmpData,dataBytes) != dataBytes)
		{
			AfxMessageBox("Read bmp data failed!");
			delete pBmpInfo;
			delete pBmpData;
			return;
		}
		bmpFile.Close();

		//���ˣ��ļ������Ѿ�������pBmpInfo��pBmpData

		Display(IDC_IMAGE,pBmpInfo,pBmpData);
		
		//�л�Ϊ�ر�ͼƬ��ť
		button_flag = 1;
		SetDlgItemText(ID_OPEN,"�ر�ͼƬ");
		GetDlgItem(IDC_FIX1)->EnableWindow(TRUE);
		GetDlgItem(IDC_FIX2)->EnableWindow(TRUE);
	}
	else
	{
		//�ر�ͼƬ��ť����

		delete[] pBmpInfo;
		delete[] pBmpData;

		dataBytes = 0;

		pBmpInfo = NULL;
		pBmpData = NULL;

		this->RedrawWindow();

		//�л�Ϊ��ͼƬ��ť
		button_flag = 0;
		SetDlgItemText(ID_OPEN,"��ͼƬ");
		GetDlgItem(IDC_FIX1)->EnableWindow(FALSE);
		GetDlgItem(IDC_FIX2)->EnableWindow(FALSE);

	}
}

int flag_fix1 = 0;
void Cimage1Dlg::OnBnClickedFix1()
{
	if (flag_fix1)
	{
		TerminateThread(pThread1, 1);

		SetDlgItemTextA(IDC_FIX1,"ͼ����1");
		flag_fix1 = 0;
		return;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pThread1 = AfxBeginThread(ThreadFunc1,this);
	SetDlgItemTextA(IDC_FIX1,"ֹͣ����");
	flag_fix1 = 1;
}

int flag_fix2 = 0;
void Cimage1Dlg::OnBnClickedFix2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (flag_fix2)
	{
		TerminateThread(pThread2, 1);

		SetDlgItemTextA(IDC_FIX1, "ͼ����2");
		flag_fix2 = 0;
		return;
	}
	pThread2 = AfxBeginThread(ThreadFunc2,this);
	SetDlgItemTextA(IDC_FIX2, "ֹͣ����");
	flag_fix1 = 1;
}



UINT ThreadFunc1(LPVOID lpParam)  
{  
	Cimage1Dlg * dlg = (Cimage1Dlg *)lpParam;
	//ͼ����1

	BYTE* pBmpData1;           //ͼ������
	pBmpData1 = (BYTE*)new char[dataBytes];
	memcpy(pBmpData1,pBmpData,dataBytes);		

	unsigned char *** c;	//ͼ������ָ��
	BMP_To_Matrix(pBmpInfo,pBmpData1,&c);
	Fix1(c,pBmpInfo->bmiHeader.biHeight,pBmpInfo->bmiHeader.biWidth,dlg);
	Matrix_To_BMP(pBmpInfo,pBmpData1,c);

	dlg->Display(IDC_IMAGE_1OUT,pBmpInfo,pBmpData1);

	delete[] pBmpData1;

	return 0;  
}

UINT ThreadFunc2(LPVOID lpParam)  
{  
	Cimage1Dlg * dlg = (Cimage1Dlg *)lpParam;

	//ͼ����2

	//��ͼƬ������һ���µĿռ��£�������ͼ����
	BYTE* pBmpData2;           
	pBmpData2 = (BYTE*)new char[dataBytes];
	memcpy(pBmpData2,pBmpData,dataBytes);		

	unsigned char *** c;	//ͼ������ָ��
	BMP_To_Matrix(pBmpInfo,pBmpData2,&c);
	Fix2(c,pBmpInfo->bmiHeader.biHeight,pBmpInfo->bmiHeader.biWidth,dlg);
	Matrix_To_BMP(pBmpInfo,pBmpData2,c);

	dlg->Display(IDC_IMAGE_2OUT,pBmpInfo,pBmpData2);

	delete[] pBmpData2;

	return 0;  
}

//========================================================================================

/*

	//�����ص����

	CDC *pDC0;
	pDC0 = GetDlgItem(IDC_IMAGE)->GetDC();//���pictrue�ؼ���DC

	for(int y=0;y<bmpInfo.biHeight;y++)
	{
		for(int x=0;x<bmpInfo.biWidth;x++)
		{
			char r,g,b;

			b = c[y][x][0];
			g = c[y][x][1];
			r = c[y][x][2];

			pDC0->SetPixel(x,y,RGB(r,g,b));
		}
	}



*/
