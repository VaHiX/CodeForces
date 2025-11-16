// Problem: CF 1934 C - Find a Mine
// https://codeforces.com/contest/1934/problem/C

/*
Algorithm/Technique: Binary search and geometric analysis on Manhattan distance
Time Complexity: O(1) per test case (constant number of queries)
Space Complexity: O(1) (only using a constant amount of extra space)

This solution uses a systematic approach to find one of the two mines on a grid:
1. First query the top-left corner (1,1) to get the minimum distance to either mine
2. Based on that result, strategically query points along the "diagonal" where mines could be located
3. Use a binary search-like approach to narrow down the location of one mine
4. The algorithm carefully handles edge cases where mines might be located near grid boundaries

The strategy relies on the key insight that if you know the minimum Manhattan distance from a point to the two mines, 
you can infer information about the location of mines relative to that point.
*/

#include <stddef.h>
#include <stdint.h>
#include <iostream>

#define int long long
#define ld long double
#define fast_io                                                                \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define peek(v)                                                                \
  for (auto x : v)                                                             \
    cout << x << " ";                                                          \
  cout << "\n";
#define dpeek(v)                                                               \
  for (vector<int> i : v) {                                                    \
    for (int j : i) {                                                          \
      cout << j << " ";                                                        \
    }                                                                          \
    cout << "\n";                                                              \
  }
using namespace std;
int32_t main() {
  fast_io;
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    cout << "? " << 1 << " " << 1 << "\n";
    cout.flush();
    int q1;
    cin >> q1;
    if (q1 == 0) {
      cout << "! " << 1 << " " << 1 << "\n";
      cout.flush();
      continue;
    }
    if (n >= q1 + 1) {
      cout << "? " << q1 + 1 << " " << 1 << "\n";
      cout.flush();
      int q2;
      cin >> q2;
      if (q2 == 0) {
        cout << "! " << q1 + 1 << " " << 1 << "\n";
        cout.flush();
        continue;
      }
      cout << "? " << q1 + 1 - q2 / 2 << " " << 1 + q2 / 2 << "\n";
      cout.flush();
      int q3;
      cin >> q3;
      if (q3 == 0) {
        cout << "! " << q1 + 1 - q2 / 2 << " " << 1 + q2 / 2 << "\n";
        cout.flush();
        continue;
      }
    } else {
      int x1 = n;
      int y1 = (q1 + 1 - n + 1);
      cout << "? " << x1 << " " << y1 << "\n";
      cout.flush();
      int q2;
      cin >> q2;
      if (q2 == 0) {
        cout << "! " << x1 << " " << y1 << "\n";
        cout.flush();
        continue;
      }
      cout << "? " << x1 - q2 / 2 << " " << y1 + q2 / 2 << "\n";
      cout.flush();
      int q3;
      cin >> q3;
      if (q3 == 0) {
        cout << "! " << x1 - q2 / 2 << " " << y1 + q2 / 2 << "\n";
        cout.flush();
        continue;
      }
    }
    if (m >= 1 + q1) {
      cout << "? " << 1 << " " << 1 + q1 << "\n";
      cout.flush();
      int q4;
      cin >> q4;
      if (q4 == 0) {
        cout << "! " << 1 << " " << 1 + q1 << "\n";
        cout.flush();
        continue;
      } else {
        cout << "! " << 1 + q4 / 2 << " " << 1 + q1 - q4 / 2 << "\n";
        cout.flush();
        continue;
      }
    } else {
      int x2 = (q1 + 1 - m + 1);
      int y2 = m;
      cout << "? " << x2 << " " << y2 << "\n";
      cout.flush();
      int q4;
      cin >> q4;
      if (q4 == 0) {
        cout << "! " << x2 << " " << y2 << "\n";
        cout.flush();
        continue;
      } else {
        cout << "! " << x2 + q4 / 2 << " " << y2 - q4 / 2 << "\n";
        cout.flush();
        continue;
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/