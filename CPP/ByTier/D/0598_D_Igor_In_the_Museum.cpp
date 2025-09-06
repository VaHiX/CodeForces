/*
 * Problem URL : https://codeforces.com/contest/598/problem/D
 * Submit Date : 2025-09-04
 */

#include<stdio.h>
int n,m,q,cnt=0,ans[1005*1005],p[1005][1005];char s[1005][1005];int dx[]={1,0,-1,0},dy[]={0,1,0,-1};void dfs(int x,int y){p[x][y]=cnt;for(int i=0;i<4;++i){int nx=x+dx[i],ny=y+dy[i];if(p[nx][ny])continue;if(s[nx][ny]=='*')ans[cnt]++;else dfs(nx,ny);}}int main(){scanf("%d%d%d",&n,&m,&q);for(int i=0;i<n;++i)scanf("%s",s[i]);while(q--){int x,y;scanf("%d%d",&x,&y);x--,y--;++cnt;if(!p[x][y])dfs(x,y);printf("%d\n",ans[p[x][y]]);}return 0;}