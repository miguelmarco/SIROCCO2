#ifndef _MP_ICOMPLEX_HPP
#define _MP_ICOMPLEX_HPP


#include <iostream>
#include <mpfr.h>
#include <mp_complex.hpp>
#include <interval.hpp>
#include <icomplex.hpp>
#include <mp_interval.hpp>

class MPIComplex {
public:


	// CONSTRUCTORS
	MPIComplex (double = 0);
	MPIComplex (double, double, double, double);
	MPIComplex (const mpfr_t);
	MPIComplex (const MPComplex &);
	MPIComplex (const mpfr_t, const mpfr_t, const mpfr_t, const mpfr_t);
	MPIComplex (const Interval &, const Interval &);
	MPIComplex (const MPInterval &, const MPInterval &);
	MPIComplex (const IComplex &);
	MPIComplex (const MPIComplex &);
	~MPIComplex ();

	// ASSIGNMENT
	MPIComplex & operator= (const MPIComplex &);
	MPIComplex & operator= (const IComplex &);
	MPIComplex & operator= (const MPInterval &);
	MPIComplex & operator= (const Interval &);
	MPIComplex & operator= (const mpfr_t);
	MPIComplex & operator= (double);

	// COMPARISON
	int operator== (double) const;
	int operator== (const std::complex<double> &) const;
	int operator== (const Interval &) const;
	int operator== (const MPInterval &) const;
	int operator== (const MPIComplex &) const;
	int operator!= (double) const;
	int operator!= (const std::complex<double> &) const;
	int operator!= (const Interval &) const;
	int operator!= (const MPInterval &) const;
	int operator!= (const MPIComplex &) const;

	// ARITHMETIC
	MPIComplex operator+ (const MPIComplex &) const;
	MPIComplex operator+ (const IComplex &) const;
	MPIComplex operator+ (const MPInterval &) const;
	MPIComplex operator+ (const Interval &) const;
	MPIComplex operator+ (const mpfr_t) const;
	MPIComplex operator+ (double) const;

	MPIComplex operator- () const;
	MPIComplex operator- (const MPIComplex &) const;
	MPIComplex operator- (const IComplex &) const;
	MPIComplex operator- (const MPInterval &) const;
	MPIComplex operator- (const Interval &) const;
	MPIComplex operator- (const mpfr_t) const;
	MPIComplex operator- (double) const;

	MPIComplex operator* (const MPIComplex &) const;
	MPIComplex operator* (const IComplex &) const;
	MPIComplex operator* (const MPInterval &) const;
	MPIComplex operator* (const Interval &) const;
	MPIComplex operator* (const mpfr_t) const;
	MPIComplex operator* (double) const;


	MPIComplex operator/ (const MPIComplex &) const;
	MPIComplex operator/ (const IComplex &) const;
	MPIComplex operator/ (const MPInterval &) const;
	MPIComplex operator/ (const Interval &) const;
	MPIComplex operator/ (const mpfr_t) const;
	MPIComplex operator/ (double) const;



	// MISC
	MPIComplex inverse () const;

	int containsZero () const;
	int contains (double) const;
	int contains (const mpfr_t) const;
	int subset (const MPIComplex &) const;
	// int subsetEq (const MPIComplex &) const;


	MPInterval r;
	MPInterval i;
};


// NON MEMBER FUNCTIONS

std::ostream & operator<< (std::ostream &, const MPIComplex &);


MPIComplex operator+ (const IComplex &, const MPIComplex &);
MPIComplex operator+ (const MPInterval &, const MPIComplex &);
MPIComplex operator+ (const Interval &, const MPIComplex &);
MPIComplex operator+ (const mpfr_t, const MPIComplex &);
MPIComplex operator+ (double, const MPIComplex &);

MPIComplex operator- (const IComplex &, const MPIComplex &);
MPIComplex operator- (const MPInterval &, const MPIComplex &);
MPIComplex operator- (const Interval &, const MPIComplex &);
MPIComplex operator- (const mpfr_t, const MPIComplex &);
MPIComplex operator- (double, const MPIComplex &);

MPIComplex operator* (const IComplex &, const MPIComplex &);
MPIComplex operator* (const MPInterval &, const MPIComplex &);
MPIComplex operator* (const Interval &, const MPIComplex &);
MPIComplex operator* (const mpfr_t, const MPIComplex &);
MPIComplex operator* (double, const MPIComplex &);

MPIComplex operator/ (const IComplex &, const MPIComplex &);
MPIComplex operator/ (const MPInterval &, const MPIComplex &);
MPIComplex operator/ (const Interval &, const MPIComplex &);
MPIComplex operator/ (const mpfr_t, const MPIComplex &);
MPIComplex operator/ (double, const MPIComplex &);




// MISCELLANEOUS FUNCTIONS FOR INVERT COMPLEX INTERVALS
MPIComplex inverse_horizontal (const mpfr_t, const mpfr_t, const mpfr_t);
MPIComplex inverse_vertical (const mpfr_t, const mpfr_t, const mpfr_t);
void f (mpfr_t, const mpfr_t, const mpfr_t, mpfr_rnd_t);
void g (mpfr_t, const mpfr_t, const mpfr_t, mpfr_rnd_t);

#endif
