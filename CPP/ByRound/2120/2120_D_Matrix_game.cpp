/*
 * Problem URL : https://codeforces.com/problemset/problem/2120/D
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
long long inv[100001];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T;
	long long i,a,b,k,d,ans;
	inv[1]=1;
	for(i=2;i<=100000;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(cin>>T;T>0;T--)
	{
		cin>>a>>b>>k;
		d=k*a-k+1;
		ans=k;
		for(i=1;i<=a;i++)ans=ans*((d-i+1)%mod)%mod*inv[i]%mod;
		cout<<d%mod<<' '<<(ans*b-ans+1+mod)%mod<<'\n';
	}
	return 0;
}