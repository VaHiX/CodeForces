/*
 * Problem URL : https://codeforces.com/problemset/problem/2124/E
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const ll N=5e4+5;
ll a[N],p[N],n;

void aua(){
	for(int i=1;i<=n;++i)
		cout<<a[i]<<' ';
	cout<<'\n';
}

void solve(){
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];

	for(int i=1;i<=n;++i)
		p[i]=p[i-1]+a[i];

	for(int i=1;i<n;++i){
		if(p[i]==p[n]-p[i]){
			cout<<1<<'\n';
			aua();return;
		}
	}

	ll P=0;
	for(int i=1;i<=n;++i)
		if(p[i-1]<p[n]/2&&p[i]>=p[n]/2)P=i;

	if(!P||p[n]&1||*max_element(a+1,a+n+1)>p[n]/2){
		cout<<-1<<'\n';
		return;
	}

	cout<<2<<'\n';
	array<ll,3>del={p[P-1],del[0]-(p[n]-2*a[P])/2,del[0]-del[1]};
	for(int i=1;i<=n;++i){
		ll t=(i<P?0:i==P?1:2),x=min(a[i],del[t]);
		cout<<x<<' ';
		del[t]-=x;
		a[i]-=x;
	}
	cout<<'\n';
	aua();
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T;cin>>T;
    while(T--)solve();
}