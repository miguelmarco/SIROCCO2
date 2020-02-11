
#include <stdio.h>
#include <vector>
#include <sirocco.hpp>
#include <list.hpp>

using namespace std;

// unsigned int *_Polynomial::combinatorial;



/******************************************
// f(z1,z2) = z1^3+2*z1*z2-3*z2-z1;
// COEFS = {{1,0,0,0}, {0,2,0}, {-1,3}, {0}}
// z1 = x + iy
// z2 = t(1+0.01i)
******************************************/

#ifndef __clang__
#pragma STDC FENV_ACCESS ON
#endif

// PERFORM A MINIMUM OF 5 ITERATIONS OF NEWTON METHOD TO CORRECT THE APPROXIMATION OF THE ROOT (SUPPOSED TO BE GOOD ENOUGH)
template <>
void correctRoot<Complex> (const Polynomial<Complex> f, const Complex &x0, Complex &y0) {
	Complex increment;
	int count = 0;
	double last_increment, new_increment;			// sizes of corrections
	new_increment = 9999.0;
	do {
		last_increment = new_increment;
		increment = f(x0,y0) / (f.diffY(x0,y0));
		new_increment = abs (increment);
		y0 = y0 - increment;
	  	++count;
	} while ((fabs(last_increment - new_increment)  > 1.0e-14 || count < 6 ) && count < 50);
	return;
}
template <>
void correctRoot<MPComplex> (const Polynomial<MPComplex> f, const MPComplex &x0, MPComplex &y0) {
	MPComplex increment;
	int count = 0;
	mpfr_t last_increment, new_increment, tol;			// sizes of corrections and tolerance
	mpfr_inits (last_increment, new_increment, tol, NULL);

	mpfr_set_d (tol, mpfr_get_default_prec(), MPFR_RNDN);
	mpfr_sub_si (tol, tol, 5, MPFR_RNDN);
	mpfr_neg (tol, tol, MPFR_RNDN);
	mpfr_exp2 (tol, tol, MPFR_RNDN);
	// std::cout << "tol = ";
	// mpfr_out_str (stdout, 10, 20, tol, MPFR_RNDN);
	// std::cout << std::endl;

	mpfr_set_d (new_increment, 9999.0, MPFR_RNDN);
	do {
		mpfr_set (last_increment, new_increment, MPFR_RNDN);
		increment = f(x0,y0) / (f.diffY(x0,y0));
		abs (new_increment, increment);
		y0 = y0 - increment;
	  	++count;

	  	// compute difference of increments and store in "last_increment"
	  	mpfr_sub (last_increment, last_increment, new_increment, MPFR_RNDN);
	  	mpfr_abs (last_increment, last_increment, MPFR_RNDN);
	} while ((mpfr_cmp (last_increment, tol) > 0 || count < 6 ) && count < 50);

	mpfr_clears (last_increment, new_increment, tol, NULL);
	return;
}

