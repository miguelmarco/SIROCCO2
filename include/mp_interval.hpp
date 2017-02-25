#ifndef _MP_INTERVAL_HPP
#define _MP_INTERVAL_HPP

#include <interval.hpp>
#include <iostream>
#include <mpfr.h>


// IMPLEMENTS [a,b],
// a,b mpfr

class MPInterval {
	// FRIEND CLASS
public:

	mpfr_t a;
	mpfr_t b;


	// CONSTRUCTORS
	// DEFAULT CONSTRUCTOR
	MPInterval (double = 0);
	// CONSTRUCTOR BY double ELEMENTS
	MPInterval (double, double);
	// CONSTRUCTOR BY string VALUE
	MPInterval (const char *);
	// CONSTRUCTOR BY string PAIR OF VALUES
	MPInterval (const char *, const char *);
	// CONSTRUCTOR BY mpfr ELEMENT
	MPInterval (const mpfr_t);
	// CONSTRUCTOR BY mpfr PAIR OF ELEMENTS
	MPInterval (const mpfr_t, const mpfr_t);
	// CONSTRUCTOR BY double Invterval
	MPInterval (const Interval &);
	// COPY CONSTRUCTOR
	MPInterval (const MPInterval &);
	// DESTRUCTOR
	~MPInterval ();

	// COMPARISON
	int operator== (double) const;
	int operator== (const Interval &) const;
	int operator== (const MPInterval &) const;
	int operator!= (double) const;
	int operator!= (const Interval &) const;
	int operator!= (const MPInterval &) const;

	// ASSIGNMENT
	MPInterval & operator= (const MPInterval &);
	MPInterval & operator= (const Interval &);
	MPInterval & operator= (const mpfr_t);
	MPInterval & operator= (double);

	// ARITHMETIC
	MPInterval operator+ (const MPInterval &) const;
	MPInterval operator+ (const Interval &) const;
	MPInterval operator+ (const mpfr_t) const;
	MPInterval operator+ (double) const;

	MPInterval operator- () const;
	MPInterval operator- (const MPInterval &) const;
	MPInterval operator- (const Interval &) const;
	MPInterval operator- (const mpfr_t) const;
	MPInterval operator- (double) const;

	MPInterval operator* (const MPInterval &) const;
	MPInterval operator* (const Interval &) const;
	MPInterval operator* (const mpfr_t) const;
	MPInterval operator* (double) const;

	MPInterval operator/ (const MPInterval &) const;
	MPInterval operator/ (const Interval &) const;
	MPInterval operator/ (const mpfr_t) const;
	MPInterval operator/ (double) const;



	// MISC
	MPInterval inverse () const;

	int containsZero () const;
	int contains (double) const;
	int contains (const mpfr_t) const;
	int subset (const MPInterval &) const;
	int subset (const Interval &) const;


};

// EXTERNAL FUNCTIONS
std::ostream & operator<< (std::ostream &, const MPInterval &);

MPInterval operator+ (double, const MPInterval &);
MPInterval operator+ (const mpfr_t, const MPInterval &);
MPInterval operator+ (const Interval &, const MPInterval &);

MPInterval operator- (double, const MPInterval &);
MPInterval operator- (const mpfr_t, const MPInterval &);
MPInterval operator- (const Interval &, const MPInterval &);

MPInterval operator* (double, const MPInterval &);
MPInterval operator* (const mpfr_t, const MPInterval &);
MPInterval operator* (const Interval &, const MPInterval &);

MPInterval operator/ (double, const MPInterval &);
MPInterval operator/ (const mpfr_t, const MPInterval &);
MPInterval operator/ (const Interval &, const MPInterval &);
#endif
