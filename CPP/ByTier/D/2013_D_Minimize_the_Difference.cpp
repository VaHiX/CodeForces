/*
 * Problem URL : https://codeforces.com/contest/2013/problem/D
 * Submit Date : 2025-09-12
 */

#include<iostream>
#define N 200005
using namespace std;
long long a[N];
void solve()
{
	int n;cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	long long s=0,minn=1e18,maxn=-1e18;
	for(int i=1;i<=n;++i)s+=a[i],minn=min(minn,s/i);
	s=0;
	for(int i=1;i<=n;++i)s+=a[n-i+1],maxn=max(maxn,(s+i-1)/i);
	cout<<maxn-minn<<"\n";
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);
	int t;cin>>t;while(t--)solve();
	return 0;
}