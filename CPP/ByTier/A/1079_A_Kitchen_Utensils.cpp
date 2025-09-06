/*
 * Problem URL : https://codeforces.com/contest/1079/problem/A
 * Submit Date : 2025-09-02
 */


#include<bits/stdc++.h>
using namespace std;
int a[110];
int t,n,k,i,x,res=0,mx=0;
int main()
{
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>x;
		if(!a[x])res++;
		a[x]++;
		mx=max(mx,a[x]);
	}
	t=mx/k;
	if(mx%k)t++;
	cout<<t*res*k-n<<endl;
}