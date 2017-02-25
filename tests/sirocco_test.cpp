#include <stdio.h>
#include <sirocco.hpp>



using namespace std;


std::ostream & operator<< (std::ostream &output, const std::complex<double> op) {
	if (op == 0.0)
		output << "0";
	else if (op.imag() > 0)
		if (op.real () != 0.0)
			output << op.real () << "+" << op.imag() << "i";
		else
			output << op.imag() << "i";
	else if (op.imag() == 0)
		output << op.real ();
	else
		if (op.real () != 0.0)
			output << op.real () << op.imag() << "i";
		else
			output << op.imag() << "i";
	return output;
}



int main(int argc, char const *argv[]) {
	mpfr_set_default_prec (162);


    double testCoefs[] = {0.000000000000000, -0.000000000000000, 0.000000000000000,
-0.000000000000000, 0.000000000000000, -0.000000000000000,
0.000000000000000, -0.000000000000000, -128.000000000000,
-128.000000000000, -96.0000000000000, -96.0000000000000,
0.000000000000000, -0.000000000000000, 0.000000000000000,
-0.000000000000000, 72.0000000000000, 72.0000000000000,
304.000000000000, 304.000000000000, 12.0000000000000,
12.0000000000000, 180.000000000000, 180.000000000000,
0.000000000000000, -0.000000000000000, 0.000000000000000,
-0.000000000000000, 90.0000000000000, 90.0000000000000,
-182.500000000000, -182.500000000000, 133.500000000000,
133.500000000000, -190.500000000000, -190.500000000000,
42.0000000000000, 42.0000000000000, -44.0000000000000,
-44.0000000000000, 0.000000000000000, -0.000000000000000,
0.000000000000000, -0.000000000000000, -40.2500000000000,
-40.2500000000000, 18.2500000000000, 18.2500000000000,
-72.0000000000000, -72.0000000000000, 21.0000000000000,
21.0000000000000, -38.5000000000000, -38.5000000000000,
5.50000000000000, 5.50000000000000, -6.00000000000000,
-6.00000000000000, -0.000000000000000, 0.000000000000000};

   	double y0R = 4.0;
   	double y0I = -4.0;
   	double *rop = homotopyPath (4, testCoefs, y0R, y0I);

		int len = (int) rop[0];
		int i;
 		for (i=0; i<len; ++i)
 		printf ("%.5e  %.5e  %.5e\n", rop[1+3*i], rop[2+3*i], rop[3+3*i]);

		delete [] rop;

		mpfr_t mp_testCoefs[60];
		for (int i=0; i<60; ++i) {
			mpfr_init_set_d (mp_testCoefs[i], testCoefs[i],
					(i%2)? MPFR_RNDU : MPFR_RNDD);
		}
		mpfr_t mp_y0R, mp_y0I;
		mpfr_init_set_d (mp_y0R, y0R, MPFR_RNDN);
		mpfr_init_set_d (mp_y0I, y0I, MPFR_RNDN);


		mpfr_t *mp_rop = homotopyPath_mp (4, mp_testCoefs, mp_y0R, mp_y0I, 5300);

		int size = mpfr_get_si (mp_rop[0], MPFR_RNDN);
     for (i=0; i<size; ++i)
         std::cout << MPComplex(mp_rop[1+3*i]) << ", " << MPComplex(mp_rop[2+3*i], mp_rop[3+3*i]) << std::endl;
		for (int i=0; i<3*size+1; ++i)
			mpfr_clear(mp_rop[i]);
		delete [] mp_rop;


		for (int i=0; i<60; ++i) {
			mpfr_clear (mp_testCoefs[i]);
		}

		mpfr_clear (mp_y0R);
		mpfr_clear (mp_y0I);



	return 0;
}
