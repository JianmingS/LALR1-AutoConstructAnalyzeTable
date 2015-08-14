
// LALR(1) AutoConstructAnalyzeTableDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LALR(1) AutoConstructAnalyzeTable.h"
#include "LALR(1) AutoConstructAnalyzeTableDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLALR1AutoConstructAnalyzeTableDlg �Ի���



CLALR1AutoConstructAnalyzeTableDlg::CLALR1AutoConstructAnalyzeTableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLALR1AutoConstructAnalyzeTableDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	FilePath = "";
}

void CLALR1AutoConstructAnalyzeTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FilePath, m_FilePath);
	DDX_Control(pDX, IDC_LISTDisplay, m_ListDisplay);
}

BEGIN_MESSAGE_MAP(CLALR1AutoConstructAnalyzeTableDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SelectGrammar, &CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedSelectgrammar)
	ON_EN_CHANGE(IDC_FilePath, &CLALR1AutoConstructAnalyzeTableDlg::OnEnChangeFilepath)
	ON_BN_CLICKED(IDC_ConstructAnalysisTable, &CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedConstructanalysistable)
	ON_BN_CLICKED(IDC_First, &CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedFirst)
	ON_BN_CLICKED(IDC_CLOSURE, &CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedClosure)
	ON_BN_CLICKED(IDC_GOTO, &CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedGoto)
END_MESSAGE_MAP()


// CLALR1AutoConstructAnalyzeTableDlg ��Ϣ�������

BOOL CLALR1AutoConstructAnalyzeTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CButton *pBtn = (CButton *)GetDlgItem(IDC_First);
	pBtn->EnableWindow(FALSE);
	pBtn = (CButton *)GetDlgItem(IDC_CLOSURE);
	pBtn->EnableWindow(FALSE);
	pBtn = (CButton *)GetDlgItem(IDC_GOTO);
	pBtn->EnableWindow(FALSE);
	pBtn = (CButton *)GetDlgItem(IDC_ConstructAnalysisTable);
	pBtn->EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLALR1AutoConstructAnalyzeTableDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLALR1AutoConstructAnalyzeTableDlg::OnPaint()
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
HCURSOR CLALR1AutoConstructAnalyzeTableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedSelectgrammar()
{
	CButton *pBtn = (CButton *)GetDlgItem(IDC_First);
	pBtn->EnableWindow(FALSE);
	pBtn = (CButton *)GetDlgItem(IDC_CLOSURE);
	pBtn->EnableWindow(FALSE);
	pBtn = (CButton *)GetDlgItem(IDC_GOTO);
	pBtn->EnableWindow(FALSE);
	pBtn = (CButton *)GetDlgItem(IDC_ConstructAnalysisTable);
	pBtn->EnableWindow(TRUE);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ���ļ�
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("SJM Files (*.sjm)|*.sjm|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		FilePath = dlgFile.GetPathName();
	}
	else {
		MessageBox(_T("�ļ���ʧ�ܣ�"), _T("���棡"), MB_OK);
	}

	m_FilePath.SetWindowTextA(FilePath);
}


void CLALR1AutoConstructAnalyzeTableDlg::OnEnChangeFilepath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_FilePath.GetWindowTextA(FilePath);
}


void CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedConstructanalysistable()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (FilePath.GetLength() == 0) {
		MessageBox(_T("��ѡ���ķ��ļ���"), _T("���棡"), MB_OK);
		return;
	}
	AutoCt.getInfile(string(FilePath));
	AutoCt.ConstructTable();
	makeHead();
	makeTable();
	CButton *pBtn = (CButton *)GetDlgItem(IDC_First);
	pBtn->EnableWindow(TRUE);
	pBtn = (CButton *)GetDlgItem(IDC_CLOSURE);
	pBtn->EnableWindow(TRUE);
	pBtn = (CButton *)GetDlgItem(IDC_GOTO);
	pBtn->EnableWindow(TRUE);
	pBtn = (CButton *)GetDlgItem(IDC_ConstructAnalysisTable);
	pBtn->EnableWindow(FALSE);
}


