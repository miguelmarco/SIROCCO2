#include <fenv.h>
#include <cmath>
#include "icomplex.hpp"

#define MIN(a,b) (((a) < (b))? (a) : (b))
#define MAX(a,b) (((a) > (b))? (a) : (b))

#ifndef __clang__
#pragma STDC FENV_ACCESS ON
#endif


// CONSTRUCTORS
IComplex::IComplex (double op)
		: r(op, op), i() {}
IComplex::IComplex (double op1, double op2, double op3, double op4) 
		: r(op1, op2), i(op3, op4) {}
IComplex::IComplex (const Interval &op1, const Interval &op2)
		: r(op1), i(op2) {}

IComplex::IComplex (const std::complex<double> &op)
		: r(op.real()), i(op.imag()) {}
	// COPY CONSTRUCTOR
IComplex::IComplex (const IComplex &op)
		: r(op.r), i(op.i) {}
IComplex::~IComplex () {}



// // ASSIGNMENT
IComplex & IComplex::operator= (const IComplex &op) {
	// CHECK WHETER WE ARE ASIGNING SOMETHING OVER ITSELF
	if (this == &op) return (*this);
	// UPDATE ELEMENTS
	this->r = op.r; this->i = op.i;
	return (*this);
}
IComplex & IComplex::operator= (const std::complex<double> &op) {
	// UPDATE ELEMENTS
	this->r = op.real (); this->i = op.imag ();
	return (*this);
}

IComplex & IComplex::operator= (const Interval &op) {
	// UPDATE ELEMENTS
	this->r = op; this->i = 0.0;
	return (*this);
}
IComplex & IComplex::operator= (double op) {
	// UPDATE ELEMENTS
	this->r = op; this->i = 0.0;
	return (*this);
}

// // COMPARISON
int IComplex::operator== (const IComplex &op) const {
	return (this->r == op.r) && (this->i == op.i);
}
int IComplex::operator== (const std::complex<double> &op) const {
	return (this->r == op.real ()) && (this->i == op.imag ());
}
int IComplex::operator== (double op) const {
	return (this->r == op) && (this->i == 0);
}
int IComplex::operator!= (const IComplex &op) const {
	return !((*this) == op);
}
int IComplex::operator!= (const std::complex<double> &op) const {
	return !((*this) == op);
}
int IComplex::operator!= (double op) const {
	return !((*this) == op);
}


// // ARITHMETIC
// A INTERVAL REAL PART
// B INTERNAL IMAG PART
// (A + iB) + (C + iD) = (A+C) + i(B+D)
IComplex IComplex::operator+ (const IComplex &op) const {
	return IComplex (this->r + op.r, this->i + op.i);
}

// (A + iB) + (C + iD) = (A+C) + i(B+D)
IComplex IComplex::operator+ (const std::complex<double> &op) const {
	return IComplex (this->r + op.real (), this->i + op.imag ());
}

// (A + iB) + C = (A+C) + iB
IComplex IComplex::operator+ (const Interval &op) const {
	return IComplex (this->r + op, this->i);
}

// (A + iB) + C = (A+C) + iB
IComplex IComplex::operator+ (double op) const {
	return IComplex (this->r + op, this->i);
}


// -(A + iB) = (-A) + i(-B)
IComplex IComplex::operator- () const {
	return IComplex (-(this->r), -(this->i));
}

// (A + iB) - (C + iD) = (A-C) + i(B-D)
IComplex IComplex::operator- (const IComplex &op) const {
	return IComplex (this->r - op.r, this->i - op.i);
}

// (A + iB) - (C + iD) = (A-C) + i(B-D)
IComplex IComplex::operator- (const std::complex<double> &op) const {
	return IComplex (this->r - op.real (), this->i - op.imag ());
}

// (A + iB) - (C + iD) = (A-C) + i(B-D)
IComplex IComplex::operator- (const Interval &op) const {
	return IComplex (this->r - op, this->i);
}

// (A + iB) - C = (A-C) + iB
IComplex IComplex::operator- (double op) const {
	return IComplex (this->r - op, this->i);
}


// (A + iB) * (C + iD) = (A*C - B*D) + i(A*D + B*C)
IComplex IComplex::operator* (const IComplex &op) const {
	return IComplex (this->r * op.r - this->i * op.i,
				this->r * op.i + this->i * op.r);
}

