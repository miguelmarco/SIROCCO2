#include <stdio.h>
#include <sirocco.h>


int main(int argc, char const *argv[]) {
	mpfr_set_default_prec (162);


    double testCoefs[] = {
-2.000000000000000, -2.000000000000000, 0.000000000000000, 0.000000000000000,
0.000000000000000, 0.000000000000000, 0.000000000000000, -0.000000000000000,
0.000000000000, 0.000000000000, 0.0000000000000, 0.0000000000000,
1.000000000000000, 1.000000000000000, 0.000000000000000, -0.000000000000000,
0.00000000000000, 0.000000000000000, 0.000000000000000, 0.0000000000000000,
1.0000000000000, 1.000000000000000, 0.000000000000000, 0.0000000000000000
};




double testCoefsotcomp[] = {
    -2.100000000000, -2.10000000000000, 0.000000000000000, 0.000000000000000,
    0.0000000000000, 0.00000000000000, 0.000000000000000, -0.000000000000000,
    0.000000000000, 0.000000000000, 0.0000000000000, 0.0000000000000,
    1.000000000000000, 1.000000000000000, 0.000000000000000, -0.000000000000000,
    0.00000000000000, 0.000000000000000, 0.000000000000000, 0.0000000000000000,
    1.0000000000000, 1.000000000000000, 0.000000000000000, 0.0000000000000000
};



int compdegs[]={2};



   	double y0R = 1.414;
   	double y0I = 0.0;
   	double *rop = homotopyPath (2, testCoefs, y0R, y0I);

		int len = (int) rop[0];
		int i;

		delete [] rop;

    double *rop2 = homotopyPath_comps (2, testCoefs, y0R, y0I,1, compdegs, testCoefsotcomp);

    delete [] rop2;

		mpfr_t mp_testCoefs[24];
		for (int i=0; i<24; ++i) {
			mpfr_init_set_d (mp_testCoefs[i], testCoefs[i],
					(i%2)? MPFR_RNDU : MPFR_RNDD);
		}

		mpfr_t mp_othercompsCoefs[24];
        for (int i=0; i<24; ++i) {
            mpfr_init_set_d (mp_othercompsCoefs[i], testCoefsotcomp[i],
                             (i%2)? MPFR_RNDU : MPFR_RNDD);
        }


		mpfr_t mp_y0R, mp_y0I;
		mpfr_init_set_d (mp_y0R, y0R, MPFR_RNDN);
		mpfr_init_set_d (mp_y0I, y0I, MPFR_RNDN);

		mpfr_t *mp_rop = homotopyPath_mp (2, mp_testCoefs, mp_y0R, mp_y0I, 106);
        mpfr_t *mp_rop2 = homotopyPath_mp_comps (2, mp_testCoefs, mp_y0R, mp_y0I,102,1,compdegs, mp_othercompsCoefs);

		int size = mpfr_get_si (mp_rop[0], MPFR_RNDN);

		for (int i=0; i<3*size+1; ++i)
			mpfr_clear(mp_rop[i]);
		delete [] mp_rop;
        delete [] mp_rop2;


		for (int i=0; i<24; ++i) {
			mpfr_clear (mp_testCoefs[i]);
		}

		for (int i=0; i<24; ++i) {
            mpfr_clear (mp_othercompsCoefs[i]);
        }

		mpfr_clear (mp_y0R);
		mpfr_clear (mp_y0I);



	return 0;
}
