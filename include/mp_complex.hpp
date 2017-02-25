#ifndef MP_COMPLEX_HPP
#define MP_COMPLEX_HPP

#include <complex>
#include <iostream>
#include <mpfr.h>



class MPComplex {
public:

	mpfr_t r;
	mpfr_t i;

	MPComplex (double = 0);
	MPComplex (double, double);
	MPComplex (const std::complex<double> &);
	MPComplex (const mpfr_t);
	MPComplex (const mpfr_t, const mpfr_t);
	~MPComplex ();

	// ASSIGNMENT
	MPComplex & operator= (double);
	MPComplex & operator= (const std::complex<double> &);
	MPComplex & operator= (const mpfr_t );
	MPComplex & operator= (const MPComplex &);

	// COMPARISON
	int operator == (double) const;
	int operator == (const std::complex<double> &) const;
	int operator == (const MPComplex &) const;
	int operator != (double) const;
	int operator != (const std::complex<double> &) const;
	int operator != (const MPComplex &) const;

	// ARITHMETIC
	MPComplex operator+ (double) const;
	MPComplex operator+ (const std::complex<double> &) const;
	MPComplex operator+ (const mpfr_t ) const;
	MPComplex operator+ (const MPComplex &) const;

	MPComplex operator- () const;
	MPComplex operator- (double) const;
	MPComplex operator- (const std::complex<double> &) const;
	MPComplex operator- (const mpfr_t ) const;
	MPComplex operator- (const MPComplex &) const;

	MPComplex operator* (double) const;
	MPComplex operator* (const std::complex<double> &) const;
	MPComplex operator* (const mpfr_t ) const;
	MPComplex operator* (const MPComplex &) const;

	MPComplex operator/ (double) const;
	MPComplex operator/ (const std::complex<double> &) const;
	MPComplex operator/ (const mpfr_t ) const;
	MPComplex operator/ (const MPComplex &) const;


};

// NON MEMBER FUNCTIONS

std::ostream & operator<< (std::ostream &, const MPComplex &);

MPComplex operator+ (double, const MPComplex &);
MPComplex operator+ (const std::complex<double> &, const MPComplex &);
MPComplex operator+ (const mpfr_t , const MPComplex &);

MPComplex operator- (double, const MPComplex &);
MPComplex operator- (const std::complex<double> &, const MPComplex &);
MPComplex operator- (const mpfr_t , const MPComplex &);

MPComplex operator* (double, const MPComplex &);
MPComplex operator* (const std::complex<double> &, const MPComplex &);
MPComplex operator* (const mpfr_t , const MPComplex &);

MPComplex operator/ (double, const MPComplex &);
MPComplex operator/ (const std::complex<double> &, const MPComplex &);
MPComplex operator/ (const mpfr_t , const MPComplex &);


void abs (mpfr_t rop, const MPComplex &op);


#endif
