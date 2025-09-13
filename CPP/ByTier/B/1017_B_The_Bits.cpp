/*
 * Problem URL : https://codeforces.com/problemset/problem/1017/B
 * Submit Date : 2025-08-18
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1017/B
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
#define ll long long
#define db double
#define N 100100
using namespace std;

ll n, m, ans, sum, ca, cb, cnt[2][2];
char a[N], b[N];

int main() {
  int i, j;
  cin >> n;
  scanf("%s%s", a + 1, b + 1);
  for (i = 1; i <= n; i++) {
    cnt[a[i] - '0'][b[i] - '0']++;
  }
  cout << cnt[0][0] * (cnt[1][0] + cnt[1][1]) + cnt[1][0] * (cnt[0][1]);
}