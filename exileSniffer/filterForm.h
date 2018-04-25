#pragma once

#include "ui_rawfilterform.h"
#include "qwidget.h"


#define FILTER_SECTION_ID 0
#define FILTER_SECTION_FUNCTION 1
#define FILTER_SECTION_SENDER 2
#define FILTER_SECTION_COUNT 3
#define FILTER_SECTION_STATE 4

class filterForm : public QWidget
{
	Q_OBJECT
public:
		filterForm(QWidget *parent = 0);
		~filterForm() {};
		void setUI(Ui::rawFilterForm *ptr) { ui = ptr; }
signals:
	void applyFilters();

public Q_SLOTS:
void applyBtnPress() { emit applyFilters(); this->hide(); }
	void includeSelectedFilters();
	void excludeSelectedFilters();
private:
	void setRowColor(int tablerow, QColor colour);
	Ui::rawFilterForm *ui = NULL;
};

class numericSortTableWidgetItem : public QTableWidgetItem {
public:
	numericSortTableWidgetItem() { this->setTextAlignment(Qt::AlignCenter); }
	bool operator <(const QTableWidgetItem &other) const
	{
		return text().toInt() < other.text().toInt();
	}
};