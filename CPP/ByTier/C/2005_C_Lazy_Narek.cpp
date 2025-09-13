/*
 * Problem URL : https://codeforces.com/contest/2005/problem/C
 * Submit Date : 2025-09-13
 */

#include<bits/stdc++.h>
using namespace std;
int t,n,m,dp[100005][5],now,cnt;
string s,e="narek";
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	dp[0][1]=dp[0][2]=dp[0][3]=dp[0][4]=0xcfcfcfcf;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>s;
			dp[i][0]=dp[i-1][0],dp[i][1]=dp[i-1][1],dp[i][2]=dp[i-1][2],dp[i][3]=dp[i-1][3],dp[i][4]=dp[i-1][4];
			for(int j=0;j<5;j++){
				now=j;
				cnt=0;
				for(int k=0;k<m;k++){
					if(s[k]==e[now]){
						now=(now+1)%5;
						cnt++;
					}
					else if(s[k]=='n'||s[k]=='a'||s[k]=='r'||s[k]=='e'||s[k]=='k'){
						cnt--;
					}
				}
				dp[i][now]=max(dp[i][now],dp[i-1][j]+cnt);
			}
		}
		cout<<max(max(max(dp[n][0],dp[n][1]-2),dp[n][2]-4),max(dp[n][3]-6,dp[n][4]-8))<<'\n';
	}
	return 0;
}