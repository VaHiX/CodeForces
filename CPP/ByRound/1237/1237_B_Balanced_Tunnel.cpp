/*
 * Problem URL : https://codeforces.com/contest/1237/problem/B
 * Submit Date : 2025-08-27
 */

#include <bits/stdc++.h>
int i,j,x,r,n,a[7<<14],b[7<<14];
main(){
 for(scanf("%d",&n);i++<n;a[x]=i)scanf("%d",&x);
 while(j++<n)scanf("%d",b+j);
 while(--j)x=a[b[j]],r+=x>n,n=x>n?n:x;
 printf("%d",r);
}