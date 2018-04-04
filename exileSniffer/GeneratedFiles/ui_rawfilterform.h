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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rawFilterForm
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QListView *listView;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QTextEdit *textEdit;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *rawClearBtn;
    QPushButton *rawOkBtn;

    void setupUi(QWidget *rawFilterForm)
    {
        if (rawFilterForm->objectName().isEmpty())
            rawFilterForm->setObjectName(QStringLiteral("rawFilterForm"));
        rawFilterForm->resize(591, 434);
        verticalLayout = new QVBoxLayout(rawFilterForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(rawFilterForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(350, 50));
        QFont font;
        font.setPointSize(10);
        groupBox->setFont(font);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout->addWidget(checkBox_2);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(rawFilterForm);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(350, 54));
        groupBox_2->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, -1, -1, 9);
        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        checkBox_4 = new QCheckBox(groupBox_2);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setMinimumSize(QSize(0, 0));
        checkBox_4->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(groupBox_2);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        horizontalLayout_2->addWidget(checkBox_5);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(rawFilterForm);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setFont(font);
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        listView = new QListView(groupBox_3);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout_3->addWidget(listView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        frame = new QFrame(groupBox_3);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        frame->setMidLineWidth(1);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 3, -1, 3);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label);

        textEdit = new QTextEdit(frame);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy2);
        textEdit->setMaximumSize(QSize(50, 26));

        horizontalLayout_4->addWidget(textEdit);

        comboBox = new QComboBox(frame);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(0, 26));
        comboBox->setMaximumSize(QSize(100, 16777215));
        comboBox->setFont(font);

        horizontalLayout_4->addWidget(comboBox);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(103, 26));

        horizontalLayout_4->addWidget(pushButton);


        horizontalLayout_3->addWidget(frame);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        rawClearBtn = new QPushButton(groupBox_3);
        rawClearBtn->setObjectName(QStringLiteral("rawClearBtn"));
        rawClearBtn->setMinimumSize(QSize(0, 26));
        rawClearBtn->setMaximumSize(QSize(87, 16777215));

        horizontalLayout_5->addWidget(rawClearBtn);

        rawOkBtn = new QPushButton(groupBox_3);
        rawOkBtn->setObjectName(QStringLiteral("rawOkBtn"));
        rawOkBtn->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(rawOkBtn);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout_2->addWidget(groupBox_3);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(rawFilterForm);
        QObject::connect(rawOkBtn, SIGNAL(clicked()), rawFilterForm, SLOT(okBtnPress()));

        QMetaObject::connectSlotsByName(rawFilterForm);
    } // setupUi

    void retranslateUi(QWidget *rawFilterForm)
    {
        rawFilterForm->setWindowTitle(QApplication::translate("rawFilterForm", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("rawFilterForm", "Exclude by Direction", Q_NULLPTR));
        checkBox->setText(QApplication::translate("rawFilterForm", "Client -> Server", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("rawFilterForm", "Server -> Client", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("rawFilterForm", "Exclude by Stream Type", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("rawFilterForm", "Login", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("rawFilterForm", "Game", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("rawFilterForm", "Exclude Specific Packet Types (first two bytes)", Q_NULLPTR));
        label->setText(QApplication::translate("rawFilterForm", "Packet ID 0x", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("rawFilterForm", "Login", Q_NULLPTR)
         << QApplication::translate("rawFilterForm", "Game", Q_NULLPTR)
        );
        pushButton->setText(QApplication::translate("rawFilterForm", "Add Filter", Q_NULLPTR));
        rawClearBtn->setText(QApplication::translate("rawFilterForm", "Clear Filters", Q_NULLPTR));
        rawOkBtn->setText(QApplication::translate("rawFilterForm", "Done", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class rawFilterForm: public Ui_rawFilterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAWFILTERFORM_H
