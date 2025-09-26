/*
 * Problem URL : https://codeforces.com/contest/2014/problem/F
 * Submit Date : 2025-09-12
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
#define N 400000
 
ll i,j,k,n,m,t,a[N+50],f[N+50][2];
 
basic_string<ll> v[N+50];
 
void dfs(int x,int fa){
	f[x][0]=0; f[x][1]=a[x];
	for(auto i:v[x])if(i!=fa){
		dfs(i,x);
		f[x][0]+=max(f[i][0],f[i][1]);
		f[x][1]+=max(f[i][0],f[i][1]-2*m);
	}
}
 
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(i=1;i<=n;i++)cin>>a[i];
		for(i=1;i<n;i++){
			cin>>j>>k; v[j]+=k; v[k]+=j;
		}
		dfs(1,0);
		cout<<max(f[1][0],f[1][1])<<'\n';
		for(i=1;i<=n;i++)v[i]={};
	}
}