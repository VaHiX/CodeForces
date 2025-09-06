/*
 * Problem URL : https://codeforces.com/contest/1637/problem/A
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
using namespace std;
int a[10010];
int main()
{
	int T,i,n;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(i=1;i<=n;i++) cin>>a[i];
		cout<<((is_sorted(a+1,a+n+1))?"NO\n":"YES\n");
	}
}