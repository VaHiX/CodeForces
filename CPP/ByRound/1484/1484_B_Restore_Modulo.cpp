/*
 * Problem URL : https://codeforces.com/contest/1484/problem/B
 * Submit Date : 2025-08-27
 */

/*
				author : Simply Hooman
*/
#include <bits/stdc++.h>
using namespace std;

int main() {	
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while (tt--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		long long m = 0;
		for (int i = 1; i + 1 < n; i++) {
			m = __gcd(m, 1LL * abs(a[i + 1] + a[i - 1] - 2 * a[i]));
		}
		if (m == 0) { 	
			cout << 0 << '\n';
		} else if (m < *max_element(a.begin(), a.end())) {
			cout << -1 << '\n';
		} else {
			cout << m << ' ' << (a[1] - a[0] + m) % m << '\n';
		}
	}
	return 0;
}