#include "GaussianElimination.h"

int main()
{
	double cff[] =
	{
		1,4,8,
		2,3,-7,
		4,1,5.3
	};

	double yrhs[] =
	{
		4.5, 3.6, 9.1
	};

	double xlhs[3] = {0};

	double cffmd[][MAXDIM] = {
		{1,4,8},
		{2,3,-7},
		{4,1,5.3}
	};


	GaussianElimination(cff, yrhs, xlhs, 3);

	GaussianEliminationMAXDIM(cffmd, yrhs, xlhs, 3);


	getchar();
	return 0;
}
