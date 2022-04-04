#include "Logs.h"

Logs::Logs(QWidget* parent)
	: QDialog(parent) {

	create_text_block();

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(edit);
	mainLayout->addWidget(buttonBox);

	setWindowTitle("Logs");
	setMinimumSize(600, 500);
	setLayout(mainLayout);
}

void 
Logs::create_text_block() {
	edit = new QTextEdit;
	edit->setReadOnly(true);
}


/*
	Rcv msg with type
		Write it
		Then save it

	PARAMETER:
		msg - QString - message to write
*/
void
Logs::log(const QString msg) {
	const LogsFormat lf = LogsFormat(LogsType::UNDEF, msg);

	write(lf);
	logs_list.push_back(lf);
}

void
Logs::info(const QString msg) {
	const LogsFormat lf = LogsFormat(LogsType::INFO, msg);

	write(lf);
	logs_list.push_back(lf);
}

void
Logs::error(const QString msg) {
	const LogsFormat lf = LogsFormat(LogsType::ERROR, msg);

	write(lf);
	logs_list.push_back(lf);
}

void
Logs::success(const QString msg) {
	const LogsFormat lf = LogsFormat(LogsType::SUCCESS, msg);

	write(lf);
	logs_list.push_back(lf);
}


/*
	Write msg to QTextEdit

	PARAMETER:
		LogsFormat {msg, type}
*/
void 
Logs::write(const LogsFormat lf) {
	QColor color;

	switch (lf.type)
	{
	case LogsType::INFO:
		color = QColor(118, 98, 0);
		break;

	case LogsType::ERROR:
		color = QColor(85, 0, 0);
		break;

	case LogsType::UNDEF:
		color = Qt::black;
		break;

	case LogsType::SUCCESS:
		color = QColor(0, 93, 6);
		break;

	default:
		color = Qt::black;
		break;
	}

	// Write msg to 
	edit->setTextColor(color);
	edit->append(lf.msg);
}