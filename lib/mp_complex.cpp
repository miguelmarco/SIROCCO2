#include "mp_complex.hpp"

MPComplex::MPComplex (double op) {
	mpfr_init (r);
	mpfr_set_d (r, op, MPFR_RNDN);
	mpfr_init_set_si (i, 0, MPFR_RNDN);
}
MPComplex::MPComplex (double op1, double op2) {
	mpfr_init_set_d (r, op1, MPFR_RNDN);
	mpfr_init_set_d (i, op2, MPFR_RNDN);
}
MPComplex::MPComplex (const std::complex<double> &op) {
	mpfr_init_set_d (r, op.real (), MPFR_RNDN);
	mpfr_init_set_d (i, op.imag (), MPFR_RNDN);
}
MPComplex::MPComplex (const mpfr_t op) {
	mpfr_init_set (r, op, MPFR_RNDN);
	mpfr_init_set_si (i, 0, MPFR_RNDN);
}
MPComplex::MPComplex (const mpfr_t op1, const mpfr_t op2) {
	mpfr_init_set (r, op1, MPFR_RNDN);
	mpfr_init_set (i, op2, MPFR_RNDN);
}
MPComplex::~MPComplex () {
	mpfr_clears (r, i, NULL);
}

	// ASSIGNMENT
MPComplex & MPComplex::operator= (double op) {
	mpfr_set_d (this->r, op, MPFR_RNDN);
	mpfr_set_si (this->i, 0, MPFR_RNDN);
	return (*this);
}
MPComplex & MPComplex::operator= (const std::complex<double> &op) {
	mpfr_set_d (this->r, op.real (), MPFR_RNDN);
	mpfr_set_d (this->i, op.imag (), MPFR_RNDN);
	return (*this);
}
MPComplex & MPComplex::operator= (const mpfr_t op) {
	mpfr_set (this->r, op, MPFR_RNDN);
	mpfr_set_si (this->i, 0, MPFR_RNDN);
	return (*this);
}
MPComplex & MPComplex::operator= (const MPComplex &op) {
	mpfr_set (this->r, op.r, MPFR_RNDN);
	mpfr_set (this->i, op.i, MPFR_RNDN);
	return (*this);
}

// COMPARISON

int MPComplex::operator == (double op) const {
	return (mpfr_cmp_d (this->r, op) == 0) && (mpfr_cmp_si (this->i, 0) == 0);
}
int MPComplex::operator == (const std::complex<double> &op) const {
	return (mpfr_cmp_d (this->r, op.real ()) == 0) && (mpfr_cmp_d (this->i, op.imag ()) == 0);
}
int MPComplex::operator == (const MPComplex &op) const {
	return (mpfr_cmp (this->r, op.r) == 0) && (mpfr_cmp (this->i, op.i) == 0);
}
int MPComplex::operator != (double op) const {
	return (mpfr_cmp_d (this->r, op) != 0) || (mpfr_cmp_si (this->i, 0) != 0);
}
int MPComplex::operator != (const std::complex<double> &op) const {
	return (mpfr_cmp_d (this->r, op.real ()) != 0) || (mpfr_cmp_d (this->i, op.imag ()) != 0);
}
int MPComplex::operator != (const MPComplex &op) const {
	return (mpfr_cmp (this->r, op.r) != 0) || (mpfr_cmp (this->i, op.i) != 0);
}

