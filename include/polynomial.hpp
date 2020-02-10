#ifndef _POLYNOMIAL_HPP
#define _POLYNOMIAL_HPP


#include <iostream>
#include <complex>      // std::complex
#include <mp_complex.hpp>
#include <icomplex.hpp>
#include <mp_icomplex.hpp>


#define MIN(a,b) (((a) < (b))? (a) : (b))
#define MAX(a,b) (((a) > (b))? (a) : (b))

class _Polynomial {
public:
	_Polynomial() {}
	~_Polynomial() {}

	static unsigned int *combinatorial;
	static void startCombinatorialNumbers (int degree);
	static void releaseCombinatorialNumbers () {
		delete [] _Polynomial::combinatorial;
	}
};


template <class T>
class Polynomial : _Polynomial {
public:

	// CONSTRUCTOR
	Polynomial (int = 0);
	Polynomial (int, const T *);
	Polynomial (const Polynomial<T> &);
	~Polynomial () {delete [] coef;}

	// ASSIGNMENT
	Polynomial & operator= (const Polynomial<T> &);
	Polynomial & operator= (const T &);
	Polynomial & operator= (double);

	T operator() (const T &, const T &) const;
	T diffX (const T &, const T &) const;
	T diffY (const T &, const T &) const;
	T diffXX (const T &, const T &) const;
	T diffXY (const T &, const T &) const;
	T diffYY (const T &, const T &) const;


	// MISC FUNCTIONS FOR HORNER
	T evalPolClassic (const T &, const T &) const;
	T evalIPolHornerXY (const T &, const T &) const {return T();}
	T evalIPolHornerYX (const T &, const T &) const {return T();}

	T evalPolYClassic (const T &, const T &) const;
	T evalIPolYHornerXY (const T &, const T &) const {return T();}
	T evalIPolYHornerYX (const T &, const T &) const {return T();}


	// CHANGE OF VARIABLE
	Polynomial<T> IlinearVarChange (const T &a) const;
	Polynomial<T> IlinearVarChange2 (const T &x0) const;

	// MEMBERS
	T *coef;
	int degree;


};

template <class T>
std::ostream & operator<< (std::ostream &output, const Polynomial<T> &op) {
	int allZero = 1;
	for (int i=0; i<=op.degree; ++i)
		for (int j=0; j<=i; ++j) {
			if (op.coef[i*(i+1)/2 + j] == 0.0) continue;
			allZero = 0;
			if (op.coef[i*(i+1)/2 + j] == -1.0)
				output << "-";
			else if (op.coef[i*(i+1)/2 + j] != 1.0)
				output << "+(" << op.coef[i*(i+1)/2 + j] << ")*";
			else
				output << "+";
			if (i == 0)
				if (op.coef[0] == T(1))
					output << "1";
			if (i != 0) {
				if (i-j == 0) {
					if (j == 1)
						output << "y";
					else
						output << "y^" << j;
				} else if (i-j == 1) {
					if (j == 0)
						output << "x";
					else if (j == 1)
						output << "x*y";
					else
						output << "x*y^" << j;
				} else {
					if (j == 0)
						output << "x^" << i;
					else if (j == 1)
						output << "x^" << (i-j) << "*y";
					else
						output << "x^" << (i-j) << "*y^" << j;
				}
			}
		}
	if (allZero) output << "0";
	return output;
}

// CONSTRUCTOR

// DEFAULT CONSTRUCTOR FOR ZERO POLYNOMIAL
template <class T>
Polynomial<T>::Polynomial (int op) {
	degree = op;
	coef = new T [((op+1)*(op+2))/2];
	for (int i=0; i<((op+1)*(op+2))/2; ++i)
		coef[i] = 0.0;
}

// CONSTRUCTOR FROM ARRAY OF COMPLEX or ICOMPLEX
template <class T>
Polynomial<T>::Polynomial (int op1, const T *op2) {
	degree = op1;
	int nCoef = ((degree+1)*(degree+2)) / 2;
	coef = new T [nCoef];
	for (int i=0; i<nCoef; ++i)
		coef[i] = op2[i];

}

// COPY CONSTRUCTOR
template <class T>
Polynomial<T>::Polynomial (const Polynomial<T> &op) {
	degree = op.degree;
	int nCoef = ((degree+1)*(degree+2)) / 2;
	coef = new T [nCoef];
	for (int i=0; i<nCoef; ++i)
		coef[i] = op.coef[i];
}


