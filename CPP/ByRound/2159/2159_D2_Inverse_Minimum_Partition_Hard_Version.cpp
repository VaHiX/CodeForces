// Problem: CF 2159 D2 - Inverse Minimum Partition (Hard Version)
// https://codeforces.com/contest/2159/problem/D2

/*
Purpose: This code computes the sum of f(b) over all contiguous subsequences b of a given sequence a.
f(b) is defined as the minimum total cost to partition b into contiguous subsequences,
where the cost of a subsequence is the ceiling of (sum of elements / length of subsequence) divided by the minimum element in the subsequence.

Algorithms/Techniques:
- Sparse Table (RMQ) for efficient range minimum queries
- Dynamic Programming with a bounded state (up to 130 states)
- Binary search to determine optimal partition points

Time Complexity: O(n * A * log(n)) where n is the length of the sequence and A=130
Space Complexity: O(n * A) for the dp table and O(n * log(n)) for sparse table
*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define F first
#define S second
#define all(x) x.begin(), x.end()
#define pb push_back
#define FIO                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const int lg = 19, N = 4e5 + 7, A = 130;
int f[A][N]; // DP table where f[j][i] represents minimum index for j partitions ending at i
ll rmq[lg][N]; // Sparse table for range minimum queries
ll di(ll x, ll y) { return (x + y - 1) / y; }
ll get(int l, int r) {
  int bit = 31 - __builtin_clz(r - l + 1); // Get the highest bit position for sparse table
  return min(rmq[bit][l], rmq[bit][r - (1 << bit) + 1]);
}
void task() {
  int n;
  cin >> n;
  vector<ll> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    rmq[0][i] = a[i]; // Initialize sparse table with original values
  }
  // Build sparse table for range minimum queries
  for (int i = 1; i < lg; i++) {
    for (int j = 0; j + (1 << i - 1) <= n; j++)
      rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << i - 1)]);
  }
  // Initialize DP table
  for (int i = 0; i < A; i++)
    f[i][0] = (!i ? 0 : -1);
  for (int i = 0; i < n; i++) {
    int g[4]; // Array to store results of binary search for different j values
    for (int j = 1; j <= 3; j++) {
      int lo = 0, hi = i;
      // Binary search to find optimal partition point for j parts
      while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (di(a[i], get(mid, i)) <= j)
          hi = mid;
        else
          lo = mid + 1;
      }
      // Check if valid partition found
      if (di(a[i], get(lo, i)) < j)
        g[j] = -1;
      else
        g[j] = lo;
    }
    // Initialize dp values for current position
    for (int j = 0; j < A; j++)
      f[j][i + 1] = (!j ? i + 1 : n + 1);
    // Update DP values based on previous partitions
    for (int j = 1; j <= 3; j++)
      if (g[j] != -1) {
        for (int k = j; k < A; k++)
          f[k][i + 1] = min(f[k][i + 1], f[k - j][g[j]]);
      }
  }
  // Calculates final result by summing weighted differences
  ll res = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < A; j++)
      if (f[j][i + 1] != -1)
        res += (f[j - 1][i + 1] - f[j][i + 1]) * j;
  }
  cout << res << "\n";
}
int main() {
  FIO;
  int tt;
  cin >> tt;
  while (tt--)
    task();
  return 0;
}


// https://github.com/VaHiX/CodeForces/