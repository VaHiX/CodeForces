/*
 * Problem URL : https://codeforces.com/contest/1677/problem/A
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
typedef long long ll;
int n,p[5005],cnt[5005];
ll ans;
void MAIN(){
	ans=0;scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%d",p+i),cnt[i]=0;
	for(int i=n-1;i>=3;i--){
		for(int j=p[i+1];j<=n;j++)cnt[j]++;
		ll now=0;
		for(int j=i-2;j;j--){
			now+=cnt[p[j+1]-1];
			if(p[j]<p[i])ans+=now;
		}
	}printf("%lld\n",ans);
}
int main(){
	int T;scanf("%d",&T);while(T--)MAIN();
	return 0;
}