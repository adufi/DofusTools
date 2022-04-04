#pragma once

#include <QtCore/QVector>

#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include "common.h"
#include "Dummy.h"
#include "SubWindow.h"
#include "CharactersRow.h"

class Characters : public QGroupBox
{
	Q_OBJECT

public:
	Characters(QWidget* parent);
	~Characters() {}

	bool is_active(const HWND hwnd);
	bool unique_process(const HWND hwnd);

	/**
	 * Get the first non null process of a row
	 * Or get a row's process for a given index
	 *
	 * @param
			int - index of the row's process
	 * @return
			Process

	 */
	const Process process();
	const Process process(int index);


	/**
	 * Get every processes for our rows
	 *
	 * @param
			no-param
	 * @return
			QVector of Process
	 */
	const QVector<Process> processes();


	// Rcv HotKey from MainWindow
	// Route them to CharactersRows
	// Or open SubWindow
	void HotKey(int id);

public slots:
	void button_sub_window();


private:
	SubWindow* _subwindow;
	QPushButton* _sw_button;

	QVector<CharactersRow *> charactersRows;
};

