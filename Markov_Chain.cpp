#include<iostream>
using namespace std;

struct pow
{
  double ar[10][10];
};
int ord;

void copy(pow&, pow&);
void mult(pow&, pow&, pow&);


pow operator^(pow &a,int n)
{
    pow c,b;
    copy(a,b);
    for(int i=0;i<n-1;i++)
    {
        mult(a,b,c);
        copy(c,b);
    }
    return c;
}
int main()
{
    pow a;
    int n;
    cout<<"Nhap bac cua matrix (toi da ord=10) ord = ";
    cin>>ord;
    cout<<"Nhap bac luy thua n = ";
    cin>>n;
    cout<<"Nhap ma tran A: "<<endl;
    for(int i=0;i<ord;i++)
        for(int j=0;j<ord;j++)
           cin>>a.ar[i][j];
    a=a^n;
    cout<<"Matrix A^"<<n<<"  = "<<endl;
    for(int i=0;i<ord;i++)
    {
        for(int j=0;j<ord;j++)
            cout<<a.ar[i][j]<<" ";
        cout<<endl;
    }
    
    double max;
    int n0;
    cout << "Nhap trang thai ban dau: ";
    cin >> n0;
    max = a.ar[n0][0];
    for (int i=1; i<n; i++)
    {
    	
    	if (max < a.ar[n0][i])
    		max = a.ar[n0][i];
	}
	cout << "Xac suat lon nhat: " << max;
    return 0;
}

void copy(pow &a,pow &b)
{
    for(int i=0;i<ord;i++)
        for(int j=0;j<ord;j++)
           b.ar[i][j]=a.ar[i][j];
}

void mult(pow &a,pow &b,pow &c)
{
    double sum=0;
    for(int i=0;i<ord;i++)
    {
       for(int j=0;j<ord;j++)
       {
           for(int k=0;k<ord;k++)
                sum+=a.ar[i][k]*b.ar[k][j];
           c.ar[i][j]=sum;
           sum=0;
       }
    }
}
