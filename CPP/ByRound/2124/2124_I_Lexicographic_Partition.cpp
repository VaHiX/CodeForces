/*
 * Problem URL : https://codeforces.com/problemset/problem/2124/I
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
const int p=998244353;
const int N=2010000;
int qpow(int a,int n){
	int as=1;
	for(;n;n>>=1){
		if(n&1)as=(ll)as*a%p;
		a=(ll)a*a%p;
	}
	return as;
}
vector<int> o[N];
int a[N];
int ans[N];int nx[N];
bool solve(int l,int r,int u,int v){
	int t=a[l]+1;
	if(r==l){
		ans[l]=u;
		return 1;
	}
	if(a[l+1]!=t)return 0;
	if(nx[l+1]>r){
		ans[l]=v;
		return solve(l+1,r,u,v-1);
	}
	ans[l]=u;
	for(int i=l+1;i<=r;i=nx[i]){
		assert(a[i]==t);
		int j=min(nx[i]-1,r);
		ans[i]=u+j-l;
		if(i<j&&(a[i+1]!=a[i]+1||(!solve(i+1,j,u+i-l,u+j-l-1))))return 0;
	}
	return 1;
}
 
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int _;cin>>_;
	while(_--){
		int n;cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)o[i].clear();
		for(int i=1;i<=n;i++)o[a[i]].pb(i);
		for(int i=1;i<=n;i++)if(o[i].size()){
			for(int j=0;j<o[i].size()-1;j++)nx[o[i][j]]=o[i][j+1];
			nx[o[i][o[i].size()-1]]=n+1;
		}
		if(solve(1,n,1,n)){
			cout<<"YES\n";
			for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
			cout<<"\n";
		}
		else cout<<"NO\n";
	}
	return 0;
}
