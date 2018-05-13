#pragma once

#include "ui_rawfilterform.h"
#include "qwidget.h"
#include "uiMsg.h"


#define FILTER_SECTION_ID 0
#define FILTER_SECTION_FUNCTION 1
#define FILTER_SECTION_SENDER 2
#define FILTER_SECTION_COUNT 3
#define FILTER_SECTION_STATE 4


enum eDisplayState { hidden, displayed };

struct PRESET_LIST {
	std::vector<ushort> IDs;
	QString name;
	QString description;
};

class filterForm : public QWidget
{
	Q_OBJECT
public:
		filterForm(QWidget *parent = 0);
		~filterForm() {};
		void setUI(Ui::rawFilterForm *ptr, SafeQueue<UI_MESSAGE *> *msgq) { ui = ptr; uiMsgQueue = msgq; }
		
		void populateFiltersList(rapidjson::GenericValue<rapidjson::UTF8<>> &msgInfo);
		void populatePresetsList();
		bool isDisplayed(ushort pktID);

		void setFilterRowState(int row, eDisplayState newState);

signals:
	void applyFilters();

public Q_SLOTS:
	void applyBtnPress() { emit applyFilters(); this->hide(); }
	void includeSelectedFilters();
	void excludeSelectedFilters();
	void saveCustom();
	void showPresetContextMenu(const QPoint& pos);
	void activatePresetListClicked();
	void deletePreset();
	void buildBuiltinPresets();
	void toggleSelectedFilter(); 
	void addPresetListToTree(PRESET_LIST& newList);
	void savePresetLists();

private:

	void add_filter_category(unsigned short pktid, QString description, 
		bool incoming, eDisplayState initialState = eDisplayState::displayed);
	void setRowColor(int tablerow, QColor colour); 
	void setPktIDFilterState(ushort pktID, eDisplayState newState);
	PRESET_LIST load_saved_preset(QString groupname);
	void activateBuiltInPresetList(int index); 
	void activatePresetList(PRESET_LIST& filters);
	

	Ui::rawFilterForm *ui = NULL;
	SafeQueue<UI_MESSAGE *> *uiMsgQueue = NULL;

	std::map<unsigned short, eDisplayState> filterStates;
	std::map<unsigned short, QTableWidgetItem *> filterTableItems;

	std::vector<PRESET_LIST> builtinPresets;
	std::vector<PRESET_LIST> customPresets;

	QSettings *savedPresetLists = NULL;
};

class numericSortTableWidgetItem : public QTableWidgetItem {
public:
	numericSortTableWidgetItem() { this->setTextAlignment(Qt::AlignCenter); }
	void setHex(int num) {
		customHex = true;
		this->setData(Qt::ItemDataRole::UserRole, num);
		this->setText("0x" + QString::number(num, 16) + "/" + QString::number(num, 10));
	}
	bool operator <(const QTableWidgetItem &other) const
	{
		if (customHex)
			return data(Qt::ItemDataRole::UserRole).toInt() < other.data(Qt::ItemDataRole::UserRole).toInt();
		else
			return text().toInt() < other.text().toInt();
	}
private:
	bool customHex = false;
};