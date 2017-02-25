#include "mp_interval.hpp"

// MACROS FOR MIN AND MAX

#define MIN(a,b) (((a) < (b))? (a) : (b))
#define MAX(a,b) (((a) > (b))? (a) : (b))

// DEFAULT CONSTRUCTOR
MPInterval::MPInterval (double op) {
	mpfr_init_set_d (a, op, MPFR_RNDD);
	mpfr_init_set_d (b, op, MPFR_RNDU);
}
// CONSTRUCTOR BY double ELEMENTS
MPInterval::MPInterval (double op1, double op2) {
	mpfr_init_set_d (a, op1, MPFR_RNDD);
	mpfr_init_set_d (b, op2, MPFR_RNDU);
}
// CONSTRUCTOR BY string VALUE
MPInterval::MPInterval (const char *op) {
	mpfr_init_set_str (a, op, 10, MPFR_RNDD);
	mpfr_init_set_str (b, op, 10, MPFR_RNDU);
}
// CONSTRUCTOR BY string PAIR OF VALUES
MPInterval::MPInterval (const char *op1, const char *op2) {
	mpfr_init_set_str (a, op1, 10, MPFR_RNDD);
	mpfr_init_set_str (b, op2, 10, MPFR_RNDU);

}
// CONSTRUCTOR BY mpfr ELEMENT
MPInterval::MPInterval (const mpfr_t op) {
	mpfr_init_set (a, op, MPFR_RNDD);
	mpfr_init_set (b, op, MPFR_RNDU);
}
// CONSTRUCTOR BY mpfr PAIR OF ELEMENTS
MPInterval::MPInterval (const mpfr_t op1, const mpfr_t op2) {
	mpfr_init_set (a, op1, MPFR_RNDD);
	mpfr_init_set (b, op2, MPFR_RNDU);
}
// CONSTRUCTOR BY double Invterval
MPInterval::MPInterval (const Interval &op) {
	mpfr_init_set_d (a, op.a, MPFR_RNDD);
	mpfr_init_set_d (b, op.b, MPFR_RNDU);
}
// COPY CONSTRUCTOR
MPInterval::MPInterval (const MPInterval &op) {
	mpfr_init_set (a, op.a, MPFR_RNDD);
	mpfr_init_set (b, op.b, MPFR_RNDU);
}
// DESTRUCTOR
MPInterval::~MPInterval () {
	mpfr_clears (a, b, NULL);
}



int MPInterval::operator== (double op) const {
	return (mpfr_cmp_d(this->a, op) == 0) && (mpfr_cmp_d(this->b, op) == 0);
}
int MPInterval::operator== (const Interval &op) const {
	return (mpfr_cmp_d (this->a, op.a) == 0) && (mpfr_cmp_d (this->b, op.b) == 0);
}
int MPInterval::operator== (const MPInterval &op) const {
	return (mpfr_cmp(this->a, op.a) == 0) && (mpfr_cmp(this->b, op.b) == 0);
}
int MPInterval::operator!= (double op) const {
	return (mpfr_cmp_d(this->a, op) != 0) || (mpfr_cmp_d(this->b, op) != 0);
}
int MPInterval::operator!= (const Interval &op) const {
	return (mpfr_cmp_d (this->a, op.a) != 0) || (mpfr_cmp_d (this->b, op.b) != 0);
}
int MPInterval::operator!= (const MPInterval &op) const {
	return (mpfr_cmp(this->a, op.a) != 0) || (mpfr_cmp(this->a, op.b) != 0);
}


// ASSIGNMENT
MPInterval & MPInterval::operator= (const MPInterval &op) {
	// CHECK WHETER WE ARE ASIGNING SOMETHING OVER ITSELF
	if (this == &op) return (*this);
	// UPDATE VALUES
	mpfr_set (this->a, op.a, MPFR_RNDD);
	mpfr_set (this->b, op.b, MPFR_RNDU);
}
MPInterval & MPInterval::operator= (const Interval &op) {
	// UPDATE VALUES
	mpfr_set_d (this->a, op.a, MPFR_RNDD);
	mpfr_set_d (this->b, op.b, MPFR_RNDU);
}
MPInterval & MPInterval::operator= (const mpfr_t op) {
	// UPDATE VALUES
	mpfr_set (this->a, op, MPFR_RNDD);
	mpfr_set (this->b, op, MPFR_RNDU);
}
MPInterval & MPInterval::operator= (double op) {
	// UPDATE VALUES
	mpfr_set_d (this->a, op, MPFR_RNDD);
	mpfr_set_d (this->b, op, MPFR_RNDU);
}


// ARITHMETIC

