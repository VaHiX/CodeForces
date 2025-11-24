// Problem: CF 1883 D - In Love
// https://codeforces.com/contest/1883/problem/D

/*
Purpose: This code solves the problem of determining whether there exists a pair of non-intersecting segments in a multiset after each add or remove operation.

Algorithms/Techniques: 
- Use of two multisets to maintain segments:
  * One multiset stores segments as (start, end) pairs.
  * Another multiset stores segments as (end, start) pairs to easily access the maximum end value and minimum start value.
- For checking non-intersection:
  * The maximum end value in the first multiset and the minimum start value in the second multiset are compared.
  * If max_end < min_start, then there exists a non-intersecting pair.
- Time Complexity: O(q * log q) where q is the number of operations, due to multiset operations (insert/delete/search).
- Space Complexity: O(q) for storing all segments in the multiset.

*/
#include <iostream>
#include <set>
#include <utility>

using namespace std;
typedef long long ll;

void solve() {
  int q;
  cin >> q;
  // m1 stores segments as (start, end)
  multiset<pair<int, int>> m1;
  // m2 stores segments as (end, start) to allow efficient min start retrieval
  multiset<pair<int, int>> m2;
  int count = 0;
  for (int i = 0; i < q; i++) {
    char c;
    int a;
    int b;
    cin >> c >> a >> b;
    if (c == '+') {
      m1.insert({a, b});
      m2.insert({b, a});
      count++;
    } else {
      auto itr = m1.find({a, b});
      m1.erase(itr);
      itr = m2.find({b, a});
      m2.erase(itr);
      count--;
    }
    if (count == 0)
      cout << "NO\n";
    else {
      // Get the segment with maximum end (last in m1)
      auto tmp = m1.end();
      tmp--;
      auto p1 = *(tmp);
      // Get the segment with minimum start (first in m2)
      auto p2 = *(m2.begin());
      // If max end < min start, segments don't intersect
      if (p1.first > p2.first)
        cout << "YES\n";
      else
        cout << "NO\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/