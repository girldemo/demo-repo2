/// Matrix cholesky decomposition
#include <stdio.h>
#include <math.h>
int CheckMatrix(float[][3], int);
void Cholesky(float[][3], int);
int main()
{
	float A[3][3];
	int n, i, j;
	printf("Nhap n: ");
	scanf("%d",&n);	
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			scanf("%f",&A[i][j]);
	if (CheckMatrix(A, n) == 0)	printf("Khong thoa man dieu kien Cholsesky");
	else
	{
		Cholesky(A,n);
	}
	return 0;
}
int CheckMatrix(float A[][3], int n)
{
	int i, j;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			if (A[i][j] != A[j][i])	return 0; // kiem tra doi xung
	if (A[0][0] < 0) return 0;	 //kiem tra xac dinh duong
	if (n>=2)
	{
		float temp = A[1][1]*A[0][0] - A[1][0]*A[0][1];
		if (temp < 0) return 0; 
	}
	if (n>=3)
	{
		float temp = A[0][0]*A[1][1]*A[2][2]+A[0][1]*A[1][2]*A[2][0]+A[0][2]*A[1][0]*A[2][1]
				    -A[2][0]*A[1][1]*A[0][2]-A[2][1]*A[1][2]*A[0][0]-A[2][2]*A[1][0]*A[0][1];
		if (temp < 0) return 0;
	}
	return 1;
}
void Cholesky(float A[][3], int n)
{
	float L[n][n], LT[n][n];
	int i, j;
	L[0][0] = sqrt(A[0][0]);		//tinh ma tran L
	L[1][0] = A[1][0]/L[0][0];
	L[2][0] = A[2][0]/L[0][0];
	L[1][1] = sqrt((A[1][1] - pow(L[1][0],2)));
	L[2][1] = (A[2][1] - L[2][0]*L[1][0])/L[1][1];
	L[2][2] = sqrt(A[2][2] - (pow(L[2][0],2) + pow(L[2][1],2)));
	L[0][1] = L[0][2] = L[1][2] = 0;
	
	for (i=0; i<n; i++)
		for(j=0; j<n; j++)		//tinh ma tran chuyen vi LT
		{
			LT[i][j] = L[j][i];
		}
	
	for (i=0; i<n; i++)			//in ra ma tran L va LT
		for(j=0; j<n; j++)
		{
			printf("%.3f ",L[i][j]);
			if (j==n-1) printf("\n");
		}
	printf("\n");
	for (i=0; i<n; i++)
		for(j=0; j<n; j++)
		{
			printf("%.3f ",LT[i][j]);
			if (j==n-1) printf("\n");
		}
}
