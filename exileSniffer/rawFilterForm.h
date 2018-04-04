#pragma once

#include "qwidget.h"

class derivedRawFilterForm : public QWidget
{
	Q_OBJECT
public:
		derivedRawFilterForm(QWidget *parent = 0);
		~derivedRawFilterForm() {};
signals:
	void newrawFilters();
public Q_SLOTS:
	void okBtnPress() { emit newrawFilters(); }
};