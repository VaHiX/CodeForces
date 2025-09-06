/*
 * Problem URL : https://codeforces.com/contest/2135/problem/C
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 2e5+50, M = 4e5+50;
const ll mod = 998244353;
int n,m,v,head[N],cnt=1,dfn[N],low[N],a[N],c[N];
set <int> s;
bool bridge[M<<1],flag;
struct E{
    int next,to;
}e[M<<1];
inline void dfs(int now,int from)
{
    dfn[now]=low[now]=++cnt;
    for(int i=head[now];i;i=e[i].next)
    {
        if(((i^1)==from))continue;
        if(!dfn[e[i].to])
        {
            dfs(e[i].to,i);
            low[now]=min(low[now],low[e[i].to]);
            if(low[e[i].to]>dfn[now]){bridge[i]=1,bridge[i^1]=1;}
        }
        else low[now]=min(low[now],dfn[e[i].to]);
    }
}
inline void dfs1(int now)
{
    if(a[now]!=-1)s.insert(a[now]);
    for(int i=head[now];i;i=e[i].next)
    {
        if(bridge[i])continue;
        if(c[e[i].to]==0)
        {
            c[e[i].to]=(c[now]^1);
            dfs1(e[i].to);
        }
        else if(c[e[i].to]==c[now])flag=1;
    }
}
inline void add(int x,int y){e[++cnt]=(E){head[x],y};head[x]=cnt;bridge[cnt]=0;}
inline void solve()
{
    cnt=1;
    cin>>n>>m>>v;
    for(int i=1;i<=n;i++)cin>>a[i],head[i]=0,dfn[i]=0,low[i]=0,c[i]=0;
    for(int i=1;i<=m;i++)
    {
        int u,v;cin>>u>>v;
        add(u,v);add(v,u);
    }
    cnt=0;
    dfs(1,0);
    ll ans=1;
    for(int i=1;i<=n;i++)
    {
        if(c[i]==0)
        {
            c[i]=2;
            s.clear();
            flag=0;
            dfs1(i);
            if(s.size()>1)ans=0;
            if(s.size()==1&&flag&&*s.begin())ans=0;
            if(!flag&&s.size()==0)ans=ans*v%mod;
        }
    }
    cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--)solve();
    return 0;
}