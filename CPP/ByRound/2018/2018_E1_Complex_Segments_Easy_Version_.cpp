/*
 * Problem URL : https://codeforces.com/contest/2018/problem/E1
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int maxn=4e4+5;
int n,t,res;
int c[maxn],f[maxn];
pii p[maxn];
int find(int x)
{
    return f[x]==x?x:f[x]=find(f[x]);
}
int calc(int m)
{
    int cnt=0;
    for(int i=1,x=0,cur=0,lim=0,lst=0;i<=n;i++)
    {
        int l=p[i].fi,r=p[i].se;
        if(l<=lim) continue;
        for(int j=lst+1;j<r;j++) f[j]=lst;
        cur++,lst=f[r]=r,x=find(l);
        if(x>lim) cur--,f[x]=x-1;
        if(cur==m) cnt++,cur=0,lim=r;
    }
    res=max(res,cnt*m);
    return cnt;
}
void solve(int l,int r,int L,int R)
{
    if(l>r||L==R) return ;
    int mid=(l+r)>>1,val=calc(mid);
    solve(l,mid-1,L,val),solve(mid+1,r,val,R);
}
int main()
{
    for(scanf("%d",&t);t--;)
    {
        scanf("%d",&n),memset(c,0,8*n),res=0;
        for(int i=1;i<=n;i++) scanf("%d",&p[i].fi),c[p[i].fi]++;
        for(int i=1;i<=n;i++) scanf("%d",&p[i].se),c[p[i].se]++;
        for(int i=1;i<=2*n;i++) c[i]+=c[i-1];
        for(int i=1;i<=n;i++) p[i].se=c[p[i].se]--;
        for(int i=1;i<=n;i++) p[i].fi=c[p[i].fi]--;
        sort(p+1,p+n+1,[&](pii x,pii y){return x.se<y.se;});
        solve(1,n,n+1,0);
        printf("%d\n",res);
    }
    return 0;
}
