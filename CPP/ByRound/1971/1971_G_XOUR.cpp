// Problem: CF 1971 G - XOUR
// https://codeforces.com/contest/1971/problem/G

/*
 * Problem: G. XOUR
 * Purpose: Given an array of non-negative integers, we can swap two elements if their XOR is less than 4.
 *          Find the lexicographically smallest array possible through any number of such swaps.
 *
 * Approach:
 * - Group indices into connected components where elements can be swapped based on XOR < 4.
 * - Within each component, we can arrange elements in sorted order.
 * - To form the result:
 *   1. Sort indices by their values (a[i] < a[j]).
 *   2. Process indices in this sorted order, grouping consecutive indices that can be swapped (XOR < 4).
 *   3. For each group, sort the actual values and assign back to those indices.
 *
 * Time Complexity: O(n log n) per test case due to sorting steps and linear processing.
 * Space Complexity: O(n) for storing arrays and auxiliary structures.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using i64 = long long;
const int N = 1e6 + 10;
const int mod = 998244353;
#define endl '\n'
bool flag = false;
int cnt = 0;
#define all(x) x.begin(), x.end()
i64 qp(i64 a, i64 b) {
  i64 res = 1;
  a %= mod;
  while (b) {
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<int> b(n);
  // Initialize b with indices 0, 1, ..., n-1
  iota(all(b), 0);
  // Sort indices based on corresponding values in a
  sort(all(b), [&](int i, int j) { return a[i] < a[j]; });
  // Lambda function to sort a group of indices and assign sorted values back
  auto work = [&](vector<int> &c) {
    sort(all(c));
    vector<int> b_values; // Store actual values at indices in c
    for (int i = 0; i < c.size(); i++) {
      b_values.push_back(a[c[i]]);
    }
    sort(all(b_values)); // Sort the actual values
    for (int i = 0; i < c.size(); i++)
      a[c[i]] = b_values[i]; // Assign sorted values back to indices
    c.clear(); // Clear group
  };
  vector<int> c; // Current group of indices to be processed together
  for (int i = 0; i < n; i++) {
    // If current element's XOR with last element in group >= 4, process the group
    if (!c.empty() && (a[b[i]] ^ a[c.back()]) >= 4) {
      work(c);
    }
    c.push_back(b[i]); // Add current index to group
  }
  work(c); // Process final group
  for (int i = 0; i < n; i++)
    cout << a[i] << " \n"[i == n - 1]; // Print result
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/