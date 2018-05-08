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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "statuswidget.h"

QT_BEGIN_NAMESPACE

class Ui_exileSniffer
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *processTabs;
    QWidget *interceptionTab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *ex_sniff_layout;
    statusWidget *keyExStatusWidget;
    statusWidget *sniffStatusWidget;
    QWidget *decrypt_status_widget;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *decryptionIconsLayout;
    QLabel *no_decrypt_label;
    QLabel *yes_decrypt_label;
    QFrame *decryptionInfoFrame;
    QHBoxLayout *horizontalLayout_9;
    QStackedWidget *decrypt_details_stack;
    QWidget *noDecryptStack;
    QVBoxLayout *verticalLayout_9;
    QLabel *decryptionStatusText;
    QWidget *yesDecryptStack;
    QVBoxLayout *verticalLayout_10;
    QLabel *label;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPlainTextEdit *keyHexText;
    QLineEdit *sendIVText;
    QLineEdit *recvIVText;
    QLabel *label_5;
    QLineEdit *sendIterText;
    QLabel *label_6;
    QLineEdit *recvIterText;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *stopDecryptBtn;
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
    QTabWidget *decodedDetailsTab;
    QWidget *decodeAnalysisTab;
    QHBoxLayout *horizontalLayout_8;
    QPlainTextEdit *decodedText;
    QWidget *decodeRawTab;
    QHBoxLayout *horizontalLayout_11;
    QPlainTextEdit *decodedRawHex;
    QPlainTextEdit *decodedRawText;
    QWidget *rawDecryptTab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *textPaneFrame;
    QTextEdit *ptHexPane;
    QTextEdit *ptASCIIPane;
    QHBoxLayout *rawControls;
    QFrame *bytesPerRowFrame;
    QFormLayout *formLayout_5;
    QLabel *bytesRowLael;
    QComboBox *bytesRowCombo;
    QFrame *horizontalFrame_3;
    QFormLayout *formLayout;
    QLabel *label_7;
    QLineEdit *maxRawLinesEdit;
    QCheckBox *rawLinewrapCheck;
    QCheckBox *rawAutoScrollCheck;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *filterLabel;
    QWidget *metaLogTab;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *metaLog;
    QWidget *settingsTab;
    QHBoxLayout *horizontalLayout_7;
    QListWidget *settingsChoiceList;
    QStackedWidget *settingsStack;
    QWidget *logSettings;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QCheckBox *logsEnabledCheck;
    QPushButton *logsOpenDirBtn;
    QLineEdit *logDirLine;
    QPushButton *logSetDirBtn;
    QWidget *feedSettings;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QFormLayout *formLayout_3;
    QLineEdit *namedPipeChosenName;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *namedPipePathResult;
    QCheckBox *pipeFeedEnableCheck;
    QWidget *utilsTab;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout_4;
    QLabel *label_10;
    QLineEdit *hashUtilInputText;
    QLabel *order1hash;
    QLabel *order2hash;
    QLabel *order1hashres;
    QLabel *order2hashres;
    QLabel *label_11;
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
        verticalLayout_4 = new QVBoxLayout(interceptionTab);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, -1, 12);
        ex_sniff_layout = new QHBoxLayout();
        ex_sniff_layout->setSpacing(0);
        ex_sniff_layout->setObjectName(QStringLiteral("ex_sniff_layout"));
        keyExStatusWidget = new statusWidget(interceptionTab);
        keyExStatusWidget->setObjectName(QStringLiteral("keyExStatusWidget"));

        ex_sniff_layout->addWidget(keyExStatusWidget);

        sniffStatusWidget = new statusWidget(interceptionTab);
        sniffStatusWidget->setObjectName(QStringLiteral("sniffStatusWidget"));

        ex_sniff_layout->addWidget(sniffStatusWidget);


        verticalLayout_4->addLayout(ex_sniff_layout);

        decrypt_status_widget = new QWidget(interceptionTab);
        decrypt_status_widget->setObjectName(QStringLiteral("decrypt_status_widget"));
        decrypt_status_widget->setMinimumSize(QSize(600, 280));
        decrypt_status_widget->setMaximumSize(QSize(999999, 99999));
        horizontalLayout_10 = new QHBoxLayout(decrypt_status_widget);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        decryptionIconsLayout = new QVBoxLayout();
        decryptionIconsLayout->setSpacing(6);
        decryptionIconsLayout->setObjectName(QStringLiteral("decryptionIconsLayout"));
        decryptionIconsLayout->setContentsMargins(-1, -1, -1, 0);
        no_decrypt_label = new QLabel(decrypt_status_widget);
        no_decrypt_label->setObjectName(QStringLiteral("no_decrypt_label"));
        no_decrypt_label->setMinimumSize(QSize(130, 130));
        no_decrypt_label->setMaximumSize(QSize(130, 130));
        no_decrypt_label->setBaseSize(QSize(130, 130));
        no_decrypt_label->setStyleSheet(QStringLiteral(""));

        decryptionIconsLayout->addWidget(no_decrypt_label);

        yes_decrypt_label = new QLabel(decrypt_status_widget);
        yes_decrypt_label->setObjectName(QStringLiteral("yes_decrypt_label"));
        yes_decrypt_label->setMinimumSize(QSize(130, 130));
        yes_decrypt_label->setMaximumSize(QSize(130, 130));
        yes_decrypt_label->setBaseSize(QSize(130, 130));
        yes_decrypt_label->setStyleSheet(QStringLiteral(""));

        decryptionIconsLayout->addWidget(yes_decrypt_label);


        horizontalLayout_10->addLayout(decryptionIconsLayout);

        decryptionInfoFrame = new QFrame(decrypt_status_widget);
        decryptionInfoFrame->setObjectName(QStringLiteral("decryptionInfoFrame"));
        horizontalLayout_9 = new QHBoxLayout(decryptionInfoFrame);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        decrypt_details_stack = new QStackedWidget(decryptionInfoFrame);
        decrypt_details_stack->setObjectName(QStringLiteral("decrypt_details_stack"));
        noDecryptStack = new QWidget();
        noDecryptStack->setObjectName(QStringLiteral("noDecryptStack"));
        verticalLayout_9 = new QVBoxLayout(noDecryptStack);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        decryptionStatusText = new QLabel(noDecryptStack);
        decryptionStatusText->setObjectName(QStringLiteral("decryptionStatusText"));
        QFont font;
        font.setPointSize(16);
        decryptionStatusText->setFont(font);
        decryptionStatusText->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(decryptionStatusText);

        decrypt_details_stack->addWidget(noDecryptStack);
        yesDecryptStack = new QWidget();
        yesDecryptStack->setObjectName(QStringLiteral("yesDecryptStack"));
        verticalLayout_10 = new QVBoxLayout(yesDecryptStack);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label = new QLabel(yesDecryptStack);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label);

        groupBox_3 = new QGroupBox(yesDecryptStack);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 16777206));
        QFont font1;
        font1.setPointSize(12);
        groupBox_3->setFont(font1);
        formLayout_2 = new QFormLayout(groupBox_3);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setHorizontalSpacing(22);
        formLayout_2->setContentsMargins(20, -1, 20, -1);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_4);

        keyHexText = new QPlainTextEdit(groupBox_3);
        keyHexText->setObjectName(QStringLiteral("keyHexText"));
        keyHexText->setMaximumSize(QSize(16777215, 50));
        QFont font2;
        font2.setFamily(QStringLiteral("Courier"));
        font2.setPointSize(10);
        keyHexText->setFont(font2);
        keyHexText->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        keyHexText->setReadOnly(true);
        keyHexText->setTabStopWidth(80);
        keyHexText->setMaximumBlockCount(0);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, keyHexText);

        sendIVText = new QLineEdit(groupBox_3);
        sendIVText->setObjectName(QStringLiteral("sendIVText"));
        QFont font3;
        font3.setFamily(QStringLiteral("Courier"));
        sendIVText->setFont(font3);
        sendIVText->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, sendIVText);

        recvIVText = new QLineEdit(groupBox_3);
        recvIVText->setObjectName(QStringLiteral("recvIVText"));
        recvIVText->setFont(font3);
        recvIVText->setReadOnly(true);

        formLayout_2->setWidget(6, QFormLayout::FieldRole, recvIVText);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font4;
        font4.setPointSize(11);
        font4.setItalic(false);
        label_5->setFont(font4);
        label_5->setIndent(15);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_5);

        sendIterText = new QLineEdit(groupBox_3);
        sendIterText->setObjectName(QStringLiteral("sendIterText"));
        sendIterText->setFont(font3);
        sendIterText->setReadOnly(true);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, sendIterText);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font5;
        font5.setPointSize(11);
        label_6->setFont(font5);
        label_6->setIndent(15);

        formLayout_2->setWidget(7, QFormLayout::LabelRole, label_6);

        recvIterText = new QLineEdit(groupBox_3);
        recvIterText->setObjectName(QStringLiteral("recvIterText"));
        recvIterText->setFont(font3);
        recvIterText->setReadOnly(true);

        formLayout_2->setWidget(7, QFormLayout::FieldRole, recvIterText);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->setItem(2, QFormLayout::FieldRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->setItem(5, QFormLayout::FieldRole, verticalSpacer_2);


        verticalLayout_10->addWidget(groupBox_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        stopDecryptBtn = new QPushButton(yesDecryptStack);
        stopDecryptBtn->setObjectName(QStringLiteral("stopDecryptBtn"));
        stopDecryptBtn->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_4->addWidget(stopDecryptBtn);


        verticalLayout_10->addLayout(horizontalLayout_4);

        decrypt_details_stack->addWidget(yesDecryptStack);

        horizontalLayout_9->addWidget(decrypt_details_stack);


        horizontalLayout_10->addWidget(decryptionInfoFrame);


        verticalLayout_4->addWidget(decrypt_status_widget);

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
        decodedFiltersBtn->setMaximumSize(QSize(60, 16777215));

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
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setForeground(brush);
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
        decodedListTable->setStyleSheet(QStringLiteral(""));
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
        decodedDetailsTab = new QTabWidget(splitter);
        decodedDetailsTab->setObjectName(QStringLiteral("decodedDetailsTab"));
        QFont font6;
        font6.setFamily(QStringLiteral("Courier"));
        font6.setPointSize(10);
        font6.setBold(true);
        font6.setWeight(75);
        decodedDetailsTab->setFont(font6);
        decodedDetailsTab->setTabPosition(QTabWidget::West);
        decodeAnalysisTab = new QWidget();
        decodeAnalysisTab->setObjectName(QStringLiteral("decodeAnalysisTab"));
        horizontalLayout_8 = new QHBoxLayout(decodeAnalysisTab);
        horizontalLayout_8->setSpacing(3);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(4, 4, 4, 4);
        decodedText = new QPlainTextEdit(decodeAnalysisTab);
        decodedText->setObjectName(QStringLiteral("decodedText"));
        QFont font7;
        font7.setFamily(QStringLiteral("Courier New"));
        font7.setPointSize(11);
        decodedText->setFont(font7);

        horizontalLayout_8->addWidget(decodedText);

        decodedDetailsTab->addTab(decodeAnalysisTab, QString());
        decodeRawTab = new QWidget();
        decodeRawTab->setObjectName(QStringLiteral("decodeRawTab"));
        horizontalLayout_11 = new QHBoxLayout(decodeRawTab);
        horizontalLayout_11->setSpacing(1);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(4, 4, 4, 4);
        decodedRawHex = new QPlainTextEdit(decodeRawTab);
        decodedRawHex->setObjectName(QStringLiteral("decodedRawHex"));
        QFont font8;
        font8.setFamily(QStringLiteral("Courier New"));
        decodedRawHex->setFont(font8);
        decodedRawHex->setReadOnly(true);

        horizontalLayout_11->addWidget(decodedRawHex);

        decodedRawText = new QPlainTextEdit(decodeRawTab);
        decodedRawText->setObjectName(QStringLiteral("decodedRawText"));
        decodedRawText->setFont(font8);
        decodedRawText->setReadOnly(true);

        horizontalLayout_11->addWidget(decodedRawText);

        horizontalLayout_11->setStretch(0, 5);
        horizontalLayout_11->setStretch(1, 3);
        decodedDetailsTab->addTab(decodeRawTab, QString());
        splitter->addWidget(decodedDetailsTab);

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
        QFont font9;
        font9.setFamily(QStringLiteral("Courier New"));
        font9.setPointSize(8);
        ptHexPane->setFont(font9);
        ptHexPane->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ptHexPane->setLineWrapMode(QTextEdit::NoWrap);
        ptHexPane->setReadOnly(true);
        ptHexPane->setTextInteractionFlags(Qt::TextSelectableByMouse);

        textPaneFrame->addWidget(ptHexPane);

        ptASCIIPane = new QTextEdit(rawDecryptTab);
        ptASCIIPane->setObjectName(QStringLiteral("ptASCIIPane"));
        ptASCIIPane->setFont(font8);
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
        bytesPerRowFrame->setMaximumSize(QSize(183, 16777215));
        bytesPerRowFrame->setFrameShape(QFrame::StyledPanel);
        bytesPerRowFrame->setFrameShadow(QFrame::Raised);
        formLayout_5 = new QFormLayout(bytesPerRowFrame);
        formLayout_5->setSpacing(6);
        formLayout_5->setContentsMargins(11, 11, 11, 11);
        formLayout_5->setObjectName(QStringLiteral("formLayout_5"));
        formLayout_5->setVerticalSpacing(0);
        formLayout_5->setContentsMargins(6, 6, 0, 0);
        bytesRowLael = new QLabel(bytesPerRowFrame);
        bytesRowLael->setObjectName(QStringLiteral("bytesRowLael"));
        bytesRowLael->setMaximumSize(QSize(86, 16777215));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, bytesRowLael);

        bytesRowCombo = new QComboBox(bytesPerRowFrame);
        bytesRowCombo->setObjectName(QStringLiteral("bytesRowCombo"));
        bytesRowCombo->setMaximumSize(QSize(60, 16777215));
        bytesRowCombo->setEditable(true);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, bytesRowCombo);


        rawControls->addWidget(bytesPerRowFrame);

        horizontalFrame_3 = new QFrame(rawDecryptTab);
        horizontalFrame_3->setObjectName(QStringLiteral("horizontalFrame_3"));
        horizontalFrame_3->setMaximumSize(QSize(150, 16777215));
        formLayout = new QFormLayout(horizontalFrame_3);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setVerticalSpacing(0);
        formLayout->setContentsMargins(3, 6, 4, 0);
        label_7 = new QLabel(horizontalFrame_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(60, 16777215));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_7);

        maxRawLinesEdit = new QLineEdit(horizontalFrame_3);
        maxRawLinesEdit->setObjectName(QStringLiteral("maxRawLinesEdit"));
        maxRawLinesEdit->setMinimumSize(QSize(0, 11));
        maxRawLinesEdit->setMaximumSize(QSize(79, 22));

        formLayout->setWidget(0, QFormLayout::FieldRole, maxRawLinesEdit);


        rawControls->addWidget(horizontalFrame_3);

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
        settingsTab = new QWidget();
        settingsTab->setObjectName(QStringLiteral("settingsTab"));
        horizontalLayout_7 = new QHBoxLayout(settingsTab);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        settingsChoiceList = new QListWidget(settingsTab);
        new QListWidgetItem(settingsChoiceList);
        new QListWidgetItem(settingsChoiceList);
        settingsChoiceList->setObjectName(QStringLiteral("settingsChoiceList"));
        settingsChoiceList->setMaximumSize(QSize(200, 16777215));
        settingsChoiceList->setSpacing(3);
        settingsChoiceList->setViewMode(QListView::ListMode);

        horizontalLayout_7->addWidget(settingsChoiceList);

        settingsStack = new QStackedWidget(settingsTab);
        settingsStack->setObjectName(QStringLiteral("settingsStack"));
        logSettings = new QWidget();
        logSettings->setObjectName(QStringLiteral("logSettings"));
        verticalLayout = new QVBoxLayout(logSettings);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_2 = new QGroupBox(logSettings);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 115));
        QFont font10;
        font10.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font10.setPointSize(10);
        groupBox_2->setFont(font10);
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        logsEnabledCheck = new QCheckBox(groupBox_2);
        logsEnabledCheck->setObjectName(QStringLiteral("logsEnabledCheck"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logsEnabledCheck->sizePolicy().hasHeightForWidth());
        logsEnabledCheck->setSizePolicy(sizePolicy);
        logsEnabledCheck->setMinimumSize(QSize(100, 0));
        logsEnabledCheck->setMaximumSize(QSize(128, 60));
        logsEnabledCheck->setLayoutDirection(Qt::LeftToRight);
        logsEnabledCheck->setChecked(true);

        gridLayout_4->addWidget(logsEnabledCheck, 0, 0, 1, 1);

        logsOpenDirBtn = new QPushButton(groupBox_2);
        logsOpenDirBtn->setObjectName(QStringLiteral("logsOpenDirBtn"));
        logsOpenDirBtn->setMinimumSize(QSize(95, 0));
        logsOpenDirBtn->setMaximumSize(QSize(100, 16777215));
        logsOpenDirBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(logsOpenDirBtn, 0, 1, 1, 1);

        logDirLine = new QLineEdit(groupBox_2);
        logDirLine->setObjectName(QStringLiteral("logDirLine"));

        gridLayout_4->addWidget(logDirLine, 1, 0, 1, 1);

        logSetDirBtn = new QPushButton(groupBox_2);
        logSetDirBtn->setObjectName(QStringLiteral("logSetDirBtn"));
        logSetDirBtn->setMinimumSize(QSize(95, 0));

        gridLayout_4->addWidget(logSetDirBtn, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        settingsStack->addWidget(logSettings);
        feedSettings = new QWidget();
        feedSettings->setObjectName(QStringLiteral("feedSettings"));
        verticalLayout_5 = new QVBoxLayout(feedSettings);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox = new QGroupBox(feedSettings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 115));
        formLayout_3 = new QFormLayout(groupBox);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        namedPipeChosenName = new QLineEdit(groupBox);
        namedPipeChosenName->setObjectName(QStringLiteral("namedPipeChosenName"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, namedPipeChosenName);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_8);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_9);

        namedPipePathResult = new QLabel(groupBox);
        namedPipePathResult->setObjectName(QStringLiteral("namedPipePathResult"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, namedPipePathResult);

        pipeFeedEnableCheck = new QCheckBox(groupBox);
        pipeFeedEnableCheck->setObjectName(QStringLiteral("pipeFeedEnableCheck"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, pipeFeedEnableCheck);


        verticalLayout_5->addWidget(groupBox);

        settingsStack->addWidget(feedSettings);

        horizontalLayout_7->addWidget(settingsStack);

        processTabs->addTab(settingsTab, QString());
        utilsTab = new QWidget();
        utilsTab->setObjectName(QStringLiteral("utilsTab"));
        verticalLayout_6 = new QVBoxLayout(utilsTab);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        groupBox_4 = new QGroupBox(utilsTab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(16777215, 135));
        QFont font11;
        font11.setPointSize(9);
        groupBox_4->setFont(font11);
        formLayout_4 = new QFormLayout(groupBox_4);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setVerticalSpacing(10);
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(100, 0));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_10);

        hashUtilInputText = new QLineEdit(groupBox_4);
        hashUtilInputText->setObjectName(QStringLiteral("hashUtilInputText"));
        hashUtilInputText->setMaximumSize(QSize(230, 16777215));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, hashUtilInputText);

        order1hash = new QLabel(groupBox_4);
        order1hash->setObjectName(QStringLiteral("order1hash"));
        order1hash->setMinimumSize(QSize(100, 0));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, order1hash);

        order2hash = new QLabel(groupBox_4);
        order2hash->setObjectName(QStringLiteral("order2hash"));
        order2hash->setMinimumSize(QSize(100, 0));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, order2hash);

        order1hashres = new QLabel(groupBox_4);
        order1hashres->setObjectName(QStringLiteral("order1hashres"));
        order1hashres->setFont(font11);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, order1hashres);

        order2hashres = new QLabel(groupBox_4);
        order2hashres->setObjectName(QStringLiteral("order2hashres"));
        order2hashres->setFont(font11);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, order2hashres);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, label_11);


        verticalLayout_6->addWidget(groupBox_4);

        processTabs->addTab(utilsTab, QString());

        gridLayout->addWidget(processTabs, 0, 0, 1, 1);

        exileSniffer->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(exileSniffer);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        exileSniffer->setStatusBar(statusBar);

        retranslateUi(exileSniffer);
        QObject::connect(bytesRowCombo, SIGNAL(activated(QString)), exileSniffer, SLOT(rawBytesRowChanged(QString)));
        QObject::connect(rawLinewrapCheck, SIGNAL(toggled(bool)), exileSniffer, SLOT(toggleRawLineWrap(bool)));
        QObject::connect(rawAutoScrollCheck, SIGNAL(toggled(bool)), exileSniffer, SLOT(toggleRawAutoScroll(bool)));
        QObject::connect(decodedListTable, SIGNAL(clicked(QModelIndex)), exileSniffer, SLOT(decodedListClicked()));
        QObject::connect(decodedListTable, SIGNAL(cellPressed(int,int)), exileSniffer, SLOT(decodedCellActivated(int,int)));
        QObject::connect(decodedListTable, SIGNAL(customContextMenuRequested(QPoint)), exileSniffer, SLOT(decodedTableMenuRequest(QPoint)));
        QObject::connect(stopDecryptBtn, SIGNAL(clicked()), exileSniffer, SLOT(stopDecrypting()));
        QObject::connect(settingsChoiceList, SIGNAL(itemSelectionChanged()), exileSniffer, SLOT(settingsSelectionChanged()));
        QObject::connect(decodedFiltersBtn, SIGNAL(clicked()), exileSniffer, SLOT(showRawFiltersDLG()));
        QObject::connect(hashUtilInputText, SIGNAL(textChanged(QString)), exileSniffer, SLOT(hashUtilInput()));
        QObject::connect(maxRawLinesEdit, SIGNAL(returnPressed()), exileSniffer, SLOT(maxRawLinesSet()));
        QObject::connect(decodedAutoscrollCheck, SIGNAL(toggled(bool)), exileSniffer, SLOT(toggleDecodedAutoScroll(bool)));

        processTabs->setCurrentIndex(2);
        decrypt_details_stack->setCurrentIndex(1);
        decodedDetailsTab->setCurrentIndex(1);
        settingsChoiceList->setCurrentRow(0);
        settingsStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(exileSniffer);
    } // setupUi

    void retranslateUi(QMainWindow *exileSniffer)
    {
        exileSniffer->setWindowTitle(QApplication::translate("exileSniffer", "exileSniffer", Q_NULLPTR));
        no_decrypt_label->setText(QString());
        yes_decrypt_label->setText(QString());
        decryptionStatusText->setText(QApplication::translate("exileSniffer", "Not decrypting", Q_NULLPTR));
        label->setText(QApplication::translate("exileSniffer", "Decryption in progress", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("exileSniffer", "Salsa Key Material", Q_NULLPTR));
        label_2->setText(QApplication::translate("exileSniffer", "Key", Q_NULLPTR));
        label_3->setText(QApplication::translate("exileSniffer", "Send IV", Q_NULLPTR));
        label_4->setText(QApplication::translate("exileSniffer", "Receive IV", Q_NULLPTR));
        keyHexText->setPlainText(QApplication::translate("exileSniffer", "33 56 29 3D B7 82 89 24 1D BA E8 CD 9A 00 01 F4 \n"
"FD DD ED DC 1A DD DD DD DD DD DD DD DD DD DD DD", Q_NULLPTR));
        label_5->setText(QApplication::translate("exileSniffer", "Iteration", Q_NULLPTR));
        label_6->setText(QApplication::translate("exileSniffer", "Iteration", Q_NULLPTR));
        stopDecryptBtn->setText(QApplication::translate("exileSniffer", "Stop Decrypting", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(interceptionTab), QApplication::translate("exileSniffer", "Decryption", Q_NULLPTR));
        decodedAutoscrollCheck->setText(QApplication::translate("exileSniffer", "Auto Scroll", Q_NULLPTR));
        decodedDisplayedLabel->setText(QApplication::translate("exileSniffer", "No packets decoded", Q_NULLPTR));
        decodedFiltersBtn->setText(QApplication::translate("exileSniffer", "Filters", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = decodedListTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("exileSniffer", "Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = decodedListTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("exileSniffer", "Origin", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = decodedListTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("exileSniffer", "PktID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = decodedListTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("exileSniffer", "Summary", Q_NULLPTR));
        decodedDetailsTab->setTabText(decodedDetailsTab->indexOf(decodeAnalysisTab), QApplication::translate("exileSniffer", "Analysis", Q_NULLPTR));
        decodedDetailsTab->setTabText(decodedDetailsTab->indexOf(decodeRawTab), QApplication::translate("exileSniffer", "Raw", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(decodeTab), QApplication::translate("exileSniffer", "Decoding", Q_NULLPTR));
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
        label_7->setText(QApplication::translate("exileSniffer", "Max lines:", Q_NULLPTR));
        maxRawLinesEdit->setText(QApplication::translate("exileSniffer", "10000", Q_NULLPTR));
        rawLinewrapCheck->setText(QApplication::translate("exileSniffer", "Line Wrap", Q_NULLPTR));
        rawAutoScrollCheck->setText(QApplication::translate("exileSniffer", "AutoScroll", Q_NULLPTR));
        filterLabel->setText(QApplication::translate("exileSniffer", "0 Packets Captured", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(rawDecryptTab), QApplication::translate("exileSniffer", "Raw Plaintext", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(metaLogTab), QApplication::translate("exileSniffer", "Log", Q_NULLPTR));

        const bool __sortingEnabled = settingsChoiceList->isSortingEnabled();
        settingsChoiceList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = settingsChoiceList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("exileSniffer", "Logfiles", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem1 = settingsChoiceList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("exileSniffer", "Feeds", Q_NULLPTR));
        settingsChoiceList->setSortingEnabled(__sortingEnabled);

        groupBox_2->setTitle(QApplication::translate("exileSniffer", "Packet Hexdumps Directory", Q_NULLPTR));
        logsEnabledCheck->setText(QApplication::translate("exileSniffer", "Logging Enabled", Q_NULLPTR));
        logsOpenDirBtn->setText(QApplication::translate("exileSniffer", "Open", Q_NULLPTR));
        logSetDirBtn->setText(QApplication::translate("exileSniffer", "{}", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("exileSniffer", "Named Pipe (Decoded Packets - JSON)", Q_NULLPTR));
        label_8->setText(QApplication::translate("exileSniffer", "Name:", Q_NULLPTR));
        label_9->setText(QApplication::translate("exileSniffer", "Path:", Q_NULLPTR));
        namedPipePathResult->setText(QApplication::translate("exileSniffer", "TextLabel", Q_NULLPTR));
        pipeFeedEnableCheck->setText(QApplication::translate("exileSniffer", "Enabled", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(settingsTab), QApplication::translate("exileSniffer", "Settings", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("exileSniffer", "Hash Lookup", Q_NULLPTR));
        label_10->setText(QApplication::translate("exileSniffer", "Input Hex:", Q_NULLPTR));
        order1hash->setText(QString());
        order2hash->setText(QString());
        order1hashres->setText(QString());
        order2hashres->setText(QString());
        label_11->setText(QApplication::translate("exileSniffer", "Enter a sequence of hex bytes to lookup a murmur2 hash. Only works for the GGPK strings we have catalogued.", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(utilsTab), QApplication::translate("exileSniffer", "Utilities", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class exileSniffer: public Ui_exileSniffer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXILESNIFFER_H
