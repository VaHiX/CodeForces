/*
 * Problem URL : https://codeforces.com/contest/2021/problem/E2
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
#define N 200000
 
int n,m,t,i,j,k,q,fa[N+50];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
 
ll res[N+50],f[N+50],sz[N+50];
vector<tuple<int,int,int> > v;
 
ll NMSL[N+50],it;
 
void hb(int x,int y,ll w){
	ll t1,t2;
	t1=w*sz[x]-f[x];
	t2=w*sz[y]-f[y];
	if(t1<t2){swap(x,y); swap(t1,t2);}
	if(sz[x]&&sz[y])NMSL[++it]=t2;
	fa[y]=x;
	sz[x]+=sz[y];
	f[x]+=w*sz[y];
}
 
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>q; it=0;
		for(i=1;i<=n;i++){
			fa[i]=i; res[i]=f[i]=sz[i]=0;
		}
		for(i=1;i<=q;i++){
			cin>>k; sz[k]=1;
		}
		v={};
		while(m--){
			cin>>i>>j>>k;
			v.push_back({k,i,j});
		}
		sort(v.begin(),v.end());
		for(auto [w,x,y]:v){
			x=find(x); y=find(y);
			if(x!=y)hb(x,y,w);
		}
		sort(NMSL+1,NMSL+it+1);
		for(i=q-1;i>=1;i--)res[i]=res[i+1]+NMSL[q-i];
		for(i=1;i<=n;i++)cout<<res[i]<<' '; cout<<'\n';
	}
}