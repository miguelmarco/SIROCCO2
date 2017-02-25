#include "mp_icomplex.hpp"

	// CONSTRUCTORS
MPIComplex::MPIComplex (double op)
		: r (op), i (0.0) {}
MPIComplex::MPIComplex (double op1, double op2, double op3, double op4)
		: r (op1, op2), i (op3, op4) {}
MPIComplex::MPIComplex (const mpfr_t op)
		: r (op), i (0.0) {}
MPIComplex::MPIComplex (const MPComplex &op)
		: r (op.r), i (op.i) {}
MPIComplex::MPIComplex (const mpfr_t op1, const mpfr_t op2, const mpfr_t op3, const mpfr_t op4)
		: r (op1, op2), i (op3, op4) {}
MPIComplex::MPIComplex (const Interval &op1, const Interval &op2)
		: r (op1), i (op2) {}
MPIComplex::MPIComplex (const MPInterval &op1, const MPInterval &op2)
		: r (op1), i (op2) {}
MPIComplex::MPIComplex (const IComplex &op)
		: r (op.r), i (op.i) {}
	// COPY CONSTRUCTOR
MPIComplex::MPIComplex (const MPIComplex &op)
		: r (op.r), i (op.i) {}
MPIComplex::~MPIComplex () {}

	// ASSIGNMENT
MPIComplex & MPIComplex::operator= (const MPIComplex &op) {
	// CHECK WHETER WE ARE ASIGNING SOMETHING OVER ITSELF
	if (this == &op) return (*this);
	// UPDATE ELEMENTS
	this->r = op.r; this->i = op.i;
	return (*this);
}
MPIComplex & MPIComplex::operator= (const IComplex &op) {
	// UPDATE ELEMENTS
	this->r = op.r; this->i = op.i;
	return (*this);
}
MPIComplex & MPIComplex::operator= (const MPInterval &op) {
	// UPDATE ELEMENTS
	this->r = op; this->i = 0.0;
	return (*this);
}
MPIComplex & MPIComplex::operator= (const Interval &op) {
	// UPDATE ELEMENTS
	this->r = op; this->i = 0.0;
	return (*this);
}
MPIComplex & MPIComplex::operator= (const mpfr_t op) {
	// UPDATE ELEMENTS
	this->r = op; this->i = 0.0;
	return (*this);
}
MPIComplex & MPIComplex::operator= (double op) {
	// UPDATE ELEMENTS
	this->r = op; this->i = 0.0;
	return (*this);
}

// 	// COMPARISON

int MPIComplex::operator== (double op) const {
	return (this->r == op) && (this->i == 0);
}
int MPIComplex::operator== (const std::complex<double> &op) const {
	return (this->r == op.real() && this->i == op.imag ());
}
int MPIComplex::operator== (const Interval &op) const {
	return (this->r == op) && (this->i == 0);
}
int MPIComplex::operator== (const MPInterval &op) const {
	return (this->r == op) && (this->i == 0);
}
int MPIComplex::operator== (const MPIComplex &op) const {
	return (this->r == op.r) && (this->i == op.i);
}
int MPIComplex::operator!= (double op) const {
	return (this->r != op) || (this->i != 0);
}
int MPIComplex::operator!= (const std::complex<double> &op) const {
	return (this->r != op.real() || this->i != op.imag ());
}
int MPIComplex::operator!= (const Interval &op) const {
	return (this->r != op) || (this->i != 0);
}
int MPIComplex::operator!= (const MPInterval &op) const {
	return (this->r != op) || (this->i != 0);
}
int MPIComplex::operator!= (const MPIComplex &op) const {
	return (this->r != op.r) || (this->i != op.i);
}



// 	// ARITHMETIC
// A INTERVAL REAL PART
// B INTERNAL IMAG PART
// (A + iB) + (C + iD) = (A+C) + i(B+D)
MPIComplex MPIComplex::operator+ (const MPIComplex &op) const {
	return MPIComplex (this->r + op.r, this->i + op.i);
}

