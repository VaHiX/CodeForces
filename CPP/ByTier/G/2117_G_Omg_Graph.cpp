/*
 * Problem URL : https://codeforces.com/problemset/problem/2117/G
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 55, INF = 1e9 + 1, MOD = 1e9 + 7;
int T, n, m;
int f[N], mn[N];
int fd(int x) {
	return f[x] == x ? x : f[x] = fd(f[x]);
} 
struct edge {
	int u, v, w;
	bool operator < (const edge &x) const {
		return w < x.w;
	}
} a[N];
signed main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
		}
		sort(a + 1, a + 1 + m);
		for (int i = 1; i <= n; i++) {
			f[i] = i;
			mn[i] = INF;
		}
		int ans = 2 * INF;
		for (int i = 1; i <= m; i++) {
			int u = a[i].u, v = a[i].v, w = a[i].w;
			int uu = fd(u);
			int vv = fd(v);
			if (uu != vv) {
				f[vv] = uu;
				mn[uu] = min(mn[uu], mn[vv]);
				mn[uu] = min(mn[uu], w);
			}
			if (fd(1) == fd(n)) {
				ans = min(ans, a[i].w + mn[fd(1)]); 
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}