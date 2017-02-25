# Sirocco Is a ROot Certified COntinuator

## General description.

This is a library for computing homotopy continuation of a given root of one 
dimensional sections of bivariate complex polynomials. The output is a 
piecewise linear aproximation of the path followed by the root, with the 
property that there is a tubular neighborhood, with square transversal section, 
that contains the actual path, and there is a three times thicker tubular 
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
the homotopyPath or homotopyPath_mp functions. In the file test/test_example you can see a simple 
example
 
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
 (0.08838834764831845, 0.9697265625, 0.0),
 (0.18495073095668707, 0.8818945614497176, 0.0),
 (0.2830354627446311, 0.7822431249849692, 0.0),
 (0.36442245301616083, 0.7509743697977961, 0.0),
 (0.4162134713480532, 0.7872237656367932, 0.0),
 (0.460346631682259, 0.8708786602233393, 0.0),
 (0.5011524089991131, 1.0046362459291838, 0.0),
 (0.5406631526749315, 1.1979177532866128, 0.0),
 (0.5801060727487398, 1.465872049076292, 0.0),
 (0.6203344167290801, 1.830059589826348, 0.0),
 (0.6620003579483648, 2.319953607100401, 0.0),
 (0.7056383582405797, 2.975174768739414, 0.0),
 (0.7517106691371234, 3.848570611753438, 0.0),
 (0.8006345979664276, 5.010356224191542, 0.0),
 (0.8528001455202311, 6.553629601012362, 0.0),
 (0.908582197461905, 8.601688407025646, 0.0),
 (0.9683494644216709, 11.317718460782247, 0.0),
 (1.0, 13.0, 0.0)]
sage: fundamental_group(f)
Finitely presented group < x0, x1 | x1*x0*x1^-1*x0^-1 >
```

The command followstrand shows the path followed y the root y0=1 of f(x,y) when 
x varies from 0 o 2. It accepts an optional argument called `prec`, for the precission
to use. By default it is set to 53 (and uses the double precission implementation). If
the computation fails, it falls back to a bigger precission until it succeeds).
The command fundamental_group uses this approach to 
compute the braid monodromy associated to this polynomial, and then uses it to 
compute the fundamental group of its complement, using Zariski-VanKampen method.

At some point we expect to have this included in SageMath as an optional (or 
maybe even standard) package. When that happens, we will probably provide a 
more natural interface for the fundamental group and/or braid monodromy 
computation.

## Dependencies:

The deppendencies are:

 - autotools/libtools/autoconf if you want to generate the configuration 
scripts (only needed if you get the source code from a git repository)
 - /make/gcc for the build process (you need them to build from a source 
tarball)
 - standard c libraries (math, io and std)
 - mpfr
 - gmp
 
 
## Installation:

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
 
