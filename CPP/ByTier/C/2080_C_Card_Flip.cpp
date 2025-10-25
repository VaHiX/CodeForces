// Problem: CF 2080 C - Card Flip
// https://codeforces.com/contest/2080/problem/C

/*
Card Flip Game Solution
=======================
Algorithms/Techniques: Sorting, Greedy, Simulation
Time Complexity: O((n + m) log(n + m))
Space Complexity: O(n + m)

This problem models a two-player game where players take turns removing or flipping cards
with the goal of removing the last card. The strategy involves analyzing the smallest card
and determining whether it's better to remove it directly or flip a double-sided card
to optimize the outcome.

The approach:
1. Combine all cards in a single array with their values and back-side info (INT_MAX for single-sided)
2. Sort all cards by value
3. Find the latest double-sided card whose front side value is less than a later single-sided card
4. Apply greedy approach to determine if first or second player wins based on parity of index

*/

#include <limits.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
typedef vector<int> vi;
typedef array<int, 2> ii;
typedef vector<ii> vii;
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
#define all(x) x.begin(), x.end()
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  os << "{";
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin())
      os << ", ";
    os << *it;
  }
  os << "}";
  return os;
}
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H;
  dbg_out(T...);
}
#ifdef GRANGER
#define dbg(...)                                                               \
  cerr << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):",             \
      dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef GRANGER
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("debug.txt", "w", stderr);
  auto start = chrono::high_resolution_clock::now();
#endif
  ll t = 1;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vii a(n + m); // Array to hold all cards: [front_value, back_value or INT_MAX]
    rep(i, 0, n) { 
      cin >> a[i][0]; // Read front side of double-sided card
    }
    rep(i, 0, n) { 
      cin >> a[i][1]; // Read back side of double-sided card
    }
    rep(i, 0, m) {
      cin >> a[n + i][0]; // Read front side of single-sided card
      a[n + i][1] = INT_MAX; // Mark as single-sided by setting back to INT_MAX
    }
    sort(all(a), [](const ii &x, const ii &y) { return x[0] < y[0]; }); // Sort all cards by front value
    int pos = -1;
    // Find the rightmost double-sided card (where back is not INT_MAX)
    for (int i = n + m - 1; i >= 0; i--) {
      if (a[i][1] != INT_MAX) {
        pos = i;
        break;
      }
    }
    dbg(pos, a[pos][0], a[pos][1]);
    int j = pos - 1;
    // Move backwards through cards to find optimal card with lower boundary
    while (j >= 0) {
      if (a[j][1] != INT_MAX && a[pos][0] > a[j][1]) { // Check if we can improve our position
        pos = j;
      }
      j--;
    }
    dbg(pos, a[pos][0], a[pos][1]);
    // Determine winner based on index parity (even means first player wins)
    cout << (pos % 2 ? "Second" : "First") << endl;
  }
#ifdef GRANGER
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed = end - start;
  cerr << "Time taken: " << elapsed.count() << " seconds\n";
#endif
}


// https://github.com/VaHiX/codeForces/