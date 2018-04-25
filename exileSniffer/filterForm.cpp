#include "stdafx.h"

#include "filterForm.h"

filterForm::filterForm(QWidget *parent)
	: QWidget(parent)
{
}

void filterForm::setRowColor(int tablerow, QColor colour)
{

	for (int tablecolumn = 0; tablecolumn < ui->filterTable->columnCount(); tablecolumn++)
	{
		QTableWidgetItem *item = ui->filterTable->item(tablerow, tablecolumn);
		if (item)
			item->setBackgroundColor(colour);
	}
}

void filterForm::includeSelectedFilters()
{
	QItemSelectionModel *selectionModel = ui->filterTable->selectionModel();
	foreach(QModelIndex index, selectionModel->selectedRows())
	{
		ui->filterTable->item(index.row(), FILTER_SECTION_STATE)->setText("Included");
		setRowColor(index.row(), QColor(230, 250, 180, 255));
	}
}

void filterForm::excludeSelectedFilters()
{
	QItemSelectionModel *selectionModel = ui->filterTable->selectionModel();
	foreach(QModelIndex index, selectionModel->selectedRows())
	{
		ui->filterTable->item(index.row(), FILTER_SECTION_STATE)->setText("Excluded");
		setRowColor(index.row(), QColor(255, 220, 220, 255));
	}
}