// (A + iB) + (C + iD) = (A+C) + i(B+D)
MPIComplex MPIComplex::operator+ (const IComplex &op) const {
	return MPIComplex (this->r + op.r, this->i + op.i);
}

// (A + iB) + C = (A+C) + iB
MPIComplex MPIComplex::operator+ (const MPInterval &op) const {
	return MPIComplex (this->r + op, this->i);
}

// (A + iB) + C = (A+C) + iB
MPIComplex MPIComplex::operator+ (const Interval &op) const {
	return MPIComplex (this->r + op, this->i);
}

// (A + iB) + C = (A+C) + iB
MPIComplex MPIComplex::operator+ (const mpfr_t op) const {
	return MPIComplex (this->r + op, this->i);
}

// (A + iB) + C = (A+C) + iB
MPIComplex MPIComplex::operator+ (double op) const {
	return MPIComplex (this->r + op, this->i);
}



// -(A + iB) = (-A) + i(-B)
MPIComplex MPIComplex::operator- () const {
	return MPIComplex (-(this->r), -(this->i));
}

// (A + iB) - (C + iD) = (A-C) + i(B-D)
MPIComplex MPIComplex::operator- (const MPIComplex &op) const {
	return MPIComplex (this->r - op.r, this->i - op.i);
}

// (A + iB) - (C + iD) = (A-C) + i(B-D)
MPIComplex MPIComplex::operator- (const IComplex &op) const {
	return MPIComplex (this->r - op.r, this->i - op.i);
}

// (A + iB) - C = (A-C) + iB
MPIComplex MPIComplex::operator- (const MPInterval &op) const {
	return MPIComplex (this->r - op, this->i);
}

// (A + iB) - C = (A-C) + iB
MPIComplex MPIComplex::operator- (const Interval &op) const {
	return MPIComplex (this->r - op, this->i);
}

// (A + iB) - C = (A-C) + iB
MPIComplex MPIComplex::operator- (const mpfr_t op) const {
	return MPIComplex (this->r - op, this->i);
}

// (A + iB) - C = (A-C) + iB
MPIComplex MPIComplex::operator- (double op) const {
	return MPIComplex (this->r - op, this->i);
}



// (A + iB) * (C + iD) = (A*C - B*D) + i(A*D + B*C)
MPIComplex MPIComplex::operator* (const MPIComplex &op) const {
	return MPIComplex (this->r * op.r - this->i * op.i,
				this->r * op.i + this->i * op.r);
}

// (A + iB) * (C + iD) = (A*C - B*D) + i(A*D + B*C)
MPIComplex MPIComplex::operator* (const IComplex &op) const {
	return MPIComplex (this->r * op.r - this->i * op.i,
				this->r * op.i + this->i * op.r);
}

// (A + iB) * C = (A*C) + i(B*C)
MPIComplex MPIComplex::operator* (const MPInterval &op) const {
	return MPIComplex (this->r * op, this->i * op);
}

// (A + iB) * C = (A*C) + i(B*C)
MPIComplex MPIComplex::operator* (const Interval &op) const {
	return MPIComplex (this->r * op, this->i * op);
}

// (A + iB) * C = (A*C) + i(B*C)
MPIComplex MPIComplex::operator* (const mpfr_t op) const {
	return MPIComplex (this->r * op, this->i * op);
}

// (A + iB) * C = (A*C) + i(B*C)
MPIComplex MPIComplex::operator* (double op) const {
	return MPIComplex (this->r * op, this->i * op);
}


MPIComplex MPIComplex::operator/ (const MPIComplex &op) const {
	return (*this) * (op.inverse ());
}
MPIComplex MPIComplex::operator/ (const IComplex &op) const {
	return (*this) * (op.inverse ());
}
MPIComplex MPIComplex::operator/ (const MPInterval &op) const {
	return (*this) * (op.inverse ());
}
MPIComplex MPIComplex::operator/ (const Interval &op) const {
	return (*this) * (op.inverse ());
}
MPIComplex MPIComplex::operator/ (const mpfr_t op) const {
	return (*this) * (MPIComplex(op).inverse ());
}
MPIComplex MPIComplex::operator/ (double op) const {
	return (*this) * (IComplex(op).inverse ());
}



