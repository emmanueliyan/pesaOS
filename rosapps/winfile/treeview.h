/*
 *  ReactOS winfile
 *
 *  treeview.h
 *
 *  Copyright (C) 2002  Robert Dickenson <robd@reactos.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __TREEVIEW_H__
#define __TREEVIEW_H__

#ifdef __cplusplus
extern "C" {
#endif


//void CreateTreeWnd(HWND parent, Pane* pane, int id);
//HTREEITEM AddItemToTree(HWND hwndTV, LPTSTR lpszItem, int nLevel);

HWND CreateTreeView(HWND hwndParent, ChildWnd* pChildWnd, int id);
void UpdateStatus(HWND hWnd, Entry* pEntry);

BOOL OnTreeExpanding(HWND hwndTV, NMTREEVIEW* pnmtv);

void OnGetDispInfo(NMTVDISPINFO* ptvdi);


#ifdef __cplusplus
};
#endif

#endif // __TREEVIEW_H__
