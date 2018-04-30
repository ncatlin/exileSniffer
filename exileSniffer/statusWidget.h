#pragma once

#include <QWidget>


class statusWidget : public QWidget
{
	Q_OBJECT

public:
	statusWidget(QWidget *parent);
	~statusWidget();

	void setTitle(QString title) { widgetMainGroupBox->setTitle(title); }

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

	struct  {
		bool active = false;
		int alpha = 167;
		bool rising = false;
	} timerFadeInfo;

	void setLabelActive(QLabel *lab, bool state);
};
