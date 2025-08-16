/*
 * Problem URL : https://codeforces.com/problemset/problem/743/D
 * Submit Date : 2025-08-16
 */

#include<cstdio>
#include<algorithm>
typedef long long ll;
const int N=200010;
const ll inf=1LL<<60;
int n,i,x,y,a[N],g[N],v[N<<1],nxt[N<<1],ed;ll f[N],dp[N],ans=-inf;
inline void add(int x,int y){v[++ed]=y;nxt[ed]=g[x];g[x]=ed;}
void dfs(int x,int y){
  f[x]=a[x];
  dp[x]=-inf;
  for(int i=g[x];i;i=nxt[i]){
    int u=v[i];
    if(u==y)continue;
    dfs(u,x);
    f[x]+=f[u];
    if(dp[x]>-inf)ans=std::max(ans,dp[x]+dp[u]);
    dp[x]=std::max(dp[x],dp[u]);
  }
  dp[x]=std::max(dp[x],f[x]);
}
int main(){
  scanf("%d",&n);
  for(i=1;i<=n;i++)scanf("%d",&a[i]);
  for(i=1;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);
  dfs(1,0);
  if(ans>-inf)printf("%I64d",ans);else puts("Impossible");
}