// ASSIGNMENT
template <class T>
Polynomial<T> & Polynomial<T>::operator= (const Polynomial<T> &op) {
	// CHECKS WHETHER ASSIGNED POL IS TARGET POL
	if (this == &op) return (*this);

	// GETS FINAL NUMBER OF COEFICIENTS
	int nCoef = ((op.degree+1)*(op.degree+2)) / 2;
	// IF NUMBER OF COEFFICIENTS ARE THE SAME, NO NEED TO REALLOCATE
	if (this->degree != op.degree) {
		delete [] this->coef;
		this->coef = new T[nCoef];
		this->degree = op.degree;
	}

	// UPDATE VALUES OF COEFICIENTS
	for (int i=0; i<nCoef; ++i)
		this->coef[i] = op.coef[i];


	return (*this);

}

template <class T>
Polynomial<T> & Polynomial<T>::operator= (const T &op) {
	// CHECKS IF TARGET POL IS ALSO A CONSTANT POL
	// IN THAT CASE THERE IS NO NEED TO REALLOCATE MEMORY
	if (this->degree != 0) {
		delete [] this->coef;
		this->coef = new T[1];
		this->degree = 0;
	}

	// UPDATE INDEPENDENT TERM
	this->coef[0] = op;

	return (*this);
}

template <class T>
Polynomial<T> & Polynomial<T>::operator= (double op) {
	// USE PREVIOUS DEFINITION
	return ((*this) = T(op));
}




// EVALUATION


template <class T>
T Polynomial<T>::evalPolClassic (const T &x, const T &y) const {
		// coef[(i*(i+1))/2 + j] is coeficient of monomial of degree 'i',
	// with degree of second variable 'j' -> coef of x^(i-j) y^j
	// i;					// counter along degree of polynomial
	// j;					// counter for monomials of equal degree

	// sets output to 0+0i
	T rop;

    // compute all powers of x and y (from 0 to degree)
    T xPower[this->degree+1], yPower[this->degree+1];
    xPower[0] = yPower[0] = 1.0;
    xPower[1] = x; yPower[1] = y;
    for (int j=1; j<this->degree; ++j) {
        xPower[j+1] = xPower[j] * x;
        yPower[j+1] = yPower[j] * y;
    }

	// loop for each monomial of each degree
	for (int i=0; i<=this->degree; ++i)
	for (int j=0; j<=i; ++j)
		rop = rop +
			((this->coef)[(i*(i+1))/2 + j]) * xPower[i-j] * yPower[j];


	return rop;
}


template <class T>
T Polynomial<T>::operator() (const T &x, const T &y) const {
	return this->evalPolClassic (x,y);
}

// Defined in lib/polynomial.cpp
template <> IComplex Polynomial<IComplex>::operator() (const IComplex &x, const IComplex &y) const;
template <> MPIComplex Polynomial<MPIComplex>::operator () (const MPIComplex &x, const MPIComplex &y) const;

template <class T>
T Polynomial<T>::diffX (const T &x, const T &y) const {
		// coef[(i*(i+1))/2 + j] is coeficient of monomial of degree 'i',
	// with degree of second variable 'j' -> coef of x^(i-j) y^j
	// i;					// counter along degree of polynomial
	// j;					// counter for monomials of equal degree

	// sets output to 0+0i
	T rop;
    
    if (this->degree == 1){
    
        rop = (this->coef)[1];
        return rop;
    }

    // compute all powers of x and y
    // (from 0 to degree-1) (from 0 to degree) resp
    T xPower[this->degree], yPower[this->degree+1];
    xPower[0] = yPower[0] = 1.0;
    xPower[1] = x; yPower[1] = y;
    for (int j=1; j<this->degree-1; ++j) {
        xPower[j+1] = xPower[j] * x;
        yPower[j+1] = yPower[j] * y;
    }
    yPower[this->degree] = yPower[this->degree-1] * y;

	// loop for each monomial of each degree
	for (int i=1; i<=this->degree; ++i)
	for (int j=0; j<i; ++j)
		rop = rop +
			T(i-j)*((this->coef)[(i*(i+1))/2 + j]) *
			xPower[i-j-1] * yPower[j];

	return rop;

}

