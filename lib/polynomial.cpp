#include "polynomial.hpp"


unsigned int *_Polynomial::combinatorial;


void _Polynomial::startCombinatorialNumbers (int degree) {
    _Polynomial::combinatorial = new unsigned int [((degree+2)*(degree+1))/2];
    unsigned int *combinatorial = _Polynomial::combinatorial;
    unsigned int i;     // counter for m
    unsigned int j;         // counter for n

    for (i=0; i<=degree; i++) {
        combinatorial[(i*(i+1))/2] = combinatorial[(i*(i+3))/2] = 1;        // FIRST AND LAST = 1

        // THE REST IS COMPUTED FROM THE RECURRENCE OF COMBINATORIAL NUMBERS.
        for (j=1; j<i; j++)
            combinatorial[(i*(i+1))/2+j] = combinatorial[((i-1)*i)/2+j-1] + combinatorial[((i-1)*i)/2+j];
        combinatorial[((i+1)*(i+2))/2-1] = 1;
    }
}


template <>
IComplex Polynomial<IComplex>::evalIPolHornerXY (const IComplex &x, const IComplex &y) const {

    //evaluate polynomial as an element of K[x][y] in Horner form
    //that is, each coefficient of y is a polynomial on x
    int i; //i will represent the on x
    int j; //j will represent the degree on y
    int d = this->degree;
    IComplex coef;
    IComplex rop;
    rop = (this->coef)[(d+2)*(d+1)/2-1];
    for (j=d-1; j>=0; --j){
        coef = (this->coef)[d*(d+1)/2+j];
        for (i=d-1-j; i>=0; --i){
        	coef = x * coef + (this->coef)[(j+i)*(j+i+1)/2+j];
        }
        rop = rop * y + coef;
    }
    return rop;
}



template <>
IComplex Polynomial<IComplex>::evalIPolHornerYX (const IComplex &x, const IComplex &y) const {
    //evaluate polynomial as an element of K[y][x] in Horner form
    //that is, each coefficient of x is a polynomial on y
    int i; //i will represent the degree on x
    int j; //j will represent the on y
    int d = this->degree;
    IComplex coef;
    IComplex rop;
    rop = (this->coef)[(d)*(d+1)/2];
    for (i=d-1; i>=0; --i){
        coef = (this->coef)[d*(d+1)/2+d-i];
        for (j=d-i-1; j>=0; --j) {
        	coef = coef * y + (this->coef)[(i+j)*(i+j+1)/2+j];
        }
        rop = rop * x + coef;
    }

    return rop;
}

template <>
IComplex Polynomial<IComplex>::operator () (const IComplex &x, const IComplex &y) const{
    IComplex rop, ropx, ropy;

    ropx = this->evalIPolHornerXY (x, y);
    ropy = this->evalIPolHornerYX (x, y);
    rop  = this->evalPolClassic (x, y);


    rop.r.a = MAX(MAX(ropx.r.a, ropy.r.a), rop.r.a);
    rop.r.b = MIN(MIN(ropx.r.b, ropy.r.b), rop.r.b);
    rop.i.a = MAX(MAX(ropx.i.a, ropy.i.a), rop.i.a);
    rop.i.b = MIN(MIN(ropx.i.b, ropy.i.b), rop.i.b);

    return rop;
}



template <>
IComplex Polynomial<IComplex>::evalIPolYHornerXY (const IComplex &x, const IComplex &y) const {
    //evaluate polynomial as an element of K[x][y] in Horner form
    //that is, each coefficient of y is a polynomial on x
    int i; //i will represent the on x
    int j; //j will represent the degree on y
    int d = this->degree;
    IComplex coef;
    IComplex rop;
    rop = (d) * (this->coef)[(d+2)*(d+1)/2-1];

    for (j=d-2; j>=0; --j){
        coef = (this->coef)[d*(d+1)/2+j+1];
        for (i=d-1; i>=j+1; --i){
        	coef = x * coef + (this->coef)[(i*(i+1))/2+j+1];
        }
        rop = rop * y + (j+1.0) * coef;
    }
    return rop;

}