double * homotopyPath (int degree, double *_coef, double _y0R, double _y0I) {

	_Polynomial::startCombinatorialNumbers (degree);

// 	/************************************************/
// 	/* VARIABLE DECLARATION AND DATA INITIALIZATION */
// 	/************************************************/
	Complex aux;								// Complex aux variable.

	double stepsize = 0.0001;					// step size
	double eps;									// radius of the box


	int nCoef = ((degree+1)*(degree+2)) / 2;	// number of monomials
	Complex coef[nCoef];						// coefficient list for floating point representation of
												// the polynomial.
	IComplex Icoef[nCoef];	 					// coefficient list for Interval representation of
												// the polynomial.

	std::vector<Cell<double> > outputList;



 	// INITIALIZE COEFICIENT DATA FROM ARGUMENT INTO APPROPIATE DATA STRUCTURES
	for (int i=0; i<nCoef; ++i) {
		Icoef[i] = IComplex (_coef[4*i] ,_coef[4*i+1] ,_coef[4*i+2] ,_coef[4*i+3]);
		coef[i] = Complex ((_coef[4*i]  + _coef[4*i+1])/2.0 ,
						(_coef[4*i+2] + _coef[4*i+3])/2.0);
	}


	Polynomial<Complex> f (degree, coef);		// complex polynomials (with fp arithmetic)
												// to be used in Newton method correction
	Polynomial<IComplex> If (degree, Icoef);	// complex polynomials (with Interval arithmetic)
	Polynomial<IComplex> Ig (degree);			// to be used in validated homotopy
	Polynomial<IComplex> Ih (degree);



 	// INITIALIZE FLOATING POINT COMPLEX APPROXIMATION OF THE ROOT
	Complex x0 (0.0);							// x0 of the root (x0.imag = 0)
	Complex y0 (_y0R, _y0I);					// approximated y0 of the root
	IComplex Ix0;								// Interval representation for x0
	IComplex Iy0;								// Interval representation for y0
	IComplex IY0;								// Interval enclosure for y0 for Newton Method
	IComplex Iy1, IY1;							// Interval representation of zeros for rotated polynomial
	IComplex Ix1;

	Complex a;									// y'(x0) as Complex
	IComplex Ia;								// y'(x0) as IComplex


#ifdef PROFILING
	int nsteps = 0;								// number of steps performed
	int nrejectedEps = 0;						// number of rejected validations of boxes
	int nrejectedSteps = 0;						// number of rejected validations of tubes
#endif



	outputList.push_back (Cell<double> (0.0, y0.real (), y0.imag ()));

	/*******************/
	/* CORRECT ROOT	   */
	/*******************/


	correctRoot<Complex> (f, x0, y0);


	/*******************/
	/** MAIN LOOP	   */
	/*******************/
	while (x0.real () < 1.0) {

#ifdef PROFILING
	nsteps++; // used for profiling only
#endif

		/***********************************************************/
		/*** BOX SIZE ESTIMATION. F RESTRICTED TO X0 IS INJECTIVE. */
		/***********************************************************/
		aux = f.diffYY (x0, y0);
		if (abs (aux) < 1.0e-10) {
			eps = 0.5;
		} else {
			eps = (abs (f.diffY(x0,y0) / aux)) / 8.0;
		}

		eps /= 2.0;
		// cout << "estima eps = " << eps << endl;

		/**************************/
		/*** VALIDATE y0 AS POINT.*/
		/**************************/
		Ix0 = x0;
		Iy0 = y0;
		IY0 = y0 + IComplex (-eps, eps, -eps, eps);


		while (!validate<IComplex> (If, Ix0, Iy0, IY0)) {
#ifdef PROFILING
	nrejectedEps++; // used for profiling
#endif
			if (eps < 1.0e-13) {
				printf ("Singularity detected. Abort Sirocco\n");
				/*******************/
				/* CLEAN VARIABLES */
				/*******************/

				_Polynomial::releaseCombinatorialNumbers ();
				return NULL;
            }
			eps *= 0.5;
			IY0 = Iy0;
			IY0 = y0 + IComplex (-eps, eps, -eps, eps);
		}
		// cout << "acepta eps = " << eps << endl;

		// COMPUTE a = -fx(x0,y0) / fy(x0.y0)
		// both fp and Interval
		a = getA<Complex> (f, x0, y0);
		Ia = a;


		/************************/
		/* ESTIMATE STEP SIZE ***/
		/************************/
		// we have: aux = fyy
		// store all in aux2

		aux = a*a*aux + 2.0*a*f.diffXY(x0,y0) + f.diffXX (x0, y0);

		// DETECT INFLEXION POINT
		if (abs(aux) < 1.0e-10)
			stepsize=1.0;
		else
			stepsize = sqrt(abs((eps * f.diffY (x0, y0) )/ aux));
		if (stepsize + x0.real () > 1.0) stepsize = 1.000001 - x0.real ();


		/*******************/
		/** VALIDATE STEP  */
		/*******************/
		Ix1 = Interval(0,stepsize);


		// PERFORM TRANSLATION AND ROTATION OF THE POLYNOMIAL
		Ig = If.IlinearVarChange2 (Ix0);
		Ih = Ig.IlinearVarChange (Ia);


		while (!validate<IComplex> (Ih, Ix1, Iy0, IY0)) {
#ifdef PROFILING
	nrejectedSteps++; // used for profiling
#endif
			stepsize *= 0.5;
			eps*=0.95;
			IY0 = y0 + IComplex (-eps, eps, -eps, eps);
			Ix1 = Interval (0, stepsize);

			if (stepsize < 1.0e-13) {
				/*******************/
				/* CLEAN VARIABLES */
				/*******************/
				_Polynomial::releaseCombinatorialNumbers ();
				return NULL;
            }

		}
#ifdef DEVELOPER
	std::cout << "x0 = " << x0.real () << " step = " << stepsize << std::endl;
#endif


// 		/**************************/
// 		/** VALIDATE FINAL STEP   */
// 		/**************************/
		if (x0.real () + stepsize > 1.0) {
			stepsize = 1.0 - x0.real ();
			Ix1.r.b = stepsize;

#ifdef DEVELOPER
	std::cout << "final step = " << stepsize << std::endl;
#endif

			while (!validate<IComplex> (Ih, Ix1, Iy0, IY0));
		}


// 		/********************/
// 		/* UPDATE VARIABLES */
// 		/********************/
		x0 = Complex (Ix0.r.a + stepsize, 0.0);
		y0 = Complex (y0.real () + Ia.r.a * stepsize,
					y0.imag () + Ia.i.a * stepsize);




// 		/*******************/
// 		/* CORRECT ROOT	   */
// 		/*******************/
		correctRoot<Complex> (f, x0, y0);

		/**********************************************/
		/* CHECK WE HAVE NOT JUMPED TO ANOTHER ROOT   */
		/**********************************************/
		if (!(IY0+Ia*stepsize).contains (y0)) {
			printf ("error! Jumped to other thread!\n");
			_Polynomial::releaseCombinatorialNumbers ();
			return NULL;
		}


		outputList.push_back (Cell<double> (x0.real (), y0.real (), y0.imag ()));

	}





	// 	/***********************************************/
	/* PREPARE OUTPUT AS A BINARY ARRAY OF DOUBLES */
	/***********************************************/

	double *rop = new double [((3 * outputList.size () + 1))];
	rop[0] = outputList.size ();
	for (int i=0; i<outputList.size (); i++) {
		rop[3*i+1] = outputList[i].x[0];
		rop[3*i+2] = outputList[i].x[1];
		rop[3*i+3] = outputList[i].x[2];
	}
	_Polynomial::releaseCombinatorialNumbers ();
	return rop;
}


