#ifndef _ICOMPLEX_HPP
#define _ICOMPLEX_HPP


#include <iostream>
#include <complex>
#include <interval.hpp>

class IComplex {
public:

	Interval r;
	Interval i;

	// CONSTRUCTORS
	IComplex (double = 0);
	IComplex (const Interval &, const Interval &);
	IComplex (double, double, double, double);
	IComplex (const std::complex<double> &);
	IComplex (const IComplex &);
	~IComplex ();

	// ASSIGNMENT
	IComplex & operator= (const IComplex &);
	IComplex & operator= (const Interval &);
	IComplex & operator= (const std::complex<double> &);
	IComplex & operator= (double);

	// COMPARISON
	int operator== (const IComplex &) const;
	int operator== (const std::complex<double> &) const;
	int operator== (double) const;
	int operator!= (const IComplex &) const;
	int operator!= (const std::complex<double> &) const;
	int operator!= (double) const;

	// ARITHMETIC
	IComplex operator+ (const IComplex &) const;
	IComplex operator+ (const Interval &) const;
	IComplex operator+ (const std::complex<double> &) const;
	IComplex operator+ (double) const;

	IComplex operator- () const;
	IComplex operator- (const IComplex &) const;
	IComplex operator- (const std::complex<double> &) const;
	IComplex operator- (const Interval &) const;
	IComplex operator- (double) const;

	IComplex operator* (const IComplex &) const;
	IComplex operator* (const std::complex<double> &) const;
	IComplex operator* (const Interval &) const;
	IComplex operator* (double) const;

	IComplex operator/ (const IComplex &) const;
	IComplex operator/ (const std::complex<double> &) const;
	IComplex operator/ (const Interval &) const;
	IComplex operator/ (double) const;



	// MISC
	IComplex inverse () const;

	int containsZero () const;
	int contains (double) const;
	int contains (const std::complex<double> &);
	int subset (const IComplex &) const;
	int subsetEq (const IComplex &) const;



};


// NON MEMBER FUNCTIONS

std::ostream & operator<< (std::ostream &, const IComplex &);


IComplex operator+ (const Interval &, const IComplex &);
IComplex operator+ (const std::complex<double> &, const IComplex &);
IComplex operator+ (double, const IComplex &);

IComplex operator- (const Interval &, const IComplex &);
IComplex operator- (const std::complex<double> &, const IComplex &);
IComplex operator- (double, const IComplex &);

IComplex operator* (const Interval &, const IComplex &);
IComplex operator* (const std::complex<double> &, const IComplex &);
IComplex operator* (double, const IComplex &);

IComplex operator/ (const Interval &, const IComplex &);
IComplex operator/ (const std::complex<double> &, const IComplex &);
IComplex operator/ (double, const IComplex &);



// MISCELLANEOUS FUNCTIONS FOR INVERT COMPLEX INTERVALS
IComplex inverse_horizontal (double, double, double);
IComplex inverse_vertical (double, double, double);
double f (double, double);
double g (double, double);

#endif
