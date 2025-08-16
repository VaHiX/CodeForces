/*
 * Problem URL : https://codeforces.com/problemset/problem/792/E
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+10;
int a[N];
int tmp;
bool check(int sz,int rem,int n)
{
    for(int i=1;i<=n;++i)
    {
        int x=a[i]/sz,y=a[i]%sz;
        if(y>x&&rem)return 0;
        if(!rem)
        {if(y>x)
        {
            --sz;
            ++rem;
            x=a[i]/sz;
            y=a[i]%sz;
        }
        if(y>x)return 0;}
    }
    tmp=sz;
    return 1;
}
int main()
{
    int n;scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    const int M=(int)sqrt(a[1])+1;
    for(int i=1;i<=M;++i)
    {
        int sz=a[1]/i,rem=a[1]%i;
        if(check(sz,rem,n))break;
    }
    ll rs=0;
    for(int i=1;i<=n;++i)
    rs+=(a[i]+tmp)/(tmp+1);
    printf("%lld\n",rs);
}
