#include <stdio.h>

int CR_theorem(int);
int main()
{
	int n;
	printf("Nhap n: ");		//bac cua he pt
	scanf("%d",&n);
	printf("x = %d", CR_theorem(n));
	return 0;
}
int CR_theorem(int n)
{
	int M_ = 1, i = 0;
	int a[10], m[10], M[10], y[10];
	
	for (i=1; i<=n; i++)
	{                                                 
		scanf("%d",&a[i]);
		scanf("%d",&m[i]);
	}
	
	for (i=1; i<=n; i++)
	{
		M_ = M_ * m[i];
	}
	
	for (i=1; i<=n; i++)
	{
		M[i] = M_ / m[i];	
	}
	
	for (i=1; i<=n; i++)
	{
		y[i] = 1;
		while ((y[i]*M[i])%m[i] != 1) 	y[i]++;
	}
	
	int x = 0;
	for (i=1; i<=n; i++)
	{
		x = x + a[i]*M[i]*y[i];
	}
	printf("mod %d\n", M_);
	return x%M_;
}