// 	// MISC
MPIComplex MPIComplex::inverse () const {
	if (this->containsZero()) {
		mpfr_t aux;
		mpfr_init (aux);
		mpfr_set_nan (aux);
		MPIComplex rop (aux);
		mpfr_clear (aux);
		return rop;
	}

	MPIComplex inv_edge[4], rop;
	inv_edge[0] = inverse_horizontal (this->r.a, this->r.b, this->i.a);
	inv_edge[1] = inverse_horizontal (this->r.a, this->r.b, this->i.b);
	inv_edge[2] = inverse_vertical (this->i.a, this->i.b, this->r.a);
	inv_edge[3] = inverse_vertical (this->i.a, this->i.b, this->r.b);

	mpfr_min (rop.r.a, inv_edge[0].r.a, inv_edge[1].r.a, MPFR_RNDD);
		mpfr_min (rop.r.a, rop.r.a, inv_edge[2].r.a, MPFR_RNDD);
		mpfr_min (rop.r.a, rop.r.a, inv_edge[3].r.a, MPFR_RNDD);


	mpfr_max (rop.r.b, inv_edge[0].r.b, inv_edge[1].r.b, MPFR_RNDU);
		mpfr_max (rop.r.b, rop.r.b, inv_edge[2].r.b, MPFR_RNDU);
		mpfr_max (rop.r.b, rop.r.b, inv_edge[3].r.b, MPFR_RNDU);

	mpfr_min (rop.i.a, inv_edge[0].i.a, inv_edge[1].i.a, MPFR_RNDD);
		mpfr_min (rop.i.a, rop.i.a, inv_edge[2].i.a, MPFR_RNDD);
		mpfr_min (rop.i.a, rop.i.a, inv_edge[3].i.a, MPFR_RNDD);


	mpfr_max (rop.i.b, inv_edge[0].i.b, inv_edge[1].i.b, MPFR_RNDU);
		mpfr_max (rop.i.b, rop.i.b, inv_edge[2].i.b, MPFR_RNDU);
		mpfr_max (rop.i.b, rop.i.b, inv_edge[3].i.b, MPFR_RNDU);


	return rop;

}

int MPIComplex::containsZero () const {
	return ((this->r).containsZero () && (this->i).containsZero());
}
int MPIComplex::contains (double op) const {
	return ((this->r).contains (op) && (this->i).contains(op));
}
int MPIComplex::contains (const mpfr_t op) const {
	return ((this->r).contains (op) && (this->i).contains(op));
}
int MPIComplex::subset (const MPIComplex &op) const {
	return (this->r).subset (op.r) && (this->i).subset (op.i);
}




// // NON MEMBER FUNCTIONS

std::ostream & operator<< (std::ostream &output, const MPIComplex &op) {
	output << op.r << " + i" << op.i;
	return output;
}


MPIComplex operator+ (const IComplex &op1, const MPIComplex &op2) {
	return MPIComplex (op1.r + op2.r, op1.i + op2.i);
}
MPIComplex operator+ (const MPInterval &op1, const MPIComplex &op2) {
	return MPIComplex (op2.r, op1 + op2.i);
}
MPIComplex operator+ (const Interval &op1, const MPIComplex &op2) {
	return MPIComplex (op1 + op2.r, op2.i);
}
MPIComplex operator+ (const mpfr_t op1, const MPIComplex &op2) {
	return MPIComplex (op1 + op2.r, op2.i);
}
MPIComplex operator+ (double op1, const MPIComplex &op2) {
	return MPIComplex (op1 + op2.r, op2.i);
}

