// Problem: CF 2044 D - Harder Problem
// https://codeforces.com/contest/2044/problem/D

/*
Purpose: Construct an array b such that for each prefix of a, the element a[i] is a mode of the prefix b[0...i].
         A mode is the most frequently occurring element in a sequence.
         The algorithm ensures b[i] is chosen to maintain a[i] as a mode of the prefix.

Algorithms/Techniques: 
    - Greedy approach to assign values to b[i]
    - Tracking which elements have been used in current prefix using boolean arrays mp1 and mp2
    - If a[i] has not been seen in the current prefix, assign it to b[i]
    - Otherwise, find the smallest unused element up to n to assign to b[i]

Time Complexity: O(n) amortized over all test cases, since each element is visited at most twice (once for mp1, once for mp2)
Space Complexity: O(n) for storing the boolean arrays and input vector
*/
#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
#define FAST_IO                                                                \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FOR_REV(i, a, b) for (int i = (a); i >= (b); --i)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (int)(x).size()
#define debug(x) cerr << #x << " = " << (x) << endl;
#define debug_binary(x) cerr << #x << " = " << bitset<32>(x) << endl;
#define debug_loop(i, n, x)                                                    \
  for (int i = 0; i < n; i++)                                                  \
    cerr << #x << "[" << i << "] = " << (x[i]) << endl;
#define DEBUG_BLOCK(code) code
#define START_TIMER auto start = chrono::high_resolution_clock::now();
#define END_TIMER                                                              \
  cerr << "Elapsed Time: "                                                     \
       << chrono::duration_cast<chrono::milliseconds>(                         \
              chrono::high_resolution_clock::now() - start)                    \
              .count()                                                         \
       << " ms" << endl;
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  os << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin())
      os << ", ";
    os << *it;
  }
  return os << "]";
}
template <typename T> ostream &operator<<(ostream &os, const set<T> &s) {
  os << "{";
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (it != s.begin())
      os << ", ";
    os << *it;
  }
  return os << "}";
}
template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
  os << "{";
  for (auto it = m.begin(); it != m.end(); ++it) {
    if (it != m.begin())
      os << ", ";
    os << it->first << ": " << it->second;
  }
  return os << "}";
}
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<bool> mp1(n + 1, false); // Tracks whether an element exists in the input array
  vector<bool> mp2(n + 1, false); // Tracks whether an element has been used in output so far
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    mp1[a[i]] = true; // Mark element as present in input
  }
  int j = 1;
  for (int i = 0; i < n; i++) {
    if (!mp2[a[i]]) {
      mp2[a[i]] = true; // Mark that we've used the element a[i] in output
      cout << a[i] << " "; // Output the same value from input
    } else {
      // Find the first unused element from 1 to n
      while (mp1[j])
        j++;
      cout << (j++) << " "; // Output the smallest unused element and increment j
    }
  }
  cout << "\n";
}
int32_t main() {
  FAST_IO
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/