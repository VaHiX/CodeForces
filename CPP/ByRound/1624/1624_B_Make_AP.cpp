/*
 * Problem URL : https://codeforces.com/problemset/problem/1624/B
 * Submit Date : 2025-08-15
 */

#include<stdio.h>
int main()
{
int t;
scanf("%d",&t);
while(t--)
{
int a,b,c;
scanf("%d %d %d",&a,&b,&c);
if((2*b-c)>0&&(2*b-c)%a==0||(a+c)%(2*b)==0||(2*b-a)>0&&(2*b-a)%c==0) printf("YES\n");
else printf("NO\n");
}
}

