/*
 * Problem URL : https://codeforces.com/contest/1027/problem/D
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
using namespace std;
int n,a[200010],c[200010],vis[200010],ans;
int main(){
scanf("%d",&n);
for(int i=1;i<=n;i++)scanf("%d",&c[i]);
for(int i=1;i<=n;i++)scanf("%d",&a[i]);
for(int i=1;i<=n;i++)
if(!vis[i]){
int u=i,res,t;
while(!vis[u])vis[u]=i,u=a[u];
if(vis[u]!=i)continue;
t=u;res=c[u];
while(a[u]!=t)u=a[u],res=min(res,c[u]);
ans+=res;
}
printf("%d",ans);
return 0;
}