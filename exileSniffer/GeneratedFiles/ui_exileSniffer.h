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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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
    QListWidget *decodedList;
    QPlainTextEdit *decodedText;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *decodedFiltersBtn;
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
        verticalLayout_3->setSpacing(1);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, -1, -1, 0);
        decodedList = new QListWidget(decodeDisplayFrame);
        decodedList->setObjectName(QStringLiteral("decodedList"));

        verticalLayout_3->addWidget(decodedList);

        decodedText = new QPlainTextEdit(decodeDisplayFrame);
        decodedText->setObjectName(QStringLiteral("decodedText"));

        verticalLayout_3->addWidget(decodedText);


        gridLayout_3->addWidget(decodeDisplayFrame, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        decodedFiltersBtn = new QPushButton(decodeTab);
        decodedFiltersBtn->setObjectName(QStringLiteral("decodedFiltersBtn"));
        decodedFiltersBtn->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(decodedFiltersBtn);


        gridLayout_3->addLayout(horizontalLayout_4, 1, 0, 1, 1);

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
        QFont font2;
        font2.setFamily(QStringLiteral("Courier New"));
        font2.setPointSize(8);
        ptHexPane->setFont(font2);
        ptHexPane->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ptHexPane->setLineWrapMode(QTextEdit::NoWrap);
        ptHexPane->setReadOnly(true);
        ptHexPane->setTextInteractionFlags(Qt::TextSelectableByMouse);

        textPaneFrame->addWidget(ptHexPane);

        ptASCIIPane = new QTextEdit(rawDecryptTab);
        ptASCIIPane->setObjectName(QStringLiteral("ptASCIIPane"));
        QFont font3;
        font3.setFamily(QStringLiteral("Courier New"));
        ptASCIIPane->setFont(font3);
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
        QObject::connect(filtersBtn, SIGNAL(clicked()), exileSniffer, SLOT(showRawFiltersDLG()));
        QObject::connect(bytesRowCombo, SIGNAL(activated(QString)), exileSniffer, SLOT(rawBytesRowChanged(QString)));
        QObject::connect(rawLinewrapCheck, SIGNAL(toggled(bool)), exileSniffer, SLOT(toggleRawLineWrap(bool)));
        QObject::connect(rawAutoScrollCheck, SIGNAL(toggled(bool)), exileSniffer, SLOT(toggleRawAutoScroll(bool)));

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
        decodedFiltersBtn->setText(QApplication::translate("exileSniffer", "Filters", Q_NULLPTR));
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
