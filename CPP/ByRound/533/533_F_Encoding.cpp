/*
 * Problem URL : https://codeforces.com/problemset/problem/533/F
 * Submit Date : 2025-08-16
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 10, C = 27, B = 273;
unsigned long long H[C], cnt[C], RH[C], tv[MAXN], A[MAXN];
int faq[C], n, m, ans;
vector<int> res;
string s, t;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> s >> t;
	tv[0] = 1;
	A[0] = 1;
	for (int i = 1; i < MAXN; i++)
		tv[i] = tv[i - 1] * B;
	for (int i = 1; i < MAXN; i++)
		A[i] = A[i - 1] * B + 1;
	for (int i = 0; i < C; i++)
		faq[i] = -1;
	for (int i = 0; i < m; i++) {
		faq[t[i] - 'a'] = max(faq[t[i] - 'a'], i);
		RH[t[i] - 'a'] *= B;
		RH[t[i] - 'a'] += i + 1;
	}
	for (int i = 0; i < m - 1; i++) {
		H[s[i] - 'a'] *= B;
		H[s[i] - 'a'] += i + 1;
		cnt[s[i] - 'a']++;
	}
	for (int i = m - 1; i < n; i++) {
		if (i - m >= 0) {
			for (int j = 0; j < C; j++)
				if (cnt[j] > 0)
					H[j] -= A[cnt[j] - 1];
				cnt[s[i - m] - 'a']--;
		}
		H[s[i] - 'a'] *= B;
		H[s[i] - 'a'] += m;
		cnt[s[i] - 'a']++;
		bool ok = true;
		for (int j = 0; j < C; j++) {
			if (faq[j] == -1)
				continue;
			char tm = s[i - m + 1 + faq[j]];
			if (H[tm - 'a'] != RH[j] || RH[tm - 'a'] != H[j])
				ok = false;
		}
		ans += ok;
		if (ok)
			res.push_back(i - m + 2);
	}
	cout << ans << endl;
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << ' ';
}
