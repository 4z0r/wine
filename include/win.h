/*
 * Window definitions
 *
 * Copyright 1993 Alexandre Julliard
 */

#ifndef WIN_H
#define WIN_H

#include <X11/Xlib.h>

#include "class.h"

#define WND_MAGIC     0x444e4957  /* 'WIND' */

  /* Built-in class names (see _Undocumented_Windows_ p.418) */
#define POPUPMENU_CLASS_NAME "#32768"  /* PopupMenu */
#define DESKTOP_CLASS_NAME   "#32769"  /* Desktop */
#define DIALOG_CLASS_NAME    "#32770"  /* Dialog */
#define WINSWITCH_CLASS_NAME "#32771"  /* WinSwitch */
#define ICONTITLE_CLASS_NAME "#32772"  /* IconTitle */

typedef struct tagWND
{
    HWND         hwndNext;       /* Next sibling */
    HWND         hwndChild;      /* First child */
    DWORD        dwMagic;        /* Magic number (must be WND_MAGIC) */
    HWND         hwndParent;     /* Window parent (from CreateWindow) */
    HWND         hwndOwner;      /* Window owner */
    HCLASS       hClass;         /* Window class */
    HANDLE       hInstance;      /* Window hInstance (from CreateWindow) */
    RECT         rectClient;     /* Client area rel. to parent client area */
    RECT         rectWindow;     /* Whole window rel. to parent client area */
    RECT         rectNormal;     /* Window rect. when in normal state */
    POINT        ptIconPos;      /* Icon position */
    POINT        ptMaxPos;       /* Maximized window position */
    HANDLE       hmemTaskQ;      /* Task queue global memory handle */
    HRGN         hrgnUpdate;     /* Update region */
    HWND         hwndPrevActive; /* Previous active top-level window */
    HWND         hwndLastActive; /* Last active popup hwnd */
    WNDPROC      lpfnWndProc;    /* Window procedure */
    DWORD        dwStyle;        /* Window style (from CreateWindow) */
    DWORD        dwExStyle;      /* Extended style (from CreateWindowEx) */
    HANDLE       hdce;           /* Window DCE (if CS_OWNDC or CS_CLASSDC) */
    HANDLE       hVScroll;       /* Vertical scroll-bar info */
    HANDLE       hHScroll;       /* Horizontal scroll-bar info */
    WORD         wIDmenu;        /* ID or hmenu (from CreateWindow) */
    HANDLE       hText;          /* Handle of window text */
    WORD         flags;          /* Misc. flags (see below) */
    Window       window;         /* X window (only for top-level windows) */
    RECT         rectClientSave; /* where client rect is saved when icon*/
    HMENU        hSysMenu;	 /* window's copy of System Menu */
    HANDLE       hProp;          /* Handle of Properties List */
    HTASK        hTask;          /* Task Handle of the owner */
    WORD         wExtra[1];      /* Window extra bytes */
} WND;

  /* WND flags values */
#define WIN_NEEDS_BEGINPAINT    0x01  /* WM_PAINT sent to window */
#define WIN_NEEDS_ERASEBKGND    0x02  /* WM_ERASEBKGND must be sent to window*/
#define WIN_NEEDS_NCPAINT       0x04  /* WM_NCPAINT must be sent to window */
#define WIN_RESTORE_MAX         0x08  /* Maximize when restoring */
#define WIN_INTERNAL_PAINT      0x10  /* Internal WM_PAINT message pending */
#define WIN_NO_REDRAW           0x20  /* WM_SETREDRAW called for this window */
#define WIN_GOT_SIZEMSG         0x40  /* WM_SIZE has been sent to the window */

#define WIN_CLASS_INFO(wndPtr)   (CLASS_FindClassPtr((wndPtr)->hClass)->wc)
#define WIN_CLASS_STYLE(wndPtr)  (WIN_CLASS_INFO(wndPtr).style)

  /* Window functions */
extern WND *WIN_FindWndPtr( HWND hwnd );
extern Window WIN_GetXWindow( HWND hwnd );
extern BOOL WIN_UnlinkWindow( HWND hwnd );
extern BOOL WIN_LinkWindow( HWND hwnd, HWND hwndInsertAfter );
extern HWND WIN_FindWinToRepaint( HWND hwnd );
extern void WIN_SendParentNotify( HWND hwnd, WORD event, LONG lParam );
extern BOOL WIN_CreateDesktopWindow(void);

extern Display * display;
extern Screen * screen;
extern Window rootWindow;

#endif  /* WIN_H */
