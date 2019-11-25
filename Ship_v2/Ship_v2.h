// Ship_v2.h : main header file for the SHIP_V2 application
//

#if !defined(AFX_SHIP_V2_H__E4DF458E_501A_4DD6_97E2_6E61AE5CA371__INCLUDED_)
#define AFX_SHIP_V2_H__E4DF458E_501A_4DD6_97E2_6E61AE5CA371__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#define GAME_WIDTH		500
#define GAME_HEIGHT		300

/////////////////////////////////////////////////////////////////////////////
// CShip_v2App:
// See Ship_v2.cpp for the implementation of this class
//

class CShip_v2App : public CWinApp
{
public:
	CShip_v2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShip_v2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShip_v2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHIP_V2_H__E4DF458E_501A_4DD6_97E2_6E61AE5CA371__INCLUDED_)
