/*
 * Problem URL : https://codeforces.com/contest/2024/problem/D
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
using namespace std;
using ll=long long;

void solve()
{
	int n;cin>>n;
	vector<int> a(n),b(n);
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<n;i++) cin>>b[i],b[i]--;
	vector<ll> dp(n,1e18);
	dp[0]=1;
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
	pq.push({0,0});
	for(int i=0;i<n;i++)
	{
		while(!pq.empty()&&pq.top().second<i) pq.pop();
		if(pq.empty()) break;
		dp[i]=pq.top().first;
		if(b[i]<=i) continue;
		pq.push({dp[i]+a[i],b[i]});
	}
	ll ans=0,sum=0;
	for(int i=0;i<n;i++)
	{
		sum+=a[i];
		ans=max(ans,sum-dp[i]);
	}
	cout<<ans<<"\n";
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int _=1;cin>>_;
	while(_--) solve();
	return 0;
}