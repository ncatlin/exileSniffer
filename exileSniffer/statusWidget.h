#pragma once

#include <QWidget>

enum statusWidgetState {eBad, ePending, eGood};

class statusWidget : public QWidget
{
	Q_OBJECT

public:
	statusWidget(QWidget *parent);
	~statusWidget();

	void setTitle(QString title) { widgetMainGroupBox->setTitle(title); }
	void setState(statusWidgetState newState);
	void setText(QString text) { statusText->setText(text); }

private slots:
	void fadeTimerLabel();

private:
	QGridLayout * widgetMainGridLayout;
	QGroupBox *widgetMainGroupBox;
	QVBoxLayout *labs_text_vertlayout;
	QHBoxLayout *labels_horizlayout;
	QLabel *lab_bad;
	QLabel *lab_pending;
	QLabel *lab_good;
	QVBoxLayout *text_vertLayout;
	QLabel *statusText;
	QTimer *fadeTimer;

	struct  {
		bool active = false;
		int alpha = 167;
		bool rising = false;
	} timerFadeInfo;

	statusWidgetState currentState = eBad;

	void setLabelActive(QLabel *lab, bool state);
};
