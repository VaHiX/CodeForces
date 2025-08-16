/*
 * Problem URL : https://codeforces.com/problemset/problem/350/C
 * Submit Date : 2025-08-14
 */

// LUOGU_RID: 109248562
#include<bits/stdc++.h>
int n,s,i,f,g,h,j;struct w{int x,y;}a[100100];bool z(w t,w c){return abs(t.x)+abs(t.y)<abs(c.x)+abs(c.y);}void v(int d,int e){printf("1 %d %c\n",d,(char)e);}main(){for(scanf("%d",&n),s=n*4,i=0;i<n;++i)scanf("%d%d",&a[i].x,&a[i].y),s+=2*(a[i].x&&a[i].y);for(std::sort(a,a+n,z),printf("%d\n",s),i=0;i<n;++i){f=abs(a[i].x),g=abs(a[i].y),h=76+(a[i].x>0)*6,j=68+(a[i].y>0)*17;if(f)v(f,h);if(g)v(g,j);puts("2");if(f)v(f,158-h);if(g)v(g,153-j);puts("3");}}
