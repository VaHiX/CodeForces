/*
 * Problem URL : https://codeforces.com/contest/2021/problem/E1
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=5050,inf=1e18;
ll T,n,m,p,S,s,sz[N],fa[N],tmp[N],dp[N][N];
struct P{
	ll x,y,w;
	bool operator<(const P& B){return w<B.w;}
}e[N];
void init(){
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) dp[i][j]=0;
}
ll getfa(ll x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
void hb(ll x,ll y,ll w){
	x=getfa(x),y=getfa(y);
	if(x==y) return;
	if(sz[x]>sz[y]) x^=y^=x^=y;
	ll A=sz[x],B=sz[y];
	fa[x]=y,sz[y]+=sz[x];
	for(int i=1;i<=A+B;i++) tmp[i]=inf;
	for(int i=1;i<=A;i++)
		for(int j=1;j<=B;j++) tmp[i+j]=min(tmp[i+j],dp[x][i]+dp[y][j]);
	for(int i=1;i<=A;i++) tmp[i]=min(tmp[i],dp[x][i]+w*B);
	for(int i=1;i<=B;i++) tmp[i]=min(tmp[i],dp[y][i]+w*A);
	for(int i=1;i<=A+B;i++) dp[y][i]=tmp[i];
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>p;init();
		for(int i=1;i<=p;i++) cin>>s,sz[s]=1;
		for(int i=1;i<=m;i++) cin>>e[i].x>>e[i].y>>e[i].w;
		sort(e+1,e+m+1);
		for(int i=1;i<=m;i++) hb(e[i].x,e[i].y,e[i].w);
		S=getfa(1);
		for(int i=1;i<=n;i++) cout<<dp[S][i]<<" ";
		cout<<"\n";
	}
	return 0;
}
