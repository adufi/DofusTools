#include "Characters.h"
#include "CharactersRow.h"

CharactersRow::CharactersRow(QWidget* parent, int index)
	: _index(index), QWidget(parent)
{
	const int ICON_SIZE = 32;

	_label_name = new QLabel("", this);
	QLabel* label_index = new QLabel(QString("#%1").arg(index + 1), this);
	QLabel* label_shortcut= new QLabel(QString("Alt+%1").arg(index + 1), this);

	// Init label name and process
	close();

	/* Icons not working
	_button_close = new QPushButton(QIcon(":/../../Resources/cross.png)"), "");
	// QString buttonStyle = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);}";
	// _button_close->setStyleSheet(buttonStyle);
	_button_close->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
	_button_close->setMinimumSize(ICON_SIZE, ICON_SIZE);
	_button_close->setMaximumSize(ICON_SIZE, ICON_SIZE);

	_button_restore = new QPushButton(QIcon("D:/Travail/Projets/Dofus/DofusHelper_v3/DofusHelper_v3/Resources/increase-size-option.png)"), "");
	_button_restore->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
	_button_restore->setMinimumSize(ICON_SIZE, ICON_SIZE);
	_button_restore->setMaximumSize(ICON_SIZE, ICON_SIZE);
	*/

	_button_close = new QPushButton("Close", this);
	_button_restore = new QPushButton("Restore", this);

	setContextMenuPolicy(Qt::CustomContextMenu);

	connect(_button_close, &QPushButton::clicked, this, &CharactersRow::close);
	connect(_button_restore, &QPushButton::clicked, this, &CharactersRow::restore);
	connect(this, SIGNAL(QWidget::customContextMenuRequested(const QPoint&)), this, SLOT(CharactersRow::show_context_menu(const QPoint&)));

	QGridLayout* mainLayout = new QGridLayout;
	mainLayout->addWidget(label_index, 0, 1);
	mainLayout->addWidget(_label_name, 0, 2);
	mainLayout->addWidget(label_shortcut, 0, 3);
	mainLayout->addWidget(_button_restore, 0, 4);
	mainLayout->addWidget(_button_close, 0, 5);

	setLayout(mainLayout);
}

void
CharactersRow::show_context_menu(const QPoint& point) {
	QMenu* menu = new QMenu("Context Menu", this);

	// Add processes
	QVector<Process> ps = Dummy::GetDofusProcesses();
	// ((Characters*)parentWidget())->processes(ps);

	menu->addSection("Clients");

	if (ps.isEmpty()) {
		QAction* action = new QAction("No client(s) found", this);
		action->setDisabled(true);
		menu->addAction(action);
	}
	else {

		for (auto p : ps) {
			QAction* action = new QAction(p._title.c_str(), this);
			action->setData(QVariant((uint)p._hwnd));

			// qDebug("HWND: %d", (uint)p._hwnd);
		
			connect(action, &QAction::triggered, this, &CharactersRow::context_menu_action);
			menu->addAction(action);
		}
	}

	// Close/Restore buttons
	QAction action_close("Close", this);
	QAction action_restore("Restore", this);

	connect(&action_close, &QAction::triggered, this, &CharactersRow::close);
	connect(&action_restore, &QAction::triggered, this, &CharactersRow::restore);

	menu->addSeparator();
	menu->addAction(&action_restore);
	menu->addAction(&action_close);

	// Set menu to cursor position
	menu->exec(mapToGlobal(point));
}

/*
	SLOTS DEFINITIONS
		Close button
		Restore button
		Client Context Menu Action
*/
void 
CharactersRow::close() {
	// Reset label name
	_label_name->setText("Right-click to choose a client");
	_label_name->setStyleSheet("font-style: italic; color: rgba(0, 0, 0, 0.7);");

	// Reset row process
	_process._hwnd = 0;
	_process._title.clear();
}

void 
CharactersRow::restore() {
	qDebug("button_restore_clicked: %d", (uint)_process._hwnd);

	if (_process._hwnd == 0) {
		QMessageBox::StandardButton msg = QMessageBox::information(this, "Informations", "Please choose a client.");
		return;
	}

	// If client no longer exist
	// Notify the user
	// and empty our row
	if (!Dummy::IsHWNDActive(_process._hwnd)) {
		QMessageBox::StandardButton msg = QMessageBox::information(this, "Informations", "Client no longer exist. Row will be emptied.");
		close();
		return;
	}

	Dummy::SetForegroundClient(_process._hwnd);
}

void
CharactersRow::context_menu_action() {
	// Reset row
	close();

	// Retrieve which action was selected
	QAction* action = (QAction*)QObject::sender();

	// Retrieve HWND form action
	QVariant data = action->data();

	Process p = { (HWND)data.value<uint>(), action->text().toStdString() };

	// Test if process is unique
	if (!((Characters*)parentWidget())->unique_process(p._hwnd)) {
		QMessageBox::StandardButton msg = QMessageBox::information(this, "Informations", "Row already exists.");
		return;
	}

	// Save process in CharactersRow
	_process = p;

	// qDebug("context_menu_action: %d", (uint)p._hwnd);

	// Change row title
	_label_name->setText(p._title.c_str());
}

void
CharactersRow::mousePressEvent(QMouseEvent* event) {}

void
CharactersRow::mouseReleaseEvent(QMouseEvent* event) {
	Qt::MouseButton mb = event->button();

	if (mb == Qt::RightButton) {
		// qDebug() << "Right Click";

		show_context_menu(event->pos());
	}
}

