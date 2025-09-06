/*
 * Problem URL : https://codeforces.com/contest/1394/problem/A
 * Submit Date : 2025-09-02
 */

#include<stdio.h>
#include<iostream>
#include<algorithm> 
using namespace std;
long long a[100009];
long long dp[100009];
int main(){
	long long n,d,m;
	scanf("%lld %lld %lld",&n,&d,&m);
	int cnt=0;
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]<=m){
			cnt++;
		}
	}
	sort(a+1,a+n+1);
	for(long long i=1;i<=n;i++){
		dp[i]=dp[i-1]+a[i];
	}
	if(cnt==n){
		printf("%lld",dp[n]);
	}else{	
		long long ans=0;
		for(long long i=n;i>cnt;i--){
			if((n-i)*d<=i-1){
				long long num=max((long long)0,(n-i)*d-(n-cnt-(n-i+1)));
				ans=max(ans,dp[cnt]-dp[num]+dp[n]-dp[i-1]);
			}else{
				break;
			}
		} 
		printf("%lld\n",ans);
	}
} 
 	