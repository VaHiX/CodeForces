/*
 * Problem URL : https://codeforces.com/contest/2039/problem/D
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N=1e5+5,V=1e5;
int _,n,m,a[N],f[N],g[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	for(int i=2;i<=V;i++)if(!f[i]){
		f[i]=1;
		for(int j=i*2;j<=V;j+=i)f[j]=f[j/i]+1;
	}
	for(int i=2;i<=V;i++)g[i]=max(g[i-1],f[i]);
	cin>>_;
	while(_--){
		cin>>n>>m;
		for(int i=1;i<=m;i++)cin>>a[i];
		if(g[n]>=m){cout<<"-1\n";continue;}
		for(int i=1;i<=n;i++)cout<<a[m-f[i]]<<' ';
		cout<<'\n';
	}
}