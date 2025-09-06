/*
 * Problem URL : https://codeforces.com/contest/1396/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << "1 " << n << '\n';
	for (int i = 0; i < n; i++) {
		cout << - 1LL * a[i] * n << " ";
	}
	cout << "\n1 1\n" << 1LL * a[0] * (n - 1) << "\n" << min(2, n) << " " << n << (n == 1 ? "\n0" : "\n");
	for (int i = 1; i < n; i++) {
		cout << 1LL * a[i] * (n - 1) << " ";
	}
	return 0;
}