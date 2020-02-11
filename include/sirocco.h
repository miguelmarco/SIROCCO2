#ifndef __SIROCCO_H__
#define __SIROCCO_H__

#include <fenv.h>
#include <mpfr.h>

// ACTIVATE ROUND MODE CONTROL
#ifndef __clang__
#pragma STDC FENV_ACCESS ON
#endif


double * homotopyPath (int degree, double *_coef, double _y0R, double _y0I);
mpfr_t * homotopyPath_mp (int degree, mpfr_t *_coef, mpfr_t _y0R, mpfr_t _y0I, int prec);

#endif
