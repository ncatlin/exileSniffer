#include "stdafx.h"
#include "inventory.h"

std::wstring slotToString(DWORD slot)
{
	if (slot > 0x20)
		return L"Stash Tab " + std::to_wstring((slot-0x20));

	switch (slot)
	{
	case INVENTORY_SLOT_BAG:
		return L"Bag";
	case INVENTORY_SLOT_CHEST:
		return L"Chest";
	case INVENTORY_SLOT_LWEAP:
		return L"LHand";
	case INVENTORY_SLOT_RWEAP:
		return L"Rhand";
	case INVENTORY_SLOT_HEAD:
		return L"Head";
	case INVENTORY_SLOT_NECK:
		return L"Neck";
	case INVENTORY_SLOT_LEFTRING:
		return L"LRing";
	case INVENTORY_SLOT_RIGHTRING:
		return L"RRing";
	case INVENTORY_SLOT_GLOVES:
		return L"Glove";
	case INVENTORY_SLOT_BOOTS:
		return L"Boot";
	case INVENTORY_SLOT_BELT:
		return L"Belt";
	case INVENTORY_SLOT_POTIONS:
		return L"Potions";
	case INVENTORY_SLOT_LWEAP_ALT:
		return L"LHandAlt";
	case INVENTORY_SLOT_RWEAP_ALT:
		return L"RHandAlt";
	default:
		{
		std::wstringstream err;
		err << L"<TODO container 0x"<<std::hex<<slot<<">";
		return err.str();
		}
	}
}
