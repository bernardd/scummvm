/* ScummVM - Scumm Interpreter
 * Copyright (C) 2002 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 */

#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include "widget.h"
#include "util.h"

class ScrollBarWidget;

enum {
	kListNumberingOff	= -1,
	kListNumberingZero	= 0,
	kListNumberingOne	= 1
};

// Height of a signle entry line
enum {
	kLineHeight			= 11
};

// Some special commands
enum {
	kListItemDoubleClickedCmd	= 'LIdb',	// 'data' will be item index
	kListItemChangedCmd			= 'LIch',	// 'data' will be item index
};

/* ListWidget */
class ListWidget : public Widget, public CommandReceiver, public CommandSender {
	typedef ScummVM::StringList StringList;
	typedef ScummVM::String String;
protected:
	StringList		_list;
	bool			_editable;
	bool			_editMode;
	int				_numberingMode;
	int				_currentPos;
	int				_entriesPerPage;
	int				_selectedItem;
	ScrollBarWidget	*_scrollBar;
	int				_currentKeyDown;
	String			_backupString;
public:
	ListWidget(Dialog *boss, int x, int y, int w, int h);
	virtual ~ListWidget();
	
	void setList(const StringList& list)		{ _list = list; scrollBarRecalc(); }
	const StringList& getList()	const			{ return _list; }
	int getSelected() const						{ return _selectedItem; }
	const String& getSelectedString() const		{ return _list[_selectedItem]; }
	void setNumberingMode(int numberingMode)	{ _numberingMode = numberingMode; }
	
	virtual void handleMouseDown(int x, int y, int button, int clickCount);
	virtual void handleMouseUp(int x, int y, int button, int clickCount);
	virtual bool handleKeyDown(char key, int modifiers);
	virtual bool handleKeyUp(char key, int modifiers);
	virtual void handleCommand(CommandSender *sender, uint32 cmd, uint32 data);

	virtual bool wantsFocus() { return true; };

	void scrollBarRecalc();

protected:
	void drawWidget(bool hilite);
	void lostFocusWidget();
	void scrollToCurrent();
};

#endif
