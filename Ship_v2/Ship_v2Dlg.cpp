// Ship_v2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ship_v2.h"
#include "Ship_v2Dlg.h"


#include "Explosion.h"
#include "MyObject.h"
#include "Score.h"
#include "MyShip.h"
#include "Submarine.h"
#include "Bomb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SHIP_VERT_POS		20
#define SKY_COLOR			RGB(0, 255, 255)
#define SEA_COLOR			RGB(0, 128, 255)
#define MAX_BOMBNUM 10
//indicate m_Objects[]     
//Fox example: use 'm_Objects[MYSHIP]' to handle "my ship"
#define MYSHIP		0
#define SUBMARINE	1
#define MY_BOMB		2
#define	ENEMY_BOMB	3
#define	EXPLOSION	4
#define	SCORE		5


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShip_v2Dlg dialog

CShip_v2Dlg::CShip_v2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShip_v2Dlg::IDD, pParent)
{
	// load image list;
	CExplosion::LoadImage();
	CMyShip::LoadImage();
	CSubmarine::LoadImage();
	CBomb::LoadImage();


// create my ship object, this is the 1st object in object list
	m_Objects[MYSHIP].AddTail(new CMyShip(CPoint((GAME_WIDTH-SHIP_WIDTH)*1/3, SHIP_VERT_POS),0 ));
	m_Objects[MYSHIP].AddTail(new CMyShip(CPoint((GAME_WIDTH-SHIP_WIDTH)*2/3, SHIP_VERT_POS),1 ));
	m_bGamePause = false;
	//{{AFX_DATA_INIT(CShip_v2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShip_v2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShip_v2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShip_v2Dlg, CDialog)
	//{{AFX_MSG_MAP(CShip_v2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShip_v2Dlg message handlers

BOOL CShip_v2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShip_v2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShip_v2Dlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	dc.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_VirtualDC, 0, 0, SRCCOPY);

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShip_v2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



int CShip_v2Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CClientDC dc(this);
	m_VirtualBitmap.CreateCompatibleBitmap(&dc, GAME_WIDTH, GAME_HEIGHT);
	m_VirtualDC.CreateCompatibleDC(&dc);
	m_VirtualDC.SelectObject(&m_VirtualBitmap);

// create loop
	SetTimer(100, 30, NULL);
	return 0;
}


void CShip_v2Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
		static int nCreator = random(15) +15 ;
	CClientDC dc(this);

	int i,j,k;
	CRect l_Rect;
	CMyObject* pObject;

	if(m_bGamePause)
		return;

// create new sub
	if(nCreator==0)
	{
		m_Objects[SUBMARINE].AddTail(new CSubmarine(random(2)%2?true:false, random(GAME_HEIGHT-SHIP_VERT_POS-SHIP_HEIGHT*2-30)+SHIP_VERT_POS+SHIP_HEIGHT+30, random(4), random(4)+3));
		nCreator = (random(15) + 15)/2;
	}

// Draw sky and see
	m_VirtualDC.FillSolidRect(0, 0, GAME_WIDTH, SHIP_VERT_POS+SHIP_HEIGHT-5, SKY_COLOR);
	m_VirtualDC.FillSolidRect(0, SHIP_VERT_POS+SHIP_HEIGHT-5, GAME_WIDTH, GAME_HEIGHT, SEA_COLOR);

// Draw all objects on the virtual dc, Be careful using "POSITION"
	POSITION pos1, pos2, pos3, pos4;
	CSubmarine* pSub;
	CMyShip* pMyShip;
	if(m_Objects[MYSHIP].GetCount()!=0)
		pMyShip=(CMyShip*)m_Objects[MYSHIP].GetHead();//Get my ship

	for(j=0;j<6;j++)
	for(i=0,pos1=m_Objects[j].GetHeadPosition(); (pos2=pos1)!=NULL; i++)
   	{
		pObject=(CMyObject*)m_Objects[j].GetNext(pos1);

		if(pObject->Draw(&m_VirtualDC, m_bGamePause))  // object terminated
		{
			m_Objects[j].RemoveAt(pos2);
			delete pObject;
		}
	//submarine throw torpedo

	}//for

