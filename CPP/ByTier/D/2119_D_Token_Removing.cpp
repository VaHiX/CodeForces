/*
 * Problem URL : https://codeforces.com/problemset/problem/2119/D
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
int n,m,t;
long long dp[5005][5005],ans;
int main(){
	cin>>t;while(t--){
		cin>>n>>m;ans=0;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=i;j++)dp[i][j]=0;
		dp[0][0]=1;
		for(int i=1;i<=n;i++)
			for(int j=0;j<=i;j++)dp[i][j]=(dp[i-1][j-1]+(n-i+1)*(j+1)*dp[i-1][j])%m;
		for(int i=0;i<=n;i++)ans=(ans+dp[n][i])%m;
		cout<<ans<<endl;
	}
	return 0;
}