/*
 * Problem URL : https://codeforces.com/contest/2005/problem/E1
 * Submit Date : 2025-09-13
 */

#include<bits/stdc++.h>
using namespace std;
const int N=304;
int t,n,m,a[N][N],b[N],f[8],p[8];
void sol(){
	cin>>t>>n>>m;
	for(int i=1;i<=t;i++)cin>>b[i];
	for(int i=t;i;i--)p[b[i]]=i;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
	for(int i=n;i;i--){
		for(int j=1,k=p[a[i][1]];j<=m;j++,k=p[a[i][j]])
			if(k&&f[k+1]<=j)f[k]=max(f[k],j);
		if(f[1]){cout<<"T\n";return;}
	}
	cout<<"N\n";
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int tc;cin>>tc;while(tc--)sol(),memset(f,0,64),memset(p,0,64);
}