//Find collision between explosion and submarine
//Notice that an explosion can trigger an explosion of the submarines nearby

	for(pos1=m_Objects[EXPLOSION].GetHeadPosition(); (pos2=pos1)!=NULL;)
	{
			pObject=(CMyObject*)m_Objects[EXPLOSION].GetNext(pos1);
		
			for(pos3=m_Objects[SUBMARINE].GetHeadPosition(); (pos4=pos3)!=NULL;)
   			{
					pSub = (CSubmarine*)m_Objects[SUBMARINE].GetNext(pos3);  
					l_Rect=pObject->GetRect();

					//if there is collision between explosion and submarine
					if( (l_Rect.IntersectRect(pSub->GetRect(), l_Rect )) )
					{
						// here we first create explosion object to make score always above that explosion
						CExplosion *pExplosion=new CExplosion(pSub->GetPos());

						// when an explosion trigger another explosion, the score should multiple
						pExplosion->SetMulti( ((CExplosion*)pObject)->GetMulti()+1 );

						m_Objects[EXPLOSION].AddTail(pExplosion);
						m_Objects[SCORE].AddTail(new CScore(pSub->GetPos(), pExplosion->GetMulti(), pSub->GetType()+1, RGB(random(255), random(255), random(255))));
						
						m_Objects[SUBMARINE].RemoveAt(pos4);
						delete pSub;
						break;
											
					}//if
			}//for
						
	}//for

//Find bombs which shoot on submarine
	for(pos1=m_Objects[MY_BOMB].GetHeadPosition(); (pos2=pos1)!=NULL;)
	{
			pObject=(CMyObject*)m_Objects[MY_BOMB].GetNext(pos1);
			
			for(pos3=m_Objects[SUBMARINE].GetHeadPosition(); (pos4=pos3)!=NULL;)
   			{
					pSub = (CSubmarine*)m_Objects[SUBMARINE].GetNext(pos3);  // save for deletion
					l_Rect=((CBomb*)pObject)->GetRect();

					//if there is collision between this bomb and submarine
					if( (l_Rect.IntersectRect(pSub->GetRect(), l_Rect )) )
					{
						// here we first create explosion object to make score always above that explosion
						m_Objects[EXPLOSION].AddTail(new CExplosion(pSub->GetPos()));
						m_Objects[SCORE].AddTail(new CScore(pSub->GetPos(),1,pSub->GetType()+1, RGB(random(255), random(255), random(255))));
						
						m_Objects[SUBMARINE].RemoveAt(pos4);
						delete pSub;
						m_Objects[MY_BOMB].RemoveAt(pos2);					
						delete pObject;
						// break is important! to avoid next recycle use a bomb not exist
						break;
											
					}//if
			}//for
						
	}//for

// Game over
	if(m_Objects[MYSHIP].GetCount()==0)
	{
		m_VirtualDC.SetTextColor(RGB(255, 0, 0));
		m_VirtualDC.SetTextAlign(TA_CENTER);
		m_VirtualDC.TextOut(GAME_WIDTH/2, GAME_HEIGHT/2,"GAME OVER");
	}
// restore old text align
	m_VirtualDC.SetTextAlign(TA_LEFT);
// sample: calculate objects numbers
	m_VirtualDC.SetBkMode(TRANSPARENT);
	m_VirtualDC.SetTextColor(RGB(255, 0, 0));
	CString string;
	string.Format("Total Enemy: %d , Total Bomb: %d", m_Objects[SUBMARINE].GetCount(),m_Objects[MY_BOMB].GetCount() );
	m_VirtualDC.TextOut(10, 10, string);
// sample: calculate total score
	string.Format("Your score: %d",CScore::GetTotalScore() );
	m_VirtualDC.TextOut(300, 10, string);


// blt the virtual dc on client dc
	dc.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_VirtualDC, 0, 0, SRCCOPY);

	nCreator--;

	CDialog::OnTimer(nIDEvent);
}


void CShip_v2Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

}

void CShip_v2Dlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CShip_v2Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )
    {

		CMyShip* pShip1 = (CMyShip*)m_Objects[MYSHIP].GetHead(); // remember that our ship1 is the first object[MYSHIP] in object list
	switch( pMsg->wParam )
	{
	case VK_LEFT:       // turn left
		 if(pShip1->GetPos().x>0)
			pShip1->SetPos(pShip1->GetPos().x-10, pShip1->GetPos().y);
		break;
	
	case VK_RIGHT: // turn right
		if(pShip1->GetPos().x<GAME_WIDTH-SHIP_WIDTH)
			pShip1->SetPos(pShip1->GetPos().x+10, pShip1->GetPos().y);
		break;

	case VK_DOWN: // throw bomb from middle
		if( m_Objects[MY_BOMB].GetCount()<MAX_BOMBNUM )
		m_Objects[MY_BOMB].AddTail(new CBomb(pShip1->GetPos().x+SHIP_WIDTH/2-BOMB_WIDTH/2, 3));
		break;
	
	}//switch
    }
	return CDialog::PreTranslateMessage(pMsg);
}