template <>
IComplex Polynomial<IComplex>::evalIPolYHornerYX (const IComplex &x, const IComplex &y) const {

    //evaluate polynomial as an element of K[x][y] in Horner form
    //that is, each coefficient of y is a polynomial on x
    int i; //i will represent the on x
    int j; //j will represent the degree on y
    int d = this->degree;
    IComplex coef;
    IComplex rop;
    rop = (this->coef)[(d)*(d+1)/2+1];

    for (i=d-2; i>=0; --i){
        coef = ((double) d-i)*(this->coef)[(d*(d+1))/2+d-i];
        for (j=d-1; j>=i+1; --j){
        	coef = y * coef + (j-i)*(this->coef)[(j*(j+1))/2+j-i];
        }
        rop = rop * x +  coef;
    }
    return rop;

}



template <>
IComplex Polynomial<IComplex>::diffY (const IComplex &x, const IComplex &y) const{
    IComplex rop, ropx, ropy;

    ropx = this->evalIPolYHornerXY (x, y);
    ropy = this->evalIPolYHornerYX (x, y);
    rop  = this->evalPolYClassic (x, y);


    rop.r.a = MAX(MAX(ropx.r.a, ropy.r.a), rop.r.a);
    rop.r.b = MIN(MIN(ropx.r.b, ropy.r.b), rop.r.b);
    rop.i.a = MAX(MAX(ropx.i.a, ropy.i.a), rop.i.a);
    rop.i.b = MIN(MIN(ropx.i.b, ropy.i.b), rop.i.b);

    return rop;
}



template <>
MPIComplex Polynomial<MPIComplex>::evalIPolHornerXY (const MPIComplex &x, const MPIComplex &y) const {

    //evaluate polynomial as an element of K[x][y] in Horner form
    //that is, each coefficient of y is a polynomial on x
    int i; //i will represent the on x
    int j; //j will represent the degree on y
    int d = this->degree;
    MPIComplex coef;
    MPIComplex rop;
    rop = (this->coef)[(d+2)*(d+1)/2-1];
    for (j=d-1; j>=0; --j){
        coef = (this->coef)[d*(d+1)/2+j];
        for (i=d-1-j; i>=0; --i){
        	coef = x * coef + (this->coef)[(j+i)*(j+i+1)/2+j];
        }
        rop = rop * y + coef;
    }
    return rop;
}



template <>
MPIComplex Polynomial<MPIComplex>::evalIPolHornerYX (const MPIComplex &x, const MPIComplex &y) const {
    //evaluate polynomial as an element of K[y][x] in Horner form
    //that is, each coefficient of x is a polynomial on y
    int i; //i will represent the degree on x
    int j; //j will represent the on y
    int d = this->degree;
    MPIComplex coef;
    MPIComplex rop;
    rop = (this->coef)[(d)*(d+1)/2];
    for (i=d-1; i>=0; --i){
        coef = (this->coef)[d*(d+1)/2+d-i];
        for (j=d-i-1; j>=0; --j) {
        	coef = coef * y + (this->coef)[(i+j)*(i+j+1)/2+j];
        }
        rop = rop * x + coef;
    }

    return rop;
}

template <>
MPIComplex Polynomial<MPIComplex>::operator () (const MPIComplex &x, const MPIComplex &y) const{
    MPIComplex rop, ropx, ropy;

    ropx = this->evalIPolHornerXY (x, y);
    ropy = this->evalIPolHornerYX (x, y);
    rop  = this->evalPolClassic (x, y);


    mpfr_max (rop.r.a, rop.r.a, ropx.r.a, MPFR_RNDD);
    	mpfr_max (rop.r.a, rop.r.a, ropy.r.a, MPFR_RNDD);
    mpfr_max (rop.i.a, rop.i.a, ropx.i.a, MPFR_RNDD);
    	mpfr_max (rop.i.a, rop.i.a, ropy.i.a, MPFR_RNDD);

    mpfr_min (rop.r.b, rop.r.b, ropx.r.b, MPFR_RNDU);
    	mpfr_min (rop.r.b, rop.r.b, ropy.r.b, MPFR_RNDU);
    mpfr_min (rop.i.b, rop.i.b, ropx.i.b, MPFR_RNDU);
    	mpfr_min (rop.i.b, rop.i.b, ropy.i.b, MPFR_RNDU);

    // rop.r.a = MAX(MAX(ropx.r.a, ropy.r.a), rop.r.a);
    // rop.r.b = MIN(MIN(ropx.r.b, ropy.r.b), rop.r.b);
    // rop.i.a = MAX(MAX(ropx.i.a, ropy.i.a), rop.i.a);
    // rop.i.b = MIN(MIN(ropx.i.b, ropy.i.b), rop.i.b);

    return rop;
}



