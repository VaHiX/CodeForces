/*
 * Problem URL : https://codeforces.com/contest/2135/problem/A
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],dp[200005];
vector<int> w[200005];
int main(){
	cin>>t;
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]),w[a[i]].emplace_back(i);
			if((int)w[a[i]].size()>=a[i]) dp[i]=max(dp[i-1],dp[w[a[i]][w[a[i]].size()-a[i]]-1]+a[i]);
			else dp[i]=dp[i-1];
		}
		printf("%d\n",dp[n]);
		for(int i=1;i<=n;i++) w[i].clear();
	}
	return 0;
}