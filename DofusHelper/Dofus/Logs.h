#pragma once

#include <QtWidgets/QTextEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QDialogButtonBox>

typedef enum {
	INFO = 1,
	ERROR = 2,
	UNDEF = 3,
	SUCCESS = 4,
} LogsType;

class LogsFormat 
{
public:
	LogsFormat() {}

	LogsFormat(const LogsType type, const QString msg) : type(type), msg(msg) {}

	LogsType type;
	QString msg;
};

class Logs : public QDialog
{
	Q_OBJECT

public:
	Logs(QWidget* parent = Q_NULLPTR);

	void log(const QString msg);
	void info(const QString msg);
	void error(const QString msg);
	void success(const QString msg);


public slots:

private:
	// Write a LogsFormat to QEditText
	void write(const LogsFormat lf);

	// Initialize QEditText
	void create_text_block();

	// List of every logs entries
	QVector<LogsFormat> logs_list;

	QTextEdit* edit;
	QDialogButtonBox* buttonBox;
};

