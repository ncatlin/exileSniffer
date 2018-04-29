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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
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
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *ex_sniff_layout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *keyex_lab_bad;
    QLabel *keyex_lab_pending;
    QLabel *keyex_lab_good;
    QVBoxLayout *verticalLayout_5;
    QLabel *keyex_text;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *sniff_lab_bad;
    QLabel *sniff_lab_pending;
    QLabel *sniff_lab_good;
    QVBoxLayout *verticalLayout_8;
    QLabel *sniff_text;
    QWidget *decrypt_status_widget;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout;
    QLabel *no_decrypt_label;
    QLabel *yes_decrypt_label;
    QFrame *horizontalFrame_3;
    QHBoxLayout *horizontalLayout_9;
    QStackedWidget *stackedWidget_3;
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
    QPlainTextEdit *plainTextEdit;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
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
        verticalLayout_4 = new QVBoxLayout(interceptionTab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        ex_sniff_layout = new QHBoxLayout();
        ex_sniff_layout->setSpacing(6);
        ex_sniff_layout->setObjectName(QStringLiteral("ex_sniff_layout"));
        groupBox = new QGroupBox(interceptionTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(300, 0));
        groupBox->setMaximumSize(QSize(16777215, 200));
        QFont font;
        font.setPointSize(12);
        groupBox->setFont(font);
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 4, -1, 4);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        keyex_lab_bad = new QLabel(groupBox);
        keyex_lab_bad->setObjectName(QStringLiteral("keyex_lab_bad"));
        keyex_lab_bad->setMaximumSize(QSize(100, 100));
        keyex_lab_bad->setStyleSheet(QStringLiteral(""));

        horizontalLayout_7->addWidget(keyex_lab_bad);

        keyex_lab_pending = new QLabel(groupBox);
        keyex_lab_pending->setObjectName(QStringLiteral("keyex_lab_pending"));
        keyex_lab_pending->setMaximumSize(QSize(100, 100));
        keyex_lab_pending->setStyleSheet(QStringLiteral(""));

        horizontalLayout_7->addWidget(keyex_lab_pending);

        keyex_lab_good = new QLabel(groupBox);
        keyex_lab_good->setObjectName(QStringLiteral("keyex_lab_good"));
        keyex_lab_good->setMaximumSize(QSize(100, 100));
        keyex_lab_good->setStyleSheet(QStringLiteral(""));

        horizontalLayout_7->addWidget(keyex_lab_good);


        verticalLayout_6->addLayout(horizontalLayout_7);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        keyex_text = new QLabel(groupBox);
        keyex_text->setObjectName(QStringLiteral("keyex_text"));
        QFont font1;
        font1.setPointSize(10);
        keyex_text->setFont(font1);
        keyex_text->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(keyex_text);


        verticalLayout_6->addLayout(verticalLayout_5);


        ex_sniff_layout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(interceptionTab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(300, 0));
        groupBox_2->setMaximumSize(QSize(16777215, 200));
        groupBox_2->setFont(font);
        verticalLayout_7 = new QVBoxLayout(groupBox_2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, 4, -1, 4);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        sniff_lab_bad = new QLabel(groupBox_2);
        sniff_lab_bad->setObjectName(QStringLiteral("sniff_lab_bad"));
        sniff_lab_bad->setMaximumSize(QSize(100, 100));
        sniff_lab_bad->setStyleSheet(QStringLiteral(""));

        horizontalLayout_8->addWidget(sniff_lab_bad);

        sniff_lab_pending = new QLabel(groupBox_2);
        sniff_lab_pending->setObjectName(QStringLiteral("sniff_lab_pending"));
        sniff_lab_pending->setMaximumSize(QSize(100, 100));
        sniff_lab_pending->setStyleSheet(QStringLiteral(""));

        horizontalLayout_8->addWidget(sniff_lab_pending);

        sniff_lab_good = new QLabel(groupBox_2);
        sniff_lab_good->setObjectName(QStringLiteral("sniff_lab_good"));
        sniff_lab_good->setMaximumSize(QSize(100, 100));
        sniff_lab_good->setStyleSheet(QStringLiteral(""));

        horizontalLayout_8->addWidget(sniff_lab_good);


        verticalLayout_7->addLayout(horizontalLayout_8);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        sniff_text = new QLabel(groupBox_2);
        sniff_text->setObjectName(QStringLiteral("sniff_text"));
        sniff_text->setFont(font1);
        sniff_text->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(sniff_text);


        verticalLayout_7->addLayout(verticalLayout_8);


        ex_sniff_layout->addWidget(groupBox_2);


        verticalLayout_4->addLayout(ex_sniff_layout);

        decrypt_status_widget = new QWidget(interceptionTab);
        decrypt_status_widget->setObjectName(QStringLiteral("decrypt_status_widget"));
        decrypt_status_widget->setMinimumSize(QSize(600, 280));
        decrypt_status_widget->setMaximumSize(QSize(999999, 250));
        horizontalLayout_10 = new QHBoxLayout(decrypt_status_widget);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        no_decrypt_label = new QLabel(decrypt_status_widget);
        no_decrypt_label->setObjectName(QStringLiteral("no_decrypt_label"));
        no_decrypt_label->setMinimumSize(QSize(130, 130));
        no_decrypt_label->setMaximumSize(QSize(130, 130));
        no_decrypt_label->setBaseSize(QSize(130, 130));
        no_decrypt_label->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(no_decrypt_label);

        yes_decrypt_label = new QLabel(decrypt_status_widget);
        yes_decrypt_label->setObjectName(QStringLiteral("yes_decrypt_label"));
        yes_decrypt_label->setMinimumSize(QSize(130, 130));
        yes_decrypt_label->setMaximumSize(QSize(130, 130));
        yes_decrypt_label->setBaseSize(QSize(130, 130));
        yes_decrypt_label->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(yes_decrypt_label);


        horizontalLayout_10->addLayout(verticalLayout);

        horizontalFrame_3 = new QFrame(decrypt_status_widget);
        horizontalFrame_3->setObjectName(QStringLiteral("horizontalFrame_3"));
        horizontalLayout_9 = new QHBoxLayout(horizontalFrame_3);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        stackedWidget_3 = new QStackedWidget(horizontalFrame_3);
        stackedWidget_3->setObjectName(QStringLiteral("stackedWidget_3"));
        noDecryptStack = new QWidget();
        noDecryptStack->setObjectName(QStringLiteral("noDecryptStack"));
        verticalLayout_9 = new QVBoxLayout(noDecryptStack);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        decryptionStatusText = new QLabel(noDecryptStack);
        decryptionStatusText->setObjectName(QStringLiteral("decryptionStatusText"));
        QFont font2;
        font2.setPointSize(16);
        decryptionStatusText->setFont(font2);
        decryptionStatusText->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(decryptionStatusText);

        stackedWidget_3->addWidget(noDecryptStack);
        yesDecryptStack = new QWidget();
        yesDecryptStack->setObjectName(QStringLiteral("yesDecryptStack"));
        verticalLayout_10 = new QVBoxLayout(yesDecryptStack);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label = new QLabel(yesDecryptStack);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label);

        groupBox_3 = new QGroupBox(yesDecryptStack);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setFont(font);
        formLayout_2 = new QFormLayout(groupBox_3);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setHorizontalSpacing(32);
        formLayout_2->setContentsMargins(20, -1, 20, -1);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_4);

        plainTextEdit = new QPlainTextEdit(groupBox_3);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, plainTextEdit);

        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEdit);

        lineEdit_2 = new QLineEdit(groupBox_3);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEdit_2);


        verticalLayout_10->addWidget(groupBox_3);

        stackedWidget_3->addWidget(yesDecryptStack);

        horizontalLayout_9->addWidget(stackedWidget_3);


        horizontalLayout_10->addWidget(horizontalFrame_3);


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
        QFont font3;
        font3.setFamily(QStringLiteral("Courier New"));
        font3.setPointSize(11);
        decodedText->setFont(font3);
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
        QFont font4;
        font4.setFamily(QStringLiteral("Courier New"));
        font4.setPointSize(8);
        ptHexPane->setFont(font4);
        ptHexPane->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ptHexPane->setLineWrapMode(QTextEdit::NoWrap);
        ptHexPane->setReadOnly(true);
        ptHexPane->setTextInteractionFlags(Qt::TextSelectableByMouse);

        textPaneFrame->addWidget(ptHexPane);

        ptASCIIPane = new QTextEdit(rawDecryptTab);
        ptASCIIPane->setObjectName(QStringLiteral("ptASCIIPane"));
        QFont font5;
        font5.setFamily(QStringLiteral("Courier New"));
        ptASCIIPane->setFont(font5);
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

        processTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(exileSniffer);
    } // setupUi

    void retranslateUi(QMainWindow *exileSniffer)
    {
        exileSniffer->setWindowTitle(QApplication::translate("exileSniffer", "exileSniffer", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("exileSniffer", "Key Extraction", Q_NULLPTR));
        keyex_lab_bad->setText(QString());
        keyex_lab_pending->setText(QString());
        keyex_lab_good->setText(QString());
        keyex_text->setText(QApplication::translate("exileSniffer", "Status: Doing Stuff", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("exileSniffer", "Network Sniffing", Q_NULLPTR));
        sniff_lab_bad->setText(QString());
        sniff_lab_pending->setText(QString());
        sniff_lab_good->setText(QString());
        sniff_text->setText(QApplication::translate("exileSniffer", "Status: Doing Stuff", Q_NULLPTR));
        no_decrypt_label->setText(QString());
        yes_decrypt_label->setText(QString());
        decryptionStatusText->setText(QApplication::translate("exileSniffer", "Not decrypting", Q_NULLPTR));
        label->setText(QApplication::translate("exileSniffer", "Decryption in progress", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("exileSniffer", "Salsa Key Material", Q_NULLPTR));
        label_2->setText(QApplication::translate("exileSniffer", "Key", Q_NULLPTR));
        label_3->setText(QApplication::translate("exileSniffer", "Send IV", Q_NULLPTR));
        label_4->setText(QApplication::translate("exileSniffer", "Receive IV", Q_NULLPTR));
        processTabs->setTabText(processTabs->indexOf(interceptionTab), QApplication::translate("exileSniffer", "Decryption", Q_NULLPTR));
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
