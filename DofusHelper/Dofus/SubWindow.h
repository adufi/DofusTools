#pragma once

#include "common.h"
#include "Dummy.h"

#include <QtGui/QPainter>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>

#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>


class SubWindow : public QDialog
{
	Q_OBJECT

public:
	SubWindow(QWidget* subparent, QWidget* parent = Q_NULLPTR);

private:
	QWidget* _subparent;

	void showEvent(QShowEvent* event);
	void paintEvent(QPaintEvent* event);

	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
};

