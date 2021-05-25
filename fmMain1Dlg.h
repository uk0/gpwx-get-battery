
// fmMain1Dlg.h : 头文件
//

#pragma once
#include "Public.h"
#include "resource.h"

// fmMain1Dlg 对话框
class fmMain1Dlg : public CDialogEx
{
// 构造
public:
	fmMain1Dlg(CWnd* pParent = NULL);	// 标准构造函数
	void*  workerContext;
// 对话框数据
	enum { IDD = IDD_DIALOG	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	void  setEpc();
	// 生成的消息映射函数B
	NOTIFYICONDATA m_nid;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnClose();
	static DWORD WINAPI NotifyIconProc(LPVOID lpParameter);
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//呵呵，有人会问了这里的线程函数为什么是静态的呢?？大家先思考一下！

	
	void RundbObjInit();


};
