/*
 * Problem URL : https://codeforces.com/contest/2006/problem/B
 * Submit Date : 2025-09-13
 */

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+9;
int n,W,fa[N],dep[N],siz[N];
int dist[N];
void solve(){
	cin>>n>>W;
	for(int i=1;i<=n;i++) siz[i]=1;
	for(int i=2;i<=n;i++) cin>>fa[i],dep[i]=dep[fa[i]]+1;
	for(int i=n;i>1;i--) siz[fa[i]]+=siz[i];
	dist[n]=dep[n];
	for(int i=1;i<n;i++) dist[i]=dep[i]+dep[i+1]-2*dep[fa[i+1]];
	int s=0,cnt=n;
	for(int i=1;i<n;i++){
		int x,w;
		cin>>x>>w;s+=w;
		dist[x-1]--;
		if(dist[x-1]==0) cnt--;
		dist[x+siz[x]-1]--;
		if(dist[x+siz[x]-1]==0) cnt--;
		cout<<s*2+(W-s)*cnt<<" ";
	}
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t; cin>>t;
	while(t--) solve();
}