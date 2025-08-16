/*
 * Problem URL : https://codeforces.com/problemset/problem/584/B
 * Submit Date : 2025-08-16
 */

#include<iostream>
using namespace std;
int M=1000000007;
int main()
{
	long long a=1,b=1;
	int n,i;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		a=(a*27)%M;
		b=(b*7)%M;
	}
	cout<<(a-b+M)%M;
}
  			   	    	 		 		 	 		    		