// ARITHMETIC
MPComplex MPComplex::operator+ (double op) const {
	MPComplex rop;
	mpfr_add_d (rop.r, this->r, op, MPFR_RNDN);
	mpfr_set (rop.i, this->i, MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator+ (const std::complex<double> &op) const {
	MPComplex rop;
	mpfr_add_d (rop.r, this->r, op.real (), MPFR_RNDN);
	mpfr_add_d (rop.i, this->i, op.imag (), MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator+ (const mpfr_t op) const {
	MPComplex rop;
	mpfr_add (rop.r, this->r, op, MPFR_RNDN);
	mpfr_set (rop.i, this->i, MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator+ (const MPComplex &op) const {
	MPComplex rop;
	mpfr_add (rop.r, this->r, op.r, MPFR_RNDN);
	mpfr_add (rop.i, this->i, op.i, MPFR_RNDN);
	return rop;
}

MPComplex MPComplex::operator- () const {
	MPComplex rop;
	mpfr_neg (rop.r, this->r, MPFR_RNDN);
	mpfr_neg (rop.i, this->i, MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator- (double op) const {
	MPComplex rop;
	mpfr_sub_d (rop.r, this->r, op, MPFR_RNDN);
	mpfr_set (rop.i, this->i, MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator- (const std::complex<double> &op) const {
	MPComplex rop;
	mpfr_sub_d (rop.r, this->r, op.real (), MPFR_RNDN);
	mpfr_sub_d (rop.i, this->i, op.imag (), MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator- (const mpfr_t op) const {
	MPComplex rop;
	mpfr_sub (rop.r, this->r, op, MPFR_RNDN);
	mpfr_set (rop.i, this->i, MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator- (const MPComplex &op) const {
	MPComplex rop;
	mpfr_sub (rop.r, this->r, op.r, MPFR_RNDN);
	mpfr_sub (rop.i, this->i, op.i, MPFR_RNDN);
	return rop;
}

MPComplex MPComplex::operator* (double op) const {
	MPComplex rop;
	mpfr_mul_d (rop.r, this->r, op, MPFR_RNDN);
	mpfr_mul_d (rop.i, this->i, op, MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator* (const std::complex<double> &op) const {
	MPComplex rop;
	mpfr_t aux; mpfr_init (aux);
	mpfr_mul_d (rop.r, this->r, op.real (), MPFR_RNDN);
	mpfr_mul_d (aux, this->i, op.imag (), MPFR_RNDN);
		mpfr_sub (rop.r, rop.r, aux, MPFR_RNDN);
	mpfr_mul_d (rop.i, this->r, op.imag (), MPFR_RNDN);
	mpfr_mul_d (aux, this->i, op.real (), MPFR_RNDN);
		mpfr_add (rop.i, rop.i, aux, MPFR_RNDN);

	mpfr_clear (aux);
	return rop;
}
MPComplex MPComplex::operator* (const mpfr_t op) const {
	MPComplex rop;
	mpfr_mul (rop.r, this->r, op, MPFR_RNDN);
	mpfr_mul (rop.i, this->i, op, MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator* (const MPComplex &op) const {
	MPComplex rop;
	mpfr_t aux; mpfr_init (aux);
	mpfr_mul (rop.r, this->r, op.r, MPFR_RNDN);
	mpfr_mul (aux, this->i, op.i, MPFR_RNDN);
		mpfr_sub (rop.r, rop.r, aux, MPFR_RNDN);
	mpfr_mul (rop.i, this->r, op.i, MPFR_RNDN);
	mpfr_mul (aux, this->i, op.r, MPFR_RNDN);
		mpfr_add (rop.i, rop.i, aux, MPFR_RNDN);

	mpfr_clear (aux);
	return rop;
}


MPComplex MPComplex::operator/ (double op) const {
	MPComplex rop;
	mpfr_div_d (rop.r, this->r, op, MPFR_RNDN);
	mpfr_div_d (rop.i, this->i, op, MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator/ (const std::complex<double> &op) const {
	MPComplex rop;
	mpfr_t aux; mpfr_init (aux);
	double factor = 1.0 / ((op.real() * op.real()) + (op.imag() * op.imag()));
	mpfr_mul_d (rop.r, this->r, op.real (), MPFR_RNDN);
	mpfr_mul_d (aux, this->i, op.imag (), MPFR_RNDN);
		mpfr_add (rop.r, rop.r, aux, MPFR_RNDN);
		mpfr_mul_d (rop.r, rop.r, factor, MPFR_RNDN);
	mpfr_mul_d (rop.i, this->i, op.real (), MPFR_RNDN);
	mpfr_mul_d (aux, this->r, op.imag (), MPFR_RNDN);
		mpfr_sub (rop.i, rop.i, aux, MPFR_RNDN);
		mpfr_mul_d (rop.i, rop.i, factor, MPFR_RNDN);
	mpfr_clear (aux);
	return rop;
}
MPComplex MPComplex::operator/ (const mpfr_t op) const {
	MPComplex rop;
	mpfr_div (rop.r, this->r, op, MPFR_RNDN);
	mpfr_div (rop.i, this->i, op, MPFR_RNDN);
	return rop;
}
MPComplex MPComplex::operator/ (const MPComplex &op) const {
	MPComplex rop;
	mpfr_t aux, factor; mpfr_inits (aux, factor, NULL);

	mpfr_mul (factor, op.r, op.r, MPFR_RNDN);
	mpfr_mul (aux, op.i, op.i, MPFR_RNDN);
	mpfr_add (factor, factor, aux, MPFR_RNDN);
	mpfr_si_div (factor, 1, factor, MPFR_RNDN);

	mpfr_mul (rop.r, this->r, op.r, MPFR_RNDN);
	mpfr_mul (aux, this->i, op.i, MPFR_RNDN);
		mpfr_add (rop.r, rop.r, aux, MPFR_RNDN);
		mpfr_mul (rop.r, rop.r, factor, MPFR_RNDN);
	mpfr_mul (rop.i, this->i, op.r, MPFR_RNDN);
	mpfr_mul (aux, this->r, op.i, MPFR_RNDN);
		mpfr_sub (rop.i, rop.i, aux, MPFR_RNDN);
		mpfr_mul (rop.i, rop.i, factor, MPFR_RNDN);

	mpfr_clears (aux, factor, NULL);
	return rop;
}

// NON MEMBER FUNCTIONS

std::ostream & operator<< (std::ostream &output, const MPComplex &op) {

	mpfr_exp_t exponent;
	char *string = mpfr_get_str (NULL, &exponent, 10, 0, op.r, MPFR_RNDD);
	if (mpfr_signbit (op.r) != 0)
		output << "-" << string[1] << "." << string+2 << "e" << exponent-1;
	else
		output << string[0] << "." << string+1 << "e" << exponent-1;
	mpfr_free_str (string);

	string = mpfr_get_str (NULL, &exponent, 10, 0, op.i, MPFR_RNDU);
	if (mpfr_signbit (op.i) != 0)
		output << "-" << string[1] << "." << string+2 << "e" << exponent-1 << "i";
	else
		output << "+" << string[0] << "." << string+1 << "e" << exponent-1 << "i";

	mpfr_free_str (string);
	return output;
}



MPComplex operator+ (double op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_add_d (rop.r, op2.r, op1, MPFR_RNDN);
	mpfr_set (rop.i, op2.i, MPFR_RNDN);
	return rop;

}
MPComplex operator+ (const std::complex<double> &op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_add_d (rop.r, op2.r, op1.real (), MPFR_RNDN);
	mpfr_add_d (rop.i, op2.i, op1.imag (), MPFR_RNDN);
	return rop;
}
MPComplex operator+ (const mpfr_t op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_add (rop.r, op2.r, op1, MPFR_RNDN);
	mpfr_set (rop.i, op2.i, MPFR_RNDN);
	return rop;
}


MPComplex operator- (double op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_d_sub (rop.r, op1, op2.r, MPFR_RNDN);
	mpfr_neg (rop.i, op2.i, MPFR_RNDN);
	return rop;

}
MPComplex operator- (const std::complex<double> &op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_d_sub (rop.r, op1.real (), op2.r, MPFR_RNDN);
	mpfr_d_sub (rop.i, op1.imag (), op2.i, MPFR_RNDN);
	return rop;
}
MPComplex operator- (const mpfr_t op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_sub (rop.r, op1, op2.r, MPFR_RNDN);
	mpfr_neg (rop.i, op2.i, MPFR_RNDN);
	return rop;
}





MPComplex operator* (double op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_mul_d (rop.r, op2.r, op1, MPFR_RNDN);
	mpfr_mul_d (rop.i, op2.i, op1, MPFR_RNDN);
	return rop;

}
MPComplex operator* (const std::complex<double> &op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_t aux; mpfr_init (aux);
	mpfr_mul_d (rop.r, op2.r, op1.real (), MPFR_RNDN);
	mpfr_mul_d (aux, op2.i, op1.imag (), MPFR_RNDN);
		mpfr_sub (rop.r, rop.r, aux, MPFR_RNDN);
	mpfr_mul_d (rop.i, op2.r, op1.imag (), MPFR_RNDN);
	mpfr_mul_d (aux, op2.r, op1.real (), MPFR_RNDN);
		mpfr_add (rop.i, rop.i, aux, MPFR_RNDN);

	mpfr_clear (aux);
	return rop;

}
MPComplex operator* (const mpfr_t op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_mul (rop.r, op2.r, op1, MPFR_RNDN);
	mpfr_mul (rop.i, op2.i, op1, MPFR_RNDN);
	return rop;

}



MPComplex operator/ (double op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_t factor;
	mpfr_init (factor);
	mpfr_mul (factor, op2.r, op2.r, MPFR_RNDN);
	mpfr_mul (rop.r, op2.i, op2.i, MPFR_RNDN);
		mpfr_add (factor, factor, rop.r, MPFR_RNDN);
		mpfr_si_div (factor, 1, factor, MPFR_RNDN);

	mpfr_mul_d (rop.r, op2.r, op1, MPFR_RNDN);
		mpfr_mul (rop.r, rop.r, factor, MPFR_RNDN);
	mpfr_mul_d (rop.i, op2.i, op1, MPFR_RNDN);
		mpfr_neg (rop.i, rop.i, MPFR_RNDN);
		mpfr_mul (rop.i, rop.i, factor, MPFR_RNDN);

	mpfr_clear (factor);
	return rop;

}
MPComplex operator/ (const std::complex<double> &op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_t factor, aux;
	mpfr_inits (factor, aux, NULL);
	mpfr_mul (factor, op2.r, op2.r, MPFR_RNDN);
	mpfr_mul (aux, op2.i, op2.i, MPFR_RNDN);
		mpfr_add (factor, factor, aux, MPFR_RNDN);
		mpfr_si_div (factor, 1, factor, MPFR_RNDN);

	mpfr_mul_d (rop.r, op2.r, op1.real (), MPFR_RNDN);
	mpfr_mul_d (aux, op2.i, op1.imag (), MPFR_RNDN);
	mpfr_add (rop.r, rop.r, aux, MPFR_RNDN);
		mpfr_mul (rop.r, rop.r, factor, MPFR_RNDN);
	mpfr_mul_d (rop.i, op2.r, op1.imag (), MPFR_RNDN);
	mpfr_mul_d (aux, op2.i, op1.real (), MPFR_RNDN);
	mpfr_sub (rop.i, rop.i, aux, MPFR_RNDN);
		mpfr_neg (rop.i, rop.i, MPFR_RNDN);
		mpfr_mul (rop.i, rop.i, factor, MPFR_RNDN);

	mpfr_clears (factor, aux, NULL);
	return rop;

}
MPComplex operator/ (const mpfr_t op1, const MPComplex &op2) {
	MPComplex rop;
	mpfr_t factor;
	mpfr_init (factor);
	mpfr_mul (factor, op2.r, op2.r, MPFR_RNDN);
	mpfr_mul (rop.r, op2.i, op2.i, MPFR_RNDN);
		mpfr_add (factor, factor, rop.r, MPFR_RNDN);
		mpfr_si_div (factor, 1, factor, MPFR_RNDN);

	mpfr_mul (rop.r, op2.r, op1, MPFR_RNDN);
		mpfr_mul (rop.r, rop.r, factor, MPFR_RNDN);
	mpfr_mul (rop.i, op2.i, op1, MPFR_RNDN);
		mpfr_neg (rop.i, rop.i, MPFR_RNDN);
		mpfr_mul (rop.i, rop.i, factor, MPFR_RNDN);

	mpfr_clear (factor);
	return rop;
}

void abs (mpfr_t rop, const MPComplex &op) {
	mpfr_t aux;
	mpfr_init (aux);
	mpfr_mul (rop, op.r, op.r, MPFR_RNDN);
	mpfr_mul (aux, op.i, op.i, MPFR_RNDN);
	mpfr_add (rop, rop, aux, MPFR_RNDN);
	mpfr_sqrt (rop, rop, MPFR_RNDN);


	mpfr_clear (aux);
	return;
}
