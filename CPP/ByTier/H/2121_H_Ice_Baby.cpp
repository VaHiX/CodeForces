/*
 * Problem URL : https://codeforces.com/problemset/problem/2121/H
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;

int t, n;
multiset < int > f;
void solve()
{
	cin >> n;
	f.insert(0);
	for (int i = 1, l, r; i <= n; i++)
	{
		cin >> l >> r;
		auto pos = f.upper_bound(r);
		f.insert(l);
		if (pos != f.end()) f.erase(pos);
		cout << f.size() - 1 << ' ';
	}
	cout << '\n';
	f.clear();
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
	return 0;
}