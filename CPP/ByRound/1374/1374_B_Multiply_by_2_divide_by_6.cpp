/*
 * Problem URL : https://codeforces.com/contest/1374/problem/B
 * Submit Date : 2025-08-27
 */

#include<cstdio>
int t,n,a,b;
main(){
 for(scanf("%d",&t);t--;){
  for(scanf("%d",&n),a=b=0;n%2<1;n/=2) ++a;
  for(;n%3<1;n/=3) ++b;
  printf("%d\n",(n^1||a>b?-1:2*b-a));
 }
}