// Problem: CF 2120 E - Lanes of Cars
// https://codeforces.com/contest/2120/problem/E

/*
E. Lanes of Cars
Algorithms/Techniques: Binary search on the answer + prefix sums + greedy optimal redistribution

Time Complexity: O(n log(max_a) + n), where max_a is the maximum value in array a
Space Complexity: O(n)

This problem involves minimizing the total angriness of cars passing through toll lanes,
where each car's angriness is the time it waits plus an additional k if it switches lanes.
The key insight is to use binary search on the optimal "base angriness" level (h),
and compute how many operations are needed to adjust all lanes such that
each lane has at most h cars, and the rest can be handled with a certain cost.

The algorithm proceeds as follows:
1. For each test case, we precompute prefix sums of sorted array.
2. Binary search on the base angriness level h (0 to N).
3. For each h, compute cost for left and right parts using prefix sums.
4. Reconstruct optimal solution, adjusting total angriness based on moves.

*/
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long LL;
typedef double DB;
const int N = 1111111;
const LL inf = 1e18;
int n, k, a[N];
LL s[N];
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T, i, l, r, h;
  LL x, y, z, o, p, t;
  cin >> T;
  while (T--) {
    cin >> n >> k;
    for (i = 1; i <= n; i++)
      cin >> a[i];
    sort(a + 1, a + n + 1);
    for (i = 1; i <= n; i++)
      s[i] = s[i - 1] + a[i];
    z = inf, o = -1;
    l = 0, r = N;
    while (l <= r) {
      h = l + r >> 1;
      i = lower_bound(a + 1, a + n + 1, h) - a - 1;
      x = (LL)i * h - s[i]; // Cost to reduce left part to at most h
      i = lower_bound(a + 1, a + n + 1, h + k) - a - 1;
      y = (s[n] - s[i]) - (LL)(n - i) * (h + k); // Cost to increase right part to at least h+k
      if (z > max(x, y))
        z = max(x, y), o = h;
      if (x < y)
        l = h + 1;
      else
        r = h - 1;
    }
    p = z * k; // Base cost from redistribution
    t = 0;
    for (i = 1; i <= n; i++) {
      x = min(max((LL)a[i], o), o + k); // Optimal angriness after adjustment
      p += (LL)x * (x + 1) / 2; // Sum of arithmetic series for angriness up to x
      t += x - a[i]; // Track net change in cars moved
    }
    if (t > 0)
      p -= (o + k) * t; // Overpayment due to too many cars at high end
    if (t < 0)
      p += (o + 1) * -t; // Underpayment due to too few cars at low end
    cout << p << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/