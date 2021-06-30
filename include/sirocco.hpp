#ifndef _SIROCCO_HPP_
#define _SIROCCO_HPP_

#include <complex>
#include <fenv.h>
#include <mp_complex.hpp>
#include <polynomial.hpp>
#include <stdio.h>


// ACTIVATE ROUND MODE CONTROL
#ifndef __clang__
#pragma STDC FENV_ACCESS ON
#endif

typedef std::complex<double> Complex;

double * homotopyPath (int degree, double *_coef, double _y0R, double _y0I);
mpfr_t * homotopyPath_mp (int degree, mpfr_t *_coef, mpfr_t _y0R, mpfr_t _y0I, int prec);

double * homotopyPath_comps (int degree, double *_coef, double _y0R, double _y0I, int nothercomps, int *degreescomps, double *_coefscomps);
mpfr_t * homotopyPath_mp_comps (int degree, mpfr_t *_coef, mpfr_t _y0R, mpfr_t _y0I, int prec, int nothercomps, int *degreescomps, mpfr_t *_coefscomps);


template <class T>  // T -> Complex, IComplex, MPComplex or MPIComplex
void correctRoot (const Polynomial<T>, const T &x0, T &y0) {}


template <class T>  // T -> Complex or MPComplex
T getA (const Polynomial<T> f, const T &x0, const T &y0) {
	return -(f.diffX (x0, y0) / f.diffY (x0, y0));
}


template <class T>	// T -> IComplex or MPIComplex
int newtonTest (const Polynomial<T> &If, const T &Ix0, const T &Iy0, const T &IY0) {

	T N, aux;

	N = If(Ix0, Iy0);


	aux = If.diffY (Ix0, IY0);

	// check we do not perform division by an interval containing 0.
	// in this case, return fail the test
	if (aux.containsZero ()) return 0;

	N = Iy0 - (N / aux);



	if (N.subset (IY0))
		return 1;
	return 0;
}


// // RETURNS WHETHER NEWTON EVALUATION N IS CONTAINED IN THE INTERVAL ENCLOSURE IY0 OF Iy0.
// // BESIDES REPEATS WITH A ENCLOSURE THREE TIMES BIGER. RETURNS SUCCESS IF BOTH ARE SATISFIED
template <class T> // T -> IComplex or MPIComplex
int validate (const Polynomial<T> &If, const T &Ix0, const T &Iy0, const T &IY0) {


	T IY1;
	if (!newtonTest<T> (If, Ix0, Iy0, IY0)) return 0;


	// COMPUTES AN ENCLOSURE THREE TIMES BIGGER FOR N2
	// CREATE A 3-TIMES BIGGER ENCLOSURE (ROUNDING TO BIGGER)
	IY1 = IY0 + IY0;
	IY1 = IY1 - IY0;

	if (!newtonTest<T> (If, Ix0, Iy0, IY1)) return 0;


	return 1;
}

template <class T>
int validate (const Polynomial<T> &If, const T &Ix0, const T &Iy0, const T &IY0, int nothercomps, const Polynomial<T> othercomps[]) {


    T IY1;
    if (!newtonTest<T> (If, Ix0, Iy0, IY0)) return 0;


    // COMPUTES AN ENCLOSURE THREE TIMES BIGGER FOR N2
    // CREATE A 3-TIMES BIGGER ENCLOSURE (ROUNDING TO BIGGER)
    IY1 = IY0 + IY0;
    IY1 = IY1 - IY0;

    if (!newtonTest<T> (If, Ix0, Iy0, IY1)) return 0;

    T evalcomp;
    for (int i=0; i<nothercomps; ++i) {

        evalcomp = othercomps[i](Ix0, IY1);


        if ( evalcomp.containsZero() ) {

            return 0;
        }
    }


    return 1;
}
#endif
