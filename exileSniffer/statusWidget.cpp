#include "stdafx.h"
#include "statusWidget.h"

statusWidget::statusWidget(QWidget *parent)
{
	widgetMainGridLayout = new QGridLayout(this);
	widgetMainGridLayout->setSpacing(6);
	widgetMainGridLayout->setContentsMargins(11, 11, 11, 11);
	widgetMainGridLayout->setObjectName(QStringLiteral("widgetMainGridLayout"));
	widgetMainGridLayout->setContentsMargins(0, 0, 0, 0);
	widgetMainGroupBox = new QGroupBox(this);
	widgetMainGroupBox->setObjectName(QStringLiteral("widgetMainGroupBox"));
	widgetMainGroupBox->setMinimumSize(QSize(300, 200));
	widgetMainGroupBox->setMaximumSize(QSize(16777215, 400));

	widgetMainGridLayout->addWidget(widgetMainGroupBox, 0, 0, 1, 1);


	QFont font;
	font.setPointSize(12);
	widgetMainGroupBox->setFont(font);
	labs_text_vertlayout = new QVBoxLayout(widgetMainGroupBox);
	labs_text_vertlayout->setSpacing(6);
	labs_text_vertlayout->setContentsMargins(11, 11, 11, 11);
	labs_text_vertlayout->setObjectName(QStringLiteral("labs_text_vertlayout"));
	labs_text_vertlayout->setContentsMargins(-1, 4, -1, 4);

	labels_horizlayout = new QHBoxLayout();
	labels_horizlayout->setSpacing(6);
	labels_horizlayout->setObjectName(QStringLiteral("labels_horizlayout"));
	labs_text_vertlayout->addLayout(labels_horizlayout);

	lab_bad = new QLabel(widgetMainGroupBox);
	lab_bad->setObjectName(QStringLiteral("lab_bad"));
	lab_bad->setMaximumSize(QSize(100, 100));
	lab_bad->setStyleSheet(QStringLiteral(""));
	labels_horizlayout->addWidget(lab_bad);

	lab_pending = new QLabel(widgetMainGroupBox);
	lab_pending->setObjectName(QStringLiteral("lab_pending"));
	lab_pending->setMaximumSize(QSize(100, 100));
	lab_pending->setStyleSheet(QStringLiteral(""));
	labels_horizlayout->addWidget(lab_pending);

	lab_good = new QLabel(widgetMainGroupBox);
	lab_good->setObjectName(QStringLiteral("lab_good"));
	lab_good->setMaximumSize(QSize(100, 100));
	lab_good->setStyleSheet(QStringLiteral(""));
	labels_horizlayout->addWidget(lab_good);


	text_vertLayout = new QVBoxLayout();
	text_vertLayout->setSpacing(6);
	text_vertLayout->setObjectName(QStringLiteral("text_vertLayout"));
	labs_text_vertlayout->addLayout(text_vertLayout);

	statusText = new QLabel(widgetMainGroupBox);
	statusText->setObjectName(QStringLiteral("statusText"));
	QFont font1;
	font1.setPointSize(10);
	statusText->setFont(font1);
	statusText->setAlignment(Qt::AlignCenter);
	statusText->setText("Status text");

	text_vertLayout->addWidget(statusText);





	lab_bad->setPixmap(QPixmap(":/icons/cross-red.png"));
	lab_pending->setPixmap(QPixmap(":/icons/timer.png"));
	lab_good->setPixmap(QPixmap(":/icons/check-green.png"));

	setLabelActive(lab_bad, true);
	setLabelActive(lab_pending, false);
	setLabelActive(lab_good, false);


	timerFadeInfo.active = true;
	timerFadeInfo.alpha = 167;
	timerFadeInfo.rising = true;

	fadeTimer = new QTimer(this);
	connect(fadeTimer, SIGNAL(timeout()), this, SLOT(fadeTimerLabel()));
}

statusWidget::~statusWidget()
{
}

void statusWidget::setState(statusWidgetState newState)
{
	if (newState == currentState) return;

	switch (currentState)
	{
	case eBad:
		setLabelActive(lab_bad, false);
		break;

	case ePending:
		fadeTimer->stop();
		setLabelActive(lab_pending, false);
		break;

	case eGood:
		setLabelActive(lab_good, false);
		break;
	}

	switch (newState)
	{
	case eBad:
		setLabelActive(lab_bad, true);
		break;

	case ePending:
		fadeTimer->start(80);
		setLabelActive(lab_pending, true);
		break;

	case eGood:
		setLabelActive(lab_good, true);
		break;
	}

	currentState = newState;
}

void statusWidget::setLabelActive(QLabel *lab, bool state)
{
	if (state)
	{
		lab->setGraphicsEffect(Q_NULLPTR);
	}
	else
	{
		QGraphicsColorizeEffect *effect;
		effect = new QGraphicsColorizeEffect;
		effect->setColor(QColor(225, 225, 225, 255));

		lab->setGraphicsEffect(effect);
	}
}


void statusWidget::fadeTimerLabel()
{
	if (timerFadeInfo.rising)
	{
		timerFadeInfo.alpha += 10;
		if (timerFadeInfo.alpha > 255)
		{
			timerFadeInfo.alpha = 255;
			timerFadeInfo.rising = false;
		}
	}
	else
	{
		timerFadeInfo.alpha -= 15;
		if (timerFadeInfo.alpha < 40)
		{
			timerFadeInfo.alpha = 40;
			timerFadeInfo.rising = true;
		}
	}

	QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect;
	effect->setColor(QColor(255, 255, 255, 255 - timerFadeInfo.alpha));

	lab_pending->setGraphicsEffect(effect);
}
