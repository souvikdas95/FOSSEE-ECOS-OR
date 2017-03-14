# README #

### Compiling ###

The following command-line should be used to compile all the 3 files:
```
#!shell
cc -O2 -Wall -DCTRLC=1 -Wextra -fPIC  -DLDL_LONG -DDLONG -Iinclude -o <output> <input> libs/libecos.a -lm -lrt
```
where,
	<input> is the source file
	<output> is the compiled file

Note: Make sure to execute the command from base directory of cloned repository or set the path manually for required libraries and header files.

### Report ###

**Q1** *(Replica of RUNECOS compiled manually)*
```
#!shell
$./Q1
ECOS 2.0.4 - (C) embotech GmbH, Zurich Switzerland, 2012-15. Web: www.embotech.com/ECOS

It     pcost       dcost      gap   pres   dres    k/t    mu     step   sigma     IR    |   BT
 0  +5.230e-01  +5.230e-01  +4e+02  9e-01  4e-01  1e+00  2e+00    ---    ---    1  1  - |  -  - 
 1  +1.527e+00  +2.220e+00  +1e+02  1e-01  8e-02  9e-01  6e-01  0.8028  1e-01   1  1  2 |  0  0
 2  +5.637e-01  +8.452e-01  +6e+01  4e-02  4e-02  4e-01  3e-01  0.7541  3e-01   2  2  2 |  0  0
 3  +5.296e-01  +7.411e-01  +5e+01  4e-02  4e-02  3e-01  2e-01  0.3012  4e-01   2  2  2 |  0  0
 4  +1.551e-01  +1.644e-01  +4e+00  3e-03  3e-03  2e-02  2e-02  0.9490  4e-02   2  2  2 |  0  0
 5  +1.458e-01  +1.490e-01  +2e+00  2e-03  1e-03  6e-03  1e-02  0.6057  3e-01   2  2  1 |  0  0
 6  +1.707e-01  +1.714e-01  +8e-01  5e-04  4e-04  2e-03  4e-03  0.7514  1e-01   2  1  1 |  0  0
 7  +1.894e-01  +1.894e-01  +2e-01  1e-04  1e-04  3e-04  9e-04  0.9859  2e-01   2  1  2 |  0  0
 8  +1.926e-01  +1.926e-01  +4e-03  2e-06  2e-06  5e-06  2e-05  0.9827  1e-03   2  1  1 |  0  0
 9  +1.927e-01  +1.927e-01  +6e-05  4e-08  3e-08  8e-08  3e-07  0.9835  1e-04   2  1  1 |  0  0
10  +1.927e-01  +1.927e-01  +4e-06  2e-09  2e-09  5e-09  2e-08  0.9392  1e-03   2  1  1 |  0  0
11  +1.927e-01  +1.927e-01  +6e-08  4e-11  3e-11  8e-11  3e-10  0.9890  6e-03   2  1  1 |  0  0
12  +1.927e-01  +1.927e-01  +1e-09  7e-13  6e-13  1e-12  6e-12  0.9815  1e-04   2  1  1 |  0  0

OPTIMAL (within feastol=7.3e-13, reltol=5.9e-09, abstol=1.1e-09).
Runtime: 0.005330 seconds.
```

**Q2**
```
#!php
	minimize: x1 + 3 * x2 + 6 * x3 + 10 * x4 + ... + n*(n+1)/2 * xn
	subject to: x1 + x2 + ... + xn >= n/2
	x1 >= 0
	x2 >= 0
	...
	xn >= 0
```
```
#!shell
$./Q2
Enter a value of n = 10

ECOS 2.0.4 - (C) embotech GmbH, Zurich Switzerland, 2012-15. Web: www.embotech.com/ECOS

It     pcost       dcost      gap   pres   dres    k/t    mu     step   sigma     IR    |   BT
 0  +1.000e+02  +2.000e+02  +5e+02  4e-01  7e-01  1e+00  4e+01    ---    ---    1  1  - |  -  - 
 1  -2.342e-01  +2.442e+01  +7e+01  5e-02  1e-01  6e+00  7e+00  0.9802  2e-01   0  0  0 |  0  0
 2  +4.882e+00  +5.439e+00  +2e+00  1e-03  3e-03  1e-01  2e-01  0.9727  1e-03   0  0  0 |  0  0
 3  +4.997e+00  +5.004e+00  +3e-02  2e-05  4e-05  2e-03  3e-03  0.9858  2e-04   0  0  0 |  0  0
 4  +5.000e+00  +5.000e+00  +3e-04  2e-07  5e-07  2e-05  3e-05  0.9890  1e-04   0  0  0 |  0  0
 5  +5.000e+00  +5.000e+00  +4e-06  2e-09  5e-09  2e-07  3e-07  0.9890  1e-04   1  0  0 |  0  0
 6  +5.000e+00  +5.000e+00  +4e-08  3e-11  6e-11  2e-09  4e-09  0.9890  1e-04   1  0  0 |  0  0

OPTIMAL (within feastol=5.7e-11, reltol=8.3e-09, abstol=4.2e-08).
Runtime: 0.000425 seconds.

Optimal Solution: for x0 = 5.000000, x1 = 0.000000, x2 = -0.000000, x3 = -0.000000, x4 = -0.000000, x5 = -0.000000, x6 = -0.000000, x7 = -0.000000, x8 = -0.000000, x9 = -0.000000, Z = 5.000000
Press any key to continue . . .
```