template <class T>
T Polynomial<T>::evalPolYClassic (const T &x, const T &y) const {
		// coef[(i*(i+1))/2 + j] is coeficient of monomial of degree 'i',
	// with degree of second variable 'j' -> coef of x^(i-j) y^j
	// i;					// counter along degree of polynomial
	// j;					// counter for monomials of equal degree

	// sets output to 0+0i
	T rop;
    
    if (this->degree == 1){
        rop = (this->coef)[2];
        return rop;
        
    }

    // compute all powers of x and y
    // (from 0 to degree) (from 0 to degree-1) resp
    T xPower[this->degree], yPower[this->degree];
    xPower[0] = yPower[0] = 1.0;
    xPower[1] = x; yPower[1] = y;
    for (int j=1; j<this->degree-1; ++j) {
        xPower[j+1] = xPower[j] * x;
        yPower[j+1] = yPower[j] * y;
    }

	// loop for each monomial of each degree
	for (int i=1; i<=this->degree; ++i)
	for (int j=1; j<=i; ++j)
		rop = rop +
			T(j)*((this->coef)[(i*(i+1))/2 + j]) *
			xPower[i-j] * yPower[j-1];

	return rop;

}


template <class T>
T Polynomial<T>::diffY (const T &x, const T &y) const {
	return this->evalPolYClassic (x,y);
}

// Defined in lib/polynomial.cpp
template <> IComplex Polynomial<IComplex>::diffY (const IComplex &x, const IComplex &y) const;
template <> MPIComplex Polynomial<MPIComplex>::diffY (const MPIComplex &x, const MPIComplex &y) const;


template <class T>
T Polynomial<T>::diffXX (const T &x, const T &y) const {
	// coef[(i*(i+1))/2 + j] is coeficient of monomial of degree 'i',
	// with degree of second variable 'j' -> coef of x^(i-j) y^j
	// i;					// counter along degree of polynomial
	// j;					// counter for monomials of equal degree

	// sets output to 0+0i
	T rop;
    
        if (this->degree == 1){
    
        return rop;
    }
    if (this->degree == 2)
    {
        rop = T(2)*(this->coef)[3];
        return rop;
    }

    // compute all powers of x and y
    // (from 0 to degree-2) (from 0 to degree-2) resp
    T xPower[this->degree-1], yPower[this->degree-1];
    xPower[0] = yPower[0] = 1.0;
    xPower[1] = x; yPower[1] = y;
    for (int j=1; j<this->degree-2; ++j) {
        xPower[j+1] = xPower[j] * x;
        yPower[j+1] = yPower[j] * y;
    }

	// loop for each monomial of each degree
	for (int i=2; i<=this->degree; ++i)
	for (int j=0; j<i-1; ++j)
		rop = rop +
			T(i-j)*(i-j-1.0)*((this->coef)[(i*(i+1))/2 + j]) *
			xPower[i-j-2] * yPower[j];

	return rop;

}

template <class T>
T Polynomial<T>::diffXY (const T &x, const T &y) const {
	// coef[(i*(i+1))/2 + j] is coeficient of monomial of degree 'i',
	// with degree of second variable 'j' -> coef of x^(i-j) y^j
	// i;					// counter along degree of polynomial
	// j;					// counter for monomials of equal degree

	// sets output to 0+0i
	T rop;
    
        if (this->degree == 1){
    
        return rop;
    }
    if (this->degree == 2)
    {
        rop = T(2)*(this->coef)[4];
        return rop;
    }
    

    // compute all powers of x and y
    // (from 0 to degree-2) (from 0 to degree-2) resp
    T xPower[this->degree-1], yPower[this->degree-1];
    xPower[0] = yPower[0] = 1.0;
    xPower[1] = x; yPower[1] = y;
    for (int j=1; j<this->degree-2; ++j) {
        xPower[j+1] = xPower[j] * x;
        yPower[j+1] = yPower[j] * y;
    }

	// loop for each monomial of each degree
	for (int i=2; i<=this->degree; ++i)
	for (int j=1; j<i; ++j)
		rop = rop +
			T(j)*T(i-j)*((this->coef)[(i*(i+1))/2 + j]) *
			xPower[i-j-1] * yPower[j-1];

	return rop;


}

