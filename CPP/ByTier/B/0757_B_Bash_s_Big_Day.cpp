/*
 * Problem URL : https://codeforces.com/problemset/problem/757/B
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 17;

int n, x, cnt[N], res = 1;

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    scanf("%d", &x), cnt[x]++;
  for (int i = 2; i < N; i++)
    for (int j = i + i; j < N; j += i)
      cnt[i] += cnt[j];
  for (int i = 2; i < N; i++)
    res = max(res, cnt[i]);
  cout << res << endl;
}