template <>
MPIComplex Polynomial<MPIComplex>::evalIPolYHornerXY (const MPIComplex &x, const MPIComplex &y) const {
    //evaluate polynomial as an element of K[x][y] in Horner form
    //that is, each coefficient of y is a polynomial on x
    int i; //i will represent the on x
    int j; //j will represent the degree on y
    int d = this->degree;
    MPIComplex coef;
    MPIComplex rop;
    rop = (d) * (this->coef)[(d+2)*(d+1)/2-1];

    for (j=d-2; j>=0; --j){
        coef = (this->coef)[d*(d+1)/2+j+1];
        for (i=d-1; i>=j+1; --i){
        	coef = x * coef + (this->coef)[(i*(i+1))/2+j+1];
        }
        rop = rop * y + (j+1.0) * coef;
    }
    return rop;

}

template <>
MPIComplex Polynomial<MPIComplex>::evalIPolYHornerYX (const MPIComplex &x, const MPIComplex &y) const {

    //evaluate polynomial as an element of K[x][y] in Horner form
    //that is, each coefficient of y is a polynomial on x
    int i; //i will represent the on x
    int j; //j will represent the degree on y
    int d = this->degree;
    MPIComplex coef;
    MPIComplex rop;
    rop = (this->coef)[(d)*(d+1)/2+1];

    for (i=d-2; i>=0; --i){
        coef = ((double) d-i)*(this->coef)[(d*(d+1))/2+d-i];
        for (j=d-1; j>=i+1; --j){
        	coef = y * coef + (j-i)*(this->coef)[(j*(j+1))/2+j-i];
        }
        rop = rop * x +  coef;
    }
    return rop;

}



template <>
MPIComplex Polynomial<MPIComplex>::diffY (const MPIComplex &x, const MPIComplex &y) const{
    MPIComplex rop, ropx, ropy;

    ropx = this->evalIPolYHornerXY (x, y);
    ropy = this->evalIPolYHornerYX (x, y);
    rop  = this->evalPolYClassic (x, y);


    /*rop.r.a = MAX(MAX(ropx.r.a, ropy.r.a), rop.r.a);
    rop.r.b = MIN(MIN(ropx.r.b, ropy.r.b), rop.r.b);
    rop.i.a = MAX(MAX(ropx.i.a, ropy.i.a), rop.i.a);
    rop.i.b = MIN(MIN(ropx.i.b, ropy.i.b), rop.i.b);*/
    mpfr_max (rop.r.a, rop.r.a, ropx.r.a, MPFR_RNDD);
    	mpfr_max (rop.r.a, rop.r.a, ropy.r.a, MPFR_RNDD);
    mpfr_max (rop.i.a, rop.i.a, ropx.i.a, MPFR_RNDD);
    	mpfr_max (rop.i.a, rop.i.a, ropy.i.a, MPFR_RNDD);

    mpfr_min (rop.r.b, rop.r.b, ropx.r.b, MPFR_RNDU);
    	mpfr_min (rop.r.b, rop.r.b, ropy.r.b, MPFR_RNDU);
    mpfr_min (rop.i.b, rop.i.b, ropx.i.b, MPFR_RNDU);
    	mpfr_min (rop.i.b, rop.i.b, ropy.i.b, MPFR_RNDU);

    return rop;
}
