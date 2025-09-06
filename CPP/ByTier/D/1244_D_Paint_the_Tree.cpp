/*
 * Problem URL : https://codeforces.com/contest/1244/problem/D
 * Submit Date : 2025-08-29
 */

/*
 * Problem URL : https://codeforces.com/contest/1244/problem/D
 * Submit Date : 2025-08-28
 */

#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
const int N=1e5+10;
bool ok;
int n,num[3],rt,c[3][N],u,v;
vector<int>E[N],f;
int ans[N];
void dfs(int x,int fa)
{
	f.pb(x);
	for(int v:E[x])
	{
		if(v==fa)continue;
		dfs(v,x);
	}
}
ll solve(int x)
{
	f.pb(0);
	dfs(x,-1);
	for(int i=0;i<3;++i)
		num[i]=i; 
	ll res=8e18;
	do
	{
		ll tmp=0;
		for(int i=1;i<=n;++i)
		tmp+=c[num[i%3]][f[i]];
		if(res>tmp)
		{
			res=tmp;
			for(int i=1;i<=n;++i)
			ans[f[i]]=num[i%3];
		}
	}while(next_permutation(num,num+3));
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int j=0;j<3;++j)
	{
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&c[j][i]);
		}
	}
	for(int i=1;i<n;++i)
	{
		scanf("%d%d",&u,&v);
		E[u].pb(v),E[v].pb(u);
	}
	for(int i=1;i<=n;++i)
	{
		if(E[i].size()>=3)
		{
			ok=1;
			break;
		}
		if(E[i].size()==1)rt=i;
	}
	if(ok)puts("-1");
	else
	{
		printf("%I64d\n",solve(rt));
		for(int i=1;i<=n;++i)
		printf("%d%c",1+ans[i]," \n"[i==n]);
	}
	return 0;
} 
