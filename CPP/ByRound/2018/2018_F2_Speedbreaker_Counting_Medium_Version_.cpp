/*
 * Problem URL : https://codeforces.com/contest/2018/problem/F2
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
using namespace std;
const int N=3e3+10;
typedef long long ll;
int n,T,mod;
ll sqr(ll x){return x*x%mod;}
ll ans[N],f[N];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&mod);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<i;j++) f[j]=0;
			f[i]=1;
			for(int j=1;j<=i;j++)
				f[i]=f[i]*(n-max(j,i-j+1)+1)%mod;
			for(int j=i+1;j<=n;j++)
				f[j]=(2*(n-(j-1))*f[j-1]+sqr(n-(j-1))*(mod-f[j-2]))%mod;
			ans[i]=f[n];
		}
		for(int i=n;i;i--)
			for(int j=i+1;j<=n;j++)
				ans[i]=(ans[i]+(mod-ans[j])*(j-i+1))%mod;
		ll s=1;
		for(int i=1;i<=n;i++) s=s*n%mod;
		for(int i=1;i<=n;i++) s=(s-ans[i]+mod)%mod;
		printf("%lld ",s);
		for(int i=1;i<=n;i++) printf("%lld%c",ans[i]," \n"[i==n]);
	}
}