
// fmMain1Dlg.h : ͷ�ļ�
//

#pragma once
#include "Public.h"
#include "resource.h"

// fmMain1Dlg �Ի���
class fmMain1Dlg : public CDialogEx
{
// ����
public:
	fmMain1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	void*  workerContext;
// �Ի�������
	enum { IDD = IDD_DIALOG	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	void  setEpc();
	// ���ɵ���Ϣӳ�亯��B
	NOTIFYICONDATA m_nid;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnClose();
	static DWORD WINAPI NotifyIconProc(LPVOID lpParameter);
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//�Ǻǣ����˻�����������̺߳���Ϊʲô�Ǿ�̬����?�������˼��һ�£�

	
	void RundbObjInit();


};
