/*
 * Problem URL : https://codeforces.com/problemset/problem/2131/D
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int T,n;
int d[maxn],a[maxn],h[maxn];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		int cnt=0,ans=0;
		for(int i=1;i<=n;i++) d[i]=0,a[i]=0;
		cin>>n;
		vector<int> G[n+5];
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			d[u]++,d[v]++;
			h[u]=v,h[v]=u;
		}
		if(n==2){
			cout<<0<<'\n';
			continue;
		}
		for(int i=1;i<=n;i++){
			if(d[i]==1){
				cnt++; 
				a[h[i]]++;
				ans=max(ans,a[h[i]]);
			}
		}
		cout<<cnt-ans<<'\n';
	}
	return 0;
}