// [a,b] + [c,d] = [a+c, b+d]
MPInterval MPInterval::operator+ (const MPInterval &op) const {
	MPInterval rop (*this);
	mpfr_add (rop.a, rop.a, op.a, MPFR_RNDD);
	mpfr_add (rop.b, rop.b, op.b, MPFR_RNDU);
	return rop;
}

// [a,b] + [c,d] = [a+c, b+d]
MPInterval MPInterval::operator+ (const Interval &op) const {
	MPInterval rop (*this);
	mpfr_add_d (rop.a, rop.a, op.a, MPFR_RNDD);
	mpfr_add_d (rop.b, rop.b, op.b, MPFR_RNDU);
	return rop;
}

// [a,b] + c = [a+c, b+c]
MPInterval MPInterval::operator+ (const mpfr_t op) const {
	MPInterval rop (*this);
	mpfr_add (rop.a, rop.a, op, MPFR_RNDD);
	mpfr_add (rop.b, rop.b, op, MPFR_RNDU);
	return rop;
}

// [a,b] + c = [a+c, b+c]
MPInterval MPInterval::operator+ (double op) const {
	MPInterval rop (*this);
	mpfr_add_d (rop.a, rop.a, op, MPFR_RNDD);
	mpfr_add_d (rop.b, rop.b, op, MPFR_RNDU);
	return rop;
}

// CHANGE OF SIGN OF AN INTERVAL
// -[a,b]  =  [-b,a]
MPInterval MPInterval::operator- () const {
	MPInterval rop;
	mpfr_neg (rop.a, this->b, MPFR_RNDD);
	mpfr_neg (rop.b, this->a, MPFR_RNDU);
	return rop;
}

// [a,b] - [c,d] = [a-d, b-c]
MPInterval MPInterval::operator- (const MPInterval &op) const {
	MPInterval rop(*this);
	mpfr_sub (rop.a, rop.a, op.b, MPFR_RNDD);
	mpfr_sub (rop.b, rop.b, op.a, MPFR_RNDU);
	return rop;
}
// [a,b] - [c,d] = [a-d, b-c]
MPInterval MPInterval::operator- (const Interval &op) const {
	MPInterval rop(*this);
	mpfr_sub_d (rop.a, rop.a, op.b, MPFR_RNDD);
	mpfr_sub_d (rop.b, rop.b, op.a, MPFR_RNDU);
	return rop;
}

// [a,b] - c = [a-c, b-c]
MPInterval MPInterval::operator- (const mpfr_t op) const {
	MPInterval rop(*this);
	mpfr_sub (rop.a, rop.a, op, MPFR_RNDD);
	mpfr_sub (rop.b, rop.b, op, MPFR_RNDU);
	return rop;
}

// [a,b] - c = [a-c, b-c]
MPInterval MPInterval::operator- (double op) const {
	MPInterval rop(*this);
	mpfr_sub_d (rop.a, rop.a, op, MPFR_RNDD);
	mpfr_sub_d (rop.b, rop.b, op, MPFR_RNDU);
	return rop;
}

