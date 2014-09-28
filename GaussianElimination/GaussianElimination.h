/*
	C X = Y
	C: Coefficient;
	Y: Yrhs;
	X: Xsolution;
	D: CDimension;

	LYC20140927
*/

#ifndef GAUSSIANELIMINATION_H_
#define GAUSSIANELIMINATION_H_

#include "stdio.h"
#include "stdlib.h"

#define MAXDIM 1024

void GaussianElimination(double *Coefficient, double *Yrhs, double *Xsolution, int CDimension);

void GaussianEliminationMAXDIM(double (*Coefficient)[MAXDIM], double *Yrhs, double *Xsolution, int CDimension);

#endif
