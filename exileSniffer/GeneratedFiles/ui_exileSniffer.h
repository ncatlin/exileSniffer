/********************************************************************************
** Form generated from reading UI file 'exileSniffer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXILESNIFFER_H
#define UI_EXILESNIFFER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_exileSniffer
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *processTabs;
    QWidget *interceptionTab;
    QVBoxLayout *verticalLayout;
    QFrame *statusFrame;
    QFormLayout *formLayout;
    QLabel *statusInfoText;
    QLabel *statusInfoLabel;
    QLabel *statusLabel;
    QLabel *statusText;
    QWidget *decodeTab;
    QGridLayout *gridLayout_3;
    QFrame *decodeDisplayFrame;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QFrame *decodedControlFrame;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *decodedAutoscrollCheck;
    QFrame *decodedLabelFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *decodedDisplayedLabel;
    QPushButton *decodedFiltersBtn;
    QSplitter *splitter;
    QTableWidget *decodedListTable;
    QPlainTextEdit *decodedText;
    QWidget *rawDecryptTab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *textPaneFrame;
    QTextEdit *ptHexPane;
    QTextEdit *ptASCIIPane;
    QHBoxLayout *rawControls;
    QFrame *bytesPerRowFrame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *bytesRowLael;
    QComboBox *bytesRowCombo;
    QCheckBox *rawLinewrapCheck;
    QCheckBox *rawAutoScrollCheck;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *filterLabel;
    QPushButton *filtersBtn;
    QWidget *metaLogTab;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *metaLog;
    QMenuBar *menuBar;
    QMenu *menuGame_Instances;
    QMenu *menuSettings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *exileSniffer)
    {
        if (exileSniffer->objectName().isEmpty())
            exileSniffer->setObjectName(QStringLiteral("exileSniffer"));
        exileSniffer->resize(827, 673);
        centralWidget = new QWidget(exileSniffer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        processTabs = new QTabWidget(centralWidget);
        processTabs->setObjectName(QStringLiteral("processTabs"));
        processTabs->setTabPosition(QTabWidget::North);
        interceptionTab = new QWidget();
        interceptionTab->setObjectName(QStringLiteral("interceptionTab"));
        verticalLayout = new QVBoxLayout(interceptionTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        statusFrame = new QFrame(interceptionTab);
        statusFrame->setObjectName(QStringLiteral("statusFrame"));
        statusFrame->setMaximumSize(QSize(16777215, 100));
        statusFrame->setFrameShape(QFrame::StyledPanel);
        statusFrame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(statusFrame);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        statusInfoText = new QLabel(statusFrame);
        statusInfoText->setObjectName(QStringLiteral("statusInfoText"));
        statusInfoText->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(12);
        statusInfoText->setFont(font);
        statusInfoText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        statusInfoText->setIndent(12);

        formLayout->setWidget(3, QFormLayout::FieldRole, statusInfoText);

        statusInfoLabel = new QLabel(statusFrame);
        statusInfoLabel->setObjectName(QStringLiteral("statusInfoLabel"));
        QFont font1;
        font1.setPointSize(13);
        statusInfoLabel->setFont(font1);

        formLayout->setWidget(3, QFormLayout::LabelRole, statusInfoLabel);

        statusLabel = new QLabel(statusFrame);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, statusLabel);

        statusText = new QLabel(statusFrame);
        statusText->setObjectName(QStringLiteral("statusText"));
        statusText->setMaximumSize(QSize(16777215, 16777215));
        statusText->setFont(font1);
        statusText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        statusText->setIndent(12);

        formLayout->setWidget(2, QFormLayout::FieldRole, statusText);


        verticalLayout->addWidget(statusFrame);

        processTabs->addTab(interceptionTab, QString());
        decodeTab = new QWidget();
        decodeTab->setObjectName(QStringLiteral("decodeTab"));
        gridLayout_3 = new QGridLayout(decodeTab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, -1, -1, 5);
        decodeDisplayFrame = new QFrame(decodeTab);
        decodeDisplayFrame->setObjectName(QStringLiteral("decodeDisplayFrame"));
        decodeDisplayFrame->setFrameShape(QFrame::StyledPanel);
        decodeDisplayFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(decodeDisplayFrame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        decodedControlFrame = new QFrame(decodeDisplayFrame);
        decodedControlFrame->setObjectName(QStringLiteral("decodedControlFrame"));
        decodedControlFrame->setFrameShape(QFrame::StyledPanel);
        decodedControlFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(decodedControlFrame);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 3, -1, 3);
        decodedAutoscrollCheck = new QCheckBox(decodedControlFrame);
        decodedAutoscrollCheck->setObjectName(QStringLiteral("decodedAutoscrollCheck"));
        decodedAutoscrollCheck->setLayoutDirection(Qt::LeftToRight);
        decodedAutoscrollCheck->setChecked(true);

        horizontalLayout_6->addWidget(decodedAutoscrollCheck);


        horizontalLayout_5->addWidget(decodedControlFrame);

        decodedLabelFrame = new QFrame(decodeDisplayFrame);
        decodedLabelFrame->setObjectName(QStringLiteral("decodedLabelFrame"));
        decodedLabelFrame->setMinimumSize(QSize(0, 0));
        decodedLabelFrame->setFrameShape(QFrame::StyledPanel);
        decodedLabelFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(decodedLabelFrame);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 3, -1, 3);
        decodedDisplayedLabel = new QLabel(decodedLabelFrame);
        decodedDisplayedLabel->setObjectName(QStringLiteral("decodedDisplayedLabel"));

        horizontalLayout_3->addWidget(decodedDisplayedLabel);

        decodedFiltersBtn = new QPushButton(decodedLabelFrame);
        decodedFiltersBtn->setObjectName(QStringLiteral("decodedFiltersBtn"));
        decodedFiltersBtn->setMaximumSize(QSize(69, 16777215));

        horizontalLayout_3->addWidget(decodedFiltersBtn);


        horizontalLayout_5->addWidget(decodedLabelFrame);


        verticalLayout_3->addLayout(horizontalLayout_5);

        splitter = new QSplitter(decodeDisplayFrame);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(2);
        decodedListTable = new QTableWidget(splitter);
        if (decodedListTable->columnCount() < 4)
            decodedListTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        decodedListTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        decodedListTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        decodedListTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        decodedListTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        decodedListTable->setObjectName(QStringLiteral("decodedListTable"));
        decodedListTable->setContextMenuPolicy(Qt::CustomContextMenu);
        decodedListTable->setLayoutDirection(Qt::LeftToRight);
        decodedListTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        decodedListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        decodedListTable->setProperty("showDropIndicator", QVariant(false));
        decodedListTable->setDragEnabled(false);
        decodedListTable->setSelectionMode(QAbstractItemView::SingleSelection);
        decodedListTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        decodedListTable->setSortingEnabled(false);
        splitter->addWidget(decodedListTable);
        decodedListTable->horizontalHeader()->setDefaultSectionSize(60);
        decodedListTable->horizontalHeader()->setMinimumSectionSize(43);
        decodedListTable->verticalHeader()->setVisible(false);
        decodedListTable->verticalHeader()->setHighlightSections(false);
        decodedText = new QPlainTextEdit(splitter);
        decodedText->setObjectName(QStringLiteral("decodedText"));
        QFont font2;
        font2.setFamily(QStringLiteral("Courier New"));
        font2.setPointSize(11);
        decodedText->setFont(font2);
        splitter->addWidget(decodedText);

        verticalLayout_3->addWidget(splitter);


        gridLayout_3->addWidget(decodeDisplayFrame, 0, 0, 1, 1);

        processTabs->addTab(decodeTab, QString());
        rawDecryptTab = new QWidget();
        rawDecryptTab->setObjectName(QStringLiteral("rawDecryptTab"));
        verticalLayout_2 = new QVBoxLayout(rawDecryptTab);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        textPaneFrame = new QHBoxLayout();
        textPaneFrame->setSpacing(1);
        textPaneFrame->setObjectName(QStringLiteral("textPaneFrame"));
        ptHexPane = new QTextEdit(rawDecryptTab);
        ptHexPane->setObjectName(QStringLiteral("ptHexPane"));
        QFont font3;
        font3.setFamily(QStringLiteral("Courier New"));
        font3.setPointSize(8);
        ptHexPane->setFont(font3);
        ptHexPane->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ptHexPane->setLineWrapMode(QTextEdit::NoWrap);
        ptHexPane->setReadOnly(true);
        ptHexPane->setTextInteractionFlags(Qt::TextSelectableByMouse);

        textPaneFrame->addWidget(ptHexPane);

        ptASCIIPane = new QTextEdit(rawDecryptTab);
        ptASCIIPane->setObjectName(QStringLiteral("ptASCIIPane"));
        QFont font4;
        font4.setFamily(QStringLiteral("Courier New"));
        ptASCIIPane->setFont(font4);
        ptASCIIPane->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ptASCIIPane->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        textPaneFrame->addWidget(ptASCIIPane);

        textPaneFrame->setStretch(0, 5);
        textPaneFrame->setStretch(1, 3);

        verticalLayout_2->addLayout(textPaneFrame);

        rawControls = new QHBoxLayout();
        rawControls->setSpacing(6);
        rawControls->setObjectName(QStringLiteral("rawControls"));
        bytesPerRowFrame = new QFrame(rawDecryptTab);
        bytesPerRowFrame->setObjectName(QStringLiteral("bytesPerRowFrame"));
        bytesPerRowFrame->setMaximumSize(QSize(200, 16777215));
        bytesPerRowFrame->setFrameShape(QFrame::StyledPanel);
        bytesPerRowFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(bytesPerRowFrame);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        bytesRowLael = new QLabel(bytesPerRowFrame);
        bytesRowLael->setObjectName(QStringLiteral("bytesRowLael"));
        bytesRowLael->setMaximumSize(QSize(86, 16777215));

        horizontalLayout_2->addWidget(bytesRowLael);

        bytesRowCombo = new QComboBox(bytesPerRowFrame);
        bytesRowCombo->setObjectName(QStringLiteral("bytesRowCombo"));
        bytesRowCombo->setMaximumSize(QSize(60, 16777215));
        bytesRowCombo->setEditable(true);

        horizontalLayout_2->addWidget(bytesRowCombo);


        rawControls->addWidget(bytesPerRowFrame);

        rawLinewrapCheck = new QCheckBox(rawDecryptTab);
        rawLinewrapCheck->setObjectName(QStringLiteral("rawLinewrapCheck"));
        rawLinewrapCheck->setMaximumSize(QSize(100, 16777215));
        rawLinewrapCheck->setChecked(true);

        rawControls->addWidget(rawLinewrapCheck);

        rawAutoScrollCheck = new QCheckBox(rawDecryptTab);
        rawAutoScrollCheck->setObjectName(QStringLiteral("rawAutoScrollCheck"));
        rawAutoScrollCheck->setMaximumSize(QSize(76, 16777215));
        rawAutoScrollCheck->setChecked(true);

        rawControls->addWidget(rawAutoScrollCheck);

        frame = new QFrame(rawDecryptTab);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMaximumSize(QSize(259, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        filterLabel = new QLabel(frame);
        filterLabel->setObjectName(QStringLiteral("filterLabel"));
        filterLabel->setMaximumSize(QSize(500, 16777215));

        horizontalLayout->addWidget(filterLabel);

        filtersBtn = new QPushButton(frame);
        filtersBtn->setObjectName(QStringLiteral("filtersBtn"));
        filtersBtn->setMaximumSize(QSize(84, 16777215));

        horizontalLayout->addWidget(filtersBtn);


        rawControls->addWidget(frame);


        verticalLayout_2->addLayout(rawControls);

        processTabs->addTab(rawDecryptTab, QString());
        metaLogTab = new QWidget();
        metaLogTab->setObjectName(QStringLiteral("metaLogTab"));
        gridLayout_2 = new QGridLayout(metaLogTab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        metaLog = new QPlainTextEdit(metaLogTab);
        metaLog->setObjectName(QStringLiteral("metaLog"));

        gridLayout_2->addWidget(metaLog, 0, 0, 1, 1);

        processTabs->addTab(metaLogTab, QString());

        gridLayout->addWidget(processTabs, 0, 0, 1, 1);

        exileSniffer->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(exileSniffer);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 827, 21));
        menuGame_Instances = new QMenu(menuBar);
        menuGame_Instances->setObjectName(QStringLiteral("menuGame_Instances"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        exileSniffer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(exileSniffer);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        exileSniffer->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(exileSniffer);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        exileSniffer->setStatusBar(statusBar);

        menuBar->addAction(menuGame_Instances->menuAction());
        menuBar->addAction(menuSettings->menuAction());

        retranslateUi(exileSniffer);
        QObject::connect(decodedFiltersBtn, SIGNAL(clicked()), exileSniffer, SLOT(showRawFiltersDLG()));
        QObject::connect(bytesRowCombo, SIGNAL(activated(QString)), exileSniffer, SLOT(rawBytesRowChanged(QString)));
        QObject::connect(rawLinewrapCheck, SIGNAL(toggled(bool)), exileSniffer, SLOT(toggleRawLineWrap(bool)));
        QObject::connect(rawAutoScrollCheck, SIGNAL(toggled(bool)), exileSniffer, SLOT(toggleRawAutoScroll(bool)));
        QObject::connect(decodedListTable, SIGNAL(clicked(QModelIndex)), exileSniffer, SLOT(decodedListClicked()));
        QObject::connect(decodedListTable, SIGNAL(cellPressed(int,int)), exileSniffer, SLOT(decodedCellActivated(int,int)));
        QObject::connect(decodedListTable, SIGNAL(customContextMenuRequested(QPoint)), exileSniffer, SLOT(decodedTableMenuRequest(QPoint)));

        processTabs->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(exileSniffer);
    } // setupUi

    void retranslateUi(QMainWindow *exileSniffer)
    {
        exileSniffer->setWindowTitle(QApplication::translate("exileSniffer", "exileSniffer", Q_NULLPTR));
        statusInfoText->setText(QApplication::translate("exileSniffer", "Waiting for processes named \"PathOfExile.exe\" or \"PathOfExile_x64.exe\"", Q_NULLPTR));
        statusInfoLabel->setText(QApplication::translate("exileSniffer", "Action:", Q_NULLPTR));
        statusLabel->setText(QApplication::translate("exileSniffer", "Status:", Q_NULLPTR));
        statusText->setText(QApplication::translate("exileSniffer", "No running Path of Exile clients found", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(interceptionTab), QApplication::translate("exileSniffer", "Interception", Q_NULLPTR));
        decodedAutoscrollCheck->setText(QApplication::translate("exileSniffer", "Auto Scroll", Q_NULLPTR));
        decodedDisplayedLabel->setText(QApplication::translate("exileSniffer", "No packets decoded", Q_NULLPTR));
        decodedFiltersBtn->setText(QApplication::translate("exileSniffer", "Filters", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = decodedListTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("exileSniffer", "Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = decodedListTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("exileSniffer", "Sender", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = decodedListTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("exileSniffer", "PktID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = decodedListTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("exileSniffer", "Summary", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(decodeTab), QApplication::translate("exileSniffer", "Decoder", Q_NULLPTR));
        ptHexPane->setHtml(QApplication::translate("exileSniffer", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        ptASCIIPane->setHtml(QApplication::translate("exileSniffer", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        bytesRowLael->setText(QApplication::translate("exileSniffer", "Bytes Per Row:", Q_NULLPTR));
        bytesRowCombo->clear();
        bytesRowCombo->insertItems(0, QStringList()
         << QApplication::translate("exileSniffer", "16", Q_NULLPTR)
         << QApplication::translate("exileSniffer", "32", Q_NULLPTR)
         << QApplication::translate("exileSniffer", "48", Q_NULLPTR)
         << QApplication::translate("exileSniffer", "64", Q_NULLPTR)
        );
        rawLinewrapCheck->setText(QApplication::translate("exileSniffer", "Line Wrap", Q_NULLPTR));
        rawAutoScrollCheck->setText(QApplication::translate("exileSniffer", "AutoScroll", Q_NULLPTR));
        filterLabel->setText(QApplication::translate("exileSniffer", "0 Packets Captured", Q_NULLPTR));
        filtersBtn->setText(QApplication::translate("exileSniffer", "Filters", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(rawDecryptTab), QApplication::translate("exileSniffer", "Raw Plaintext", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(metaLogTab), QApplication::translate("exileSniffer", "Log", Q_NULLPTR));
        menuGame_Instances->setTitle(QApplication::translate("exileSniffer", "Game Processes", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("exileSniffer", "Settings", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class exileSniffer: public Ui_exileSniffer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXILESNIFFER_H