**Q3**
```
#!php
	minimize: c.x
	subject to: s <= Ax <= b
	l <= x <= u
	where A, b, c, l, s, u are given in a user specified input file.
	
	Input file content format:
	
	n, m
	c1, c2, ..., cn (without line breaks)
	s1, s2, ..., sm (without line breaks)
	b1, b2, ..., bm (without line breaks)
	l1, l2, ..., ln (without line breaks)
	u1, u2, ..., un (without line breaks)
	A11, A12, ..., A1n (without line breaks)
	A21, A22, ..., A2n (without line breaks)
	..., ..., ..., ...
	Am1, Am2, ..., Amn (without line breaks)

	sample.txt:

	3,5
	1.0, 3.0, -2.0
	0.0, 1.0, 0.0, 0.0, 0.0
	15.0, 18.0, 20.0, 10.0, 10.0
	-50.0, -50.0, -50.0
	50.0,  50.0,  50.0
	-1.0, 1.0, 1.0
	3.0,  1.0, 2.0
	1.0, 1.0, -1.0
	-1.0, 1.0, -1.0
	100.0, 2.0, -1.0
```
```
#!shell
$./Q3
Enter Input File: input/sample.txt

ECOS 2.0.4 - (C) embotech GmbH, Zurich Switzerland, 2012-15. Web: www.embotech.com/ECOS

It     pcost       dcost      gap   pres   dres    k/t    mu     step   sigma     IR    |   BT
 0  +1.743e+01  -1.215e+03  +1e+03  6e-03  3e-09  1e+00  7e+01    ---    ---    1  1  - |  -  - 
 1  +8.687e+00  -1.939e+02  +2e+02  1e-03  4e-08  6e-01  1e+01  0.8381  7e-03   0  0  0 |  0  0
 2  +1.441e+00  -1.226e+01  +1e+01  7e-05  5e-08  2e-01  9e-01  0.9438  1e-02   0  0  0 |  0  0
 3  +4.737e-01  -1.887e+00  +2e+00  1e-05  2e-08  3e-02  1e-01  0.8318  5e-03   0  0  0 |  0  0
 4  +3.890e-01  +6.674e-02  +3e-01  2e-06  5e-09  1e-02  2e-02  0.9269  7e-02   0  0  0 |  0  0
 5  +3.383e-01  +2.973e-01  +4e-02  2e-07  2e-09  2e-03  3e-03  0.8738  1e-03   0  0  0 |  0  0
 6  +3.339e-01  +3.312e-01  +3e-03  1e-08  1e-10  1e-04  2e-04  0.9660  3e-02   0  0  0 |  0  0
 7  +3.333e-01  +3.333e-01  +3e-05  2e-10  7e-12  1e-06  2e-06  0.9890  1e-04   0  0  0 |  0  0
 8  +3.333e-01  +3.333e-01  +3e-07  2e-12  1e-13  2e-08  2e-08  0.9890  1e-04   1  0  0 |  0  0
 9  +3.333e-01  +3.333e-01  +4e-09  2e-14  2e-15  2e-10  2e-10  0.9890  1e-04   1  0  0 |  0  0

OPTIMAL (within feastol=1.9e-14, reltol=1.1e-08, abstol=3.7e-09).
Runtime: 0.000598 seconds.

Solution is Optimal!
Optimal Solution: for x0 = -0.000000, x1 = 0.333333, x2 = 0.333333, Z = 0.333333
Press any key to continue . . .
```

### Annotations ###

1. x0, x1... x(n-1) ==> 'n' Primal Variables
2. Z ==> Objective Function

----------------

### What is this repository for? ###

* Quick summary:

	FOSSEE Project **Optimization Toolkit** *Intern Evaluation*

### How do I get set up? ###

* Requirements
	* CC/GCC Toolkit
	* ECOS header files & libraries

### Who do I talk to? ###

* Author: Souvik Das (souvikdas95@yahoo.co.in)