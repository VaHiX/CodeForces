/*
 * Problem URL : https://codeforces.com/contest/587/problem/A
 * Submit Date : 2025-09-04
 */

#include<stdio.h>
int a[2000005],ans=0;
 
int main()
{
    int n,x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        a[x]++;
    }
 
    for(int i=0;i<=2000000;i++)
    {
        a[i+1]+=a[i]>>1;
        if(a[i]&1) ans++;
    }
    printf("%d\n",ans);
}