/// SVD Decomposition
#include <iostream>
#include <Eigen/Dense>
#include <iomanip>
#include <cmath>
#define N 5
using namespace std;
using namespace Eigen;

// Quick Sort
void Swap(double*, double*);
int Partition(double[], int, int);
void QuickSort(double[], int, int);
//
void MulMatrix(double[][N], double[][N], double[][N], int, int, int); // Nhan hai ma tran (mxn)*(nxk)
void EigenMatrix(double[][N], double[][N], double[][N], int); // Tim vecto rieng va gt rieng
void SVD(double[][N], int, int); // Singular values decomposition

int main()
{
	cout << setprecision(5) << showpoint;
	double A[N][N] = {{7, -4, 1},
					  {-4, 9, 2},
					  {1, 2, 11}};
	cout << "A = " << endl;
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
		{
			cout << A[i][j] << " ";
			if (j==3-1) cout << endl;
		}
	SVD(A, 3, 3);
	return 0;
}

// QuickSort ----------------------------
void Swap(double* a, double* b)
{
	double t = *a;
	*a = *b;
	*b = t;
}
int Partition(double A[], int low, int high)
{
	double pivot = A[high]; 
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (A[j] > pivot)
		{
			i++;
			Swap(&A[i], &A[j]);
		}
	}
	Swap(&A[i + 1], &A[high]);
	return (i + 1);
}
void QuickSort(double A[], int low, int high)
{
	if (low < high)
	{
		int pi = Partition(A, low, high);
		QuickSort(A, low, pi - 1);
		QuickSort(A, pi + 1, high);
	}
}
//---------------------

void MulMatrix(double A[][N], double B[][N], double Mul[][N], int m, int n, int k)
{
	for (int i=0; i<m; i++)
		for (int j=0; j<k; j++)
		{
			Mul[i][j] = 0;
			for (int index=0; index<n; index++)	
				Mul[i][j] += A[i][index] * B[index][j];
		}
}

void EigenMatrix(double S[][N], double Sigma[][N], double V[][N], int n)
{
	MatrixXd _S(n, n), _Sigma(n, n), _V(n, n);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			_S(i, j) = S[i][j];
	EigenSolver<Matrix3d> eigensolver(_S, true);
	
	_Sigma = eigensolver.pseudoEigenvalueMatrix(); // ma tran mà duong cheo chinh la cac gt rieng
	double eValue[N];
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
		{
			if (i==j)
			{
				if (_Sigma(i, j) < 0.000005)
				{
					_Sigma(i, j) = 0;
				}
				if (_Sigma(i, j) < 0)  // Kiem tra gia tri rieng co am hay ko 
				{
					cout << "Co gia tri am nen khong the phan ra ma tran bang SVD" << endl;
					return;
				}
				eValue[i] = _Sigma(i, j);
			}
			
			Sigma[i][j] = _Sigma(i, j);
		}
	QuickSort(eValue, 0, n-1);	 // Sap xep gia tri rieng theo thu tu giam dan
	for (int i=0; i<n; i++)
		Sigma[i][i] = sqrt(eValue[i]); 	// Hoan thien ma tran Sigma

	_V = eigensolver.pseudoEigenvectors(); // Ma tran mà các cot la vecto rieng (truc giao)
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			V[i][j] = _V(i, j);  // Hoan thien ma tran V
}

void SVD(double A[][N], int m, int n) // A = U*Sigma*VT
{
	double At[N][N], S[N][N];
	
	for(int i=0; i<n; i++)			// Ma tran chuyen vi AT : nxm
		for(int j=0; j<m; j++)
			At[i][j] = A[j][i];
	
	MulMatrix(At, A, S, n, m, n);  // Tinh ma tran S = AT*A : nxn
	
	double Sigma[N][N], V[N][N];	// Tim gia tri rieng va vecto rieng -> bien doi thanh Sigma va V;
	EigenMatrix(S, Sigma, V, n);
	
	double U[N][N];		      // Tim ma tran U theo CT: u(i) = 1/sigma(i)*A*v(i)
	double u[m][N], v[n][N];
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
			v[j][0] = V[j][i];
		MulMatrix(A, v, u, m, n, 1);
		for (int j=0; j<m; j++)
			U[j][i] = u[j][0] / Sigma[i][i];  // Hoan thien ma tran U
	}
	
// In ra ma tran U, Sigma, VT
cout << "A = U*Sigma*VT" << endl;
cout << "U = " << endl;
for (int i=0; i<m; i++)
	for (int j=0; j<m; j++)
	{
		cout << U[i][j] << " ";
		if (j == m-1) cout << endl;
	}
cout << "Sigma = " << endl;
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
		{
			cout << Sigma[i][j] << " ";
			if (j == n-1) cout << endl;
		}
cout << "VT = " << endl;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
		{
			cout << V[j][i] << " ";
			if (j == n-1) cout << endl;
		}
}
