#include <stdafx.h>

#include <Dx.h>
#include <Win.h>
#include <Case.h>
#include <Reader.h>
#include <Experiment.h>

Experiment::Experiment( Winfo* p_winfo ) {
	m_winfo = p_winfo;
	
	m_dx = nullptr;
	m_win = nullptr;
}
Experiment::~Experiment() {
	assert( m_win );
	assert( m_dx );
	
	delete m_win;
	delete m_dx;
}

HRESULT Experiment::init() {
	HRESULT hr = S_OK;

	// Initialize dx:
	if( SUCCEEDED( hr ) ) {
		hr = initWin();
	}
	if( SUCCEEDED( hr ) ) {
		hr = initDx();
	}
	return hr;
}

int Experiment::run( int argc, char *argv[] ) {
	// Initialize case data:
	Case< int > _case;
	Reader< int >::loadCase( _case ); // test

	MSG msgWin = { 0 };
	while( WM_QUIT!=msgWin.message ) { 
		if( PeekMessage( &msgWin, NULL, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msgWin );
			DispatchMessage( &msgWin );
		} else {
			// Do things.
			m_dx->render();
		}
	}
	return (int)msgWin.wParam;
}

HRESULT Experiment::initWin() {
	m_win = new Win( m_winfo->hInstance, m_winfo->hInstancePrev, m_winfo->lpCmdLine, m_winfo->nCmdShow );
	return m_win->init();
}
HRESULT Experiment::initDx() {
	HRESULT hr = S_OK;
	m_dx = new Dx();
	hr = m_dx->init( m_win );

	return hr;
}