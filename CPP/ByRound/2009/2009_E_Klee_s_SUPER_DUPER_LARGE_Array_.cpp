/*
 * Problem URL : https://codeforces.com/contest/2009/problem/E
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
using namespace std;

void solve()
{
	long long n, k;
	cin>>n>>k;
	long long res = (k+n-1)*(k+n)/2+k*(k-1)/2;
	long long t = floor(sqrt(res));
	cout<<min(abs(res-t*(t+1)), abs(res-(t+1)*(t+2)))<<endl;
}

int main()
{
	int t;
	cin>>t;
	while (t--) solve();
	return 0;
}