/*
 * Problem URL : https://codeforces.com/contest/979/problem/C
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
using namespace std;
vector<int> a[300010];
int dfs(int u,int p,int k)
{
	int ans=1;
	for(auto i:a[u]) if(i!=p && i!=k) ans+=dfs(i,u,k);
	return ans;
}
int main()
{
	int n,x,y;
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		a[u].push_back(v);
		a[v].push_back(u);
	}
	printf("%lld",(long long)n*(n-1)-(long long)(n-dfs(x,-1,y))*(n-dfs(y,-1,x)));
	return 0;
}