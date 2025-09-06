/*
 * Problem URL : https://codeforces.com/contest/1458/problem/A
 * Submit Date : 2025-09-01
 */

#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long x,g=0,n,m,a1;
	cin>>n>>m>>a1;
	for(int i=1;i<n;i++)cin>>x,g=__gcd(g,abs(x-a1));
	for(int i=0;i<m;i++)cin>>x,cout<<__gcd(g,a1+x)<<" ";
	return 0;
}