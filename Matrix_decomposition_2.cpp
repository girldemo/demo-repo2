//// Eigendecomposition and Diagonalization
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

// Tim ma tran nghich dao
void getCofactor(double[][10], double[][10], int, int, int);
double determinant(double[][10], int);
void adjoint(double[][10], double[][10], int);
bool inverse(double[][10], double[][10], int);
//

// EigenDecomposition
void MatrixInverse(double[][10], int); 
void EigenVV(double[][10], int);
//

int main()
{
	//int n;
	//cout << "Nhap n: ";
	//cin >> n;
	double A[10][10] = {{2, 0, 0},
					   {1, 2, -1},
					   {1, 3, -2}};
   	EigenVV(A, n);

	
    return 0;
}

// Tim ma tran nghich dao
void getCofactor(double A[10][10], double temp[10][10], int p, int q, int n)
{
	int i = 0, j = 0;

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q)
			{
				temp[i][j++] = A[row][col];
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}

double determinant(double A[10][10], int n)
{
	double D = 0; 

	if (n == 1)
		return A[0][0];

	double temp[10][10]; 
	double sign = 1; 

	for (int f = 0; f < n; f++)
	{
		getCofactor(A, temp, 0, f, n);
		D += sign * A[0][f] * determinant(temp, n - 1);
		sign = -sign;
	}
	return D;
}

void adjoint(double A[10][10], double adj[10][10], int n)
{
	if (n == 1)
	{
		adj[0][0] = 1;
		return;
	}

	double sign = 1, temp[10][10];

	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			getCofactor(A, temp, i, j, n);
			sign = ((i+j)%2==0)? 1: -1;
			adj[j][i] = (sign)*(determinant(temp, n-1));
		}
	}
}

bool inverse(double A[10][10], double inverse[10][10], int n)
{
	double det = determinant(A, n);	// tinh dinh thuc ma tran
	if (det == 0)
	{
		cout << "Singular matrix, can't find its inverse";
		return false;
	}

	double adj[10][10];
	adjoint(A, adj, n);	// Tim ma tran phu hop

	// Tim ma tran nghic dao theo cong thuc "inverse(A) = adj(A)/det(A)"
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			inverse[i][j] = adj[i][j]/det;

	return true;
}

// Tim gia tri rieng va vecto rieng ma tran nxn, ma tran nghich dao va in ra
void EigenVV(double A[][10], int n) 
{
	MatrixXd _Vec(n, n);
	MatrixXd _A(n, n);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			_A(i, j) = A[i][j];
	Eigen::EigenSolver<Eigen::Matrix3d> eigensolver(_A, true);

	cout << "A = PDP^-1" << endl;
	
	cout << "P = " << endl;
	cout << eigensolver.pseudoEigenvectors() << endl;
	
	cout << "D = " << endl;
	cout << eigensolver.pseudoEigenvalueMatrix() << endl;
	
	cout << "P^-1 = " << endl;
	//Tinh va in ma tran ngich dao
	_Vec = eigensolver.pseudoEigenvectors();
	double Vec[10][10];
	double Inver[10][10];
	
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			Vec[i][j] = _Vec(i, j);
	
	if (inverse(Vec, Inver, n) == true)
	{
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
			{
				cout << Inver[i][j] << " ";
				if (j == n-1) cout << endl;
			}
	}
	return;
}
