/*
 * Problem URL : https://codeforces.com/contest/1324/problem/B
 * Submit Date : 2025-08-27
 */

#include <bits/stdc++.h>
using namespace std;
 
main()
{
	int t; cin>>t;
	while (t--)
	{
		int n,p[5001]={},ans=0; 
		cin>>n;
		for (int i=1; i<=n; ++i)
		{
			int a; cin>>a;
			if (!p[a]) p[a]=i;
			if (i-p[a]>1) ans=1;
		}
		cout<<(ans? "YES\n": "NO\n");
	}
}