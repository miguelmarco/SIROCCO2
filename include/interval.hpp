#ifndef _INTERVAL_HPP
#define _INTERVAL_HPP

#include <iostream>


// IMPLEMENTS [a,b], 
// a,b double 

class Interval {
	// FRIEND CLASS

public:

	double a;
	double b;


	// CONSTRUCTORS
	// DEFAULT CONSTRUCTOR
	Interval (double = 0);
	// CONSTRUCTOR BY ELEMENTS
	Interval (double, double);
	// COPY CONSTRUCTOR
	Interval (const Interval &);
	// DESTRUCTOR
	~Interval ();

	// ASSIGNMENT
	Interval & operator= (const Interval &);
	Interval & operator= (double);

	// COMPARISON
	int operator== (const Interval &) const; 
	int operator!= (const Interval &) const; 

	// ARITHMETIC
	Interval operator+ (const Interval &) const;
	Interval operator+ (double) const;
	
	Interval operator- () const;
	Interval operator- (const Interval &) const;
	Interval operator- (double) const;
	
	Interval operator* (const Interval &) const;
	Interval operator* (double) const;
	
	Interval operator/ (const Interval &) const;
	Interval operator/ (double) const;
	


	// MISC
	Interval inverse () const;

	int containsZero () const;
	int contains (double) const;
	int subset (const Interval &) const;
	int subsetEq (const Interval &) const;

	
};

// EXTERNAL FUNCTIONS
std::ostream & operator<< (std::ostream &, const Interval &);

Interval operator+ (double, const Interval &);
Interval operator- (double, const Interval &);
Interval operator* (double, const Interval &);
Interval operator/ (double, const Interval &);
#endif