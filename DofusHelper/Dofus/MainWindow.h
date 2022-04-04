#pragma once

#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QApplication>

#include "Logs.h"
#include "common.h"
#include "Characters.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();

public slots:
	void menu_logs_triggered();
	void menu_exit_triggered();

private:
	void create_menu_bar();

	/**
	 * Register our global hotkeys
	 *
	 * @param
			no-param
	 * @return

	 */
	bool Register() {
		FOR(i, MAX_CHARS + 1) {
			if (RegisterHotKey((HWND)winId(), i, MOD_ALT, (VK_NUMPAD0 + i)) == TRUE) {
				qDebug("Register() Successfully register hotkey no: %d", i);
			}
			else {
				qDebug("Register() Failed to register hotkey no: %d", i);
			}
		}
		return true;
	}

	/**
	 * Unregister our global hotkeys
	 *
	 * @param
			no-param
	 * @return

	 */
	bool Unregister() {
		FOR(i, MAX_CHARS + 1) {
			if (UnregisterHotKey((HWND)winId(), i)) {
				qDebug("Unregister() Successfully unregister hotkey no: %d", i);
			}
			else {
				qDebug("Unregister() Failed to unregister hotkey no: %d", i);
			}
		}
		return true;
	}


	/**
	 * Send Hotkeys to Characters
	 * Or get a row's process for a given index
	 *
	 * @param
			int - id of hotkey
	 * @return

	 */
	void HotKey(int id) {
		// qDebug("HotKey() rcvd with id: %d", id);
		characters->HotKey(id);
	}

	/**
	 * QWidget event override for core Windows events
	 *
	 * @param
			void* message - event data
	 * @return
			bool - 

	 */
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) {
		Q_UNUSED(eventType);
		Q_UNUSED(result);

		MSG* msg = reinterpret_cast<MSG*>(message);
		switch (msg->message)
		{
		case WM_HOTKEY:
			HotKey(msg->wParam);
			break;
		}
		return false;
	}


	QMenuBar* menuBar;

	QMenu* fileMenu;
	QMenu* accountMenu;

	QAction* logsAction;
	QAction* exitAction;

	Logs* logs;
	Characters* characters;
};
