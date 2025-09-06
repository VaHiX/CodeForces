/*
 * Problem URL : https://codeforces.com/contest/813/problem/C
 * Submit Date : 2025-09-01
 */

#include<bits/stdc++.h>
using namespace std;
vector<vector<int> > adj;
const int maxn=2e5+5;
int fa[maxn],dpth[maxn],dist[maxn];
int x,n,i,a,b,ans;
void dfs(int v,int p){
	dpth[v]=0;
	fa[v]=p;
	for(auto &to : adj[v])
		if(to!=p){
			dist[to]=dist[v]+1;
			dfs(to,v);
			dpth[v]=max(dpth[v],dpth[to]+1);
		}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>x;
	adj.resize(n+1);
	for(i=0;i<n-1;++i){
		cin>>a>>b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1,0);
	for(a=x,i=0,ans=0;i<=(dist[x]-1)/2;a=fa[a],i++)
		ans=max(ans,dist[a]+dpth[a]);
	cout<<2*ans;
}