// (A + iB) * (C + iD) = (A*C - B*D) + i(A*D + B*C)
IComplex IComplex::operator* (const std::complex<double> &op) const {
	return IComplex (this->r * op.real () - this->i * op.imag (),
				this->r * op.imag () + this->i * op.real ());
}

// (A + iB) * C = (A*C) + i(B*C)
IComplex IComplex::operator* (const Interval &op) const {
	return IComplex (this->r * op, this->i * op);
}

// (A + iB) * C = (A*C) + i(B*C)
IComplex IComplex::operator* (double op) const {
	return IComplex (this->r * op, this->i * op);
}



IComplex IComplex::operator/ (const IComplex &op) const {
	return (*this) * (op.inverse ());
}
IComplex IComplex::operator/ (const std::complex<double> &op) const {
	return (*this) * (IComplex(op).inverse ());
}
IComplex IComplex::operator/ (const Interval &op) const {
	return IComplex (this->r / op, this->i / op);
}
IComplex IComplex::operator/ (double op) const {
	return IComplex (this->r / op, this->i / op);
}



// // MISC
IComplex IComplex::inverse () const {
	if (this->containsZero())
		return IComplex (NAN, NAN, NAN, NAN);
	IComplex inv_edge[4], rop;
	inv_edge[0] = inverse_horizontal (this->r.a, this->r.b, this->i.a);
	inv_edge[1] = inverse_horizontal (this->r.a, this->r.b, this->i.b);
	inv_edge[2] = inverse_vertical (this->i.a, this->i.b, this->r.a);
	inv_edge[3] = inverse_vertical (this->i.a, this->i.b, this->r.b);

	rop.r.a = MIN (MIN (MIN (inv_edge[0].r.a, 
			inv_edge[1].r.a), inv_edge[2].r.a), inv_edge[3].r.a);
	rop.r.b = MAX (MAX (MAX (inv_edge[0].r.b, 
			inv_edge[1].r.b), inv_edge[2].r.b), inv_edge[3].r.b);
	rop.i.a = MIN (MIN (MIN (inv_edge[0].i.a, 
			inv_edge[1].i.a), inv_edge[2].i.a), inv_edge[3].i.a);
	rop.i.b = MAX (MAX (MAX (inv_edge[0].i.b, 
			inv_edge[1].i.b), inv_edge[2].i.b), inv_edge[3].i.b);

	return rop;
}

// CHECKS WHETHER 0 IS IN A + iB
int IComplex::containsZero () const {
	return ((this->r).containsZero () && (this->i).containsZero());
}

// CHECKS WHETHER A VALUE IS in A + iB
int IComplex::contains (double op) const {
	return ((this->r).contains (op) && (this->i).contains(op));
}
int IComplex::contains (const std::complex<double> &op) {
	return ((this->r).contains(op.real()) && (this->i).contains(op.imag ()));
}


// CHECK WHETHER A COMPLEX INTERVAL IS INSIDE ANOTHER WITHOUT TOUCHING THE EDGES
int IComplex::subset (const IComplex &op) const {
	return (this->r).subset (op.r) && (this->i).subset (op.i);
}

// CHECK WHETHER A COMPLEX INTERVAL IS INSIDE ANOTHER
int IComplex::subsetEq (const IComplex &op) const {
	return (this->r).subsetEq (op.r) && (this->i).subsetEq (op.i);
}

	


// // NON MEMBER FUNCTIONS

// OVERLOAD OUTPUT STREAM
std::ostream & operator<< (std::ostream &output, const IComplex &op) {
	output << op.r << " + i*" << op.i;
	return output;
}
	

// C + (A + iB) = (A+C) + iB
IComplex operator+ (const std::complex<double> &op1, const IComplex &op2) {
	return IComplex (op1.real () + op2.r, op1.imag () + op2.i);
}

// C + (A + iB) = (A+C) + iB
IComplex operator+ (const Interval &op1, const IComplex &op2) {
	return IComplex (op1 + op2.r, op2.i);
}

// C + (A + iB) = (A+C) + iB
IComplex operator+ (double op1, const IComplex &op2) {
	return IComplex (op1 + op2.r, op2.i);
}

