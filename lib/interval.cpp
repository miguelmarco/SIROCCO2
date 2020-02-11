#include "interval.hpp"
#include <fenv.h>
#include <cmath>



// ACTIVATE ROUND MODE CONTROL
#ifndef __clang__
#pragma STDC FENV_ACCESS ON
#endif

// MACROS FOR MIN AND MAX
#define MIN(a,b) (((a) < (b))? (a) : (b))
#define MAX(a,b) (((a) > (b))? (a) : (b))

// DEFAULT CONSTRUCTOR 
Interval::Interval (double op) {
	a = b = op;
}

// CONSTRUCTOR BY ELEMENT
Interval::Interval (double op1, double op2) {
	a = op1; b = op2;
}

// COPY CONSTRUCTOR
Interval::Interval (const Interval &op) {
	a = op.a; b = op.b;
}

// DESTRUCTOR. NOTHING TO DO...
Interval::~Interval () {}


// ASSIGNMENT
Interval & Interval::operator= (const Interval &op) {
	// CHECK WHETER WE ARE ASIGNING SOMETHING OVER ITSELF
	if (this == &op) return (*this);
	// UPDATE VALUES
	this->a = op.a; this->b = op.b;
	return (*this);
}

Interval & Interval::operator= (double op) {
	// UPDATE VALUES
	this->a = op; this->b = op;
	return (*this);
}


// COMPARISON
int Interval::operator== (const Interval &op) const {
	// BOTH END POINTS MUST BE THE SAME TO BE EQUAL
	if (this->a == op.a && this->b == op.b) return 1;
	return 0;
} 
int Interval::operator!= (const Interval &op) const {
	// BOTH END POINTS MUST BE THE SAME TO BE NOT DIFFERENT
	if (this->a == op.a && this->b == op.b) return 0;
	return 1;
} 


// ARITHMETIC

// [a,b] + [c,d] = [a+c, b+d]
Interval Interval::operator+ (const Interval &op) const {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();

	fesetround (FE_DOWNWARD);
	rop.a = this->a + op.a;

	fesetround (FE_UPWARD);
	rop.b = this->b + op.b;

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);

	return rop;
}
// [a,b] + c = [a+c, b+c]
Interval Interval::operator+ (double op) const {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();

	fesetround (FE_DOWNWARD);
	rop.a = this->a + op;

	fesetround (FE_UPWARD);
	rop.b = this->b + op;

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);

	return rop;
}

// CHANGE OF SIGN OF AN INTERVAL
// -[a,b]  =  [-b,a]
Interval Interval::operator- () const {
	Interval rop;
	rop.a = -this->b;
	rop.b = -this->a;
	return rop;
}

// [a,b] - [c,d] = [a-d, b-c]
Interval Interval::operator- (const Interval &op) const {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();

	fesetround (FE_DOWNWARD);
	rop.a = this->a - op.b;

	fesetround (FE_UPWARD);
	rop.b = this->b - op.a;

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);

	return rop;
}

// [a,b] - c = [a-c, b-c]
Interval Interval::operator- (double op) const {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();

	fesetround (FE_DOWNWARD);
	rop.a = this->a - op;

	fesetround (FE_UPWARD);
	rop.b = this->b - op;

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);

	return rop;
}

// [a,b]*[c,d] = [min(a*c,a*d,b*c,b*d), max(a*c,a*d,b*c,b*d)]
Interval Interval::operator* (const Interval &op) const {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();


	fesetround (FE_DOWNWARD);
	rop.a = MIN(MIN(MIN(this->a*op.a, this->a*op.b), this->b*op.a), this->b*op.b);

	fesetround (FE_UPWARD);
	rop.b = MAX(MAX(MAX(this->a*op.a, this->a*op.b), this->b*op.a), this->b*op.b);

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);
	return rop;


}

// [a,b]*c = [min(a*c,b*c), max(a*c,b*c)]
Interval Interval::operator* (double op) const {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();


	fesetround (FE_DOWNWARD);
	rop.a = MIN(this->a*op, this->b*op);

	fesetround (FE_UPWARD);
	rop.b = MAX(this->a*op, this->b*op);

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);
	return rop;
}