MPIComplex operator- (const IComplex &op1, const MPIComplex &op2) {
	return MPIComplex (op1.r - op2.r, op1.i - op2.i);
}
MPIComplex operator- (const MPInterval &op1, const MPIComplex &op2) {
	return MPIComplex (op1 - op2.r, -op2.i);
}
MPIComplex operator- (const Interval &op1, const MPIComplex &op2) {
	return MPIComplex (op1 - op2.r, -op2.i);
}
MPIComplex operator- (const mpfr_t op1, const MPIComplex &op2) {
	return MPIComplex (op1 - op2.r, -op2.i);
}
MPIComplex operator- (double op1, const MPIComplex &op2) {
	return MPIComplex (op1 - op2.r, -op2.i);
}

MPIComplex operator* (const IComplex &op1, const MPIComplex &op2) {
	return MPIComplex (op1.r * op2.r - op1.i * op2.i,
				op1.r * op2.i + op1.i * op2.r);
}
MPIComplex operator* (const MPInterval &op1, const MPIComplex &op2) {
	return MPIComplex (op1 * op2.r, op1 * op2.i);
}
MPIComplex operator* (const Interval &op1, const MPIComplex &op2) {
	return MPIComplex (op1 * op2.r, op1 * op2.i);
}
MPIComplex operator* (const mpfr_t op1, const MPIComplex &op2) {
	return MPIComplex (op1 * op2.r, op1 * op2.i);
}
MPIComplex operator* (double op1, const MPIComplex &op2) {
	return MPIComplex (op1 * op2.r, op1 * op2.i);
}

MPIComplex operator/ (const IComplex &op1, const MPIComplex &op2) {
	return op1 * (op2.inverse ());
}
MPIComplex operator/ (const MPInterval &op1, const MPIComplex &op2) {
	return op1 * (op2.inverse ());
}
MPIComplex operator/ (const Interval &op1, const MPIComplex &op2) {
	return op1 * (op2.inverse ());
}
MPIComplex operator/ (const mpfr_t op1, const MPIComplex &op2) {
	return op1 * (op2.inverse ());
}
MPIComplex operator/ (double op1, const MPIComplex &op2) {
	return op1 * (op2.inverse ());
}




// // MISCELLANEOUS FUNCTIONS FOR INVERT COMPLEX INTERVALS

