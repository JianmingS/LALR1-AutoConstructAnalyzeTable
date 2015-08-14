
// LALR(1) AutoConstructAnalyzeTableDlg.h : ͷ�ļ�
//

#pragma once

#include "afxwin.h"
#include "AutoConstruct.h"
#include "afxcmn.h"
#include <sstream>
#include <map>

// CLALR1AutoConstructAnalyzeTableDlg �Ի���
class CLALR1AutoConstructAnalyzeTableDlg : public CDialogEx
{

private:
	AutoConstruct AutoCt;
	CString FilePath;
	map<char, int> mapCharIntVT;
	map<char, int> mapCharIntVN;
	string forFormatState(int val);
	template <class Type>
	void TypeTostring(Type TypeTmp, string& strTmp);
	void makeHead();
	void makeTable();
// ����
public:
	CLALR1AutoConstructAnalyzeTableDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LALR1AUTOCONSTRUCTANALYZETABLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelectgrammar();
	// �ļ�·��
	CEdit m_FilePath;
	afx_msg void OnEnChangeFilepath();
	afx_msg void OnBnClickedConstructanalysistable();
	// LALR������
	CListCtrl m_ListDisplay;
	afx_msg void OnBnClickedgetFirst();
	afx_msg void OnBnClickedFirst();
	afx_msg void OnBnClickedCLOSURE();
	afx_msg void OnBnClickedGOTO();
	afx_msg void OnBnClickedClosure();
	afx_msg void OnBnClickedGoto();
};
