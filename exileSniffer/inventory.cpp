#include "stdafx.h"
#include "inventory.h"

std::string slotToString(byte slot)
{
	switch (slot)
	{
	case INVENTORY_SLOT_BAG:
		return "Bag";
	case INVENTORY_SLOT_CHEST:
		return "Chest";
	case INVENTORY_SLOT_LWEAP:
		return "LHand";
	case INVENTORY_SLOT_RWEAP:
		return "Rhand";
	case INVENTORY_SLOT_HEAD:
		return "Head";
	case INVENTORY_SLOT_NECK:
		return "Neck";
	case INVENTORY_SLOT_LEFTRING:
		return "LRing";
	case INVENTORY_SLOT_RIGHTRING:
		return "RRing";
	case INVENTORY_SLOT_GLOVES:
		return "Glove";
	case INVENTORY_SLOT_BOOTS:
		return "Boot";
	case INVENTORY_SLOT_BELT:
		return "Boot";
	case INVENTORY_SLOT_POTIONS:
		return "Belt";
	default:
		return "<TODO>";
	}
}
