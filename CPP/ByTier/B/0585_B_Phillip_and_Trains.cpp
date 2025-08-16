/*
 * Problem URL : https://codeforces.com/problemset/problem/585/B
 * Submit Date : 2025-08-14
 */

#include <stdio.h>
int i,n,k,t,g;
char a[3][105];
bool c(int x, int y){
  return a[x][y]=='.' || a[x][y]=='\0';
}
bool d(int x, int y){
  if(y>=n-2)return 1;
  a[x][y]='s';
  if(a[x][y+1]!='.')return 0;
  if(c(x,y+3) && d(x,y+3))return 1;
  if(x && a[x-1][y+1]=='.' && c(x-1,y+3) && d(x-1,y+3)) return 1;
  if(x!=2 && a[x+1][y+1]=='.' && c(x+1,y+3) && d(x+1,y+3))return 1;
  return 0;
}
int main() {
    scanf("%d",&t);
    for(i=0;i<t;i++){
      scanf("%d%d",&n,&k);
      scanf("%s%s%s",a[0],a[1],a[2]);
      if(a[0][0]=='s')k=d(0,0);
      if(a[1][0]=='s')k=d(1,0);
      if(a[2][0]=='s')k=d(2,0);
      if(k)printf("YES\n");
      else printf("NO\n");
    }
    return 0;
}