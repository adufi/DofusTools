#pragma once

#include "common.h"
#include <windows.h>

#define LPWSTR char*
#define WIDTH(r) (r.right - r.left)
#define HEIGHT(r) (r.bottom - r.top)

#define DUMMY_LBUTTON 1
#define DUMMY_RBUTTON 2

#pragma comment(lib, "user32.lib")

using namespace std;

typedef struct {
	HWND _hwnd;
	string _title;
	
	// QVector<uint> _pids;
	// QVector<QString> _classnames;
} Process;

class Dummy
{
public:
	/**
	 * Test a given HWND
	 *
	 * @param
			HWND to test
	 * @return
			True if HWND exist
			False if not
	 */
	static bool IsHWNDActive(HWND hwnd) {
		return IsWindow(hwnd);
	}


	/**
	 * Put given window on foreground and give it the focus
	 * ShowWindow + SetForegroundWindow
	 *
	 * @param
			HWND of the window
	 * @return
			
	 */
	static void SetForegroundClient(HWND hwnd) {
		ShowWindow(hwnd, SW_RESTORE);
		SetForegroundWindow(hwnd);
	}


	/**
	 * Get HWND of the foreground window
	 *
	 * @param 
			no-pram
	 * @return
			HWND of the foreground window
	 */
	static HWND GetForegroundClient() {
		return GetForegroundWindow();
	}


	/**
	 * Get Title and HWND of the foreground window
	 *
	 * @param
			HWND pointer (optional)
	 * @return
			Title of the foreground window
			HWND of the foreground window (if pHwnd is specified)
	 */
	static string GetForegroundClientTitle(HWND* pHwnd = nullptr) {
		HWND hwnd = GetForegroundWindow();

		string title(MAX_PATH, L'\0');
		GetWindowTextA(hwnd, &title[0], MAX_PATH);
		
		// If user need hwnd
		if (pHwnd != nullptr)
			*pHwnd = hwnd;

		return title;
	}


	/**
	 * Give every processes with Dofus in its title
	 *
	 * @param
			no-param
	 * @return
			QVector of Process - with every processes with Dofus in its title
	 */
	static QVector<Process> GetDofusProcesses() {		
		bool ok = false;

		HWND fwindow = FindWindowEx(nullptr, nullptr, nullptr, nullptr);
		HWND window = fwindow;

		string windowtext(MAX_PATH, L'\0');
		string consoletitle(MAX_PATH, L'\0');

		QVector<Process> ps;

		GetConsoleTitleA(&windowtext[0], MAX_PATH);

		while (!ok) {
			windowtext = string(MAX_PATH, L'\0');
			
			GetWindowTextA(window, &windowtext[0], MAX_PATH);
			// qDebug("Trying to find Dofus in %s\n", windowtext.c_str());

			if ((windowtext.find("Dofus 2.") != string::npos ||
				windowtext.find("WAKFU") != string::npos) &&
				windowtext.find(consoletitle) == string::npos) {
				
				Process p = { window, windowtext };
				ps.push_back(p);

				// qDebug("Found window with text: %s\n", windowtext.c_str());
			}

			window = FindWindowEx(nullptr, window, nullptr, nullptr);
			if (window == nullptr || window == fwindow) {
				// qDebug("Search complete... with size: %d", _hwnds.size());
				ok = true;
			}
		}
		return ps;
	}


	/**
	 * Give window boundaries for a given HWND
	 *
	 * @param
			HWND - Window handle
	 * @return
			RECT - Window boundaries
	 */
	static RECT GetClientRect(HWND hwnd) {
		SetForegroundClient(hwnd);

		RECT rect;
		GetWindowRect(hwnd, (LPRECT)& rect);

		// Border Glitch - CSS-Like (0, 7, 7, 7)
		rect.left += 7;
		rect.right -= 7;
		rect.bottom -= 7;

		return rect; // 784 - 182 - 1872 - 1047
	}


	static void SendKeyboardEvent(HWND hwnd, uint wVk) {
		/*
		SetForegroundWindow(x);

		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;

		ip.ki.wVk = wVk;
		ip.ki.dwFlags = 0;
		SendInput(1, &ip, sizeof(INPUT));

		ip.ki.wVk = wVk;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(100);
		*/

		// Check HWND
		if (hwnd == 0 ||
			!IsHWNDActive(hwnd))
			return;

		SendMessage(hwnd, WM_KEYDOWN, wVk, 0);
		SendMessage(hwnd, WM_KEYUP, wVk, 0);
	}

	static void SendMouseEvent(HWND hwnd, int dummy_type, LONG dx, LONG dy) {
		/*
		SetForegroundWindow(x);

		INPUT ip;
		ip.type = INPUT_MOUSE;
		ip.mi.mouseData = 0;
		ip.mi.time = 0;
		ip.mi.dwExtraInfo = 0;

		ip.mi.dx = dx;
		ip.mi.dy = dy;
		ip.mi.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &ip, sizeof(INPUT));

		ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(100);

		ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(500);
		*/

		// Check HWND
		if (hwnd == 0 ||
			!IsHWNDActive(hwnd))
			return;

		UINT _1 = 0, _2 = 0;

		switch (dummy_type) {
		case DUMMY_LBUTTON:
			_1 = WM_LBUTTONDOWN;
			_2 = WM_LBUTTONUP;
			break;

		case DUMMY_RBUTTON:
			_1 = WM_RBUTTONDOWN;
			_2 = WM_RBUTTONUP;
			break;

		default:
			break;
		}

		SendMessage(hwnd, _1, MK_LBUTTON, MAKELPARAM(dx, dy));
		SendMessage(hwnd, _2, MK_LBUTTON, MAKELPARAM(dx, dy));
	}

	

	static RECT GetTopClientRect() {
		/*
		// We need to check if the foreground window is a Dofus client
		// Get foreground window informations
		HWND window = GetForegroundWindow();
		HWND fwindow = window;
		string fwindowtext(MAX_PATH, L'\0');
		GetWindowTextA(fwindow, &fwindowtext[0], MAX_PATH);

		// If fwindows is not a Dofus client
		// Set our first client to foreground
		if (fwindowtext.find("Dofus 2.52.11.1") == string::npos) {
			window = _hwnds[0];
			SetForegroundWindow(window);
		}

		// GetClientRect(window, (LPRECT)& rect);
		GetWindowRect(window, (LPRECT)&rect);

		// Border Glitch - CSS-Like (0, 7, 7, 7)
		rect.left += 7;
		rect.right -= 7;
		rect.bottom -= 7;
		*/

		RECT rect;
		return rect; // 784 - 182 - 1872 - 1047
	}

private:
	
};

