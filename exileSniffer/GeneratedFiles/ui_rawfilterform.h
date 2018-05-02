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
    QPushButton *applyBtn;
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
            rawFilterForm->setObjectName(QStringLiteral("rawFilterForm"));
        rawFilterForm->resize(585, 434);
        rawFilterForm->setContextMenuPolicy(Qt::CustomContextMenu);
        rawFilterForm->setToolTipDuration(0);
        verticalLayout = new QVBoxLayout(rawFilterForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(rawFilterForm);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        filtersTab = new QWidget();
        filtersTab->setObjectName(QStringLiteral("filtersTab"));
        verticalLayout_4 = new QVBoxLayout(filtersTab);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_2 = new QLabel(filtersTab);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setItalic(true);
        label_2->setFont(font);

        verticalLayout_4->addWidget(label_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
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
        filterTable->setObjectName(QStringLiteral("filterTable"));
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
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        includeBtn = new QPushButton(filtersTab);
        includeBtn->setObjectName(QStringLiteral("includeBtn"));
        includeBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(includeBtn);

        excludeBtn = new QPushButton(filtersTab);
        excludeBtn->setObjectName(QStringLiteral("excludeBtn"));
        excludeBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(excludeBtn);

        applyBtn = new QPushButton(filtersTab);
        applyBtn->setObjectName(QStringLiteral("applyBtn"));
        applyBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(applyBtn);


        verticalLayout_4->addLayout(horizontalLayout);

        tabWidget->addTab(filtersTab, QString());
        presetsTab = new QWidget();
        presetsTab->setObjectName(QStringLiteral("presetsTab"));
        verticalLayout_3 = new QVBoxLayout(presetsTab);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        presetsTree = new QTreeWidget(presetsTab);
        new QTreeWidgetItem(presetsTree);
        presetsTree->setObjectName(QStringLiteral("presetsTree"));
        presetsTree->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_3->addWidget(presetsTree);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(presetsTab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        saveName = new QLineEdit(presetsTab);
        saveName->setObjectName(QStringLiteral("saveName"));

        horizontalLayout_2->addWidget(saveName);

        saveBtn = new QPushButton(presetsTab);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));

        horizontalLayout_2->addWidget(saveBtn);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tabWidget->addTab(presetsTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(rawFilterForm);
        QObject::connect(excludeBtn, SIGNAL(clicked()), rawFilterForm, SLOT(excludeSelectedFilters()));
        QObject::connect(includeBtn, SIGNAL(clicked()), rawFilterForm, SLOT(includeSelectedFilters()));
        QObject::connect(applyBtn, SIGNAL(clicked()), rawFilterForm, SLOT(applyBtnPress()));
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
        rawFilterForm->setWindowTitle(QApplication::translate("rawFilterForm", "Manage Message Filters", Q_NULLPTR));
        label_2->setText(QApplication::translate("rawFilterForm", "Hint: You can save a custom filter list on the preset tab", Q_NULLPTR));
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
#ifndef QT_NO_TOOLTIP
        filterTable->setToolTip(QApplication::translate("rawFilterForm", "These apply to newly received packets. Press 'Refresh Decoded List' to apply them to past packets", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        filterTable->setStatusTip(QApplication::translate("rawFilterForm", "These apply to newly received packets. Press 'Refresh Decoded List' to apply them to past packets", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        includeBtn->setText(QApplication::translate("rawFilterForm", "Include Selected", Q_NULLPTR));
        excludeBtn->setText(QApplication::translate("rawFilterForm", "Exclude Selected", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        applyBtn->setToolTip(QApplication::translate("rawFilterForm", "Filter past entries in the decoded packet list based on the current filters", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        applyBtn->setStatusTip(QApplication::translate("rawFilterForm", "Filters past entries in the decoded packet list based on the current filters", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        applyBtn->setText(QApplication::translate("rawFilterForm", "Refresh Decoded List", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(filtersTab), QApplication::translate("rawFilterForm", "Filters", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = presetsTree->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("rawFilterForm", "Summary", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("rawFilterForm", "Category", Q_NULLPTR));

        const bool __sortingEnabled = presetsTree->isSortingEnabled();
        presetsTree->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = presetsTree->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("rawFilterForm", "Builtin", Q_NULLPTR));
        presetsTree->setSortingEnabled(__sortingEnabled);

        label->setText(QApplication::translate("rawFilterForm", "Save custom preset:", Q_NULLPTR));
        saveName->setText(QApplication::translate("rawFilterForm", "presetName", Q_NULLPTR));
        saveBtn->setText(QApplication::translate("rawFilterForm", "Save", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(presetsTab), QApplication::translate("rawFilterForm", "Presets", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class rawFilterForm: public Ui_rawFilterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAWFILTERFORM_H
