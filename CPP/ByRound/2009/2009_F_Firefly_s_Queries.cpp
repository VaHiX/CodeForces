/*
 * Problem URL : https://codeforces.com/contest/2009/problem/F
 * Submit Date : 2025-09-13
 */

#include<bits/stdc++.h>
long long a[400005];
int T,n,m;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			scanf("%lld",&a[i]),a[n+i]=a[i];
		for(int i=1;i<=(n<<1);++i)a[i]+=a[i-1];
		for(long long l,r;m--;){
			scanf("%lld%lld",&l,&r);
			printf("%lld\n",(r/n-(l-1)/n-1)*a[n]+a[(l-1)/n%n+n]-a[(l-1)/n%n+(l-1)%n]+a[r/n%n+r%n]-a[r/n%n]);
		}
	}
	return 0;
}