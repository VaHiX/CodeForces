/*
 * Problem URL : https://codeforces.com/contest/2007/problem/E
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

constexpr int MAXN = 200000;
int p[MAXN + 5];
int pid[MAXN + 5];
int cnt[MAXN + 5];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	stack<int> st;
	st.push(1);
	while(t--) {
		int n; ll w;
		cin >> n >> w;
		for(int i = 2; i <= n; i++) cin >> p[i];
		fill(pid, pid + n + 2, 0);
		fill(cnt, cnt + n + 2, 1);
		cnt[n + 1] = 0;
		p[n + 1] = 1;
		for(int i = 2; i <= n + 1; i++) {
			while(st.top() != p[i]) {
				cnt[i]++;
				pid[st.top()] = i;
				st.pop();
			}
			st.push(i);
		}
		st.pop();
		ll acc = 0;
		int u1 = n;
		for(int i = 0; i < n - 1; i++) {
			int x; ll y;
			cin >> x >> y;
			acc += y;
			cnt[x]--;
			if(cnt[x] == 0) --u1;
			if(pid[x]) {
				acc += y;
				cnt[pid[x]]--;
				if(cnt[pid[x]] == 0) --u1;
			}
			w -= y;
			ll ans = w * u1 + acc;
			cout << ans << ' ';
		}
		cout << '\n';
	}
}