// C - (A + iB) = (C-A) + i(-B)
IComplex operator- (const std::complex<double> &op1, const IComplex &op2) {
	return IComplex (op1.real () - op2.r, op1.imag () -op2.i);
}
// C - (A + iB) = (C-A) + i(-B)
IComplex operator- (const Interval &op1, const IComplex &op2) {
	return IComplex (op1 - op2.r, -op2.i);
}

// C - (A + iB) = (C-A) + i(-B)
IComplex operator- (double op1, const IComplex &op2) {
	return IComplex (op1 - op2.r, -op2.i);
}

// C * (A + iB) = (C*A) + i(C*B)
IComplex operator* (const std::complex<double> &op1, const IComplex &op2) {
	return (IComplex (op1.real () * op2.r - op1.imag () * op2.i, 
				op1.real () * op2.i + op1.imag () * op2.r));
}

// C * (A + iB) = (C*A) + i(C*B)
IComplex operator* (const Interval &op1, const IComplex &op2) {
	return (IComplex (op1 * op2.r, op1 * op2.i));
}

// C * (A + iB) = (C*A) + i(C*B)
IComplex operator* (double op1, const IComplex &op2) {
	return (IComplex (op1 * op2.r, op1 * op2.i));
}

// C / (A + iB) = C * (A + iB)^-1
IComplex operator/ (const std::complex<double> &op1, const IComplex &op2) {
	return op1 * (op2.inverse ());
}

// C / (A + iB) = C * (A + iB)^-1
IComplex operator/ (const Interval &op1, const IComplex &op2) {
	return op1 * (op2.inverse ());
}

// C / (A + iB) = C * (A + iB)^-1
IComplex operator/ (double op1, const IComplex &op2) {
	return op1 * (op2.inverse ());
}


// MISC METHODS FOR INVERSION

// returns inverse of horizontal segment [a,b] + ci
IComplex inverse_horizontal (double a, double b, double c) {
	IComplex rop;
	int oldRoundingMode = fegetround ();
	// case c = 0
	if (c == 0) {
		if (a < 0 && b > 0) {
			rop.r.a = rop.r.b = rop.i.a = rop.i.b = NAN;
		} else {
			rop.i.a = rop.i.b = 0.0;
			fesetround (FE_DOWNWARD);
			rop.r.a = 1.0 / b;
			fesetround (FE_UPWARD);
			rop.r.b = 1.0 / a;
		}
	// case c > 0
	} else if (c > 0) {
		// case a<0<b
		if (a < 0 && 0 < b) {
			fesetround (FE_DOWNWARD);

			if (a < -c)
				rop.r.a = -0.5 / c;
			else 
				rop.r.a = f (a, c);

			rop.i.a = -1.0 / c;

			fesetround (FE_UPWARD);

			if (c < b)
				rop.r.b = 0.5 / c;
			else
				rop.r.b = f (b, c);
			
			if (b > (-a))
				rop.i.b = g (b, c); 
			else
				rop.i.b = g (a, c);
		}

		// case 0<=a<b
		else if (0 <= a) {
			fesetround (FE_DOWNWARD);

			rop.r.a = MIN (f (a, c), f(b, c));
			rop.i.a = g (a, c);

			fesetround (FE_UPWARD);

			if (b < c)
				rop.r.b = f (b, c);
			else if (c < a)
				rop.r.b = f (a, c);
			else
				rop.r.b = 0.5 / c;

			rop.i.b = g (b, c);
		}

		// case a<b<=0
		else if (b <= 0) {
			fesetround (FE_DOWNWARD);

			if (-c < a)
				rop.r.a = f (a, c);
			else if (b < -c)
				rop.r.a = f (b, c);
			else 
				rop.r.a = -0.5 / c;

			rop.i.a = g (b, c);

			fesetround (FE_UPWARD);

			rop.r.b = MAX (f (a, c), f (b, c));
			rop.i.b = g (a, c);
		}
	// case c < 0
	} else {
		rop = inverse_horizontal (a, b, -c);
		rop.i = -rop.i;
	}


	fesetround (oldRoundingMode);
	return rop;
}

// returns inverse of verticla segment c + [a,b]i
IComplex inverse_vertical (double a, double b, double c) {
	IComplex rop;
	rop = inverse_horizontal (-b, -a, c);
	Interval aux (rop.i);
	rop.i = rop.r;
	rop.r = -aux;

	return rop;
}

double f (double x, double c) {
	return x / (x*x + c*c);	
}
double g (double x, double c) {
	return -c / (x*x + c*c);
}
