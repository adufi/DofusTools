#include "SubWindow.h"
#include "Characters.h"

SubWindow::SubWindow(QWidget* subparent, QWidget* parent) : _subparent(subparent),
	QDialog(parent) 
{
	setWindowTitle("DofusHelper - Sub Window");
	setMinimumSize(800, 600);
	setWindowOpacity((qreal)40/100);
	// setWindowFlags(Qt::FramelessWindowHint);
	// setAttribute(Qt::WA_TranslucentBackground);
	// setWindowState(Qt::WindowFullScreen);

	QGridLayout main_layout;
	main_layout.setMargin(5);
	setLayout(&main_layout);
	
	// Init Dummy
	// _dummy.GetDofusProcesses();
}

void 
SubWindow::showEvent(QShowEvent* event) {
	Q_UNUSED(event);

	qDebug("showEvent()");

	// Working HWND
	HWND window = 0;

	// Useful if window is called by a hotkey
	HWND fwindow = Dummy::GetForegroundClient();

	// If FG window is our set it as main
	if (((Characters*)_subparent)->is_active(fwindow)) {
		window = fwindow;
		qDebug("showEvent() - FG window");
	}
	// If not get the first window of our rows
	else {
		window = ((Characters*)_subparent)->process()._hwnd;
		qDebug("showEvent() - Get window with handle: %d", window);
	}

	// If window is null
	if (window == 0) {

		// Set default size
		setMinimumSize(800, 600);
		qDebug("showEvent() - handle is null - set default size");
	}
	else {

		// Get window rect
		RECT r = Dummy::GetClientRect(window);
		qDebug("showEvent() - GetClientRect() - %d - %d - %d - %d", r.left, r.top, WIDTH(r), HEIGHT(r));

		setGeometry(
			r.left, r.top + 30, 
			WIDTH(r), (HEIGHT(r) - 30)
		);

		QRect qr = rect();
		qDebug("showEvent() - Dialog: %d - %d - %d - %d\n", qr.x(), qr.y(), qr.width(), qr.height());
	}
	   	
	// Set current to foreground
	Dummy::SetForegroundClient(window);
	Dummy::SetForegroundClient((HWND)winId());
}

void 
SubWindow::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	QBrush background(QColor(0, 0, 0));

	painter.setBrush(background);
	painter.setPen(Qt::NoPen); // No stroke

	painter.drawRect(0, 0, width(), height());
}

void
SubWindow::keyPressEvent(QKeyEvent* event) {
	QString debug;
	debug += QString("keyPressEvent with key: %1 and mod: ").arg(event->key());

	if (event->modifiers() & Qt::NoModifier)
		debug += "Nomodifier ";
	if (event->modifiers() & Qt::ShiftModifier)
		debug += "ShiftModifier ";
	if (event->modifiers() & Qt::ControlModifier)
		debug += "ControlModifier ";
	if (event->modifiers() & Qt::AltModifier)
		debug += "AltModifier ";
	if (event->modifiers() & Qt::MetaModifier)
		debug += "MetaModifier ";
	if (event->modifiers() & Qt::KeypadModifier)
		debug += "KeypadModifier ";

	qDebug() << debug;
}

void 
SubWindow::keyReleaseEvent(QKeyEvent* event) {
	QString debug;
	debug += QString("keyReleaseEvent with key: %1 and mod: ").arg(event->key());

	if (event->modifiers() & Qt::NoModifier)
		debug += "Nomodifier ";
	if (event->modifiers() & Qt::ShiftModifier)
		debug += "ShiftModifier ";
	if (event->modifiers() & Qt::ControlModifier)
		debug += "ControlModifier ";
	if (event->modifiers() & Qt::AltModifier)
		debug += "AltModifier ";
	if (event->modifiers() & Qt::MetaModifier)
		debug += "MetaModifier ";
	if (event->modifiers() & Qt::KeypadModifier)
		debug += "KeypadModifier ";

	qDebug() << debug;

	VPROCESS ps = ((Characters*)_subparent)->processes();
	qDebug("keyReleaseEvent() ps.size() = %d", ps.size());
	FOR (i, ps.size())
		Dummy::SendKeyboardEvent(ps[i]._hwnd, event->key());
}

void 
SubWindow::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		qDebug("mousePressEvent() with Left Button");
	}
	if (event->button() == Qt::RightButton) {
		qDebug("mousePressEvent() with Right Button");
	}

	qDebug("mousePressEvent() with offset: %1 %2", event->x(), event->y());
 }

void
SubWindow::mouseReleaseEvent(QMouseEvent* event) {
	// Dummy Type
	int _1 = 0;

	if (event->button() == Qt::LeftButton) {
		_1 = DUMMY_LBUTTON;
		qDebug("mouseReleaseEvent() with Left Button");
	}
	if (event->button() == Qt::RightButton) {
		_1 = DUMMY_RBUTTON;
		qDebug("mouseReleaseEvent() with Right Button");
	}

	qDebug("mouseReleaseEvent() with offset: %1 %2", event->x(), event->y());

	// _dummy.SendMouseEvent(0, event->x(), event->y());
	VPROCESS ps = ((Characters*)_subparent)->processes();
	FOR(i, ps.size())
		Dummy::SendMouseEvent(ps[i]._hwnd, _1, event->x(), event->y());
}