// returns inverse of horizontal segment [a,b] + ci
MPIComplex inverse_horizontal (const mpfr_t a, const mpfr_t b, const mpfr_t c) {
	MPIComplex rop;
	mpfr_t aux;
	mpfr_init (aux);
	// case c = 0
	if (mpfr_cmp_si (c, 0) == 0) {
		if (mpfr_cmp_si (a, 0) < 0 && mpfr_cmp_si (b, 0) > 0) {
			mpfr_set_nan (rop.r.a);
			mpfr_set_nan (rop.r.b);
			mpfr_set_nan (rop.i.a);
			mpfr_set_nan (rop.i.b);
		} else {
			mpfr_si_div (rop.r.a, 1, b, MPFR_RNDD);
			mpfr_si_div (rop.r.b, 1, a, MPFR_RNDU);
			mpfr_set_si (rop.i.a, 0, MPFR_RNDD);
			mpfr_set_si (rop.i.b, 0, MPFR_RNDU);
		}
	// case c > 0
	} else if (mpfr_cmp_si (c, 0) > 0) {
		// case a<0<b
		if (mpfr_cmp_si (a, 0) < 0 && mpfr_cmp_si (b, 0) > 0) {
			mpfr_si_div (rop.i.a, -1, c, MPFR_RNDD);

			if (mpfr_cmpabs (b, a) > 0)
				g (rop.i.b, b, c, MPFR_RNDU);
			else
				g (rop.i.b, a, c, MPFR_RNDU);


			if (mpfr_cmpabs (a, c) > 0) {
				mpfr_mul_si (aux, c, 2, MPFR_RNDD);
				mpfr_si_div (rop.r.a, -1, aux, MPFR_RNDD);
			} else
				f (rop.r.a, a, c, MPFR_RNDD);


			if (mpfr_cmp (c, b) < 0) {
				mpfr_mul_si (aux, c, 2, MPFR_RNDU);
				mpfr_si_div (rop.r.b, 1, aux, MPFR_RNDU);
			} else {
				f (rop.r.b, b, c, MPFR_RNDU);
			}
		}

		// case 0<=a<b
		else if (mpfr_cmp_si (a, 0) >= 0) {
			g (rop.i.a, a, c, MPFR_RNDD);

			g (rop.i.b, b, c, MPFR_RNDU);

			f (aux, a, c, MPFR_RNDD);
			f (rop.r.a, b, c, MPFR_RNDD);
			mpfr_min (rop.r.a, rop.r.a, aux, MPFR_RNDD);

			if (mpfr_cmp (b, c) < 0) {
				f (rop.r.b, b, c, MPFR_RNDU);
			} else if (mpfr_cmp (c, a) < 0) {
				f (rop.r.b, a, c, MPFR_RNDU);
			} else {
				mpfr_mul_si (rop.r.b, c, 2, MPFR_RNDU);
				mpfr_si_div (rop.r.b, 1, rop.r.b, MPFR_RNDU);
			}
		}

		// case a<b<=0
		else if (mpfr_cmp_si (b, 0) <= 0) {
			g (rop.i.a, b, c, MPFR_RNDD);
			g (rop.i.b, a, c, MPFR_RNDU);
			f (aux, a, c, MPFR_RNDU);
			f (rop.r.b, b, c, MPFR_RNDU);
			mpfr_max (rop.r.b, rop.r.b, aux, MPFR_RNDU);

			if (mpfr_cmpabs (c, a) > 0) {
				f (rop.r.a, a, c, MPFR_RNDD);
			} else if (mpfr_cmpabs (b, c) > 0) {
				f (rop.r.a, b, c, MPFR_RNDD);
			} else {
				mpfr_mul_si (rop.r.a, c, 2, MPFR_RNDD);
				mpfr_si_div (rop.r.a, -1, rop.r.a, MPFR_RNDD);
			}
		}
	// case c < 0
	} else {
		mpfr_neg (aux, c, MPFR_RNDN);	// ???
		rop = inverse_horizontal (a, b, aux);
		rop.i = -rop.i;
	}
	mpfr_clear (aux);
	return rop;

}

// returns inverse of verticla segment c + [a,b]i
MPIComplex inverse_vertical (const mpfr_t a, const mpfr_t b, const mpfr_t c) {
	mpfr_t aux1, aux2;
	mpfr_inits (aux1, aux2, NULL);
	mpfr_neg (aux1, b, MPFR_RNDD);
	mpfr_neg (aux2, a, MPFR_RNDU);
	MPIComplex rop;
	rop = inverse_horizontal (aux1, aux2, c);

	MPInterval aux (rop.i);
	rop.i = rop.r;
	rop.r = -aux;

	mpfr_clears (aux1, aux2, NULL);
	return rop;


}
void f (mpfr_t rop, const mpfr_t x, const mpfr_t c, mpfr_rnd_t roundMode) {
	mpfr_t aux;
	mpfr_init(aux);
	mpfr_mul (aux, c, c, roundMode);
	mpfr_mul (rop, x, x, roundMode);
	mpfr_add (rop, rop, aux, roundMode);
	mpfr_div (rop, x, rop, roundMode);
	mpfr_clear (aux);
}
void g (mpfr_t rop, const mpfr_t x, const mpfr_t c, mpfr_rnd_t roundMode) {
	mpfr_t aux;
	mpfr_init (aux);
	mpfr_mul (aux, c, c, roundMode);
	mpfr_mul (rop, x, x, roundMode);
	mpfr_add (rop, rop, aux, roundMode);
	mpfr_neg (aux, c, roundMode);
	mpfr_div (rop, aux, rop, roundMode);
	mpfr_clear (aux);
}
