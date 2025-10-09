// Problem: CF 2008 H - Sakurako's Test
// https://codeforces.com/contest/2008/problem/H

/*
H. Sakurako's Test

Purpose:
This code solves a problem where for each query value x, we need to compute the minimum possible median of an array after repeatedly subtracting x from any element that is greater than or equal to x.

Algorithms/Techniques:
- Binary search on answer (for each x, find minimum valid threshold)
- Prefix sums for efficient range queries
- Greedy approach combined with binary search

Time Complexity: O(n log n + q * log n * log n), where n is array size and q is number of queries.
Space Complexity: O(n)

*/

#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

void solve() {
  int n, q;
  cin >> n >> q;
  int cnt[n + 1]; // frequency count of elements
  for (int i = 0; i <= n; i++) cnt[i] = 0; // initialize to zero
  for (int i = 0, x; i < n; i++)
    cin >> x, cnt[x]++; // count occurrences of each value
  for (int i = 1; i <= n; i++)
    cnt[i] += cnt[i - 1]; // prefix sum to get cumulative counts

  int ans[n + 1]; // stores the answer for each possible x
  for (int x = 1; x <= n; x++) {
    int l = 0, r = x, val = r; // binary search on threshold value
    while (l <= r) {
      int m = (l + r) >> 1, c;
      c = cnt[m]; // base count up to threshold m
      for (int i = 1; i * x <= n; i++)
        c += cnt[min(n, i * x + m)] - cnt[i * x - 1]; // add counts for multiples of x shifted by m
      if (c - 1 >= n / 2) // check if this threshold is valid
        r = m - 1, val = m;
      else
        l = m + 1;
    }
    ans[x] = val; // store result for x
  }

  while (q--) {
    int x;
    cin >> x;
    cout << ans[x] << ' '; // respond to each query
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/