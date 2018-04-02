#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_exileSniffer.h"

class exileSniffer : public QMainWindow
{
	Q_OBJECT

public:
	exileSniffer(QWidget *parent = Q_NULLPTR);

private:
	Ui::exileSnifferClass ui;
};
