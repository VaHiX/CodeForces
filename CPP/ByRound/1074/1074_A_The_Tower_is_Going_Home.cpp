/*
 * Problem URL : https://codeforces.com/contest/1074/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
#define inf 0x3f3f3f3f

using namespace std;

int a[100005],b[100005];

int main() {
  int n,m;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  a[++n]=1e9;
  int cnt=0;
  for(int i=1;i<=m;i++) {
  	int x1,x2,y;
  	scanf("%d%d%d",&x1,&x2,&y);
  	if (x1==1) b[++cnt]=x2;
  }
  sort(a+1,a+n+1);
  sort(b+1,b+cnt+1);
  int r=1,ans=inf;
  for(int i=1;i<=n;i++) {
  	while (r<=cnt&&b[r]<a[i]) r++;
  	ans=min(ans,cnt-r+i);
  }
  printf("%d\n",ans);
  return 0;
}