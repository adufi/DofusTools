#include "Characters.h"

Characters::Characters(QWidget* parent)
	: QGroupBox(parent)
{
	charactersRows = QVector<CharactersRow*>(MAX_CHARS);

	QVBoxLayout* mainLayout = new QVBoxLayout;

	for (int i = 0; i < charactersRows.size(); ++i) {
		charactersRows[i] = new CharactersRow(this, i);
		mainLayout->addWidget(charactersRows[i]);
	}

	// SubWindow
	_subwindow = new SubWindow(this);
	_sw_button = new QPushButton("Open shadow window (Alt+0)", this);
	mainLayout->addWidget(_sw_button);
	connect(_sw_button, &QPushButton::clicked, this, &Characters::button_sub_window);

	setLayout(mainLayout);
}

void 
Characters::HotKey(int id) {
	// SubWindow
	if (id == 0) {
		_subwindow->show();
	}
	else {
		charactersRows[id - 1]->restore();
	}
}

/*
	################
	PROCESSES HELPER
	################
*/
bool 
Characters::is_active(const HWND hwnd) {
	return !unique_process(hwnd);
}

bool
Characters::unique_process(const HWND hwnd) {
	FOR(i, charactersRows.size()) {
		if (charactersRows[i]->process()._hwnd == hwnd)
			return false;
	}
	return true;
}

const Process
Characters::process() {
	FOR(i, charactersRows.size()) {
		if (charactersRows[i]->process()._hwnd != 0)
			return charactersRows[i]->process();
	}
	return {};
}

const Process
Characters::process(int index) {
	if (index > charactersRows.size() - 1)
		return {};
	return charactersRows[index]->process();
}

const QVector<Process> 
Characters::processes() {
	QVector<Process> ps;
	FOR(i, charactersRows.size())
		ps.push_back(charactersRows[i]->process());
	return ps;
}

/*
	#################
	SLOTS DEFINITIONS
	#################
*/
void
Characters::button_sub_window() {
	_subwindow->show();
}