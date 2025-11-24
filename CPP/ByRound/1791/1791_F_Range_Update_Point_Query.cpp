// Problem: CF 1791 F - Range Update Point Query
// https://codeforces.com/contest/1791/problem/F

/*
Purpose: This code handles range update point query operations on an array where each update transforms elements into the sum of their digits.
           It uses a Binary Indexed Tree (Fenwick Tree) to track how many times each element has been updated and precomputed digit sum sequences
           to efficiently retrieve final values after multiple transformations.

Algorithms/Techniques:
- Binary Indexed Tree (Fenwick Tree) for efficient range updates and point queries
- Precomputation of digit sum sequences for fast lookup
- Lazy propagation simulation using counter in Fenwick Tree

Time Complexity:
- Precomputation: O(K^2) where K=100 (precomputed digit sums for values up to 100)
- Each query: O(log n + log K) where n is array size and K is max possible digits sum
- Overall: O(q * (log n + log K)) for q queries

Space Complexity:
- O(n + K^2) for Fenwick tree and precomputed digit sum lists
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
#define pii pair<int, int>
#define vi vector<int>
#define pb push_back
#define sz(v) ((int)(v).size())
#define all(x) (x).begin(), (x).end()
#define mp make_pair
#define fs first
#define sc second
#define next hunext
#define prev huprev
#define hash huhash
const int K = 100;
vi lst[K]; // Precomputed digit sum sequences for values 1 to K-1
int calc(int x) {
  int res = 0;
  while (x > 0) {
    res += x % 10; // Add last digit
    x /= 10;       // Remove last digit
  }
  return res;
}
void init() {
  for (int i = 1; i < K; ++i) {
    int cur = i;
    for (;;) {
      int ncur = calc(cur); // Compute digit sum
      lst[i].pb(ncur);     // Store sequence
      if (cur == ncur) {   // Stop if no change
        break;
      }
      cur = ncur;
    }
  }
}
void add(vi &fen, int pos, int val) {
  // Update Fenwick Tree with value at position
  while (pos < sz(fen)) {
    fen[pos] += val;
    pos = (pos | (pos + 1)); // Move to parent
  }
}
int get(const vi &fen, int pos) {
  // Get prefix sum up to position
  int res = 0;
  while (pos >= 0) {
    res += fen[pos];
    pos = (pos & (pos + 1)) - 1; // Move to previous node
  }
  return res;
}
void solve() {
  int n, q;
  cin >> n >> q;
  vi a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vi fen(n, 0); // Fenwick Tree to count updates per index
  for (int i = 0; i < q; ++i) {
    int t;
    cin >> t;
    if (t == 1) {
      int l, r;
      cin >> l >> r;
      --l;
      --r;
      add(fen, l, 1);     // Mark start of update range
      add(fen, r + 1, -1); // Mark end of update range
    } else {
      assert(t == 2);
      int x;
      cin >> x;
      --x;
      int cnt = get(fen, x); // Get number of updates for that index
      if (cnt == 0) {
        cout << a[x] << "\n"; // No update, return original value
      } else {
        int y = calc(a[x]);   // First digit sum
        --cnt;
        if (cnt == 0) {
          cout << y << "\n"; // After one update
        } else if (cnt - 1 < sz(lst[y])) {
          cout << lst[y][cnt - 1] << "\n"; // Lookup precomputed value
        } else {
          cout << lst[y].back() << "\n"; // Too many updates, return final value
        }
      }
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef LOCAL42
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  init();
  int t = 1;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/