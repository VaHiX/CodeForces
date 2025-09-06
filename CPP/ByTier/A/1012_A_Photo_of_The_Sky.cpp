/*
 * Problem URL : https://codeforces.com/contest/1012/problem/A
 * Submit Date : 2025-09-02
 */

#include<bits/stdc++.h>
#define ll long long
int a[200005];
int n;
int main()
{
	scanf("%d",&n);
	for(int i=0; i<n*2; i++)
		scanf("%d",a+i);
	std::sort(a,a+n*2);
	ll ans=a[n-1]-a[0];
	ans*=a[n*2-1]-a[n];
	for(int i=1; i<n; i++) {
		ll h=a[i+n-1]-a[i];
		ll w=a[2*n-1]-a[0];
		ans=std::min(ans,h*w);
	}
	printf("%lld\n",ans);
}