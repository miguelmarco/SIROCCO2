# Sirocco Is a ROot Certified COntinuator

## General description.

This is a library for computing homotopy continuation of a given root of one
dimensional sections of bivariate complex polynomials.
The output is a piecewise linear aproximation of the path followed by the root,
with the property that there is a tubular neighborhood, with square transversal
section, that contains the actual path, and there is a three times thicker tubular
neigborhood guaranted to contain no other root of the polynomial. This second
property ensures that the piecewise linear approximation computed from all roots
of a polynomial form a topologically correct deformation of the actual braid,
since the inner tubular neighborhoods cannot intersect.

The first version of the library was written in C, and provided only double
precission. This is the second version, rewritten in C++, and provides the
possibility of using arbitrary precission computations. Hence, it deppends on
the [MPFR](http://www.mpfr.org/) and [GMP](https://gmplib.org/) libraries.

## Authors:

 - Miguel Marco
 - Marcos Rodriguez

## Usage:

After installing the library, you can call it from any .cpp program by calling
the `homotopyPath` or `homotopyPath_mp` functions. In the file tests/sirocco_test.cpp
you can see a simple example

### Double precission:

The input of the homotopyPath function is the following:

- An integer representing the total degree of the polynomial
- A malloc'ed array of double precission floats. Each four consecutive entries
of this list represent a coefficient, in the form of a rectangular complex
interval. These four numbers represent the following:
    - the lower bound of the real part
    - the upper bound of the real part
    - the lower bound of the imaginary part
    - the upper bound of the imaginary part

  These coefficients are written in increasing deglex order. That is, the first
coefficients are the corresponding to the monomials $1, x, y, x^2, x y, y^2,
x^3, x^2 y, x y^2, y^3...$

- A double precission float corresponding to the real part of an approximate
solution y0
- A double precission float corresponding to the imaginary part of an
approximate solution y0

The use of complex intervals allows us to represent polynomials with non
rational coefficients (even transcendental): just give an interval that
contains it.

y0 must be an approximation of a simple root of the univariate polynomial
f(0,y).

For example, the input 1, [2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 3.2, 3.2, -4.5, -4.5,
0.7, 0.7], 6.1, -3.3 would represent the polynomial of degree 1 f(x,y)=(2) +
(3.2*i)*x + (-4.5 + 0.7)*y , and the approximate root y0= 6.1-3.3*i

The output is a malloc'ed array of double floats. The first entry represents
the number of points in the piecewise linear path. Then, each three entries
correspond to one of these points. The first entry of these triplets is the x
coordinate of the point (will be a real number between 0 and 1), the next two
are the real and imaginary parts of the y coordinate.

This path represents the movement of the root y0 of f(x,y) when x varies from 0
to 1. So for each t between 0 and 1, there is a value y_t which is the linear
interpolation of the returned values. The computation certifies that for each
t, there is a square neighborhood centered around y_t that contains one and
only one root of f(t,y). That is, there is a tube around the piecewise linear
path that contains the actual path followed by y0. Moreover, the corresponding
tubes of two different roots computed this way will not intersect.

Note that the method might fail if there is a singularity (i.e. a value xt for
which f(xt, y) has multiple roots). In that case, you will either get a NULL
value, or an infinite running time.

### Arbitrary precission

The input of the homotopyPath_mp function is the following:

- An integer representing the total degree of the polynomial
- A malloc'ed array of mpfr_t numbers. As before, each four entries
represent an (intervalar) coefficient of a polynomial, following
increasing deglex order.
- A mpfr_t number corresponding to the real part of an approximate
solution y0
- A mpfr_t number corresponding to the imaginary part of an
approximate solution y0
- An integer representing the precission to be used in the internal
computations (and the output).

The output is a malloc'ed array of mpfr_t numbers as before, being the first
equal to the length of the list of points.


### From [SageMath](https://www.sagemath.org)

If you have the library and headers installed correctly, you can call this
library from a [sagemath](https://www.sagemath.org) session. The relevant files
for that are `sage-sirocco_interface.pyx` and `ZVK.py`. The first one contains
the interface code, and the second one several functions to compute the
fundamental group of the complement of a curve in the complex plane, using this
library. Reffer to the comments in `ZVK.py` for a more detailed explanation of
the functions available there.

An example of session using this library can be the following

```
sage: load("sage-sirocco_interface.pyx")
Compiling ./sage-sirocco_interface.pyx...
sage: load("ZVK.py")
sage: R.<x,y>=QQ[]
sage: f = x^4*y - x^2*y - y^2 + y
sage: followstrand(f, 0, 2, 1)
[(0.0, 1.0, 0.0),
 (0.0625, 0.984619140625, 0.0),
 (0.12764635845490785, 0.9390733273680929, 0.0),
 (0.2052599190422273, 0.8598746563676689, 0.0),
 (0.2738388312761707, 0.7900196735949514, 0.0),
 (0.33595920835462223, 0.752354737862309, 0.0),
 (0.37742976502219505, 0.7548738424164684, 0.0),
 (0.41234462235565617, 0.7824404587459047, 0.0),
 (0.44384260852985935, 0.8329353859054077, 0.0),
 (0.4733854965730891, 0.907113389122892, 0.0),
 (0.5018340661499732, 1.0074037381755196, 0.0),
 (0.529765293818804, 1.137637068382814, 0.0),
 (0.557600298953678, 1.3030485992155871, 0.0),
 (0.5856659871973544, 1.5104164286992712, 0.0),
 (0.6142284603481915, 1.7682957386440397, 0.0),
 (0.6435127330480354, 2.0873408693121487, 0.0),
 (0.6737151554114301, 2.480720326965522, 0.0),
 (0.7050116648058133, 2.964637418672337, 0.0),
 (0.7375635167677792, 3.558975212506035, 0.0),
 (0.7715214229939402, 4.288090367126086, 0.0),
 (0.8070286452864655, 5.181786778567655, 0.0),
 (0.8442233838690689, 6.276507417916129, 0.0),
 (0.8832406761016618, 7.616791574925573, 0.0),
 (0.9242139476600717, 9.257055380403543, 0.0),
 (0.9672763120876258, 11.263766404273989, 0.0),
 (1.0, 13.0, 0.0)]
sage: fundamental_group(f)
Finitely presented group < x0, x1 | x1*x0*x1^-1*x0^-1 >
```

We can specify the precission as follows:
```
sage: load("sage-sirocco_interface.pyx")
Compiling ./sage-sirocco_interface.pyx...
sage: load("ZVK.py")
sage: R.<x,y>=QQ[]
sage: f = x^4*y - x^2*y - y^2 + y
sage: followstrand(f, 0, 2, 1, 64)
[(0.000000000000000000, 1.00000000000000000, 0.000000000000000000),
 (0.0883883476483184405, 0.969726562500000000, 0.000000000000000000),
 (0.184950730956687066, 0.881894561449717605, 0.000000000000000000),
 (0.283035462744631192, 0.782243124984969131, 0.000000000000000000),
 (0.364422453016160885, 0.750974369797796147, 0.000000000000000000),
 (0.416213471348053255, 0.787223765636793229, 0.000000000000000000),
 (0.460346631682259060, 0.870878660223339468, 0.000000000000000000),
 (0.501152408999113160, 1.00463624592918436, 0.000000000000000000),
 (0.540663152674931619, 1.19791775328661377, 0.000000000000000000),
 (0.580106072748739940, 1.46587204907629284, 0.000000000000000000),
 (0.620334416729080238, 1.83005958982634992, 0.000000000000000000),
 (0.662000357948364900, 2.31995360710040316, 0.000000000000000000),
 (0.705638358240579886, 2.97517476873941566, 0.000000000000000000),
 (0.751710669137123514, 3.84857061175344128, 0.000000000000000000),
 (0.800634597966427747, 5.01035622419154600, 0.000000000000000000),
 (0.852800145520231329, 6.55362960101237132, 0.000000000000000000),
 (0.908582197461905312, 8.60168840702565921, 0.000000000000000000),
 (0.968349464421671190, 11.3177184607822591, 0.000000000000000000),
 (1.00000000000000000, 13.0000000000000000, 0.000000000000000000)]
```

The command followstrand shows the path followed y the root y0=1 of f(x,y) when
x varies from 0 o 2. It accepts an optional argument called `prec`, for the precission
to use. By default it is set to 53 (and uses the double precission implementation). If
the computation fails, it falls back to a bigger precission until it succeeds).
The command fundamental_group uses this approach to
compute the braid monodromy associated to this polynomial, and then uses it to
get a presentation of the fundamental group of its complement, using Zariski-VanKampen method.

At some point we expect to have this included in SageMath as an optional (or
maybe even standard) package. When that happens, we will probably provide a
more natural interface for the fundamental group and/or braid monodromy
computation.

## Dependencies:

This library deppends on:

 - autotools/libtools/autoconf if you want to generate the configuration
scripts (only needed if you get the source code from a git repository)
 - /make/gcc for the build process with C++ support (you need them to build from
a source tarball)
 - standard c libraries (math, io and std)
 - mpfr
 - gmp


## Installation:

The following instructions install the library and header files in the standard
system locations. If you want to install it in a different location, you can pass
extra arguments to the configure script.

In particular, if you want to install it so it can be used from a SageMath install
you have to use

```
./configure --prefix=<sagedir>/local --libdir=<sagedir>/local/lib
```
where <sagedir> is the directory where SageMath is installed.


### From the git repository

You can get the git repository by running

```
git clone https://github.com/miguelmarco/SIROCCO2.git
```

And then cd in the directory and run

```
autoreconf --install
```

to create the configure script then from there you can continue as usual:

```
./configure
make
make install
```

This last line might require superuser privileges for writing in system folders

### From a tar.gz package

If you got a tarball produced by a `make dist`command, just unpack it and run

```
./configure
make
make install
```

as before.

## To do:

 - include an option for passing the factors of the polynomial, for the cases
where the original polynomial is reducible. This might speed up the computations

