/*
 * Problem URL : https://codeforces.com/contest/2021/problem/E3
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
using namespace std;

#define maxn 200'007
int par[maxn];
int sz[maxn];
long long cal[maxn];
pair<long long, pair<int,int>> edges[maxn];

int find(int u)
{
	return par[u] == u ? u : par[u] = find(par[u]);
}

vector<long long> bag;
long long answer[maxn], total;
int cur;

void unite(int u, int v, long long w)
{
	u = find(u);v = find(v);
	if(u == v) return;
	long long valu = w * sz[u] - cal[u],
					  valv = w * sz[v] - cal[v];
	if(valu < valv) {
		swap(u,v);
		swap(valu, valv);
	}
	if(sz[u] && sz[v]) {
		bag.push_back(valv);
	}
	sz[u] += sz[v];
	cal[u] += w*sz[v];
	par[v] = u;
}

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;cur = k-1;
	total = 0;
	bag.clear();
	for(int i=1;i<=n;i++) {
		sz[i] = 0;
		par[i] = i;
		cal[i] = 0;
		answer[i] = 0;
	}
	for(int i=1;i<=k;i++) {
		int input;
		cin >> input;
		sz[input]++;
	}
	for(int i=1;i<=m;i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edges[i] = {w, {u,v}};
	}
	sort(edges+1,edges+1+m);
	for(int i=1;i<=m;i++) unite(edges[i].second.first,edges[i].second.second,edges[i].first);
	sort(bag.begin(), bag.end());
	for(auto &x:bag) {
		total += x;
		answer[cur--] = total;
	}
	for(int i=1;i<=n;i++) cout << answer[i] << ' ';cout << '\n';
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

	int t;
	cin >> t;
	while(t--) solve();
}
