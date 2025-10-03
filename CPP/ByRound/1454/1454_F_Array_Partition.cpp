/*
 * Problem URL : https://codeforces.com/contest/1454/problem/F
 * Submit Date : 2025-09-11
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 2e5+7;
int n, a[N], ml[N], mr[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while (t--) {
		cin >> n;
		ml[0] = 0; mr[n+1] = 0;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) 
			ml[i] = max(a[i], ml[i-1]);
		for (int i = n; i >= 1; i--) 
			mr[i] = max(a[i], mr[i+1]);
		//
		vector<int> mx;
		for (int i = 1; i <= n; i++)
			if (a[i] == ml[n]) mx.push_back(i);
		//
		int c = ml[n];
		int l = mx[mx.size()/2], r = l;
		while (true) {
			// cout << l << " " << r << ", ";
			if (l == 1 || r == n) {
				cout << "NO\n";
				break;
			}
			if (ml[l-1] == c && mr[r+1] == c) {
				cout << "YES\n";
				cout << l-1 << " " << r - l + 1 << " " << n - r << "\n";
				break;
			}
			//
			int nxt_l = -1, nxt_r = -1;
			if (l-2 >= 1) nxt_l = min(a[l-1], ml[l-2]);
			if (r+2 <= n) nxt_r = min(a[r+1], mr[r+2]);
			//
			if (nxt_l > nxt_r) c = min(c, a[--l]);
			else c = min(c, a[++r]);
		}
	}
	return 0;
}
