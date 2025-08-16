/*
 * Problem URL : https://codeforces.com/problemset/problem/2124/F1
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
int t,n,m,vis[101][101],dp[101],dp2[101][101];
bool check(int x,int y,int st)
{
	int now=0;
	for(int i=st;i<=y;i++)
		if(vis[i][++now]) return false;
	for(int i=x;i<st;i++)
		if(vis[i][++now]) return false;
	return true;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		memset(vis,0,sizeof(vis));
		memset(dp,0,sizeof(dp));
		memset(dp2,0,sizeof(dp2));
		cin>>n>>m;
		for(int i=1,id,x;i<=m;i++) cin>>id>>x,vis[id][x]=1;
		dp[0]=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=i;j++)
				for(int k=j;k<=i;k++)
					if(check(j,i,k))
						dp[i]+=dp[j-1]-dp2[j-1][i-k+1]*(j!=k),dp[i]=(dp[i]%mod+mod)%mod;
			for(int j=1;j<=i;j++)
				if(check(j,i,j))
					dp2[i][i-j+1]+=dp[j-1],dp2[i][i-j+1]%=mod;
		}
		cout<<dp[n]<<"\n";
	}
	return 0;
}