/*
 * Problem URL : https://codeforces.com/contest/2018/problem/C
 * Submit Date : 2025-09-11
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,f[500005],g[500005];
vector <int> edge[500005];

int dfs(int x,int from,int deep){
	int tmp = deep; f[deep]++;
	for(auto y : edge[x])
		if(y != from){
			tmp = max(tmp,dfs(y,x,deep + 1));
		}
	g[tmp]++;
	return tmp;
}

inline void solve(){
	scanf("%d",&n);
	for(int i = 1;i < n;i++){
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0,0); int ans = 0;
	for(int i = 1;i <= n;i++)
		f[i] += f[i - 1] - g[i - 1], ans = max(ans,f[i]);
	printf("%d\n",n - ans);
}
inline void clear(){
	for(int i = 0;i <= n;i++)
		f[i] = g[i] = 0, edge[i].clear();
}

int main(){
	int t; scanf("%d",&t);
	while(t--){
		clear();
		solve();
	}
}