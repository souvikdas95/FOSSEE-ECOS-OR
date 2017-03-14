/*
	Q2
	
	minimize: x1 + 3 * x2 + 6 * x3 + 10 * x4 + ... + n*(n+1)/2 * xn
	subject to: x1 + x2 + ... + xn >= n/2
	x1 >= 0
	x2 >= 0
	...
	xn >= 0
*/

#include <stdio.h>

#include "ecos.h"

int main()
{
	int i;
	
	// User input # Primal Variables
	idxint n;
	printf("Enter a value of n = ");
	if(scanf("%ld", &n) != 1)
	{
		printf("Invalid input!\n");
		getchar();
		return 0;
	}
	getchar();
	
	// # Non Equality/ Conic/ Relative Constraints
	idxint m = 1 + n;

	// # Equality Constraints
	idxint p = 0;
	
	// # Positive Orthant.
	idxint l = m;	// In LPP, l = m ?

	// # Second Order Cones
	idxint ncones = 0;	// Not using Conic Optimization

	// Array (size ncones) Second Order Cones
	idxint* q = NULL;	// Not using Conic Optimization

	// # Exponential Cones
	idxint e = 0;	// Not using Exponential Cones

	/*	Column Compressed Storage (CCS) data structure of Sparse Matrix G representing
		Co-efficients of Primal Variables in Non-Equality Constraints	*/
	
	// All Non-Zero Elements read Column-wise
	pfloat* Gpr = (pfloat*)malloc(sizeof(pfloat) * (2 * n));	// (1 in 1st Non-Equality Constraint + 1 for Non-Negativity Constraint) : each for n Primal Variables
	for (i = 0; i < 2 * n; ++i) { Gpr[i] = -1; }	// Convert Gteq to Lteq w/ all (Co-efficient = 1) * -1

	// Starting with 0, Cumulative count of # Non-Zero Elements per Column
	idxint* Gjc = (idxint*)malloc(sizeof(idxint) * (n + 1));	// With Gjc[0] always equal to 0, rest equals # Columns = # Primal Variables
	for (i = 0; i < n + 1; ++i) { Gjc[i] = i * 2; }	// Semantically same as 2 Non-Zero Elements per Column

	// Corresponds to Gpr, Indicates Row ID that the Non-Zero element belongs to
	idxint* Gir = (idxint*)malloc(sizeof(idxint) * (2 * n));	// Size is same as Gpr as it directly corresponds to it
	for (i = 0; i < n; ++i)	// Note: Traversal is Column-wise
	{
		Gir[2 * i] = 0;	// Indicate Row ID for Primary Non-Equality Constraint 
		Gir[2 * i + 1] = i + 1;	// Indicate Row ID for Non-Negative Constraint
	}

	/*	Column Compressed Storage (CCS) data structure of Sparse Matrix A representing
		Co-efficients of Primal Variables in Equality Constraints	*/

	// All Non-Zero Elements read Column-wise
	pfloat* Apr = NULL;	// No Equality Constraints

	// Starting with 0, Cumulative count of # Non-Zero Elements per Column
	pfloat* Ajc = NULL;	// No Equality Constraints

	// Corresponds to Apr, Indicates Row ID that the Non-Zero element belongs to
	pfloat* Air = NULL;	// No Equality Constraints

	// C Matrix representing Co-efficients of Primal Variables in Objective Function
	pfloat* c = (pfloat*)malloc(sizeof(pfloat) * n);	// each for n Primal Variables
	for (i = 1; i <= n; ++i) { c[i - 1] = (pfloat)i * (pfloat)(i + 1) / (pfloat)2; }	// Logic: (N * (N + 1)) / 2. Also, force Type Casting explicity.

	// H Matrix Representing RHS of each Non-Equality Constraints
	pfloat* h = (pfloat*)malloc(sizeof(pfloat) * m);	// each for m Non-Equality Constraints
	h[0] = (pfloat)-1 * (pfloat)n / (pfloat)2;	// As Given: (n/2) * -1 (to convert gteq to lteq)
	for (i = 1; i < m; ++i) { h[i] = 0; }	// Rest all RHS = 0 (Non-Negative Constraints)

	// H Matrix Representing RHS of each Equality Constraints
	pfloat* b = NULL;	// No Equality Constraints

	pwork* mywork = (pwork*)ECOS_setup((idxint)n, (idxint)m, (idxint)p, (idxint)l, (idxint)ncones, (idxint*)q, (idxint)e,
			(pfloat*)Gpr, (idxint*)Gjc, (idxint*)Gir,
			(pfloat*)Apr, (idxint*)Ajc, (idxint*)Air,
			(pfloat*)c, (pfloat*)h, (pfloat*)b);

	idxint exitflag = ECOS_solve((pwork*)mywork);

	pfloat cx = 0.0;
	if (exitflag == ECOS_OPTIMAL)
	{
		printf("Optimal Solution: for ");
		for (int i = 0; i < mywork->n; ++i)
		{
			printf("x%d = %f, ", i, mywork->x[i]);
			cx += mywork->c[i] * mywork->x[i];
		}
		printf("Z = %f\n", cx);
		// printf("cx = %f, best_cx = %f\n", mywork->cx, mywork->best_cx);
	}
	else
		printf("exitflag = %ld\n", exitflag);

	ECOS_cleanup((pwork*)mywork, (idxint)0);

	printf("Press any key to continue . . .\n");
	getchar();
	return 0;
}
