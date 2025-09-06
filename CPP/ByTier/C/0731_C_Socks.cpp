/*
 * Problem URL : https://codeforces.com/contest/731/problem/C
 * Submit Date : 2025-09-02
 */

#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+17;
int n,m,k;
int c[MAXN];
int fat[MAXN];
vector<vector<int > >v(MAXN);
inline int find(int x){
	return fat[x]=fat[x]==x?x:find(fat[x]);
}
int js[MAXN];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)scanf("%d",&c[i]),fat[i]=i;
	for(int i=1,l,r;i<=m;++i){
		scanf("%d%d",&l,&r);
		fat[find(l)]=find(r);
	}
	for(int i=1;i<=n;++i)v[find(i)].push_back(i);
	int ans=0;
	for(int i=1;i<=n;++i)if(find(i)==i){
		int mx=0;
		for(int j=0;j<v[i].size();++j)mx=max(++js[c[v[i][j]]],mx);
		ans+=v[i].size()-mx;
		for(int j=0;j<v[i].size();++j)js[c[v[i][j]]]=0;
	}
	cout<<ans;
	return 0;
} 
									 	  	   	 				   					