// [a,b]/[c,d] = [min(a/c,a/d,b/c,b/d), max(a/c,a/d,b/c,b/d)]
Interval Interval::operator/ (const Interval &op) const {
	if (op.containsZero()) return Interval (NAN);
	
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();

	fesetround (FE_DOWNWARD);
	rop.a = MIN(MIN(MIN(this->a/op.a, this->a/op.b), this->b/op.a), this->b/op.b);

	fesetround (FE_UPWARD);
	rop.b = MAX(MAX(MAX(this->a/op.a, this->a/op.b), this->b/op.a), this->b/op.b);

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);
	return rop;
}

// [a,b]/c = [min(a/c,b/c), max(a/c,b/c)]
Interval Interval::operator/ (double op) const {
	if (op == 0.0) return Interval (NAN);

	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();


	fesetround (FE_DOWNWARD);
	rop.a = MIN(this->a/op, this->b/op);

	fesetround (FE_UPWARD);
	rop.b = MAX(this->a/op, this->b/op);

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);
	return rop;
}




// MISC
Interval Interval::inverse () const {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();

	if (0<this->a || this->b<0) {
		fesetround (FE_DOWNWARD);
		rop.a = 1.0 / (this->b);
		fesetround (FE_UPWARD);
		rop.b = 1.0 / (this->a);
	} else {
		rop.a = rop.b = NAN;
	}

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);
	return rop;
}

// CHECKS WHETHER 0 in [a,b]
int Interval::containsZero () const {
	if (this->a <= 0 && this->b >= 0) return 1;
	return 0;
}
// CHECKS WHETHER a value is in [a,b]
int Interval::contains (double op) const {
	if (this->a <= op && this->b >= op) return 1;
	return 0;

}
// CHECKS WHETHER [a,b] subset of [c,d] with a!=c and b!=d
int Interval::subset (const Interval &op) const {
	if (this->a > op.a && this->b < op.b) return 1;
	return 0;
}

// CHECKS WHETHER [a,b] subseteq of [c,d]
int Interval::subsetEq (const Interval &op) const {
	if (this->a >= op.a && this->b <= op.b) return 1;
	return 0;
}





//EXTERNAL FUNCTIONS
// OVERLOAD OUTPUT STREAM
std::ostream & operator<< (std::ostream &output, const Interval &op) {
	output << "[" << op.a << ", " << op.b << "]";
	return output;
}


// c + [a,b] = [a+c, b+c]
Interval operator+ (double op1, const Interval &op2) {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();

	fesetround (FE_DOWNWARD);
	rop.a = op1 + op2.a;

	fesetround (FE_UPWARD);
	rop.b = op1 + op2.b;

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);

	return rop;

}

// c - [a,b] = [c-b, c-a]
Interval operator- (double op1, const Interval &op2) {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();

	fesetround (FE_DOWNWARD);
	rop.a = op1 - op2.b;

	fesetround (FE_UPWARD);
	rop.b = op1 - op2.a;

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);

	return rop;
}


// c*[a,b] = [min(a*c,b*c), max(a*c,b*c)]
Interval operator* (double op1, const Interval &op2) {
	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();


	fesetround (FE_DOWNWARD);
	rop.a = MIN(op2.a*op1, op2.b*op1);

	fesetround (FE_UPWARD);
	rop.b = MAX(op2.a*op1, op2.b*op1);

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);
	return rop;
}


// c/[a,b] = [min(c/a,c/b), max(c/a,c/b)]
Interval operator/ (double op1, const Interval &op2) {
	if (op2.containsZero ()) return Interval (NAN);

	Interval rop;

	// STORE OLD ROUNDING MODE
	int oldRound = fegetround ();


	fesetround (FE_DOWNWARD);
	rop.a = MIN(op1 / op2.a, op1 / op2.b);

	fesetround (FE_UPWARD);
	rop.b = MAX(op1 / op2.a, op1 / op2.b);

	// RESTORE OLD ROUNDING MODE
	fesetround (oldRound);
	return rop;
}
