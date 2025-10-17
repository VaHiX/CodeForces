/*
 * Problem URL : https://codeforces.com/contest/2022/problem/E1
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
#define endl ??
using ll=long long;
using PII=pair<int,int>;

const int N=1e5+10,M=1000000007;
int getans(int freeCount) {
	if(freeCount<0)return 0;
	ll res=1,p2=1<<30;
	while(freeCount) {
		if(freeCount&1)res=res*p2%M;
		p2=p2*p2%M;
		freeCount>>=1;
	}
	return res;
}
int n,m,k,q;
struct {
	int f[N*2],size[N*2],_dist[N*2],cc;
	void init() {
		cc=n+m;
		for(int i=1; i<=n+m; ++i) {
			f[i]=i,size[i]=1;
			_dist[i]=0;
		}
	}
	int find(int x) {
		if(f[x]==x)return x;
		return find(f[x]);
	}
	int xdist(int x) {
		if(f[x]==x)return 0;
		return _dist[x]^xdist(f[x]);
	}
	bool link(int u,int v,int w) {
		int fu=find(u),fv=find(v);
		if(fu==fv)
			return (xdist(u)^xdist(v))==w;
		if(size[fu]<size[fv])swap(fu,fv),swap(u,v);
		_dist[fv]=xdist(u)^xdist(v)^w;
		f[fv]=fu;
		size[fu]+=size[fv];
		cc--;
		return true;
	}
}dsu;
void solve() {
	cin>>n>>m>>k>>q;
	dsu.init();
	bool flag=1;
	for(int i=0,r,c,v; i<k; ++i) {
		cin>>r>>c>>v;
		if(flag) flag=dsu.link(r,n+c,v);
	}
	if(!flag)cout<<0<<nl;
	else cout<<getans(dsu.cc-1)<<nl;
	for(int i=0,r,c,v; i<q; ++i) {
		cin>>r>>c>>v;
		if(flag) flag=dsu.link(r,n+c,v);
		if(flag) cout<<getans(dsu.cc-1)<<nl;
		else cout<<0<<nl;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T=1;
	cin>>T;
	while(T--) {
		solve();
	}
	fflush(stdout);
}
