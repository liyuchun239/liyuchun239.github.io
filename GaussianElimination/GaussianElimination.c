#include "GaussianElimination.h"

void GaussianElimination(double *Coefficient, double *Yrhs, double *Xsolution, int CDimension)
{
	int i, j, k;
	double CColumnTemp;
	double YTemp;
	double maxElement;
	int maxIndex;
	double ratio;
	double *CoeffCopy;
	double *YrhsCopy;

	//Copy (Coefficent, Yrhs) to (CoeffCopy, YrhsCopy), and the latter is working matrix.
	CoeffCopy = (double *)malloc(CDimension*CDimension*sizeof(double));
	if(CoeffCopy==NULL){
		puts("Memory allocation failed.");
		exit(EXIT_FAILURE);
	}
	YrhsCopy = (double *)malloc(CDimension*sizeof(double));
	if(YrhsCopy==NULL){
		puts("Memory allocation failed.");
		exit(EXIT_FAILURE);
	}
	for(i=0; i!=CDimension; ++i){
		for(j=0; j!=CDimension; ++j){
			*(CoeffCopy + CDimension*i + j) = *(Coefficient + CDimension*i + j);
		}
		*(YrhsCopy + i) = *(Yrhs + i);
	}

	//Gaussian Elimination with choosing column pivot clement. Take care of boundary condition.
	for(i=0; i!=CDimension-1; ++i){
		//Find the maximum element (maxElement)of the column, and its row(maxIndex) location.
		maxElement = *(CoeffCopy + i*CDimension + i);
		maxIndex = i;
		for(j=i+1; j!=CDimension; ++j){
			if(*(CoeffCopy + j*CDimension + i) > maxElement){
				maxElement = *(CoeffCopy + j*CDimension + i);
				maxIndex = j;
			}
		}
		//Exception
		if(maxElement==0){
			puts("These equations can not be solved by Gaussian Elimination.");
			exit(EXIT_FAILURE);
		}
		//Exchange the i-th and maxIndex-th row, including Y.
		//C exchange;
		for(j=i; j!=CDimension; ++j){
			CColumnTemp = *(CoeffCopy + i*CDimension + j);
			*(CoeffCopy + i*CDimension + j) = *(CoeffCopy + maxIndex*CDimension + j);
			*(CoeffCopy + maxIndex*CDimension + j) = CColumnTemp;
		}
		//Y exchange
		YTemp = *(YrhsCopy + i);
		*(YrhsCopy + i) = *(YrhsCopy + maxIndex);
		*(YrhsCopy + maxIndex) = YTemp;
		//Elimination, making elements under the i-th row be 0;
		for(j=i+1; j!=CDimension; ++j){
			ratio = (*(CoeffCopy + j*CDimension +i)) / maxElement;
			//C being modified correspondingly.
			for(k=i+1; k!=CDimension; ++k){
				*(CoeffCopy + j*CDimension + k) -=  ratio * (*(CoeffCopy + i*CDimension + k));
			}
			//Y being modified correspondingly.
			*(YrhsCopy + j) -= ratio * *(YrhsCopy + i);
			//Elements under the i-th row.
			*(CoeffCopy + j*CDimension +i) = 0;
		}
	}

/**/
	//Output the coefficients and yrhs after elimination.
	for(i=0; i!=CDimension; ++i){
		for(j=0; j!=CDimension; ++j){
			printf("%lf\t", *(CoeffCopy + i*CDimension + j));
		}
		printf("| %lf\n", *(YrhsCopy + i));
	}
	printf("\n");
/**/

	//Solve X by back substitution;
	*(Xsolution+CDimension-1) = *(YrhsCopy + CDimension-1) / *(CoeffCopy + (CDimension-1)*(CDimension+1));
	for(i=CDimension-2; -1!=i; --i){
		*(Xsolution + i) = *(YrhsCopy + i);
		for(j=CDimension-1; j!=i; --j){
			*(Xsolution + i) -= (*(CoeffCopy + i*CDimension + j)) * (*(Xsolution + j));
		}
		*(Xsolution + i) /= (*(CoeffCopy + i*CDimension + i));
	}

/**/
	//Output the solutions of X;
	printf("X= ");
	for(i=0; i!=CDimension; ++i){
		printf("%lf\t", *(Xsolution + i));
	}
	printf("\nDone.\n\n");
/**/

	free(CoeffCopy);
	free(YrhsCopy);

	return;
}

void GaussianEliminationMAXDIM(double (*Coefficient)[MAXDIM], double *Yrhs, double *Xsolution, int CDimension)
{
	int i, j;
	double *CoeffCopy;
	double *YrhsCopy;
	CoeffCopy = (double *)malloc(CDimension*CDimension*sizeof(double));
	if(CoeffCopy==NULL){
		puts("Memory allocation failed.");
		exit(EXIT_FAILURE);
	}
	YrhsCopy = (double *)malloc(CDimension*sizeof(double));
	if(YrhsCopy==NULL){
		puts("Memory allocation failed.");
		exit(EXIT_FAILURE);
	}
	for(i=0; i!=CDimension; ++i){
		for(j=0; j!=CDimension; ++j){
			*(CoeffCopy + CDimension*i + j) = Coefficient[i][j];
		}
		*(YrhsCopy + i) = *(Yrhs + i);
	}

	GaussianElimination(CoeffCopy, YrhsCopy, Xsolution, CDimension);

	free(CoeffCopy);
	free(YrhsCopy);

	return;

}
