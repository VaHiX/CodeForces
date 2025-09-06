/*
 * Problem URL : https://codeforces.com/contest/1165/problem/E
 * Submit Date : 2025-08-28
 */

#include "bits/stdc++.h"
using namespace std;
const int N=2e5+20,MOD=998244353;
int n;
long long a[N],b[N],ans;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%lld",&a[i]),a[i]*=1ll*(i+1)*(n-i);
	for(int i=0;i<n;i++) scanf("%lld",&b[i]);

	sort(a,a+n),sort(b,b+n);
	for(int i=0;i<n;i++)
	{
		a[i]%=MOD;
		ans+=1ll*a[i]*b[n-i-1];
		ans%=MOD;
	}
	printf("%lld",ans);
}