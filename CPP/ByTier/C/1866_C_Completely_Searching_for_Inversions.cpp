/*
 * Problem URL : https://codeforces.com/problemset/problem/1866/C
 * Submit Date : 2025-08-15
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005;
const int mod=998244353;
int n,ans[N],f[N][2];
vector< pair<int,int> > v[N];
bool vis[N];
void dfs(int x)
{
	if (vis[x]) return;
	vis[x]=1;
	for (auto u:v[x])
	{
		int y=u.first,w=u.second;
		ans[x]=(ans[x]+(w==0)*f[x][1]%mod)%mod;
		f[x][w]++;
		dfs(y);
		int res=((f[y][0]*f[x][1]%mod)+ans[y])%mod;
		ans[x]=(ans[x]%mod+res)%mod;
		(f[x][0]+=f[y][0])%=mod;
		(f[x][1]+=f[y][1])%=mod;
	}
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		int m,x,y;cin>>m;
		for (int j=1;j<=m;j++)
		{
			cin>>x>>y;
			v[i].push_back(make_pair(x,y));
		}
	}
	dfs(1);
	cout<<ans[1]<<'\n';
	return 0;
}
