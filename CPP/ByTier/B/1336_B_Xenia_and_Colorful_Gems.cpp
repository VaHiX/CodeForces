/*
 * Problem URL : https://codeforces.com/contest/1336/problem/B
 * Submit Date : 2025-09-11
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll ans;
int a[3][N], n[3];
ll sq(int x) { return 1ll * x * x; }
void f(int p, int q, int r)
{
	int j = -1, k = 0;
	for (int i = 0; i < n[p]; i++)
	{
		while (k < n[r] && a[r][k] < a[p][i])
			k++;
		if (k == n[r])
			break;
		while (j + 1 < n[q] && a[q][j + 1] <= a[p][i])
			j++;
		if (j == -1)
			continue;
		ans = min(ans, sq(a[p][i] - a[q][j]) + sq(a[q][j] - a[r][k]) + sq(a[p][i] - a[r][k]));
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n[0] >> n[1] >> n[2];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < n[i]; j++)
				cin >> a[i][j];
			sort(a[i], a[i] + n[i]);
		}
		ans = 5e18;
		f(0, 1, 2);
		f(0, 2, 1);
		f(1, 0, 2);
		f(1, 2, 0);
		f(2, 0, 1);
		f(2, 1, 0);
		cout << ans << '\n';
	}
}