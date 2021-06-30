
#### magic comment that tells Cython to link to libsirocco.so
#clang C++
#clib sirocco

#include 'cysignals/signals.pxi'

from cysignals.signals cimport sig_on, sig_off
from cysignals.memory cimport check_allocarray, sig_free as free

from sage.libs.mpfr cimport *
from sage.rings.real_mpfr cimport RealNumber
from sage.rings.real_mpfr import RealField




cdef extern from "sirocco.h":
    mpfr_t* homotopyPath_mp (int degree, mpfr_t *_coef, mpfr_t _y0R, mpfr_t _y0I, int prec)
    mpfr_t* homotopyPath_mp_comps (int degree, mpfr_t *_coef, mpfr_t _y0R, mpfr_t _y0I, int prec, int nothercomps, int *degreescomps, mpfr_t *_coefscomps)
    double * homotopyPath (int degree, double *_coef, double _y0R, double _y0I)
    double * homotopyPath_comps (int degree, double *_coef, double _y0R, double _y0I, int nothercomps, int *degreescomps, double *_coefscomps)



def contpath_mp(deg, values, RealNumber y0r, RealNumber y0i, int prec):
    cdef int cdeg = deg
    cdef mpfr_t* cvalues = <mpfr_t*> check_allocarray(len(values), sizeof(mpfr_t))
    cdef mpfr_t* rop
    cdef int j
    for i in range(len(values)):
        j = <int>i
        sig_on()
        mpfr_init2(cvalues[j], prec)
        mpfr_set(cvalues[j], (<RealNumber>values[j]).value, MPFR_RNDN)
        sig_off()
    cdef mpfr_t y0R
    cdef mpfr_t y0I
    sig_on()
    mpfr_init2(y0R, prec)
    mpfr_set(y0R, (<RealNumber>y0r).value, MPFR_RNDN)
    mpfr_init2(y0I, prec)
    mpfr_set(y0I, (<RealNumber>y0i).value, MPFR_RNDN)
    rop = homotopyPath_mp(cdeg, cvalues, y0R, y0I, prec)
    sig_off()
    for i in range(len(values)):
        j = <int>i
        sig_on()
        mpfr_clear(cvalues[j])
        sig_off()
    free(cvalues)
    if rop == NULL:
        raise ValueError("libsirocco could not guarantee one step")
    cdef int n = mpfr_get_si(rop[0], MPFR_RNDN)

    #cdef RealNumber res = RealField(53)()
    cdef double res
    l = []

    for i in range(1, 3*n+1):
        RN = RealField(prec)()
        sig_on()
        res = mpfr_set((<RealNumber>RN).value, rop[i], MPFR_RNDN)
        mpfr_clear(rop[i])
        sig_off()
        l.append(RN)
    free(rop)
    return [(l[3*i], l[3*i+1], l[3*i+2]) for i in range(len(l)/3)]



def contpath_mp_comps(deg, values, RealNumber y0r, RealNumber y0i, int prec, otherdegrees, othercoefs):
    cdef int cdeg = deg
    cdef mpfr_t* cvalues = <mpfr_t*> check_allocarray(len(values),sizeof(mpfr_t))
    cdef mpfr_t* cothercoefs = <mpfr_t*> check_allocarray(len(othercoefs),sizeof(mpfr_t))
    cdef mpfr_t* rop
    cdef int j
    for i in range(len(values)):
        j = <int>i
        sig_on()
        mpfr_init2(cvalues[j], prec)
        mpfr_set(cvalues[j], (<RealNumber>values[j]).value, MPFR_RNDN)
        sig_off()

    for i in range(len(othercoefs)):
        j = <int>i
        sig_on()
        mpfr_init2(cothercoefs[j], prec)
        mpfr_set(cothercoefs[j], (<RealNumber>othercoefs[j]).value, MPFR_RNDN)
        sig_off()

    cdef int* c_otherdegrees = <int*> check_allocarray(len(otherdegrees),sizeof(int))
    for i in range(len(otherdegrees)):
        c_otherdegrees[i] = int(otherdegrees[i])

    cdef mpfr_t y0R
    cdef mpfr_t y0I
    sig_on()
    mpfr_init2(y0R, prec)
    mpfr_set(y0R, (<RealNumber>y0r).value, MPFR_RNDN)
    mpfr_init2(y0I, prec)
    mpfr_set(y0I, (<RealNumber>y0i).value, MPFR_RNDN)
    rop = homotopyPath_mp_comps(cdeg, cvalues, y0R, y0I, prec, int(len(otherdegrees)), c_otherdegrees, cothercoefs)
    sig_off()
    for i in range(len(values)):
        j = <int>i
        sig_on()
        mpfr_clear(cvalues[j])
        sig_off()

    for i in range(len(othercoefs)):
        j = <int>i
        sig_on()
        mpfr_clear(cothercoefs[j])
        sig_off()

    free(cvalues)
    free(cothercoefs)
    free(c_otherdegrees)
    if rop == NULL:
        raise ValueError("libsirocco could not guarantee one step")
    cdef int n = mpfr_get_si(rop[0], MPFR_RNDN)

    #cdef RealNumber res = RealField(53)()
    cdef double res
    l = []

    for i in range(1, 3*n+1):
        RN = RealField(prec)()
        sig_on()
        res = mpfr_set((<RealNumber>RN).value, rop[i], MPFR_RNDN)
        mpfr_clear(rop[i])
        sig_off()
        l.append(RN)
    free(rop)
    return [(l[3*i], l[3*i+1], l[3*i+2]) for i in range(len(l)/3)]




def contpath(deg,values,y0r,y0i):
    cdef double* rop
    cdef double* c_values = <double*> check_allocarray(len(values),sizeof(double))
    cdef int clen = <int> len(values)
    for i,v in enumerate(values):
        c_values[i] = values[i]

    cdef double y0R = y0r
    cdef double y0I = y0i
    sig_on()
    rop = homotopyPath (int(deg), c_values, y0R, y0I)
    sig_off()
    if rop == NULL:
        raise ValueError("libsirocco could not guarantee one step")
    n=int(rop[0])
    l=[0 for i in range(n)]
    for i in range(n):
        l[i]=(rop[3*i+1],rop[3*i+2],rop[3*i+3])
    free(rop)
    free(c_values)
    return l


def contpath_comps(deg, values, y0r, y0i, otherdegrees, othercomps):
    cdef double* rop
    cdef double* c_values = <double*> check_allocarray(len(values),sizeof(double))
    for i,v in enumerate(values):
        c_values[i] = values[i]

    cdef double* c_othercomps = <double*> check_allocarray(len(othercomps),sizeof(double))

    for i,v in enumerate(othercomps):
        c_othercomps[i] = othercomps[i]

    cdef int* c_otherdegrees = <int *> check_allocarray(len(otherdegrees),sizeof(int))

    for i,v in enumerate(otherdegrees):
        c_otherdegrees[i] = int(otherdegrees[i])

    cdef double y0R = y0r
    cdef double y0I = y0i
    sig_on()
    rop = homotopyPath_comps (int(deg), c_values, y0R, y0I, int(len(otherdegrees)), c_otherdegrees, c_othercomps)
    sig_off()
    if rop == NULL:
        raise ValueError("libsirocco could not guarantee one step")
    n=int(rop[0])
    l=[0 for i in range(n)]
    for i in range(n):
        l[i]=(rop[3*i+1],rop[3*i+2],rop[3*i+3])
    free(rop)
    free(c_values)
    free(c_othercomps)
    free(c_otherdegrees)
    return l
