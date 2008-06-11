#ifndef GME_DYNMENU_H
#define GME_DYNMENU_H

class CDynMenuItem {
	friend class CDynMenu;
public:
	CDynMenuItem(int iden,CString &lab,CString &hmsg) : id(iden), label(lab), helpMsg(hmsg) {}
protected:
	int id;
	CString label;
	CString helpMsg;
public:
	CString &GetLabel()		{ return label; }
	CString &GetHelpMsg()	{ return helpMsg; }
};

class CDynMenu {
public:
	CDynMenu(int iden,char *nm);
	~CDynMenu();
protected:
	int id;
	int minID,maxID;
	CString name;
	CDynMenuItemList items;
	CMenu menu;
public:
	void SetName(CString nm)	{ name = nm; }
	void SetID(int i)			{ id = i; }
	CMenu &GetMenu()			{ return menu; }
	int GetMinID()				{ return minID; }
	int GetMaxID()				{ return maxID; }
	bool IsEmpty()				{ return items.GetCount() == 0; }
	int GetCount()				{ return items.GetCount(); }

	void AddItem(int id,CString &label,CString helpMsg);
	CDynMenuItem *FindItem(int id);
};

#endif // whole file

