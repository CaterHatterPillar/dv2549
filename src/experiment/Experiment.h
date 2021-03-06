#ifndef DV2549_EXPERIMENT_EXPERIMENT_H
#define DV2549_EXPERIMENT_EXPERIMENT_H

#include <Dx.h>
#include <Win.h>
#include <Case.h>
#include <Reader.h>
#include <Printer.h>
#include <Inspector.h> // Get rid of these includes somehow.

template < class T >
class Experiment {
public:
	Experiment( Winfo* p_winfo, ExperimentConf p_conf ) {
		m_winfo	= p_winfo;
		m_conf	= p_conf;
		
		m_dx	= nullptr;
		m_win	= nullptr;
	}
	~Experiment() {
		ASSERT_DELETE( m_win );
		ASSERT_DELETE( m_dx );
	}
	
	HRESULT init() {
		HRESULT hr = BOOL_TO_HRESULT( Reader< T >::loadCase( m_case ) );
		if( SUCCEEDED( hr ) ) {
			hr = initWin();
		}
		if( SUCCEEDED( hr ) ) {
			hr = initDx();
		}
		return hr;
	}

	int run( int argc, char *argv[] ) {
		// Perform matrix multiplication of specified case using DirectCompute:
		m_case.ms = m_dx->run();

		// Compare result to reference matrix compiled by C++ AMP:
		Inspector< T > inspector( m_case );
		bool isEqual = inspector.inspect();

		Printer< T > printer( m_conf.confPrecision, m_case );
		bool sucessfulPrint = printer.print();

		return !isEqual;
	}
protected:
	HRESULT initWin() {
		m_win = new Win( m_winfo->hInstance, m_winfo->hInstancePrev, m_winfo->lpCmdLine, m_winfo->nCmdShow );
		return m_win->init();
	}
	HRESULT initDx() {
		m_dx = new Dx< T >( m_case, m_conf );
		return m_dx->init( m_win );;
	}
private:
	Win* m_win;
	ExperimentConf m_conf;

	Dx< T >* m_dx;
	Case< T > m_case;

	// Junk:
	Winfo* m_winfo;
};

#endif // DV2549_EXPERIMENT_EXPERIMENT_H