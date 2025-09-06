/*
 * Problem URL : https://codeforces.com/contest/1242/problem/A
 * Submit Date : 2025-09-02
 */

#include<bits/stdc++.h>
using namespace std;
long long n;
int main()
{
	cin>>n;
	for(long long i=2;i*i<=n;i++)
	{
		if(n%i==0)
		{
			while(n%i==0)
			n/=i;
			if(n!=1)
			cout<<1;
			else
			cout<<i;
			return 0;
		}
	}
	cout<<n; 
	
}