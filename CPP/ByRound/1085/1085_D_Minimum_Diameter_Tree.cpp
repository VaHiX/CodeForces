/*
 * Problem URL : https://codeforces.com/contest/1085/problem/D
 * Submit Date : 2025-08-30
 */

#include <stdio.h>
int n,l,g[100001],i,a,b;
double x;
int main(){
    scanf("%d%lf",&n,&x);
    for(i=1;i<n;i++)scanf("%d%d",&a,&b),g[a]++,g[b]++;
    for(i=1;i<=n;i++)l+=!(g[i]-1);
    x=(2*x)/l;
    printf("%.7lf",x);
}
