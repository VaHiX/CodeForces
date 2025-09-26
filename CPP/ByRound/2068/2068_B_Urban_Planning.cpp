/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/B
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  i64 k;
  cin >> k;

  constexpr int N = 2025;
  constexpr int M = 30;
  vector<string> ans(N, string(N, '#'));

  i64 tot = 1LL * N * (N - 1) / 2 * N * (N - 1) / 2;

  for (int i = 0; i <= M; i++) {
    for (int j = 0; j <= M; j++) {
      tot -= (N - 1 - i) * (N - 1 - j);
      ans[i][j] = '.';
    }
  }

  int lastx = -1, lasty = -1;
  // Greedily remove additional rectangles while tot is too high.
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (ans[i][j] == '#' && tot > k) {
        tot -= (N - 1 - i) * (N - 1 - j);
        ans[i][j] = '.';
        lastx = i;
        lasty = j;
      }
    }
  }
  // The variable (lastx,lasty) records the last changed cell.

  // A helper lambda to “fix” the grid further.
  auto work = [&](int x, int y) {
    while (tot < k - N) {
      int len = 0;
      while (tot + 1LL * len * (len + 1) / 2 * (N - 1 - x) <= k) {
        len++;
      }
      tot += 1LL * len * (len - 1) / 2 * (N - 1 - x);
      y--;
      for (int i = 0; i < len; i++) {
        ans[x][y--] = '#';
      }
    }
  };

  if (lasty > 300) {
    work(lastx, lasty);
  } else {
    work(lastx - 1, N - 1);
  }

  // Adjust k by the rectangles already subtracted.
  k -= tot;

  // Now, fill some additional areas in the grid to add exactly k more walks.
  int curx = 0, cury = 0;
  while (k >= M * (M - 1) / 2) {
    int len = 2;
    while (len * (len + 1) / 2 * M * (M - 1) / 2 <= k) {
      len++;
    }
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < M; j++) {
        ans[curx + i][cury + j] = '#';
      }
    }
    k -= len * (len - 1) / 2 * M * (M - 1) / 2;
    curx += len + 1;
  }
  while (k) {
    int len = 2;
    while (len * (len + 1) / 2 <= k) {
      len++;
    }
    if (cury + len > M) {
      curx += 3;
      cury = 0;
    }
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < len; j++) {
        ans[curx + i][cury + j] = '#';
      }
    }
    k -= len * (len - 1) / 2;
    cury += len + 1;
  }

  // Output the final grid.
  cout << N << " " << N << "\n";
  for (int i = 0; i < N; i++) {
    cout << ans[i] << "\n";
  }

  return 0;
}