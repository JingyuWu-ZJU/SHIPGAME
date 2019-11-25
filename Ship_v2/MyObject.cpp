// MyObject.cpp: implementation of the CMyObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ship_v2.h"
#include "MyObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyObject::CMyObject()
{
	m_bSubmarine = false;

}

CMyObject::~CMyObject()
{

}
