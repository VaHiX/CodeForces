/*
 * Problem URL : https://codeforces.com/contest/2023/problem/B
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>
#define	ll long long
using namespace std;const int N=4e5+5;int T,n,b[N];ll a[N],f[N],s[N];
void add(int u,ll v){while(u)s[u]=min(s[u],v),u-=u&-u;}
ll ask(int u){ll res=1e18;while(u<=n)res=min(res,s[u]),u+=u&-u;return res;}
int main(){ios::sync_with_stdio(0),cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){cin>>n,fill(f,f+1+n,1e18),fill(s,s+1+n,1e18);
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		add(1,0);ll ans=0,sum=0;
		for(int i=1;i<=n;i++)f[i]=ask(i),add(b[i],f[i]+a[i]);
		for(int i=1;i<=n;i++)sum+=a[i],ans=max(ans,sum-f[i]);
		cout<<ans<<"\n";
	}
}