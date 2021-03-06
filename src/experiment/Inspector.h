#ifndef DV2549_EXPERIMENT_INSPECTOR_H
#define DV2549_EXPERIMENT_INSPECTOR_H

template < class T >
class Inspector {
public:
	Inspector( Case< T >& p_case ) {
		m_case = &p_case;
	}
	~Inspector() {
		// Do nothing.
	}

	bool inspect() {
		bool isEqual = false;
		
		T* m1 = m_case->ref->get();
		T* m2 = m_case->c->get();
		unsigned rows = m_case->ref->getNumRows();
		unsigned cols = m_case->ref->getNumCols();

		unsigned size = rows * cols * sizeof( T );
		int comparison = memcmp( m1, m2, size );
		if( comparison==0 ) {
			isEqual = true;
		}
		m_case->equalToRef = isEqual;

		return isEqual;
	}
protected:
private:
	Case< T >* m_case;
};

#endif // DV2549_EXPERIMENT_INSPECTOR_H

/*T* m1 = m_case->m_ref->get();
T* m2 = m_case->m_c->get();
unsigned rows = m_case->m_ref->getNumRows();
unsigned cols = m_case->m_ref->getNumCols();
for( unsigned row = 0; row < rows; row++ ) {
for( unsigned col = 0; col < cols; col++ ) {
T a = m1[];
if(  )
}
}*/