/********************************************************************************
** Form generated from reading UI file 'rawfilterform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAWFILTERFORM_H
#define UI_RAWFILTERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rawFilterForm
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *filtersTab;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *filterTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *includeBtn;
    QPushButton *excludeBtn;
    QWidget *presetsTab;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *presetsTree;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *saveName;
    QPushButton *saveBtn;

    void setupUi(QWidget *rawFilterForm)
    {
        if (rawFilterForm->objectName().isEmpty())
            rawFilterForm->setObjectName(QString::fromUtf8("rawFilterForm"));
        rawFilterForm->resize(665, 434);
        rawFilterForm->setContextMenuPolicy(Qt::CustomContextMenu);
        rawFilterForm->setToolTipDuration(0);
        verticalLayout = new QVBoxLayout(rawFilterForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(rawFilterForm);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        filtersTab = new QWidget();
        filtersTab->setObjectName(QString::fromUtf8("filtersTab"));
        verticalLayout_4 = new QVBoxLayout(filtersTab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_2 = new QLabel(filtersTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setItalic(true);
        label_2->setFont(font);

        verticalLayout_4->addWidget(label_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        filterTable = new QTableWidget(filtersTab);
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
        filterTable->setObjectName(QString::fromUtf8("filterTable"));
        filterTable->setContextMenuPolicy(Qt::CustomContextMenu);
        filterTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        filterTable->setDragDropOverwriteMode(false);
        filterTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
        filterTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        filterTable->setTextElideMode(Qt::ElideLeft);
        filterTable->setGridStyle(Qt::DotLine);
        filterTable->setSortingEnabled(true);
        filterTable->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(filterTable);


        verticalLayout_4->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        includeBtn = new QPushButton(filtersTab);
        includeBtn->setObjectName(QString::fromUtf8("includeBtn"));
        includeBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(includeBtn);

        excludeBtn = new QPushButton(filtersTab);
        excludeBtn->setObjectName(QString::fromUtf8("excludeBtn"));
        excludeBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(excludeBtn);


        verticalLayout_4->addLayout(horizontalLayout);

        tabWidget->addTab(filtersTab, QString());
        presetsTab = new QWidget();
        presetsTab->setObjectName(QString::fromUtf8("presetsTab"));
        verticalLayout_3 = new QVBoxLayout(presetsTab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        presetsTree = new QTreeWidget(presetsTab);
        new QTreeWidgetItem(presetsTree);
        presetsTree->setObjectName(QString::fromUtf8("presetsTree"));
        presetsTree->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_3->addWidget(presetsTree);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(presetsTab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        saveName = new QLineEdit(presetsTab);
        saveName->setObjectName(QString::fromUtf8("saveName"));

        horizontalLayout_2->addWidget(saveName);

        saveBtn = new QPushButton(presetsTab);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));

        horizontalLayout_2->addWidget(saveBtn);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tabWidget->addTab(presetsTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(rawFilterForm);
        QObject::connect(excludeBtn, SIGNAL(clicked()), rawFilterForm, SLOT(excludeSelectedFilters()));
        QObject::connect(includeBtn, SIGNAL(clicked()), rawFilterForm, SLOT(includeSelectedFilters()));
        QObject::connect(presetsTree, SIGNAL(customContextMenuRequested(QPoint)), rawFilterForm, SLOT(showPresetContextMenu(QPoint)));
        QObject::connect(saveBtn, SIGNAL(clicked()), rawFilterForm, SLOT(saveCustom()));
        QObject::connect(saveName, SIGNAL(returnPressed()), rawFilterForm, SLOT(saveCustom()));
        QObject::connect(presetsTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), rawFilterForm, SLOT(activatePresetListClicked()));
        QObject::connect(presetsTree, SIGNAL(itemActivated(QTreeWidgetItem*,int)), rawFilterForm, SLOT(activatePresetListClicked()));
        QObject::connect(filterTable, SIGNAL(cellActivated(int,int)), rawFilterForm, SLOT(toggleSelectedFilter()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(rawFilterForm);
    } // setupUi

    void retranslateUi(QWidget *rawFilterForm)
    {
        rawFilterForm->setWindowTitle(QApplication::translate("rawFilterForm", "Manage Message Filters", nullptr));
        label_2->setText(QApplication::translate("rawFilterForm", "Hint: You can save a custom filter list on the preset tab", nullptr));
        QTableWidgetItem *___qtablewidgetitem = filterTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("rawFilterForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = filterTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("rawFilterForm", "Function", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = filterTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("rawFilterForm", "Origin", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = filterTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("rawFilterForm", "Session Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = filterTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("rawFilterForm", "Filter", nullptr));
#ifndef QT_NO_TOOLTIP
        filterTable->setToolTip(QApplication::translate("rawFilterForm", "These apply to newly received packets. Press 'Refresh Decoded List' to apply them to past packets", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        filterTable->setStatusTip(QApplication::translate("rawFilterForm", "These apply to newly received packets. Press 'Refresh Decoded List' to apply them to past packets", nullptr));
#endif // QT_NO_STATUSTIP
        includeBtn->setText(QApplication::translate("rawFilterForm", "Include Selected", nullptr));
        excludeBtn->setText(QApplication::translate("rawFilterForm", "Exclude Selected", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(filtersTab), QApplication::translate("rawFilterForm", "Filters", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = presetsTree->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("rawFilterForm", "Summary", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("rawFilterForm", "Category", nullptr));

        const bool __sortingEnabled = presetsTree->isSortingEnabled();
        presetsTree->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = presetsTree->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("rawFilterForm", "Builtin", nullptr));
        presetsTree->setSortingEnabled(__sortingEnabled);

        label->setText(QApplication::translate("rawFilterForm", "Save custom preset:", nullptr));
        saveName->setText(QApplication::translate("rawFilterForm", "presetName", nullptr));
        saveBtn->setText(QApplication::translate("rawFilterForm", "Save", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(presetsTab), QApplication::translate("rawFilterForm", "Presets", nullptr));
    } // retranslateUi

};

namespace Ui {
    class rawFilterForm: public Ui_rawFilterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAWFILTERFORM_H