template <class T>
T Polynomial<T>::diffYY (const T &x, const T &y) const {
	// coef[(i*(i+1))/2 + j] is coeficient of monomial of degree 'i',
	// with degree of second variable 'j' -> coef of x^(i-j) y^j
	// i;					// counter along degree of polynomial
	// j;					// counter for monomials of equal degree

	// sets output to 0+0i
	T rop;
    
    if (this->degree == 1){
    
        return rop;
    }
    if (this->degree == 2)
    {
        rop = T(2)*(this->coef)[5];
        return rop;
    }

    // compute all powers of x and y
    // (from 0 to degree-2) (from 0 to degree-2) resp
    T xPower[this->degree-1];
		T yPower[this->degree-1];
    xPower[0] = yPower[0] = 1.0;
    xPower[1] = x; yPower[1] = y;
    for (int j=1; j<this->degree-2; ++j) {
        xPower[j+1] = xPower[j] * x;
        yPower[j+1] = yPower[j] * y;
    }

	// loop for each monomial of each degree
	for (int i=2; i<=this->degree; ++i)
	for (int j=2; j<=i; ++j)
		rop = rop +
			T(j)*T(j-1)*((this->coef)[(i*(i+1))/2 + j]) *
			xPower[i-j] * yPower[j-2];

	return rop;
}




// CHANGE OF VARIABLE

// RETURNS q = p(x, y + ax);
// q = sum D(i,j)x^(i-j)y^j
template <class T>
Polynomial<T> Polynomial<T>::IlinearVarChange (const T &a) const {


    int i;					// counter for degree
    int j;					// counter for exponent of y
    int k;					// counter for elements modifying x^(i-j) y^j

    // for each degree i, only coefficients of monomials with j in {0, ..., i-1} are changed
    // for each j, only monomials with degree i and k in {j+1, ..., i} modify it
    // for each k, coef[(i*(i+1))/2+k] x^(i-k) (y+ax)^k
    // from binomial expansion, the term with x^(i-j) y^j has multiplier:
    // coef[(i*(i+1))/2+k] a^(k-j)  (k over j)
    T aPower[this->degree+1];
    aPower[0] = 1;
    aPower[1] = a;
    for (i=1; i<this->degree; ++i)
    	aPower[i+1] = aPower[i] * a;

    unsigned int *combinatorial = _Polynomial::combinatorial;

    Polynomial<T> rop(this->degree);

    // rop = sum_{i=0}^{degree} sum_{j=0}^{i} D(i,j)x^{i-j}y^j
    // D(i,j) = sum_{k=j}^{i} C(i,k)(k over j) a^{k-j}
    for (i=0; i<=this->degree; ++i) for (j=0; j<=i; ++j) {
    	rop.coef[(i*(i+1))/2 + j] = this->coef[(i*(i+1))/2 + j];
    	for (k=j+1; k<=i; ++k)
    		rop.coef[(i*(i+1))/2 + j] = rop.coef[(i*(i+1))/2 + j] +
    				combinatorial[(k*(k+1))/2+j] * aPower[k-j] * this->coef[(i*(i+1))/2+k];
    }

    return rop;

}
// RETURNS q = p(x+x0, y);
template <class T>
Polynomial<T> Polynomial<T>::IlinearVarChange2 (const T &x0) const {
    int i;					// counter for degree
    int j;					// counter for exponent of y
    int k;					// counter for elements modifying x^(i-j) y^j

    // for each degree i, only coefficients of monomials with j in {0, ..., i-1} are changed
    // for each j, only monomials with degree i and k in {j+1, ..., i} modify it
    // for each k, coef[(i*(i+1))/2+k] x^(i-k) (y+ax)^k
    // from binomial expansion, the term with x^(i-j) y^j has multiplier:
    // coef[(i*(i+1))/2+k] a^(k-j)  (k over j)
    T x0Power[this->degree+1];
    x0Power[0] = 1;
    x0Power[1] = x0;
    for (i=1; i<this->degree; ++i)
    	x0Power[i+1] = x0Power[i] * x0;

    unsigned int *combinatorial = _Polynomial::combinatorial;

    Polynomial<T> rop(this->degree);

    // rop = sum_{i=0}^{degree} sum_{j=0}^{i} D(i,j)x^{i-j}y^j
    // D(i,j) = sum_{k=i}^{degree} (k-j over i-j) C(k,j) x0^(k-i)
    for (i=0; i<=this->degree; ++i) for (j=0; j<=i; ++j) {
    	rop.coef[(i*(i+1))/2+j] = this->coef[(i*(i+1))/2+j];
    	for (k=i+1; k<=this->degree; ++k)
    		rop.coef[(i*(i+1))/2+j] = rop.coef[(i*(i+1))/2+j] +
    				combinatorial[((k-j)*(k-j+1))/2 + i-j] * this->coef[(k*(k+1))/2+j] * x0Power[k-i];
    }

    return rop;

}


#endif
