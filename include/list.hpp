#ifndef _LIST_HPP
#define _LIST_HPP

#include <mpfr.h>
#include <iostream>
#include <vector>


template <class T>
class Cell {
	T x[3];
	Cell () {}
	Cell (T data[3]) {}
	Cell (T x0, T y0R, T y0I) {}
	~Cell () {}
};

template <>
class Cell<double> {
public:
	double x[3];
	Cell () {}
	Cell (double data[3]) {x[0] = data[0]; x[1] = data[1], x[2] = data[2];}
	Cell (double x0, double y0R, double y0I) {x[0] = x0; x[1] = y0R; x[2] = y0I;}
	~Cell () {}
};
template <>
class Cell<mpfr_t> {
public:
	mpfr_t x[3];
	Cell () {}
	Cell (mpfr_t x0, mpfr_t y0R, mpfr_t y0I) {
		mpfr_inits (x[0], x[1], x[2], NULL);
		mpfr_set (x[0], x0, MPFR_RNDN);
		mpfr_set (x[1], y0R, MPFR_RNDN);
		mpfr_set (x[2], y0I, MPFR_RNDN);
	}

	Cell (const Cell<mpfr_t> &op) {
		mpfr_inits (x[0], x[1], x[2], NULL);
		mpfr_set (x[0], op.x[0], MPFR_RNDN);
		mpfr_set (x[1], op.x[1], MPFR_RNDN);
		mpfr_set (x[2], op.x[2], MPFR_RNDN);
    }

	~Cell () {
		mpfr_clears (x[0], x[1], x[2], NULL);
	}
};

std::ostream & operator<< (std::ostream &output, const Cell<double> &op) {
	output << op.x[0] << "  ";
	output << op.x[1] << "  ";
	output << op.x[2];

	return output;
}

std::ostream & operator<< (std::ostream &output, const Cell<mpfr_t> &op) {
	output << op.x[0] << "  ";
	output << op.x[1] << "  ";
	output << op.x[2];

	return output;
}

std::ostream & operator<< (std::ostream &output, const std::vector<Cell<double> > &op) {
	for (int i=0; i<op.size(); ++i)
		output << op[i];
	return output;
}

std::ostream & operator<< (std::ostream &output, const std::vector<Cell<mpfr_t> > &op) {
	for (int i=0; i<op.size(); ++i)
		output << op[i];
	return output;
}


#endif
