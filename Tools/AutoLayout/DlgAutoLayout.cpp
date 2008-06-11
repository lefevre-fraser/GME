// DlgAutoLayout.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAutoLayout.h"
#include "CommonSmart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoLayout dialog


CDlgAutoLayout::CDlgAutoLayout(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutoLayout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAutoLayout)
	m_startFromScratch = TRUE;
	//}}AFX_DATA_INIT
    m_currentSolution = NULL;
}

CDlgAutoLayout::~CDlgAutoLayout()
{
}

void CDlgAutoLayout::initialzie( IMgaProject * project, IMgaModel* model )
{
    m_project = project;
    m_model   = model;
    
    COMTHROW( m_model->get_Meta((IMgaMetaFCO**)PutOut(m_metaModel)) );
    COMTHROW( m_metaModel->get_Aspects( PutOut(m_metaAspects) ) );    
}

void CDlgAutoLayout::update( int percentage, LayoutSolution * sol, double score  )
{
    m_score = score;
    m_currentSolution = sol;
    m_progressOptimization.SetPos(percentage);
    m_graph.Invalidate(FALSE);
    m_graph.UpdateWindow();


    m_updateTime++;
    if( m_updateTime > 50 )
    {
        m_updateTime = 0;
        Invalidate(FALSE);
        UpdateWindow();
    }
}
  
void CDlgAutoLayout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAutoLayout)
	DDX_Control(pDX, IDC_LIST_ASPECTS, m_listAspects);
	DDX_Control(pDX, IDC_PROGRESS_OPT, m_progressOptimization);
	DDX_Control(pDX, IDC_PROGRESS_ASPECT, m_progressAspect);
	DDX_Control(pDX, IDC_BUTTON_GRAPH, m_graph);
	DDX_Check(pDX, IDC_CHECK_STARTFROMSCRATCH, m_startFromScratch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAutoLayout, CDialog)
	//{{AFX_MSG_MAP(CDlgAutoLayout)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoLayout message handlers

BOOL CDlgAutoLayout::OnInitDialog() 
{
	CDialog::OnInitDialog();

    m_graph.GetClientRect( m_graphRect );
    m_backBrush.CreateSolidBrush( RGB( 192, 192, 192 ) );
    CDC* dc = m_graph.GetDC();
    m_graphDC.CreateCompatibleDC( dc );
    m_graphBmp.CreateCompatibleBitmap( dc, m_graphRect.Width(), m_graphRect.Height() );
    m_graphOldBmp = (CBitmap*)m_graphDC.SelectObject( &m_graphBmp );
    m_graph.ReleaseDC( dc );

    long aspectNum;
    COMTHROW( m_metaAspects->get_Count( &aspectNum ) );    
    m_listAspects.ResetContent();
    for( int i=0; i<aspectNum; ++i )
    {
        CComObjPtr<IMgaMetaAspect>  aspect;
        COMTHROW( m_metaAspects->get_Item( i+1, PutOut(aspect) ) );
        CComBSTR aspectName;
        COMTHROW( aspect->get_Name(&aspectName) );
        m_listAspects.AddString( CString(aspectName) );
    }
    m_listAspects.SetSel(0,TRUE);

    m_progressOptimization.ShowWindow( SW_HIDE );
    m_progressAspect.ShowWindow( SW_HIDE );
	
	
	return TRUE;
}

