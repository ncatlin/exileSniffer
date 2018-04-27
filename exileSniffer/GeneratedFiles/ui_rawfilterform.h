/********************************************************************************
** Form generated from reading UI file 'rawfilterform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAWFILTERFORM_H
#define UI_RAWFILTERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rawFilterForm
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *filterTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *includeBtn;
    QPushButton *excludeBtn;
    QPushButton *applyBtn;

    void setupUi(QWidget *rawFilterForm)
    {
        if (rawFilterForm->objectName().isEmpty())
            rawFilterForm->setObjectName(QStringLiteral("rawFilterForm"));
        rawFilterForm->resize(575, 434);
        verticalLayout = new QVBoxLayout(rawFilterForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_3 = new QGroupBox(rawFilterForm);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QFont font;
        font.setPointSize(10);
        groupBox_3->setFont(font);
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        filterTable = new QTableWidget(groupBox_3);
        if (filterTable->columnCount() < 5)
            filterTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        filterTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        filterTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        filterTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        filterTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        filterTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        filterTable->setObjectName(QStringLiteral("filterTable"));
        filterTable->setEditTriggers(QAbstractItemView::SelectedClicked);
        filterTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
        filterTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        filterTable->setTextElideMode(Qt::ElideLeft);
        filterTable->setGridStyle(Qt::DotLine);
        filterTable->setSortingEnabled(true);
        filterTable->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(filterTable);


        verticalLayout_2->addWidget(groupBox_3);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        includeBtn = new QPushButton(rawFilterForm);
        includeBtn->setObjectName(QStringLiteral("includeBtn"));
        includeBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(includeBtn);

        excludeBtn = new QPushButton(rawFilterForm);
        excludeBtn->setObjectName(QStringLiteral("excludeBtn"));
        excludeBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(excludeBtn);

        applyBtn = new QPushButton(rawFilterForm);
        applyBtn->setObjectName(QStringLiteral("applyBtn"));
        applyBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(applyBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(rawFilterForm);
        QObject::connect(excludeBtn, SIGNAL(clicked()), rawFilterForm, SLOT(excludeSelectedFilters()));
        QObject::connect(includeBtn, SIGNAL(clicked()), rawFilterForm, SLOT(includeSelectedFilters()));
        QObject::connect(applyBtn, SIGNAL(clicked()), rawFilterForm, SLOT(applyBtnPress()));

        QMetaObject::connectSlotsByName(rawFilterForm);
    } // setupUi

    void retranslateUi(QWidget *rawFilterForm)
    {
        rawFilterForm->setWindowTitle(QApplication::translate("rawFilterForm", "Form", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("rawFilterForm", "Filter Settings (Right click for presets)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = filterTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("rawFilterForm", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = filterTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("rawFilterForm", "Function", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = filterTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("rawFilterForm", "Origin", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = filterTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("rawFilterForm", "Session Count", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = filterTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("rawFilterForm", "Filter", Q_NULLPTR));
        includeBtn->setText(QApplication::translate("rawFilterForm", "Include Selected", Q_NULLPTR));
        excludeBtn->setText(QApplication::translate("rawFilterForm", "Exclude Selected", Q_NULLPTR));
        applyBtn->setText(QApplication::translate("rawFilterForm", "Apply Filters", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class rawFilterForm: public Ui_rawFilterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAWFILTERFORM_H