// [a,b]*[c,d] = [min(a*c,a*d,b*c,b*d), max(a*c,a*d,b*c,b*d)]
MPInterval MPInterval::operator* (const MPInterval &op) const {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_mul (rop.a, this->a, op.a, MPFR_RNDD);
	mpfr_mul (aux, this->a, op.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_mul (aux, this->b, op.a, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_mul (aux, this->b, op.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_mul (rop.b, this->a, op.a, MPFR_RNDU);
	mpfr_mul (aux, this->a, op.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_mul (aux, this->b, op.a, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_mul (aux, this->b, op.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;

}

// [a,b]*[c,d] = [min(a*c,a*d,b*c,b*d), max(a*c,a*d,b*c,b*d)]
MPInterval MPInterval::operator* (const Interval &op) const {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_mul_d (rop.a, this->a, op.a, MPFR_RNDD);
	mpfr_mul_d (aux, this->a, op.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_mul_d (aux, this->b, op.a, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_mul_d (aux, this->b, op.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_mul_d (rop.b, this->a, op.a, MPFR_RNDU);
	mpfr_mul_d (aux, this->a, op.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_mul_d (aux, this->b, op.a, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_mul_d (aux, this->b, op.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;
}


// [a,b]*c = [min(a*c,b*c), max(a*c,b*c)]
MPInterval MPInterval::operator* (const mpfr_t op) const {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_mul (rop.a, this->a, op, MPFR_RNDD);
	mpfr_mul (aux, this->b, op, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_mul (rop.b, this->a, op, MPFR_RNDU);
	mpfr_mul (aux, this->b, op, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;
}

// [a,b]*c = [min(a*c,b*c), max(a*c,b*c)]
MPInterval MPInterval::operator* (double op) const {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_mul_d (rop.a, this->a, op, MPFR_RNDD);
	mpfr_mul_d (aux, this->b, op, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_mul_d (rop.b, this->a, op, MPFR_RNDU);
	mpfr_mul_d (aux, this->b, op, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;
}



// [a,b]/[c,d] = [min(a/c,a/d,b/c,b/d), max(a/c,a/d,b/c,b/d)]
MPInterval MPInterval::operator/ (const MPInterval &op) const {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_div (rop.a, this->a, op.a, MPFR_RNDD);
	mpfr_div (aux, this->a, op.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_div (aux, this->b, op.a, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_div (aux, this->b, op.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_div (rop.b, this->a, op.a, MPFR_RNDU);
	mpfr_div (aux, this->a, op.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_div (aux, this->b, op.a, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_div (aux, this->b, op.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;
}

// [a,b]/[c,d] = [min(a/c,a/d,b/c,b/d), max(a/c,a/d,b/c,b/d)]
MPInterval MPInterval::operator/ (const Interval &op) const {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_div_d (rop.a, this->a, op.a, MPFR_RNDD);
	mpfr_div_d (aux, this->a, op.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_div_d (aux, this->b, op.a, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_div_d (aux, this->b, op.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_div_d (rop.b, this->a, op.a, MPFR_RNDU);
	mpfr_div_d (aux, this->a, op.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_div_d (aux, this->b, op.a, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_div_d (aux, this->b, op.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;
}

// [a,b]/c = [min(a/c,b/c), max(a/c,b/c)]
MPInterval MPInterval::operator/ (const mpfr_t op) const {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_div (rop.a, this->a, op, MPFR_RNDD);
	mpfr_div (aux, this->b, op, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_div (rop.b, this->a, op, MPFR_RNDU);
	mpfr_div (aux, this->b, op, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;
}

// [a,b]/c = [min(a/c,b/c), max(a/c,b/c)]
MPInterval MPInterval::operator/ (double op) const {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_div_d (rop.a, this->a, op, MPFR_RNDD);
	mpfr_div_d (aux, this->b, op, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_div_d (rop.b, this->a, op, MPFR_RNDU);
	mpfr_div_d (aux, this->b, op, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;
}



// MISC
// [a,b] ^ -1 = [1/b, 1/a]
MPInterval MPInterval::inverse () const {
	MPInterval rop;

	// CHECK WHETER 0 IS IN THE INTERVAL
	if (this->containsZero ()) {
		mpfr_si_div (rop.a, 1, this->b, MPFR_RNDD);
		mpfr_si_div (rop.b, 1, this->a, MPFR_RNDU);
	} else {
		mpfr_set_nan (rop.a);
		mpfr_set_nan (rop.b);
	}

	return rop;

}

// CHECK WHETER 0 IS IN THE INTERVAL
int MPInterval::containsZero () const {
	if (mpfr_cmp_si (this->a, 0) <= 0 && mpfr_cmp_si (this->b, 0) >= 0)
		return 1;
	return 0;
}

// CHECK WHETER A VALUE IS IN THE INTERVAL
int MPInterval::contains (double op) const {
	if (mpfr_cmp_d (this->a, op) <= 0 && mpfr_cmp_d (this->b, op) >= 0)
		return 1;
	return 0;
}


// CHECK WHETER A VALUE IS IN THE INTERVAL
int MPInterval::contains (const mpfr_t op) const {
	if (mpfr_cmp (this->a, op) <= 0 && mpfr_cmp (this->b, op) >= 0)
		return 1;
	return 0;
}

// CHECKS WHETER THE INTERVAL [a,b] IS SUBSET OF ANOTHER [c,d].
// c<a<b<d
int MPInterval::subset (const MPInterval &op) const {
	if (mpfr_cmp (this->a, op.a) > 0 && mpfr_cmp (this->b, op.b) < 0)
		return 1;
	return 0;
}

// CHECKS WHETER THE INTERVAL [a,b] IS SUBSET OF ANOTHER [c,d].
// c<a<b<d
int MPInterval::subset (const Interval &op) const {
	if (mpfr_cmp_d (this->a, op.a) > 0 && mpfr_cmp_d (this->b, op.b) < 0)
		return 1;
	return 0;
}



// EXTERNAL FUNCTIONS
// OVERLOAD OUTPUT STREAM
std::ostream & operator<< (std::ostream &output, const MPInterval &op) {
	mpfr_exp_t exponent;
	char *string = mpfr_get_str (NULL, &exponent, 10, 0, op.a, MPFR_RNDD);
	if (mpfr_signbit (op.a) != 0)
		output << "[-" << string[1] << "." << string+2 << "e" << exponent-1 << ", ";
	else
		output << "[" << string[0] << "." << string+1 << "e" << exponent-1 << ", ";
	mpfr_free_str (string);

	string = mpfr_get_str (NULL, &exponent, 10, 0, op.b, MPFR_RNDU);
	if (mpfr_signbit (op.b) != 0)
		output << "-" << string[1] << "." << string+2 << "e" << exponent-1 << "]";
	else
		output << string[0] << "." << string+1 << "e" << exponent-1 << "]";
	mpfr_free_str (string);
	return output;
}

// c + [a,b] = [a+c, b+c] = [a,b] + c
MPInterval operator+ (double op1, const MPInterval &op2) {
	return op2 + op1;
}
// c + [a,b] = [a+c, b+c] = [a,b] + c
MPInterval operator+ (const mpfr_t op1, const MPInterval &op2) {
	return op2 + op1;
}
// [c,d] + [a,b] = [a+c, b+c] = [a,b] + [c,d]
MPInterval operator+ (const Interval &op1, const MPInterval &op2) {
	return op2 + op1;
}

// c - [a,b] = [c-b, c-a]
MPInterval operator- (double op1, const MPInterval &op2) {
	MPInterval rop;
	mpfr_d_sub (rop.a, op1, op2.b, MPFR_RNDD);
	mpfr_d_sub (rop.b, op1, op2.a, MPFR_RNDU);
	return rop;
}

// c - [a,b] = [c-b, c-a]
MPInterval operator- (const mpfr_t op1, const MPInterval &op2) {
	MPInterval rop;
	mpfr_sub (rop.a, op1, op2.b, MPFR_RNDD);
	mpfr_sub (rop.b, op1, op2.a, MPFR_RNDU);
	return rop;
}

// [c,d]- [a,b] = [c-b, d-a]
MPInterval operator- (const Interval &op1, const MPInterval &op2) {
	MPInterval rop;
	mpfr_d_sub (rop.a, op1.a, op2.b, MPFR_RNDD);
	mpfr_d_sub (rop.b, op1.b, op2.a, MPFR_RNDU);
	return rop;
}

// c*[a,b] = [a,b]*c
MPInterval operator* (double op1, const MPInterval &op2) {
	return op2 * op1;
}

// c*[a,b] = [a,b]*c
MPInterval operator* (const mpfr_t op1, const MPInterval &op2) {
	return op2 * op1;
}
// [c,d] * [a,b] = [a,b] * [c,d]
MPInterval operator* (const Interval &op1, const MPInterval &op2) {
	return op2 * op1;
}


// c / [a,b] = [min (c/a, c/b), max (c/a, c/b)]
MPInterval operator/ (double op1, const MPInterval &op2) {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_d_div (rop.a, op1, op2.a, MPFR_RNDD);
	mpfr_d_div (aux, op1, op2.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_d_div (rop.b, op1, op2.a, MPFR_RNDU);
	mpfr_d_div (aux, op1, op2.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;
}

// c / [a,b] = [min (c/a, c/b), max (c/a, c/b)]
MPInterval operator/ (const mpfr_t op1, const MPInterval &op2) {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_div (rop.a, op1, op2.a, MPFR_RNDD);
	mpfr_div (aux, op1, op2.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_div (rop.b, op1, op2.a, MPFR_RNDU);
	mpfr_div (aux, op1, op2.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;
}

// [a,b]/[c,d] = [min(a/c,a/d,b/c,b/d), max(a/c,a/d,b/c,b/d)]
MPInterval operator/ (const Interval &op1, const MPInterval &op2) {
	mpfr_t aux;
	mpfr_init (aux);
	MPInterval rop;

	mpfr_d_div (rop.a, op1.a, op2.a, MPFR_RNDD);
	mpfr_d_div (aux, op1.a, op2.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_d_div (aux, op1.b, op2.a, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);
	mpfr_d_div (aux, op1.b, op2.b, MPFR_RNDD);
		mpfr_min (rop.a, rop.a, aux, MPFR_RNDD);


	mpfr_d_div (rop.b, op1.a, op2.a, MPFR_RNDU);
	mpfr_d_div (aux, op1.a, op2.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_d_div (aux, op1.b, op2.a, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);
	mpfr_d_div (aux, op1.b, op2.b, MPFR_RNDU);
		mpfr_max (rop.b, rop.b, aux, MPFR_RNDU);

	mpfr_clear (aux);
	return rop;

}
