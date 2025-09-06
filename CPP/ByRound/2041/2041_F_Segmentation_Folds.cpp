/*
 * Problem URL : https://codeforces.com/contest/2041/problem/F
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
using i64=long long;
namespace pr{
int p[2000010],pn;
void init(){
   constexpr int n=2000000;
   for(int i=2;i<=n;i++){
      if(!p[i])p[++pn]=i;
      for(int j=1;j<=pn&&i*p[j]<=n;j++){
         p[i*p[j]]=1;
         if(i%p[j]==0)break;
      }
   }
}
}
bool vis[200010];
int pre[200010],nex[200010],mi,cnt;
void dfs(int l,int r){
   if(mi>r-l){
      mi=r-l,cnt=1;
   }else if(mi==r-l)cnt++;
   int x=pre[(l+r)/2];
   if(x!=-1&&x>l)dfs(x,r);
   int y=nex[(l+r+1)/2];
   if(y!=-1&&y<r)dfs(l,y);
}
void solve(){
   i64 l,r;
   scanf("%lld%lld",&l,&r);
   l*=2,r*=2,mi=1e9,cnt=0;
   for(i64 i=l;i<=r;i++)vis[i-l]=true;
   for(int i=1;i<=pr::pn;i++){
      int x=pr::p[i];
      for(i64 j=max((l+x-1)/x,2ll)*x;j<=r;j+=x)vis[j-l]=false;
   }
   pre[0]=-1;
   for(i64 i=l+1;i<=r;i++){
      pre[i-l]=vis[i-l]?i-l:pre[i-l-1];
   }
   nex[r-l]=-1;
   for(i64 i=r-1;i>=l;i--){
      nex[i-l]=vis[i-l]?i-l:nex[i-l+1];
   }
   dfs(0,r-l);
   printf("%d\n",cnt);
}
int main(){
   pr::init();
   int T;for(scanf("%d",&T);T--;)solve();
   return 0;
}