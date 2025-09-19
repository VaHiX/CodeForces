/*
 * Problem URL : https://codeforces.com/contest/2004/problem/F
 * Submit Date : 2025-09-13
 */

#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+10;
 
int n,a[maxn];
 
void sol() {
	cin>>n;for(int i=1;i<=n;++i)cin>>a[i];
	unordered_map<int,int>cnt(n*n*2);
	long long ans=0;
	for(int i=1;i<=n;++i)
		for(int j=i,s=0;j<=n;++j){
			int&p=cnt[s+=a[j]];
			ans+=j-i-p++;
		}
	cout<<ans<<'\n';
}
 
signed main() {
	ios::sync_with_stdio(0),cin.tie(0);
	int T;cin>>T;while(T--)sol();
}