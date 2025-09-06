/*
 * Problem URL : https://codeforces.com/contest/737/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define NN 202020

using namespace std;
using INT=long long;

int c[NN], v[NN], len[NN], dp[NN], m, s, t;
INT sum[NN];

bool can(int v) {if(len[m]>v) return 0;
	int id=upper_bound(len+1, len+m+1, v>>1)-len;
	return dp[id-1] + (sum[id]-(INT)v*(m-id+1)) <= t;
}

int main() {
	
	int n, k; scanf("%d %d %d %d", &n, &k, &s, &t);
	for(int i=1; i<=n; i++) scanf("%d %d", c+i, v+i);
	
	len[m++]=0, len[m++]=s;
	while(k--) scanf("%d", len+m), m++;
	sort(len, len+m);
	
	for(int i=m; --i; ) len[i]-=len[i-1];
	m--, sort(len+1, len+m+1);
	
	for(int i=1; i<=m; i++) dp[i]=dp[i-1]+len[i];
	for(int i=m; i; i--) sum[i]=sum[i+1]+3LL*len[i];
	
	int ans=inf;
	for(int i=1; i<=n; i++) {
		if(can(v[i])) ans=min(ans, c[i]);
	}
	printf("%d", ans<inf? ans: -1);
}
   