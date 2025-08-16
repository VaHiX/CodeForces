/*
 * Problem URL : https://codeforces.com/problemset/problem/2122/D
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
#define ll long long
using vi=basic_string<int>;
const ll N=5000;
int i,j,k,n,m,t,f[N+50],g[N+50];
vi v[5005];
void solve(){
	fill(f,f+n+1,int(1e9)); f[1]=0;
	for(int T=0;;T++){
		if(f[n]<f[0]){cout<<T<<' '<<f[n]<<'\n';break;}
		for(i=1;i<=n;i++)g[i]=f[i]+1;
		for(i=1;i<=n;i++){k=v[i][T%v[i].size()]; g[k]=min(g[k],f[i]);}
		memcpy(f,g,n*4+50);
		f[0]=1e9;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		while(m--){cin>>i>>j;v[i]+=j;v[j]+=i;}
		solve();
		for(i=1;i<=n;i++)v[i]={};
	}
}