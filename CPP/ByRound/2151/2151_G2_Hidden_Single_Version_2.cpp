// Problem: CF 2151 G2 - Hidden Single (Version 2)
// https://codeforces.com/contest/2151/problem/G2

/*
G2. Hidden Single (Version 2)
Interactive problem to find a unique element in an array of size 2*n-1 where all
numbers from 1 to n appear twice except one.

Algorithms:
- Binary search with query-based decision making
- Divide and conquer approach on the array indices
- Uses a randomized shuffle for initial array ordering

Time Complexity: O(n * log(2*n-1)) = O(n * log n)
Space Complexity: O(n)

The algorithm performs binary search over the indices of the hidden array. For
each query, it partitions the elements and determines whether the unique element
lies in the left or right half based on the responses. The process continues
until a single candidate is found.

*/

#include <algorithm>
#include <assert.h>
#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using vi = vector<int>;
#define pb push_back
const int MAX = 1000;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int id[MAX];
int ask(int x, int l, int r) {
  cout << "? " << x << " ";
  cout << r - l + 1 << " ";
  for (int i = l; i <= r; ++i)
    cout << id[i] << ' ';
  cout << endl;
  int y;
  cin >> y;
  return y;
}
void testcase() {
  int n;
  cin >> n;
  for (int i = 1; i <= 2 * n - 1; ++i)
    id[i] = i;
  shuffle(id + 1, id + 2 * n, rng);
  auto solve = [&]() {
    int L = 1, R = 2 * n - 1, MID = L + R >> 1;
    vi pl, npl, pr, npr;
    for (int u = 1; u <= n; ++u) {
      if (!ask(u, L, MID))
        pr.pb(u);
      else {
        if (ask(u, MID + 1, R)) {
          npl.pb(u);
          npr.pb(u);
        } else
          pl.pb(u);
      }
    }
    if ((MID - L + 1) == 2 * (int)pl.size() + (int)npl.size()) {
      for (auto u : pr) {
        int l = MID + 1, r = R;
        while (l < r) {
          int mid = l + r >> 1;
          if (!ask(u, l, mid))
            l = mid + 1;
          else if (!ask(u, mid + 1, r))
            r = mid;
          else
            break;
        }
        if (l == r)
          return u;
      }
      assert(false);
    } else {
      for (auto u : pl) {
        int l = L, r = MID;
        while (l < r) {
          int mid = l + r >> 1;
          if (!ask(u, l, mid))
            l = mid + 1;
          else if (!ask(u, mid + 1, r))
            r = mid;
          else
            break;
        }
        if (l == r)
          return u;
      }
      assert(false);
    }
  };
  int ans = solve();
  cout << "! " << ans << '\n';
}
int main() {
  int tests = 1;
  cin >> tests;
  while (tests--)
    testcase();
  return 0;
}

// https://github.com/VaHiX/CodeForces/