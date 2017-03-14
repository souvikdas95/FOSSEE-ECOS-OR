/*
	Q3
	
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
*/

#include <stdio.h>
#include <string.h>

#include "ecos.h"

int main()
{
	idxint i, j;
	
	// Retrieve File
	char szF[128];
	printf("Enter Input File: ");
	if (fgets(szF, sizeof(szF), stdin) == NULL)
	{
		printf("Invalid Input\n");
		getchar();
		return 0;
	}
	szF[strnlen(szF, sizeof(szF)) - 1] = '\0';
	FILE* f = fopen(szF, "r");
	if (f == NULL)
	{
		perror("File not found!\n");
		getchar();
		return 0;
	}

	// Read Line 1 ==> n, x
	idxint n, x;
	if (fscanf(f, "%ld,%ld", &n, &x) != 2) { printf("Invalid Input!\n"); getchar(); fclose(f); return 0; }
	// printf("n = %ld\nx = %ld\n", n, x);

	// Read Line 2 ==> c1, c2, ...cn
	pfloat* c = (pfloat*)malloc(sizeof(pfloat) * n);
	for (i = 0; i < n; ++i)
		if (fscanf(f, "%lf,", &(c[i])) != 1) { printf("Invalid Input!\n"); getchar(); fclose(f); return 0; }
	// for (i = 0; i < n; ++i)
	// 	printf("c%d = %lf\n", i, c[i]);

	// Read Line 3 ==> s1, s2, ...sm
	pfloat* s = (pfloat*)malloc(sizeof(pfloat) * x);
	for (i = 0; i < x; ++i)
		if (fscanf(f, "%lf,", &(s[i])) != 1) { printf("Invalid Input!\n"); getchar(); fclose(f); return 0; }
	// for (i = 0; i < x; ++i)
	// 	printf("s%d = %lf\n", i, s[i]);

	// Read Line 4 ==> b1, b2, ...bm
	pfloat* b = (pfloat*)malloc(sizeof(pfloat) * x);
	for (i = 0; i < x; ++i)
		if (fscanf(f, "%lf,", &(b[i])) != 1) { printf("Invalid Input!\n"); getchar(); fclose(f); return 0; }
	// for (i = 0; i < x; ++i)
	// 	printf("b%d = %lf\n", i, b[i]);

	// Read Line 5 ==> l1, b2, ...ln
	pfloat* l = (pfloat*)malloc(sizeof(pfloat) * n);
	for (i = 0; i < n; ++i)
		if (fscanf(f, "%lf,", &(l[i])) != 1) { printf("Invalid Input!\n"); getchar(); fclose(f); return 0; }
	// for (i = 0; i < n; ++i)
	// 	printf("l%d = %lf\n", i, l[i]);

	// Read Line 6 ==> u1, u2, ...un
	pfloat* u = (pfloat*)malloc(sizeof(pfloat) * n);
	for (i = 0; i < n; ++i)
		if (fscanf(f, "%lf,", &(u[i])) != 1) { printf("Invalid Input!\n"); getchar(); fclose(f); return 0; }
	// for (i = 0; i < n; ++i)
	// 	printf("u%d = %lf\n", i, u[i]);

	// Read x Lines ==> A1<n>, A2<n>, ...Ax<n>
	pfloat **A = (pfloat**)malloc(sizeof(pfloat*) * x);
	for (i = 0; i < x; ++i)
	{
		A[i] = (pfloat*)malloc(sizeof(pfloat) * n);
		for (j = 0; j < n; ++j)
		{
			if (fscanf(f, "%lf,", &(A[i][j])) != 1) { printf("Invalid Input!\n"); getchar(); fclose(f); return 0; }
			// printf("A[%d][%d] = %lf,", i, j, A[i][j]);
		}
		// printf("\n");
	}
	fclose(f);

	// Setup
	idxint _n = n;
	idxint _m = 2 * x + 2 * n;
	idxint _p = 0;
	idxint _l = _m;

	idxint _ncones = 0;
	idxint* _q = NULL;
	idxint _e = 0;

	pfloat* _Gpr = (pfloat*)malloc(sizeof(pfloat) * (_n * _m));
	idxint* _Gjc = (idxint*)malloc(sizeof(idxint) * (_n + 1));
	idxint* _Gir = (idxint*)malloc(sizeof(idxint) * (_n * _m));
	int k1 = 0, k2 = 0;
	_Gjc[0] = 0;
	for (i = 0; i < _n; ++i)
	{
		if (i > 0)
		{
			_Gjc[i] = _Gjc[i - 1] + k2;
			k2 = 0;
		}
		// corresponding to -Si
		for (j = 0; j < x; ++j)
		{
			if (-1 * A[j][i] != 0)
			{
				_Gpr[k1] = -1 * A[j][i];
				_Gir[k1] = j;
				k1++;
				k2++;
			}
		}
		// corresponding to bi
		for (j = x; j < 2 * x; ++j)
		{
			if (A[j - x][i] != 0)
			{
				_Gpr[k1] = A[j - x][i];
				_Gir[k1] = j;
				k1++;
				k2++;
			}
		}
		// corresponding to -li
		_Gpr[k1] = -1;
		_Gir[k1] = 2 * x + i;
		k1++;
		k2++;
		// corresponding to ui
		_Gpr[k1] = 1;
		_Gir[k1] = 2 * x + n + i;
		k1++;
		k2++;
	}
	_Gjc[n] = _Gjc[n - 1] + k2;
	_Gpr = (pfloat*)realloc(_Gpr, sizeof(pfloat) * k1);	// Release remaining memory of _Gpr
	_Gir = (idxint*)realloc(_Gir, sizeof(idxint) * k1);	// Release remaining memory of _Gir
	// for (i = 0; i < k1; ++i)
	// 	printf("Gpr[%d] = %lf, Gir[%d] = %ld\n", i, _Gpr[i], i, _Gir[i]);
	// for (i = 0; i < n + 1; ++i)
	// 	printf("Gjc[%d] = %ld\n", i, _Gjc[i]);

	pfloat* _Apr = NULL;
	pfloat* _Ajc = NULL;
	pfloat* _Air = NULL;

	pfloat* _c = c;
	pfloat* _h = (pfloat*)malloc(sizeof(pfloat) * _m);
	for (i = 0; i < x; ++i) { _h[i] = -1 * s[i]; }
	for (i = x; i < 2 * x; ++i) { _h[i] = b[i - x]; }
	for (i = 2 * x; i < 2 * x + n; ++i) { _h[i] = -1 * l[i - 2 * x]; }
	for (i = 2 * x + n; i < _m; ++i) { _h[i] = u[i - (2 * x + n)]; }
	pfloat* _b = NULL;

	pwork* mywork = (pwork*)ECOS_setup((idxint)_n, (idxint)_m, (idxint)_p, (idxint)_l, (idxint)_ncones, (idxint*)_q, (idxint)_e,
		(pfloat*)_Gpr, (idxint*)_Gjc, (idxint*)_Gir,
		(pfloat*)_Apr, (idxint*)_Ajc, (idxint*)_Air,
		(pfloat*)_c, (pfloat*)_h, (pfloat*)_b);
	if (mywork == NULL)
	{
		printf("ECOS Setup Failed!\n");
		getchar();
		return 0;
	}

	// Solve
	idxint exitflag = ECOS_solve((pwork*)mywork);
	switch (exitflag)
	{
		case ECOS_OPTIMAL:		/* Problem solved to optimality              */
		{
			printf("Solution is Optimal!\n");
			pfloat cx = 0.0;
			printf("Optimal Solution: for ");
			for (int i = 0; i < mywork->n; ++i)
			{
				printf("x%d = %f, ", i, mywork->x[i]);
				cx += mywork->c[i] * mywork->x[i];
			}
			printf("Z = %f\n", cx);
		} break;
		case ECOS_PINF:			/* Found certificate of primal infeasibility */
		{
			printf("Solution is Primal Infeasible!\n");
		} break;
		case ECOS_DINF:			/* Found certificate of dual infeasibility   */
		{
			printf("Solution is Dual Infeasible!\n");
		} break;
		case ECOS_INACC_OFFSET:	/* Offset exitflag at inaccurate results     */
		{
			printf("Solution is Inaccurate!\n");
		} break;
		case ECOS_MAXIT:		/* Maximum number of iterations reached      */
		{
			printf("Solution has reached Maximum Iterations = %d!\n", MAXIT);
		} break;
		case ECOS_NUMERICS:		/* Search direction unreliable               */
		{
			printf("Solution is Direction Unreliable!\n");
		} break;
		case ECOS_OUTCONE:		/* s or z got outside the cone, numerics?    */
		{
			printf("Solution is outside the Cone / Numerics!\n");
		} break;
		case ECOS_SIGINT:		/* solver interrupted by a signal/ctrl-c     */
		{
			printf("Solution is interrupted by Signal!\n");
		} break;
		case ECOS_FATAL:		/* Unknown problem in solver                 */
		{
			printf("Solver has a Problem!\n");
		} break;
		default:
		{
			printf("Failed to get solution!\n");
		}
	}

	// Cleanup
	ECOS_cleanup((pwork*)mywork, (idxint)0);

	printf("Press any key to continue . . .\n");
	getchar();
	return 0;
}
