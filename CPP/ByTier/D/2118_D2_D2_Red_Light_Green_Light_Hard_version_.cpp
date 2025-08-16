/*
 * Problem URL : https://codeforces.com/problemset/problem/2118/D2
 * Submit Date : 2025-08-14
 */

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
int n,m,l,t,lp[400010],ant[200010],to[400010];
long long md,p[200010],d[200010];
pair<long long,int> q[200010];
bool ans[200010];
map<long long,int> mp;
void dfs(int x)
{
	lp[x]=1;
	if(!to[x])
	{
		lp[x]=2;
		return;
	}
	if(!lp[to[x]]) dfs(to[x]);
	lp[x]=lp[to[x]];
}
void solve()
{
	scanf("%d%lld",&n,&md);
	for(int i=1;i<=n;++i) to[i]=lp[i]=to[n+i]=lp[n+i]=0;
	for(int i=1;i<=n;++i) scanf("%lld",&p[i]);
	for(int i=1;i<=n;++i) scanf("%lld",&d[i]);
	scanf("%d",&m);
	for(int i=0;i<m;++i)
	{
		scanf("%lld",&q[i].first);
		q[i].second=i;
		ant[i]=0;
	}
	sort(q,q+m);
	mp.clear();
	for(int i=1;i<=n;++i)
	{
		to[i]=mp[(p[i]+d[i])%md];
		mp[(p[i]+d[i])%md]=n+i;
	}
	mp.clear();
	for(int i=n,j=m-1;j>=0||i;--i)
	{
		while(j>=0&&(!i||p[i]<q[j].first))
		{
			ant[j]=mp[q[j].first%md];
			--j;
		}
		if(!i) break;
		//if(i==1) printf("?%d\n",mp[(p[i]+md-d[i])%md]);
		to[n+i]=mp[(p[i]+md-d[i])%md];
		mp[(p[i]+md-d[i])%md]=i;
	}
	//for(int i=1;i<=2*n;++i) printf("[%d]->[%d]\n",i,to[i]);
	//for(int j=0;j<m;++j) printf("{%d}",ant[j]);
	//printf("DF");
	for(int i=1;i<=2*n;++i) if(!lp[i]) dfs(i);
	for(int j=0;j<m;++j)
	{
		if(!ant[j]) ans[q[j].second]=1;
		else ans[q[j].second]=~lp[ant[j]]&1;
	}
	for(int j=0;j<m;++j) printf(ans[j]?"YES\n":"NO\n");
}
int main()
{
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