mpfr_t * homotopyPath_mp (int degree, mpfr_t *_coef, mpfr_t _y0R, mpfr_t _y0I, int prec) {
    mpfr_prec_t oldprec = mpfr_get_default_prec();
    mpfr_set_default_prec(prec);

	_Polynomial::startCombinatorialNumbers (degree);

// // 	/************************************************/
// // 	/* VARIABLE DECLARATION AND DATA INITIALIZATION */
// // 	/************************************************/
	MPComplex aux;								// Complex aux variable.

	mpfr_t stepsize , eps, calc, tol;
	mpfr_inits (stepsize, eps, calc, tol, NULL); // step size and radius of the box
	mpfr_set_d (stepsize, 0.0001, MPFR_RNDN);
	mpfr_set_d (tol, mpfr_get_default_prec(), MPFR_RNDN);
	mpfr_sub_si (tol, tol, 10, MPFR_RNDN);
	mpfr_neg (tol, tol, MPFR_RNDN);
	mpfr_exp2 (tol, tol, MPFR_RNDN);


	int nCoef = ((degree+1)*(degree+2)) / 2;	// number of monomials
	MPComplex coef[nCoef];						// coefficient list for floating point representation of
												// the polynomial.
	MPIComplex Icoef[nCoef];	 					// coefficient list for Interval representation of
												// the polynomial.

	std::vector<Cell<mpfr_t> > outputList;



 // 	INITIALIZE COEFICIENT DATA FROM ARGUMENT INTO APPROPRIATE DATA STRUCTURES
	for (int i=0; i<nCoef; ++i) {
		Icoef[i] = MPIComplex (_coef[4*i] ,_coef[4*i+1] ,_coef[4*i+2] ,_coef[4*i+3]);
		coef[i] = 0.5*(MPComplex (_coef[4*i] , _coef[4*i+2]) +
							MPComplex (_coef[4*i+1] , _coef[4*i+3]));
	}


	Polynomial<MPComplex> f (degree, coef);		// complex polynomials (with fp arithmetic)
												// to be used in Newton method correction
	Polynomial<MPIComplex> If (degree, Icoef);	// complex polynomials (with Interval arithmetic)
	Polynomial<MPIComplex> Ig (degree);			// to be used in validated homotopy
	Polynomial<MPIComplex> Ih (degree);



//  	// INITIALIZE FLOATING POINT COMPLEX APPROXIMATION OF THE ROOT
	MPComplex x0 (0.0);							// x0 of the root (x0.imag = 0)
	MPComplex y0 (_y0R, _y0I);					// approximated y0 of the root
	MPIComplex Ix0;								// Interval representation for x0
	MPIComplex Iy0;								// Interval representation for y0
	MPIComplex IY0;								// Interval enclosure for y0 for Newton Method
	MPIComplex Iy1, IY1;							// Interval representation of zeros for rotated polynomial
	MPIComplex Ix1;

	MPComplex a;									// y'(x0) as Complex
	MPIComplex Ia;								// y'(x0) as MPIComplex


#ifdef PROFILING
	int nsteps = 0;								// number of steps performed
	int nrejectedEps = 0;						// number of rejected validations of boxes
	int nrejectedSteps = 0;						// number of rejected validations of tubes
#endif


	outputList.push_back (Cell<mpfr_t> (x0.r, y0.r, y0.i));

// 	/*******************/
// 	/* CORRECT ROOT	   */
// 	/*******************/


	correctRoot<MPComplex> (f, x0, y0);


// 	/*******************/
// 	/** MAIN LOOP	   */
// 	/*******************/
	while (mpfr_cmp_si(x0.r, 1.0) < 0) {

#ifdef PROFILING
	nsteps++; // used for profiling only
#endif

		/***********************************************************/
		/*** BOX SIZE ESTIMATION. F RESTRICTED TO X0 IS INJECTIVE. */
		/***********************************************************/
		aux = f.diffYY (x0, y0);
		abs (calc, aux);
		if (mpfr_cmp_d (calc, 1.0e-10) < 0) {
			mpfr_set_d (eps, 0.5, MPFR_RNDN);
		} else {
			abs (eps, (f.diffY(x0,y0) / aux));
			mpfr_div_si (eps, eps, 8, MPFR_RNDN);
		}

		/**************************/
		/*** VALIDATE y0 AS POINT.*/
		/**************************/
		Ix0 = x0;
		Iy0 = y0;
		IY0 = MPIComplex(y0) + eps*MPIComplex (-1.0, 1.0, -1.0, 1.0);


		while (!validate<MPIComplex> (If, Ix0, Iy0, IY0)) {
#ifdef PROFILING
	nrejectedEps++; // used for profiling
#endif
			if (mpfr_cmp (eps ,tol) < 0) {
				printf ("Singularity detected. Abort Sirocco\n");
				/*******************/
				/* CLEAN VARIABLES */
				/*******************/
				mpfr_clears (stepsize, eps, calc, tol, NULL);

                mpfr_set_default_prec(oldprec);

				_Polynomial::releaseCombinatorialNumbers ();
				return NULL;
            }
			mpfr_div_si (eps, eps, 2, MPFR_RNDN);
			IY0 = Iy0;
			IY0 = MPIComplex(y0) + eps*MPIComplex (-1.0, 1.0, -1.0, 1.0);
		}

		// COMPUTE a = -fx(x0,y0) / fy(x0.y0)
		// both fp and Interval
		a = getA<MPComplex> (f, x0, y0);
		Ia = a;


		/************************/
		/* ESTIMATE STEP SIZE ***/
		/************************/
		// we have: aux = fyy
		// store all in aux2

		aux = a*a*aux + 2.0*a*f.diffXY(x0,y0) + f.diffXX (x0, y0);

		// DETECT INFLEXION POINT
		abs (calc, aux);
		if (mpfr_cmp_d(calc, 1.0e-10) < 0) {
			mpfr_set_si (stepsize, 1, MPFR_RNDN);
		} else {
			abs (calc, (eps * f.diffY (x0, y0) )/ aux);
			mpfr_sqrt (stepsize, calc, MPFR_RNDN);
		}

		// if (stepsize + x0.real () > 1.0) stepsize = 1.000001 - x0.real ();
		mpfr_add (calc, x0.r, stepsize, MPFR_RNDU);
		if (mpfr_cmp_si (calc, 1) > 0) {
			mpfr_si_sub (stepsize, 1, x0.r, MPFR_RNDU);
		}


		/*******************/
		/** VALIDATE STEP  */
		/*******************/
		mpfr_set_si (calc, 0, MPFR_RNDN);
		Ix1 = MPInterval(calc,stepsize);


		// PERFORM TRANSLATION AND ROTATION OF THE POLYNOMIAL
		Ig = If.IlinearVarChange2 (Ix0);
		Ih = Ig.IlinearVarChange (Ia);


		while (!validate<MPIComplex> (Ih, Ix1, Iy0, IY0)) {
#ifdef PROFILING
	nrejectedSteps++; // used for profiling
#endif
			mpfr_div_si (stepsize, stepsize, 2, MPFR_RNDN);
			mpfr_mul_d (eps, eps, 0.95, MPFR_RNDN);

			IY0 = MPIComplex(y0) + eps*MPIComplex (-1.0, 1.0, -1.0, 1.0);
			Ix1 = MPInterval (calc, stepsize);

			if (mpfr_cmp_d (stepsize, 1.0e-13) < 0) {
				/*******************/
				/* CLEAN VARIABLES */
				/*******************/
				mpfr_clears (stepsize, eps, calc, tol, NULL);

                mpfr_set_default_prec(oldprec);
				_Polynomial::releaseCombinatorialNumbers ();
				return NULL;
            }

		}
#ifdef DEVELOPER
	std::cout << "x0 = " << x0.r << " step = " << stepsize << std::endl;
#endif

// // 		/********************/
// // 		/* UPDATE VARIABLES */
// // 		/********************/
		x0 = MPComplex (Ix0.r.a) + MPComplex (stepsize);
		y0 = y0 + stepsize*a;




// 		/*******************/
// 		/* CORRECT ROOT	   */
// 		/*******************/
		correctRoot<MPComplex> (f, x0, y0);

		/**********************************************/
		/* CHECK WE HAVE NOT JUMPED TO ANOTHER ROOT   */
		/**********************************************/
		if (!(MPIComplex(y0).subset (IY0+Ia*stepsize))) {
			mpfr_clears (stepsize, eps, calc, tol, NULL);
			printf ("error! Jumped to other thread!\n");
            mpfr_set_default_prec(oldprec);
			_Polynomial::releaseCombinatorialNumbers ();
			return NULL;
		}


		outputList.push_back (Cell<mpfr_t> (x0.r, y0.r, y0.i));

	}


	// 	/***********************************************/
	/* PREPARE OUTPUT AS A BINARY ARRAY OF DOUBLES */
	/***********************************************/

	mpfr_t *rop = new mpfr_t [((3 * outputList.size () + 1))];
    mpfr_init(rop[0]);
	mpfr_set_si(rop[0], outputList.size(), MPFR_RNDN);
	for (int i=0; i<outputList.size (); i++) {
        mpfr_init(rop[3*i+1]);
        mpfr_init(rop[3*i+2]);
        mpfr_init(rop[3*i+3]);
		mpfr_set(rop[3*i+1], outputList[i].x[0], MPFR_RNDN);
		mpfr_set(rop[3*i+2], outputList[i].x[1], MPFR_RNDN);
		mpfr_set(rop[3*i+3], outputList[i].x[2], MPFR_RNDN);
	}


mpfr_clears (stepsize, eps, calc, tol, NULL);

mpfr_set_default_prec(oldprec);
_Polynomial::releaseCombinatorialNumbers ();
return rop;
}