void CDlgAutoLayout::drawSolution( CDC * dc, LayoutSolution * sol )
{
    unsigned int i,j;

    // draw background
    dc->FillRect( &m_graphRect, &m_backBrush );
    dc->Draw3dRect( &m_graphRect, RGB( 128, 128, 128 ), RGB( 255, 255, 255 ) );

    if( sol == NULL )
        return;

    // draw nodes    
    NodePosVec& nodes = sol->getNodes();
    LayoutOptProblem * problem = sol->getProblem();
    double psx = problem->getWidth();
    double psy = problem->getHeight();
    for( i=0; i<nodes.size(); ++i )
    {
        int x  = (int)(m_graphRect.Width()  * nodes[i].m_x / psx);
        int y  = (int)(m_graphRect.Height() * nodes[i].m_y / psy);
        int sx = (int)(m_graphRect.Width()  * nodes[i].m_node->m_sx / psx );
        int sy = (int)(m_graphRect.Height() * nodes[i].m_node->m_sy / psy );
        dc->Rectangle( x, y, x+sx, y+sy );
        // draw ports
        for( j=0; j<nodes[i].m_node->m_ports.size(); ++j )
        {
            Node * port = nodes[i].m_node->m_ports[j];
            int x1  = x + (int)(m_graphRect.Width()  * port->m_x / psx);
            int y1  = y + (int)(m_graphRect.Height()  * port->m_y / psy);
            int sx1 = (int)(m_graphRect.Width()  * port->m_sx / psx);
            int sy1 = (int)(m_graphRect.Height()  * port->m_sy / psy);
            dc->Rectangle( x1, y1, x1+sx1, y1+sy1 );
        }
    }

    // draw edges
    EdgeVec& edges = problem->getEdges();
    for( i=0; i<edges.size(); ++i )
    {
        int x1, y1, x2, y2;
        sol->calcEdgeEnds( edges[i], x1, y1, x2, y2 );

        int xp1 = (int)(m_graphRect.Width()  * x1 / psx);
        int yp1 = (int)(m_graphRect.Height() * y1 / psy);
        int xp2 = (int)(m_graphRect.Width()  * x2 / psx);
        int yp2 = (int)(m_graphRect.Height() * y2 / psy);

        dc->MoveTo( xp1, yp1 );
        dc->LineTo( xp2, yp2 );
    }

    // draw score
    dc->SetBkMode( TRANSPARENT );
    CString scoreLabel;
    scoreLabel.Format("Fitness = %.6f", m_score );
    dc->TextOut( 10, 10, scoreLabel );
}

void CDlgAutoLayout::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CDC* dc = CDC::FromHandle( lpDrawItemStruct->hDC );

    if( nIDCtl == IDC_BUTTON_GRAPH )
    {
        drawSolution( &m_graphDC, m_currentSolution );        

        dc->BitBlt( 0, 0, m_graphRect.right, m_graphRect.bottom, &m_graphDC, 0, 0, SRCCOPY );

    }
}


void CDlgAutoLayout::OnButton1()
{
    try
    {
        UpdateData();

        m_progressOptimization.ShowWindow( SW_SHOW );
        m_progressAspect.ShowWindow( SW_SHOW );
        m_progressAspect.SetPos(1);
        m_progressAspect.UpdateWindow();
    
        int selNum = m_listAspects.GetSelCount();
        int aspectsProcessed = 0;

        if( selNum == 0 )
            return;

        for( int i=0; i<m_listAspects.GetCount(); ++i )
        {
            if( m_listAspects.GetSel(i) > 0 )
            {
                aspectsProcessed++;
                m_progressAspect.SetPos( (int)(100*aspectsProcessed/(double)selNum) );

                CComObjPtr<IMgaMetaAspect>  aspect;
                COMTHROW( m_metaAspects->get_Item( i+1, PutOut(aspect) ) );

                // oprimize aspect layout
                GMEGraph graph( m_project, m_model, aspect );
                LayoutOptimizer optimizer( &graph );
                m_updateTime = 0;
                optimizer.optimize( this, m_startFromScratch>0 );    
                m_currentSolution = NULL;
                m_graph.Invalidate(FALSE);

                // write back results to gme
                CComObjPtr<IMgaParts> parts;
                long   n;
                COMTHROW( m_model->get_AspectParts(aspect, 0, PutOut(parts)) );
                COMTHROW( parts->get_Count(&n) );

                for( int i=0; i<n; ++i )
                {
                    CComObjPtr<IMgaPart>     part;
                    CComObjPtr<IMgaFCO>      fco;
                    CComBSTR                 icon;
                    long                     x,y;

                    COMTHROW( parts->get_Item(i+1, PutOut(part)) );
                    COMTHROW( part->get_FCO(PutOut(fco)) );

                    for( unsigned int j=0; j<graph.m_nodes.size(); ++j )
                    {
                        if( fco == graph.m_nodes[j]->m_fco )
                        {
                            COMTHROW( part->GetGmeAttrs(&icon, &x, &y) );
                            COMTHROW( part->SetGmeAttrs(icon, graph.m_nodes[j]->m_x, graph.m_nodes[j]->m_y) );
                        }
                    }
                }
            }
        }

        m_progressOptimization.ShowWindow( SW_HIDE );
        m_progressAspect.ShowWindow( SW_HIDE );    
    }
    catch(...)
    {
        AfxMessageBox("An internal error occurred in AutoLayout component. Error code = 1");
        CDialog::OnCancel();
    }
    
    CDialog::OnOK();
}
