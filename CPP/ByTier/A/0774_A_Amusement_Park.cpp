/*
 * Problem URL : https://codeforces.com/contest/774/problem/A
 * Submit Date : 2025-09-04
 */

#include<stdio.h>
#define lli long long int

lli n,c1,c2,pr=0;

lli calc(lli gr)
{
    lli num=n/gr;
    lli r=n%gr;
    lli ret=gr*c1;
    ret+=r*(n/gr)*(n/gr)*c2;
    ret+=(gr-r)*(n/gr-1)*(n/gr-1)*c2;
    return ret;
}

int main() {
    scanf("%lld%",&n);
    scanf("%lld%",&c1);
    scanf("%lld%",&c2);
    char s[n+1];
    gets(s);
    int ch=0;
    int i;
    for(i=0;i<n;i++)
        if(s[i]=='1')
            pr++;
        else
            ch++;
    int l=1,h=pr;
    lli ans=calc(l);
    for(i=l+1;i<=h;i++)
    {
        lli cur=calc(i);
        if(cur<ans)
            ans=cur;
    }
    printf("%lld",ans);
    return 0;
}