/*
 * Problem URL : https://codeforces.com/contest/986/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
using namespace std;const int N=1e5+1007;
vector<int>e[N],s[N];int h[N],i,j,q[N],t,w,n,m,K,S,x,y,res;
void ins(int u,int v){e[u].push_back(v);}
void insert(int u,int v){ins(u,v);ins(v,u);}
int bfs(int x){
	memset(h,-1,sizeof(h));t=0;w=1;q[0]=x;h[x]=0;
	while(t!=w){
		x=q[t++];
		for(auto&y:e[x])if(h[y]==-1){
			h[y]=h[x]+1;
			q[w++]=y;
		}
	}
	for(int i=1;i<=n;++i)s[i].push_back(h[i]-1);
}
int main(){
	for(scanf("%d%d%d%d",&n,&m,&K,&S),i=1;i<=n;++i)scanf("%d",&x),ins(x+n,i);
	for(i=1;i<=m;++i)scanf("%d%d",&x,&y),insert(x,y);
	for(i=1;i<=K;++i)bfs(n+i);
	for(i=1;i<=n;++i){
		sort(s[i].begin(),s[i].end());
		for(j=res=0;j<S;++j)res+=s[i][j];
		printf("%d ",res);
	}
}