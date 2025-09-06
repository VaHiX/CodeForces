/*
 * Problem URL : https://codeforces.com/contest/2134/problem/A
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	cin>>t;
	while(t--)
	{
		int n,a,b;
		cin>>n>>a>>b;
		swap(a,b);
		if((n+a)%2==0&&(max(b-a,0))%2==0)cout<<"YES\n";
		else cout<<"NO\n";
	}
}