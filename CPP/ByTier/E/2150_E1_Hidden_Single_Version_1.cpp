// Problem: CF 2150 E1 - Hidden Single (Version 1)
// https://codeforces.com/contest/2150/problem/E1

/*
Hidden Single Problem - Version 1
Algorithm: Binary Search with Query Filtering
Time Complexity: O(n*log(n))
Space Complexity: O(n)

This is an interactive problem where we are given a hidden array of size 2n-1 containing numbers from 1 to n,
with each number appearing twice except one that appears once. 
We use binary search on the positions and query filtering to isolate the unique element.

The algorithm uses a divide-and-conquer approach:
1. Binary search over possible values
2. For each value x, determine which half of the array it can possibly be in
3. Based on queries, eliminate parts of the search space

The key insight is that for a given value x, if we query a subset of positions and get 0, then x cannot be in those positions.
If we get 1, then x might be in those positions.

The total number of queries used is bounded by 4n + 2 * ceil(log2(n)).
*/
#include <time.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
const int kMaxN = 301;
int a[kMaxN * 2], v[kMaxN * 2], t, n;
mt19937 rnd(time(0));
int Q(int l, int r, int x) {
  cout << "? " << x << ' ' << r - l + 1 << ' ';
  for (int i = l; i <= r; i++) {
    cout << a[i] << ' ';
  }
  cout << endl;
  cin >> x;
  return x;
}
int Solve(int l, int r, vector<int> &b, vector<int> &c) {
  // Base case: if the size of c equals the range [l, r], then answer must be in b
  if (r - l == c.size()) {
    return b[0];
  }
  int m = l + r >> 1; // Midpoint for binary search
  vector<int> lb, rb, lc, rc;
  // Partition 'c' into left and right parts based on whether element x is in the first half [l, m]
  for (int i : c) {
    Q(l, m, i) ? lc.emplace_back(i) : rc.emplace_back(i);
  }
  // Partition 'b' into left and right parts according to query results
  for (int i : b) {
    if (!Q(l, m, i)) {
      rb.emplace_back(i); // Value is in [m+1, r] part of array
    } else if (!Q(m + 1, r, i)) {
      lb.emplace_back(i); // Value is in [l, m] part of array
    } else {
      lc.emplace_back(i), rc.emplace_back(i); // Value can be in both parts (both queries return true)
    }
  }
  // Recurse on the side that contains the answer based on size comparison
  return lb.size() * 2 + lc.size() == m - l + 2 ? Solve(l, m, lb, lc)
                                                : Solve(m + 1, r, rb, rc);
}
int main() {
  for (cin >> t; t--;) {
    cin >> n;
    // Initialize 'a' with 1..2n-1 and assign random weights to them
    for (int i = 1; i < 2 * n; i++) {
      v[i] = rnd(), a[i] = i;
    }
    // Sort indices based on their random value so that they are shuffled
    sort(a + 1, a + 2 * n, [](int i, int j) { return v[i] < v[j]; });
    vector<int> b, c;
    // Fill 'b' with values from 1 to n as potential candidates for unique element
    for (int i = 1; i <= n; i++) {
      b.emplace_back(i);
    }
    int ans = Solve(1, 2 * n - 1, b, c);
    cout << "! " << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/