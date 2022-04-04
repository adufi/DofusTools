#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	// Windows properties
	setWindowTitle("DofusHelper");
	setMinimumSize(800, 600);
	// setWindowOpacity((qreal)20/100);


	// Create our central widget
	QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);


	// Create our main layout
	QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);


	// Menu Bar
	// And add it to our layout
	create_menu_bar();
	mainLayout->setMenuBar(menuBar);


	// Logs
	// + DEBUG
	logs = new Logs;
	logs->log("UNDEF msg");
	logs->info("INFO msg");
	logs->error("ERROR msg");
	logs->success("SUCCESS msg");
	// logs->show();


	// Characters
	characters = new Characters(this);
	mainLayout->addWidget(characters);	
	

	// Register global hotkeys
	Register();
}

MainWindow::~MainWindow() {
	Unregister();
}

void
MainWindow::create_menu_bar() {
	menuBar = new QMenuBar;
	fileMenu = new QMenu(tr("&File"), this);

	logsAction = fileMenu->addAction(tr("&Logs"));
	exitAction = fileMenu->addAction(tr("&Exit"));
	menuBar->addMenu(fileMenu);

	// accountMenu = new QMenu(tr("&Account"), this));



	connect(logsAction, &QAction::triggered, this, &MainWindow::menu_logs_triggered);
	connect(exitAction, &QAction::triggered, this, &MainWindow::menu_exit_triggered);
}


/*
	#################
	SLOTS Definitions
	#################
*/
void
MainWindow::menu_logs_triggered() {
	// Open Logs
	// if (logs->is)
	logs->show();
}

void
MainWindow::menu_exit_triggered() {
	QApplication::quit();
}

