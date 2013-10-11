#ifndef DV2549_MATRIXGEN_AMPERSAND_H
#define DV2549_MATRIXGEN_AMPERSAND_H

template < class T >
class Matrix;

#include <amp_tinymt_rng.h>

/*
The constructor of Ampersand, as well as matrixPopulate - or any use of C++ AMP it seems - seems to cause memory leaks.
I'm not sure what causes it, whether or not it is expected behaviour or if I've done something wrong.
*/

template < class T >
class Ampersand {
public:
	Ampersand() {
		concurrency::accelerator default_device;
		std::wcout << std::endl << L"Initializing C++ AMP with device: " << default_device.get_description() + L".";
		if( default_device==concurrency::accelerator( concurrency::accelerator::direct3d_ref) ) {
			std::cout << std::endl << "Warning. Running C++ AMP using a slow emulator.";
		}
		
		srand( time( 0 ) );
	}
	~Ampersand() {
		// Do nothing.
	}

	template < class T >
	void matrixPopulate( Matrix< T >* p_matrix, int p_min, int p_max ) {
		const unsigned rows = p_matrix->getNumRows();
		const unsigned cols = p_matrix->getNumCols();
		T* matrix = p_matrix->get();

		// Initialize RNG:
		long seed = rand();
		concurrency::extent< 2 > e_size( rows, cols );
		tinymt_collection< 2 > rng( e_size, seed );
		char ref[50];
		sprintf_s( ref, "%d", matrix );
		std::cout << std::endl << "C++ AMP RNG initialized with seed: " + Util::toString( seed ) + "." << std::endl << "Proceeding to generate random numbers for matrix: " + std::string( ref ) + ".";
	
		concurrency::array_view< T, 2 > ioMatrix( rows, cols, matrix );
		parallel_for_each(
			ioMatrix.extent,
			[=]( concurrency::index< 2 > idx ) restrict( amp ) {
				int row = idx[ 0 ];
				int col = idx[ 1 ];
		
				auto t = rng[ idx ];
				float random = t.next_single(); // Gives a floating point in-between 0-1.
				ioMatrix[ row ][ col ] = int( concurrency::precise_math::nearbyint( random * p_max + p_min ) );
			}
		);
		ioMatrix.synchronize();
	}

	template < class T >
	void matrixMultiply( Matrix< T >* p_c, Matrix< T >* p_a, Matrix< T >* p_b ) {
		const unsigned rows = p_c->getNumRows();
		const unsigned cols = p_c->getNumCols();
		
		T* a = p_a->get();
		T* b = p_b->get();
		T* c = p_c->get();

		concurrency::array_view< T, 2 > iA( p_a->getNumRows(), p_a->getNumCols(), a ); 
		concurrency::array_view< T, 2 > iB( p_b->getNumRows(), p_b->getNumCols(), b );
		concurrency::array_view< T, 2 > ioC( p_c->getNumRows(), p_c->getNumCols(), c );
		parallel_for_each(
			ioC.extent,
			[=]( concurrency::index< 2 > idx ) restrict( amp ) {
				int row = idx[ 0 ];
				int col = idx[ 1 ];
				for( unsigned i = 0; i < rows; i++ ) {
					ioC[ idx ] += iA( row, i ) * iB( i, col );
				}
			}
		);
		ioC.synchronize();
	}
protected:
private:
};
// http://amprng.codeplex.com/SourceControl/latest#test/main.cpp

#endif // DV2549_MATRIXGEN_AMPERSAND_H