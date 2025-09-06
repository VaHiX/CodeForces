/*
 * Problem URL : https://codeforces.com/contest/1207/problem/C
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
using namespace std;
long long int t,n,a,b,dp[200010][2];
char s[200010];
int main()
{
	cin>>t;
	while(t--)
	{
		memset(dp,0x3f,sizeof dp);
		scanf("%lld%lld%lld%s",&n,&a,&b,s+1);	
		dp[0][0]=0;
		for(int i=1;i<=n;i++)
		{
			if(s[i]=='0')
				dp[i][0]=min(dp[i-1][0]+a+b,dp[i-1][1]+2*a+2*b);
			dp[i][1]=min(dp[i-1][1]+a+2*b,dp[i-1][0]+2*a+2*b);
		}
		cout<<dp[n][0]+b<<endl;
	}
	return 0;
}
    	   		 	    	 				 	 	