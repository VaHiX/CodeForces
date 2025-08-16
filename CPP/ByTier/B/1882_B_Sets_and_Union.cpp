/*
 * Problem URL : https://codeforces.com/problemset/problem/1882/B
 * Submit Date : 2025-08-15
 */

#include<bits/stdc++.h>
using namespace std;
#define LL long long
int T,n,k,x;
LL a[55],s;
int32_t main()
// int32_t main()
{
	scanf("%d",&T);
	while(T--){
		int mx=0;
		s=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			a[i]=0;
			scanf("%d",&k);
			while(k--)scanf("%d",&x),a[i]|=1ll<<x;
			s|=a[i];
		}
		for(int i=1;i<=50;i++)if(s>>i&1){
			LL tmp=0;
			for(int j=1;j<=n;j++)if(!(a[j]>>i&1))tmp|=a[j];
			mx=max(mx,__builtin_popcountll(tmp));
		}
		printf("%d\n",mx);
	}
}