void CLALR1AutoConstructAnalyzeTableDlg::makeHead() {
	int VnNum = AutoCt.Get_Vn.size();
	int VtNum = AutoCt.Get_Vt.size();
	int allNum = VtNum + VtNum;

	CRect rect;
	m_ListDisplay.GetClientRect(&rect);
	m_ListDisplay.SetExtendedStyle(m_ListDisplay.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListDisplay.InsertColumn(0, "", LVCFMT_CENTER, rect.Width() / allNum, 0);
	CString strTmp = "";
	
	vector<char> charTmpVT;
	vector<char> charTmpVN;
	Set_Ch_Itr it;
	int pos = 1;
	for (it = AutoCt.Get_Vt.begin(); it != AutoCt.Get_Vt.end(); ++it) {
		if ((*it) != '#') {
			charTmpVT.push_back(*it);
			mapCharIntVT.insert(make_pair(*it, pos++));
		}
	}
	mapCharIntVT.insert(make_pair('#', pos++));

	charTmpVN.push_back(AutoCt.getBegin());
	mapCharIntVN.insert(make_pair(AutoCt.getBegin(), pos++));
	for (it = AutoCt.Get_Vn.begin(); it != AutoCt.Get_Vn.end(); ++it) {
		charTmpVN.push_back(*it);
		mapCharIntVN.insert(make_pair(*it, pos++));
	}

	for (int i = 0; i < VtNum; ++i) {
		if (i == VtNum - 1) {
			m_ListDisplay.InsertColumn(i + 1, "#", LVCFMT_CENTER, rect.Width() / allNum, i + 1);
			continue;
		}
		strTmp += charTmpVT[i];
		m_ListDisplay.InsertColumn(i + 1, strTmp, LVCFMT_CENTER, rect.Width() / allNum, i + 1);
		strTmp = "";
	}
	for (int i = 0; i < VnNum; ++i) {
		strTmp += charTmpVN[i];
		m_ListDisplay.InsertColumn(i + 1 + VtNum, strTmp, LVCFMT_CENTER, rect.Width() / allNum, i + 1 + VtNum);
		strTmp = "";
	}
}


void CLALR1AutoConstructAnalyzeTableDlg::makeTable() {
	int totalSta = AutoCt.getTotalSta();
	for (int i = 0; i <= totalSta; ++i) {
		CString strTmp;
		strTmp.Format(_T("%d"), i);
		m_ListDisplay.InsertItem(i, strTmp);
		for (int j = 0; j < AutoCt.Action[i].size(); ++j) {
			strTmp.Format(_T("%d"), AutoCt.Action[i][j].Go);
			if (mapCharIntVT.end() == mapCharIntVT.find(AutoCt.Action[i][j].meet)) {
				MessageBox(_T("���ս������ʧ�ܣ�"), _T("���棡"), MB_OK);
				return;
			}
			if (AutoCt.Action[i][j].Judge != "ACC") {
				m_ListDisplay.SetItemText(i, mapCharIntVT[AutoCt.Action[i][j].meet], AutoCt.Action[i][j].Judge.c_str() + strTmp);
			}
			else {
				m_ListDisplay.SetItemText(i, mapCharIntVT[AutoCt.Action[i][j].meet], AutoCt.Action[i][j].Judge.c_str());
			}

		}
		for (int j = 0; j < AutoCt.GOTO[i].size(); ++j) {
			strTmp.Format(_T("%d"), AutoCt.GOTO[i][j].Go);
			if (mapCharIntVN.end() == mapCharIntVN.find(AutoCt.GOTO[i][j].meet)) {
				MessageBox(_T("���ս������ʧ�ܣ�"), _T("���棡"), MB_OK);
				return;
			}
			m_ListDisplay.SetItemText(i, mapCharIntVN[AutoCt.GOTO[i][j].meet], AutoCt.GOTO[i][j].Judge.c_str() + strTmp);
			
		}
		
	}
}


void CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedgetFirst()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
}


void CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedFirst()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	string myFirst = AutoCt.Get_FIRST_View();
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_Display);
	pBoxOne->SetWindowTextA(myFirst.c_str());

}



void CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedClosure()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	string myFirst = AutoCt.Get_Closure_View();
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_Display);
	pBoxOne->SetWindowTextA(myFirst.c_str());
}


void CLALR1AutoConstructAnalyzeTableDlg::OnBnClickedGoto()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	string myFirst = AutoCt.Get_Goto_View();
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_Display);
	pBoxOne->SetWindowTextA(myFirst.c_str());
}
