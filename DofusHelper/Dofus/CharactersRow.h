#pragma once


#include <QtGui/QIcon>
#include <QtGui/QMouseEvent>

#include <Qtcore/QString>
#include <Qtcore/QVariant>

#include <QtWidgets/QMenu>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>

#include "Dummy.h"
#include "common.h"
#include "Helper.h"

/*
	TODO
	 fn Close
		set name to default
		re-init process

	fn Restore
		test hwnd status
		showwindod
		close on need

	remove 
		button_close_clicked
		button_restore_clicked
*/

class CharactersRow :
	public QWidget
{
	Q_OBJECT

public:
	CharactersRow(QWidget* parent = Q_NULLPTR, int index = 0);


public slots:
	void close();
	void restore();

	void context_menu_action();

	void setProcess(const Process p) { _process = p; }
	const Process process() { return _process; }

private:
	// Create a Context Menu
	void show_context_menu(const QPoint& point);

	// Widget Events 
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);


	int _index;
	Process _process;

	QLabel* _label_name;
	QPushButton* _button_close;
	QPushButton* _button_restore;
};

