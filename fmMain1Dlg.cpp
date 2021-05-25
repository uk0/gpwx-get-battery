
#include "stdafx.h"
#include "fmMain1.h"
#include "fmMain1Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include "Public.h"
#include <windows.h>
#include <Lmcons.h>
#include <sys/timeb.h>
#include <time.h>
#include <queue>
#include <thread>
#include <regex>
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include <winuser.h>
#include <conio.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#if !defined(_WINSOCK2API_) && !defined(_WINSOCKAPI_)
struct timeval 
{
	    long tv_sec;
		long tv_usec;
};
#endif 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

union{
	long lngSec;
	char bufSec[4];

}nowSec;

union{
	long lngUSec;
	char bufUSec[4];

}nowUSec;



fmMain1Dlg::fmMain1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(fmMain1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void fmMain1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(fmMain1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_CLOSE()

	ON_WM_TIMER()

END_MESSAGE_MAP()




void fmMain1Dlg::OnClose() {
	
	// close dom
	CDialogEx::OnClose();
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	Shell_NotifyIcon(NIM_DELETE, &m_nid);//关闭软件时卸载托盘图标  
}


BOOL fmMain1Dlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();


	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// resizefile


	HICON m_hicon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));//加载一个托盘图标  
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = m_hWnd;                          //指定窗口句柄  
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;  //指定有效成员  
	m_nid.uCallbackMessage = WM_SYSTEMTRAY;       //自定义消息  
	m_nid.hIcon = m_hicon;                        //指定托盘图标  
	strcpy(m_nid.szTip, _T("Beattery"));           //添加气泡提示  
	::Shell_NotifyIcon(NIM_ADD, &m_nid);          //在托盘区添加图标   
	HANDLE hNotifyTherad = CreateThread(NULL, 0, NotifyIconProc, (LPVOID)&m_nid, 0, NULL);//创建一个线程来更新托盘图标  
	CloseHandle(hNotifyTherad);



	return TRUE;
}




void fmMain1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);


		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR fmMain1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void fmMain1Dlg::RundbObjInit()
{
}

using namespace std;

std::string ltrim(std::string str) {
	return std::regex_replace(str, std::regex("^\\s+"), std::string(""));
}

std::string rtrim(std::string str) {
	return std::regex_replace(str, std::regex(" "), std::string(""));
}

std::string trim(std::string str) {
	return ltrim(rtrim(str));
}




DWORD WINAPI fmMain1Dlg::NotifyIconProc(LPVOID lpParameter)
{
	NOTIFYICONDATA* pnotifyicon = (NOTIFYICONDATA*)lpParameter;//把传递进来的指针转换  

	// 先在工程里面调入几个图标
	HICON m_hstateicon_1 = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));//加载4个图标  
	HICON m_hstateicon_2 = ::LoadIcon(AfxGetInstanceHandle(), NULL);//空图标

		/**
			pnotifyicon->uFlags = NIF_ICON| NIF_TIP;
			pnotifyicon->hIcon = m_hstateicon_2;
			strcpy(pnotifyicon->szTip, _T("1234"));
			::Shell_NotifyIcon(NIM_MODIFY, pnotifyicon);
			Sleep(400);//400ms切换一次
		**/
		
	pnotifyicon->uFlags = NIF_ICON;
	pnotifyicon->hIcon = m_hstateicon_1;
	::Shell_NotifyIcon(NIM_MODIFY, pnotifyicon);
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);
	string s_username(username);
	// 不断的切换托盘图标
		while (true)
			// Administrator
			// C:\Users\{User}\AppData\Local\LGHUB\settings.json
		{

			Debug_TRACE("--------------------------------");
			char buffer[1024];
			const auto Key = std::string("battery/proxwirelessmouse/percentage");

			std::ifstream in("C:\\Users\\" + s_username + "\\AppData\\Local\\LGHUB\\settings.json");
			//std::ifstream in("C:\\Users\\"+ s_username +"\\Desktop\\workspace\\c99_workspace\\logic-ghub-battery-get\\batteryGet\\Debug\\settings.json");
			if (!in.is_open())
			{
				std::cout << "Error opening file"; exit(1);
			}
			std::regex r("\"percentage\":([0-9]*)");
			while (!in.eof())
			{
				in.getline(buffer, 1024);

				std::string str_find(buffer);
				if (str_find.find(Key) != -1) {
					in.getline(buffer, 1024);

					std::string battery(buffer);

					std::string battery1 = trim(battery);

					for (std::sregex_iterator i = std::sregex_iterator(battery1.begin(), battery1.end(), r);
						i != std::sregex_iterator();
						++i)
					{
						std::smatch m = *i;
						
						pnotifyicon->uFlags = NIF_TIP;
						CString c;
						c.Format("5 Seconds ago battery %s", m[1].str().c_str());
						strcpy(pnotifyicon->szTip, _T(c));
						::Shell_NotifyIcon(NIM_MODIFY, pnotifyicon);
					}
					in.close();
				}
			}

			
			Sleep(5000);
		
		}
	return 0;
}


LRESULT fmMain1Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加专用代码和/或调用基类
	switch (message)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_MINIMIZE)
		{
			fmMain1Dlg* dlg = (fmMain1Dlg*)AfxGetApp()->GetMainWnd();//获取窗口CWnd指针  
			HWND hwnd = dlg->m_hWnd;//获取h_hWnd指针  
			::ShowWindow(hwnd, 0);//隐藏界面  
			return TRUE;
		}
		if (wParam == SC_RESTORE)
		{
		}
		break;

	case WM_CLOSE:
		Shell_NotifyIcon(NIM_DELETE, &m_nid);//关闭软件时卸载托盘图标  
		break;
	case WM_SYSTEMTRAY:
	{
		if (wParam != IDR_MAINFRAME)
			return 1;
		switch (lParam)
		{
		case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个"关闭"   
		{
			CMenu menu;
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);     // 得到鼠标位置
			menu.CreatePopupMenu(); // 声明一个弹出式菜单
			SetForegroundWindow();//如果点击弹出菜单的时候,菜单失去焦点让菜单自动关闭
			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("Exit"));// 增加菜单项"关闭"，点击则发送消息WM_DESTROY 给主窗口（已隐藏），将程序结束
			//此类型的菜单需要自定义消息，做消息映射和相关的消息响应函数
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);// 确定弹出式菜单的位置

			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();// 资源回收
			delete lpoint;// 资源回收
			break;
		}
		case WM_LBUTTONDBLCLK://双击左键的处理   
		{
			this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿  
			break;
		}
		case WM_LBUTTONDOWN://单击左键的处理
		{
			this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿 
			break;
		}
		}
	}
	break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}